#ifndef RANDOM_H
#define RANDOM_H

void init_twister(void);
void sgenrand(unsigned long int rng_num, unsigned long seed);
unsigned long genrand(unsigned long int rng_num);

#endif /* RANDOM_H */

