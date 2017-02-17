#ifndef LED_h_
#define LED_h_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#define LED_COUNT 8
#define LED_PHYSICAL_COUNT (LED_COUNT*3)
// BT + FX
#define LED_VIRTUAL_COUNT 6
#define LED_TOTAL_COUNT (LED_PHYSICAL_COUNT + LED_VIRTUAL_COUNT)
// Internally how many brightness levels you can use - for higher res fades
#define BRIGHTNESS_LEVELS    128
#define BRIGHTNESS_MAX       (BRIGHTNESS_LEVELS-1)
// How many are actually PWM'd, because the chip isn't that quick
// MUST be a multiple of BRIGHTNESS_LEVELS
#define BRIGHTNESS_DOWNSCALE 128

typedef struct {
    uint8_t r, g, b;
} RGB_t;

// Arranged left to right, top to bottom
// LED order is BGR...BGR
extern uint8_t leds[LED_PHYSICAL_COUNT];

// Maps BT/FX keys to their associated LED
// Order is BT-1-4, FX-L, FX-R
static const uint8_t ledMap[] = {2, 0, 1, 3, 6, 7};

// map LEDs to run in a circle
static const PROGMEM uint8_t ledCircleMap[]      = {0, 2, 4, 6, 7, 5, 3, 1};
static const PROGMEM uint8_t ledLeftCircleMap[]  = {0, 2, 4, 6};
static const PROGMEM uint8_t ledRightCircleMap[] = {7, 5, 3, 1};

void led_init(void);
void led_commit(void);
void led_set(uint8_t num, uint8_t r, uint8_t g, uint8_t b);
void led_fade_over(uint8_t num, uint8_t r, uint8_t g, uint8_t b, uint8_t strength);
void led_fade_all(uint8_t r, uint8_t g, uint8_t b, uint8_t strength);
void led_set_all(uint8_t r, uint8_t g, uint8_t b);
void led_set_indiv(uint8_t num, uint8_t val);

void led_set_rgb(uint8_t num, RGB_t* colour);
void led_fade_over_rgb(uint8_t num, RGB_t* colour, uint8_t strength);
void led_fade_all_rgb(RGB_t* colour, uint8_t strength);
void led_set_all_rgb(RGB_t* colour);


// http://electronics.stackexchange.com/a/11100/95969
PROGMEM const static uint8_t ledLogCurve[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
    0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B,
    0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0F, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2B, 0x2C,
    0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x43, 0x45, 0x47, 0x4A, 0x4C, 0x4F,
    0x51, 0x54, 0x57, 0x59, 0x5C, 0x5F, 0x62, 0x64, 0x67, 0x6A, 0x6D, 0x70, 0x73, 0x76, 0x79, 0x7C,
    0x7F, 0x82, 0x85, 0x88, 0x8B, 0x8E, 0x91, 0x94, 0x97, 0x9A, 0x9C, 0x9F, 0xA2, 0xA5, 0xA7, 0xAA,
    0xAD, 0xAF, 0xB2, 0xB4, 0xB7, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
    0xD0, 0xD2, 0xD3, 0xD5, 0xD7, 0xD8, 0xDA, 0xDB, 0xDD, 0xDE, 0xDF, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
    0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xED, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2,
    0xF2, 0xF3, 0xF3, 0xF4, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF8,
    0xF9, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
    0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF};

#endif
