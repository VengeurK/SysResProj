#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "printing.h"
#include "io.h"
#include "gdt.h"

void kmain() {
	terminal_initialize();
	unsigned char key = 0;
        kprintf("Init\n");
        //asm("cli"); // Clear interrupts
        //init_descriptor(); // trying to init GDT..
        //launch();
	while(true) {
		unsigned char cur = inportb(0x60);
		if(cur != key) {
			key = cur;
			if(key == 128 + 82) init_gdt();
			if(key >= 128) {
				putchar('R');
				putint(key - 128);
			} else {
				putchar('P');
				putint(key);
			}
			putchar(' ');
		}
	}
}


