#ifndef CHANNEL_H
#define CHANNEL_H
#include "int.h"
#include "kernel.h"
#include <stddef.h>
#include "error.h"

#define CHANNEL_SIZE 512
#define NB_MAX_CHANNELS 128

typedef struct {
    u8 *data;
    size_t size;
    size_t len;
    size_t read;
    size_t write;
    pid_t sender;
    pid_t receiver;
    int nb_users;
} channel_t;

int new_channel(channel_state_t *channels);
ssize_t send(state *s);
ssize_t receive(state *s);
int free_channel(state *s, int chanid, channel_state_t *channels);
ssize_t wait_channel(state *s);
channel_t channels_table[NB_MAX_CHANNELS];

#endif /* CHANNEL_H */

