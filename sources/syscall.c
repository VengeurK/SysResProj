#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "printing.h"
#include "kernel.h"


/* This file contains all the syscalls seen from the user side.
   This means that the user is supposed to ahave access to it. */

// TODO Determiner si il faut sauver les registres avant de mettre les args.

pid_t kfork(priority prio) {
    kprintf("Requested a fork, with priority %d\n", prio);
    pid_t child;
    int ret_value;
    
    asm volatile("\
        movl $3, %%eax \n \
        movl %2, %%ebx \n \
        int $0x80 \n \
        movl %%eax, %0 \n \
        movl %%ebx, %1"
        : "=m" (ret_value), "=m" (child)
        : "m" (prio)
        : "%ebx", "esi", "edi"
        );
    
    kprintf("Fork returned with code %d, and child %d \n", ret_value, child);
    if (!ret_value)
        return -1;

    return child;
}

pid_t kwait(int *status) {
    int ret_value, exit_value;
    pid_t child;
    
    asm volatile("\
        movl $5, %%eax \n \
        int $0x80 \n \
        movl %%eax, %0 \n \
        movl %%ebx, %1 \n \
        movl %%ecx, %2"
        : "=m" (ret_value), "=m" (child), "=m" (exit_value)
        :
        : "%ebx", "esi", "edi"
        );

    if (ret_value) {
        // A Zombie child has been found.        
        *status = exit_value;
        return child;
    }
    else {
        // No child found.
        return -1;
    }
}

void kexit(int status) {
    asm volatile("\
        movl $4, %%eax \n \
        movl %0, %%ebx \n \
        int $0x80"
        :
        : "m" (status)
        : "%ebx", "esi", "edi"
        );
    
    // This syscall should never return.
    kprintf("WARNING : Returned after exit. Trying again.\n");
    //kexit(status);
}

// Utilisera-t-on des file descriptors ? TODO
int ksend(chanid channel, int msg) {
    int ret_value;
    
    asm volatile("\
        movl $1, %%eax \n \
        movl %1, %%ebx \n \
        movl %2, %%ecx \n \
        int $0x80 \n \
        movl %%eax, %0 \n"
        : "=m" (ret_value)
        : "m" (channel), "m" (msg)
        : "%ebx", "esi", "edi"
        );
    
    if (ret_value) {
        return 0;
    }
    else {
        // No such channel or already occupied.
        return -1;  
    }
}

int kreceive(chanid channel[4], int *dest) {    
    int ret_value, res;
    chanid chan;
    
    asm volatile("\
        movl %3, %%ebx \n \
        movl %4, %%ecx \n \
        movl %5, %%edx \n \
        movl %6, %%esi \n \
        movl $2, %%eax \n \
        int $0x80 \n \
        movl %%eax, %0 \n \
        movl %%ebx, %1 \n \
        movl %%ecx, %2 \n"
        : "=m" (ret_value), "=m" (chan), "=m" (res)
        : "m" (channel[0]), "m" (channel[1]), "m" (channel[2]), "m" (channel[3])
        : "%ebx", "esi", "edi"
        );
    kprintf("Bonjour, je reviens de receive ! \n");
   
    if (ret_value) {   
        //TODO On ignore le channel choisi ici ?
        *dest = res;
        return 0;
    }
    else {
        // No valid channel
        return -1;
    }
}

chanid knew_channel() {
    chanid chan;
    asm volatile("\
                movl $0, %%eax \n \
                int $0x80 \n \
                movl %%eax, %0"
                : "=m" (chan)
                :
                : "%ebx", "esi", "edi");
    return chan;
}

void new_launch() {
    kprintf("Initial state\n");
    chanid channels[4];
    // A priori superflu
    registers_t regs;
    state* s = picoinit(&regs);
    log_state(s);

    kprintf("Forking init\n");
    pid_t init = kfork(MAX_PRIORITY);
    kprintf("We have a new process : %d\n", init);
    log_state(s);

    kprintf("Asking for a new channel, in r4\n");
    chanid chan1 = knew_channel();
    kprintf("Channel obtenu : %d\n", chan1);
    log_state(s);
    
    kprintf("Making init wait for a message on the channel\n");
    kprintf("This should switch to the child process since init is BlockedReading\n");
    
    channels[0] = chan1;
    channels[1] = -1;
    channels[2] = -1;
    channels[3] = -1;
    int res;
    kprintf("J'ai demande %d \n", chan1);
    kreceive(channels, &res);
    log_state(s);

    kprintf("Getting a new channel in r3\n");
    //s->registers->eax = 0;
    //picotransition(s, SYSCALL);
    //s->registers->edx = s->registers->eax;
    chanid chan2 = knew_channel();
    log_state(s);

    kprintf("What about having a child of our own?\n");
    //s->registers->eax = 3;
    //s->registers->ebx = MAX_PRIORITY - 1;
    //picotransition(s, SYSCALL);
    pid_t child2 = kfork(MAX_PRIORITY - 1);
    log_state(s);

    kprintf("Let's wait for him to die!\n");
    //s->registers->eax = 5;
    //picotransition(s, SYSCALL);
    int status;
    int res_wait = kwait(&status);
    log_state(s);

    kprintf("On with the grandchild, which'll send on channel r3\n");
    //s->registers->eax = 1;
    //s->registers->ebx = s->registers->edx;
    //s->registers->ecx = -12;
    //picotransition(s, SYSCALL);
    int res_send = ksend(chan2, -12);
    log_state(s);

    kprintf("On with idle, to listen to the grandchild!\n");
    //s->registers->eax = 2;
    //s->registers->ebx = 1; // Little hack, not supposed to know it's gonna be channel one
    //s->registers->ecx = -1;
    //s->registers->edx = -1;
    //s->registers->esi = -1;
    //picotransition(s, SYSCALL);
    channels[0] = 1;
    int dest2;
    int res_recv = kreceive(channels, &dest2);
    log_state(s);

    kprintf("Letting the timer tick until we're back to the grandchild\n");
    for (int i = MAX_TIME_SLICES; i >= 0; i--) {
        picotransition(s, TIMER);
    }
    log_state(s);

    kprintf("Hara-kiri\n");
    //s->registers->eax = 4;
    //s->registers->ebx = 125;
    //picotransition(s, SYSCALL);
    kexit(125);
    log_state(s);

    kprintf("Let's speak to dad!\n");
    //s->registers->eax = 1;
    //s->registers->ebx = s->registers->esi;
    //s->registers->ecx = 42;
    //picotransition(s, SYSCALL);
    ksend(chan1, 42);
    log_state(s);

    kprintf("Our job is done, back to dad! (see 42 in r2?)\n");
    //s->registers->eax = 4;
    //s->registers->ebx = 12; // Return value
    //picotransition(s, SYSCALL);
    kexit(12);
    log_state(s);

    kprintf("Let's loot the body of our child (see 12 in r2?)\n");
    //s->registers->eax = 5;
    //spicotransition(s, SYSCALL);

    kwait(&status);
    log_state(s);
}