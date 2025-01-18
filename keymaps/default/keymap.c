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
*                | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
*                |      |      |      |      |/       /         \      \ |      |      |      |      |
*                `----------------------------------'           '------''---------------------------'
    */

    // encoder buttons are mapped to col5/row3 but are moved up one row for better visualization

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


#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}
#endif


void keyboard_pre_init_user(void) {
    gpio_set_pin_output(17);
    gpio_write_pin_high(17);
}
