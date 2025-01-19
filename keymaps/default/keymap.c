/* Copyright 2023 Brian Low
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "gpio.h"
#include "qp.h"
#include "qp_comms.h"
#include "generated/minecraft_standard.qff.h"
#include <math.h>

enum layer_names { LAYER_0, LAYER_1, LAYER_2, LAYER_3 };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
*         c5     c4     c3     c2     c1     c0
*     ,-----------------------------------------.                    ,-----------------------------------------.
* r0  |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
*     |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* r1  | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
*     |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* r2  | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
*     |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
* r3  |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
*     `-----------------------------------------/       /     \      \-----------------------------------------'
* r4             | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
*                |      |      |      |      |/       /         \      \ |      |      |      |      |
*                `----------------------------------'           '------''---------------------------'
*/

    // encoder buttons are mapped to c5/r4 but are moved up one row for better visualization

    [LAYER_0] = LAYOUT(
       KC_GRV,   KC_1,    KC_2,        KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,        KC_8,            KC_9,    KC_0,     KC_GRV,
       KC_ESC,   KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,        KC_I,            KC_O,    KC_P,     KC_BSPC,
       KC_TAB,   KC_A,    KC_S,        KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,        KC_K,            KC_L,    KC_SCLN,  KC_QUOT,
       KC_LSFT,  KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,  KC_N,    KC_M,        KC_COMM,         KC_DOT,  KC_SLSH,  KC_RSFT,
                          KC_LCTL, MO(LAYER_1), KC_LGUI, KC_LALT, KC_ENT,    KC_SPC,   KC_RALT, MO(LAYER_3), MO(LAYER_2),     KC_RCTL
    ),

    [LAYER_1] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______
    ),

    [LAYER_2] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______
    ),

    [LAYER_3] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
                         _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______
    ),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_0] ={ ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LAYER_1] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    [LAYER_2] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    [LAYER_3] ={ ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif


painter_device_t display;
void keyboard_pre_init_user(void) {
    // enable power led on the ProMicro RP2040
    gpio_set_pin_output(17);
    gpio_write_pin_high(17);

    display = qp_sh1106_make_i2c_device(OLED_HEIGHT,OLED_WIDTH, 0x3C); // width and height are swapped before rotation
    qp_init(display, QP_ROTATION_90);
    qp_clear(display);
}

static painter_font_handle_t mcs_font;
void keyboard_post_init_kb(void) {
    mcs_font = qp_load_font_mem(font_minecraft_standard);
}

void housekeeping_task_user(void) {
    static uint32_t last_draw     = 0;
    static uint32_t frame_counter = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        qp_rect(display, 0, 0, 32, 16, 0, 0, 0, true);
        for (uint8_t i = 0; i < OLED_WIDTH; i++) {
            qp_setpixel(display, i, sin((i + frame_counter++) / 5.0) * 8 + 8, 255, 255, 255);
        }
        qp_drawtext(display, 0, OLED_HEIGHT - font_minecraft_height * 2, mcs_font, "Sofle");
        qp_drawtext(display, 0, OLED_HEIGHT - font_minecraft_height, mcs_font, "Choc");
        qp_flush(display);
    }
}
