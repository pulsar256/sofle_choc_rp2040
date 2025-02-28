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

#include <stdint.h>
#include QMK_KEYBOARD_H
#include "gpio.h"
#include <math.h>

enum layer_names { LAYER_0, LAYER_1, LAYER_2, LAYER_3 };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*         c5     c4     c3     c2     c1     c0
*     ,-----------------------------------------.                    ,-----------------------------------------.
* r0  |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
*     |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* r1  | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Del  |
*     |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* r2  | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
*     |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
* r3  |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
*     `-----------------------------------------/       /     \      \-----------------------------------------'
* r4             | LCTL | MO1  | LCMD | LALT | /Enter  /       \Space \  | RALT |  MO3 |  MO2 | RCTL |
*                |      |      |      |      |/       /         \      \ |      |      |      |      |
*                `----------------------------------'           '------''---------------------------'
*/

    // encoder buttons are mapped to c5/r4 but are moved up one row for better visualization

    [LAYER_0] = LAYOUT(
       KC_ESC,   KC_1,    KC_2,        KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,        KC_8,            KC_9,    KC_0,     KC_BSPC,
       KC_GRV,   KC_Q,    KC_W,        KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,        KC_I,            KC_O,    KC_P,     KC_DEL,
       KC_TAB,   KC_A,    KC_S,        KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,        KC_K,            KC_L,    KC_SCLN,  KC_QUOT,
       KC_LSFT,  KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,  KC_N,    KC_M,        KC_COMM,         KC_DOT,  KC_SLSH,  KC_RSFT,
                          KC_LCTL, MO(LAYER_1), KC_LGUI, KC_LALT, KC_ENT,    KC_SPC,   KC_RALT, MO(LAYER_3), MO(LAYER_2),     KC_RCTL
    ),

    // red
    [LAYER_1] = LAYOUT(
       _______, _______, _______, _______, _______,  _______,                       _______, _______, _______, KC_MINUS, KC_EQUAL,     KC_PAGE_UP,
       _______, _______, KC_HOME, KC_UP,   KC_END,   _______,                       _______, KC_HOME, KC_UP,   KC_END,   _______,      KC_PAGE_DOWN,
       _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                       _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BACKSLASH, _______,
       _______, _______, _______, _______, _______,  _______, _______,    _______,  _______, _______, _______, _______,  _______,      _______,
                         _______, _______, _______,  _______, _______,    _______,  _______, _______, _______, _______
    ),

    // green
    [LAYER_2] = LAYOUT(
       KC_F1,   KC_F2,                 KC_F3,                  KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
       _______, KC_LEFT_BRACKET,       KC_RIGHT_BRACKET,       _______, _______, _______,                       _______, KC_VOLD, KC_MSTP, KC_VOLU, _______, KC_PAUSE,
       _______, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), _______, _______, _______,                       _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_PRINT_SCREEN,
       _______, _______,               _______,                _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
                                       _______,                _______, _______, _______, _______,    _______,  _______, _______, _______, _______
    ),

    // blue
    [LAYER_3] = LAYOUT(
        QK_RGB_MATRIX_MODE_PREVIOUS, QK_RGB_MATRIX_MODE_NEXT, QK_RGB_MATRIX_VALUE_DOWN,    QK_RGB_MATRIX_VALUE_UP,    QK_RGB_MATRIX_SPEED_DOWN,    QK_RGB_MATRIX_SPEED_UP,                       QK_RGB_MATRIX_TOGGLE,         _______,               _______,                KC_MINUS,         KC_EQUAL,     KC_PAGE_UP,
        _______, _______, _______,    _______,    _______,    _______,                       _______,         KC_HOME,               KC_UP,                  KC_END,           _______,      KC_PAGE_DOWN,
        _______, _______, _______,    _______,    _______,    _______,                       _______,         KC_LEFT,               KC_DOWN ,               KC_RIGHT,         KC_BACKSLASH, _______,
        _______, _______, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,     _______, KC_LEFT_BRACKET, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), KC_RIGHT_BRACKET, _______,      _______,
                          _______,    _______,    _______,    _______, _______,     _______, _______,         _______,               _______,                _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_0] ={ ENCODER_CCW_CW(KC_VOLD, KC_VOLU),       ENCODER_CCW_CW(QK_MOUSE_WHEEL_DOWN, QK_MOUSE_WHEEL_UP) },
    [LAYER_1] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),      ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [LAYER_2] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),      ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [LAYER_3] ={ ENCODER_CCW_CW(LCTL(KC_Z), RCS(KC_Z)),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t matrix_brigtness = rgb_matrix_get_val();

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED) {
                uint16_t layer0_keycode = keymap_key_to_keycode(0, (keypos_t){col, row});

                rgb_t red = hsv_to_rgb((hsv_t){0, 255, matrix_brigtness});
                rgb_t green = hsv_to_rgb((hsv_t){85, 255, matrix_brigtness});
                rgb_t blue = hsv_to_rgb((hsv_t){170, 255, matrix_brigtness});
                rgb_t yellow = hsv_to_rgb((hsv_t){43, 255, matrix_brigtness});

                switch (layer0_keycode) {
                    case MO(LAYER_1):
                        rgb_matrix_set_color(index, red.r, red.g, red.b);
                        break;
                    case MO(LAYER_2):
                        rgb_matrix_set_color(index, green.r, green.g, green.b);
                        break;
                    case MO(LAYER_3):
                        rgb_matrix_set_color(index, blue.r, blue.g, blue.b);
                        break;
                    case KC_F:
                    case KC_J:
                    case KC_LGUI:
                        rgb_matrix_set_color(index, yellow.r, yellow.g, yellow.b);
                        break;
                }

                if (get_highest_layer(layer_state) > 0 && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                    switch (layer) {
                        case 1:
                            rgb_matrix_set_color(index, red.r, red.g, red.b);
                            break;
                        case 2:
                            rgb_matrix_set_color(index, green.r, green.g, green.b);
                            break;
                        case 3:
                            rgb_matrix_set_color(index, blue.r, blue.g, blue.b);
                            break;
                    }
                }
            }
        }
    }
    return true;
}

