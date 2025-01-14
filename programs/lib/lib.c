#include "lib.h"

u16 *get_screen() {
    return (u16*) 0x88000000;
}

void set_char_at(u8 c, u8 fg, u8 bg, u8 x, u8 y) {
    u16* screen = get_screen();
    screen[(x%VGA_WIDTH) + (y%VGA_HEIGHT) * VGA_WIDTH] = (bg << 0xC) + (fg << 0x8) + c;
}

void clear_screen(u8 color) {
    for(u8 y = 0; y < VGA_HEIGHT; y++)
        for(u8 x = 0; x < VGA_WIDTH; x++)
            set_char_at(' ', color, color, x , y);
}

void switch_clock() {
    u8 *clock = (u8*)CLOCK;
    *clock = !*clock;
}

void update_clock(u8 fg, u8 bg) {
    u8 *clock = (u8*)CLOCK;
    rtc_time_t t;
    if (gettimeofday(&t))
        return;
    
    for (u8 i = 0; i < 20; i++) {
        clock[2*i+2] = (bg << 4) + fg;
    }
    int x = 1;
    t.hours += 2;
    clock[x++] = '0' + t.hours / 10;
    x++;
    clock[x++] = '0' + t.hours % 10;
    x++;
    clock[x++] = ':';
    x++;
    clock[x++] = '0' + t.minutes / 10;
    x++;
    clock[x++] = '0' + t.minutes % 10;
    x++;
    clock[x++] = ':';
    x++;
    clock[x++] = '0' + t.seconds / 10;
    x++;
    clock[x++] = '0' + t.seconds % 10;
    x++;
    clock[x++] = ',';
    x++;
    clock[x++] = ' ';
    x++;
    clock[x++] = '0' + t.day / 10;
    x++;
    clock[x++] = '0' + t.day % 10;
    x++;
    clock[x++] = '/';
    x++;
    clock[x++] = '0' + t.month / 10;
    x++;
    clock[x++] = '0' + t.month % 10;
    x++;
    clock[x++] = '/';
    x++;
    clock[x++] = '2';
    x++;
    clock[x++] = '0';
    t.year = (t.year % 100);
    x++;
    clock[x++] = '0' + t.year / 10;
    x++;
    clock[x++] = '0' + t.year % 10;
}

void set_cursor(u8 x, u8 y) {
    *((u8*)CURSOR_X) = x;
    *((u8*)CURSOR_Y) = y;  
}

u32 last_rand;

u32 rand() {
    
    //last_rand = (last_rand * 16807) % (((u32) 1 << 31) -1);
    return genrand(42);
}

void lib_init() {
    init_malloc();
    memset(get_screen(), 0, VGA_HEIGHT * VGA_WIDTH * 2);
    create_channel_stream(1);
    initCharTable();
    init_error_msg();
    rtc_time_t t;
    gettimeofday(&t);
    last_rand = ((u32) 16807 * 16807 * 16807 * ((u32) t.century - (u32) t.year + (u32) t.month) +
            16807 * 16807 * ((u32)t.day - (u32)t.hours) + 
            16807 * ((u32)t.minutes + (u32)t.seconds) +  49 * (u32)t.mseconds) % (((u32) 1 << 31) - 1);
    init_twister();
    sgenrand(42, last_rand);
}

void *memcpy(void *dst, void *src, u32 n) {
    u8 *p = dst;
    while(n--)
        *(u8*)dst++ = *(u8*)src++;
    return p;
}

void memset(void *dst, u8 src, u32 len) {
    // Copy len times src from the address dst.
    while (len--) {
        *(u8*)dst++ = src;
    }
}

int strEqual(char *strA, char *strB) {
    int i = 0;
    while(strA[i] == strB[i]) {
        if(strA[i] == 0) return 1;
        i++;
    }
    return 0;
}

void strCopy(char *src, char* dest) {
    while (*src) {
        *dest ++ = *src ++;
    }
    *dest = 0;
}

u32 strlen(const char* str) {
    u32 ret = 0;
    while(str[ret] != 0)
        ret++;
    return ret;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a < b ? b : a;
}

u32 umax(u32 a, u32 b) {
    return a < b ? b : a;
}

u32 umin(u32 a, u32 b) {
    return a < b ? a : b;
}
