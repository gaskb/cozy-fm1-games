/* SPDX-License-Identifier: GPL-3.0-only */
#pragma once
#include <stdint.h>

enum {
    GAME_MENU = 0,
    GAME_SNAKE = 1,
    GAME_TETRIS = 2,
    GAME_ARKANOID = 3,
    GAME_OUTRUN = 4,
    GAME_HERO = 5,
    GAME_FROGGER = 6,
    GAME_GALAGA = 7,
    GAME_PACMAN = 8,
    GAME_DINO = 9,
    GAME_FLAPPY = 10
};

#define MASK_KEY_C   ((1u << 7)  | (1u << 19))
#define MASK_KEY_D   ((1u << 9)  | (1u << 21))
#define MASK_KEY_E   ((1u << 11) | (1u << 23))
#define MASK_KEY_F   ((1u << 12) | (1u << 24))
#define MASK_KEY_UP  ((1u << 8)  | (1u << 10) | (1u << 20) | (1u << 22))

static struct {
    uint16_t hi_snake;
    uint16_t hi_tetris;
    uint16_t hi_arkanoid;
    uint16_t hi_outrun;
    uint16_t hi_hero;
    uint16_t hi_frogger;
    uint16_t hi_galaga;
    uint16_t hi_pacman;
    uint16_t hi_dino;
    uint16_t hi_flappy;
} save_data = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

static uint32_t arcade_rng = 0x12345678u;

static uint32_t arcade_rand(void)
{
    uint32_t x = arcade_rng ^ (fm1_ms & 0xFFu);
    if (x == 0u) x = 0xCAFEBABEu;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    arcade_rng = x;
    return x;
}

static void fmt_num(char *dst, uint16_t v, uint8_t digits)
{
    int32_t i;
    for (i = (int32_t)digits - 1; i >= 0; i--) {
        dst[i] = (char)('0' + (v % 10u));
        v /= 10u;
    }
    dst[digits] = 0;
}

static void save_scores(void)
{
    settings_save(&save_data, sizeof save_data);
}

/* Light up useful buttons (except BTN_PLAY) and keyboard keys for the active screen */
static void arcade_update_leds(uint8_t game)
{
    uint32_t btn_mask = 0u;
    uint32_t key_mask = 0u;
    uint32_t i;

    if (game == GAME_MENU) {
        btn_mask = (1u << BTN_ENV) | (1u << BTN_SEL);
        key_mask = MASK_KEY_UP | MASK_KEY_D | MASK_KEY_E | MASK_KEY_F;
    } else {
        btn_mask = (1u << BTN_HOME);
        if (game == GAME_SNAKE) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP) |
                        (1u << BTN_ENV) | (1u << BTN_SEL) |
                        (1u << BTN_FX) | (1u << BTN_LFO);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_UP;
        } else if (game == GAME_TETRIS) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP) |
                        (1u << BTN_ENV) | (1u << BTN_SEL) |
                        (1u << BTN_FX) | (1u << BTN_REC);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        } else if (game == GAME_ARKANOID) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP);
            key_mask = MASK_KEY_C | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        } else if (game == GAME_OUTRUN) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP) |
                        (1u << BTN_ENV) | (1u << BTN_SEL) | (1u << BTN_FX);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        } else if (game == GAME_HERO) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP);
            /* All C..B white keys (C4..B4 and C5..E5) */
            key_mask = (1u << 7) | (1u << 9) | (1u << 11) | (1u << 12) |
                       (1u << 14) | (1u << 16) | (1u << 18) |
                       (1u << 19) | (1u << 21) | (1u << 23) | (1u << 24) | (1u << 26);
        } else if (game == GAME_FROGGER || game == GAME_PACMAN) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP) |
                        (1u << BTN_ENV) | (1u << BTN_SEL);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_UP;
        } else if (game == GAME_GALAGA) {
            btn_mask |= (1u << BTN_OCT_DOWN) | (1u << BTN_OCT_UP) | (1u << BTN_ENV);
            key_mask = MASK_KEY_C | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        } else if (game == GAME_DINO) {
            btn_mask |= (1u << BTN_ENV) | (1u << BTN_SEL);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        } else if (game == GAME_FLAPPY) {
            btn_mask |= (1u << BTN_ENV);
            key_mask = MASK_KEY_C | MASK_KEY_D | MASK_KEY_E | MASK_KEY_F | MASK_KEY_UP;
        }
    }

#ifndef FM1_NBTN
#define FM1_NBTN 14u
#endif
    for (i = 0u; i < FM1_NBTN; i++) {
        if (i == BTN_PLAY) continue;
        fm1_led_key(i, (btn_mask & (1u << i)) ? 1 : 0);
    }
    for (i = 0u; i < 27u; i++) {
        fm1_led_key(14u + i, (key_mask & (1u << i)) ? 1 : 0);
    }
}