bool oled_task_user(void) {
    char buffer[32];
    oled_write_P(PSTR("Lyr: \n"), false);

        switch (get_highest_layer(layer_state)) {
            case LAYER_0:
                oled_write("Def\n", false);
                break;
            case LAYER_1:
                oled_write("Red\n", false);
                break;
            case LAYER_2:
                oled_write("Green\n", false);
                break;
            case LAYER_3:
                oled_write("Blue\n", false);
                break;
            default:
                oled_write(PSTR("Undefined"), false);
        }

        oled_write("\nRGB LEDs\n",false);

        uint8_t matrix_mode = rgb_matrix_get_mode();
        oled_write("Fx: ",false);
        sprintf(buffer,"%02d\n",matrix_mode);
        oled_write(buffer,false);

        uint8_t matrix_brigtness = rgb_matrix_get_val();
        oled_write("Br: ",false);
        sprintf(buffer,"%03d\n",matrix_brigtness);
        oled_write(buffer,false);

        uint8_t matrix_speed = rgb_matrix_get_speed();
        oled_write("Spd: ",false);
        sprintf(buffer,"%03d\n",matrix_speed);
        oled_write(buffer,false);

        uint8_t wpm = get_current_wpm();
        oled_write("WPM: ",false);
        sprintf(buffer,"%03d\n",wpm);
        oled_write(buffer,false);

    return false;
}

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(17);
    gpio_write_pin_high(17);
}

void keyboard_post_init_kb(void) {
}

void suspend_power_down_user() {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user() {
    rgb_matrix_set_suspend_state(false);
}

void housekeeping_task_user(void) {
}
