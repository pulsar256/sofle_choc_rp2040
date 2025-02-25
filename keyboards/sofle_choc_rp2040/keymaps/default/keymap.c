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

#include "generated/minecraft_standard.qff.h"
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

    [LAYER_1] = LAYOUT(
       _______, _______, _______, _______, _______,  _______,                       _______, _______, _______, KC_MINUS, KC_EQUAL,     KC_PAGE_UP,
       _______, _______, KC_HOME, KC_UP,   KC_END,   _______,                       _______, KC_HOME, KC_UP,   KC_END,   _______,      KC_PAGE_DOWN,
       _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                       _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BACKSLASH, _______,
       _______, _______, _______, _______, _______,  _______, _______,    _______,  _______, _______, _______, _______,  _______,      _______,
                         _______, _______, _______,  _______, _______,    _______,  _______, _______, _______, _______
    ),

    [LAYER_2] = LAYOUT(
       KC_F1,   KC_F2,                 KC_F3,                  KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
       _______, KC_LEFT_BRACKET,       KC_RIGHT_BRACKET,       _______, _______, _______,                       _______, KC_VOLD, KC_MSTP, KC_VOLU, _______, KC_PAUSE,
       _______, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), _______, _______, _______,                       _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_PRINT_SCREEN,
       _______, _______,               _______,                _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
                                       _______,                _______, _______, _______, _______,    _______,  _______, _______, _______, _______
    ),

    [LAYER_3] = LAYOUT(
        _______, _______, _______,    _______,    _______,    _______,                       _______,         _______,               _______,                KC_MINUS,         KC_EQUAL,     KC_PAGE_UP,
        _______, _______, _______,    _______,    _______,    _______,                       _______,         KC_HOME,               KC_UP,                  KC_END,           _______,      KC_PAGE_DOWN,
        _______, _______, _______,    _______,    _______,    _______,                       _______,         KC_LEFT,               KC_DOWN ,               KC_RIGHT,         KC_BACKSLASH, _______,
        _______, _______, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,     _______, KC_LEFT_BRACKET, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), KC_RIGHT_BRACKET, _______,      _______,
                          _______,    _______,    _______,    _______, _______,     _______, _______,         _______,               _______,                _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_0] ={ ENCODER_CCW_CW(KC_VOLD, KC_VOLU),       ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LAYER_1] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),      ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [LAYER_2] ={ ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),      ENCODER_CCW_CW(KC_UP, KC_DOWN)   },
    [LAYER_3] ={ ENCODER_CCW_CW(LCTL(KC_Z), RCS(KC_Z)),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED) {
                uint16_t layer0_keycode = keymap_key_to_keycode(0, (keypos_t){col, row});

                switch (layer0_keycode) {
                    case MO(LAYER_1):
                        rgb_matrix_set_color(index, RGB_RED);
                        break;
                    case MO(LAYER_2):
                        rgb_matrix_set_color(index, RGB_GREEN);
                        break;
                    case MO(LAYER_3):
                        rgb_matrix_set_color(index, RGB_BLUE);
                        break;
                    case KC_F:
                        rgb_matrix_set_color(index, RGB_YELLOW);
                        break;
                    case KC_J:
                        rgb_matrix_set_color(index, RGB_YELLOW);
                        break;
                    case KC_LGUI:
                        rgb_matrix_set_color(index, RGB_YELLOW);
                        break;
                }

                if (get_highest_layer(layer_state) > 0 && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                    switch (layer) {
                        case 1:
                            rgb_matrix_set_color(index, RGB_RED);
                            break;
                        case 2:
                            rgb_matrix_set_color(index, RGB_GREEN);
                            break;
                        case 3:
                            rgb_matrix_set_color(index, RGB_BLUE);
                            break;
                    }
                }
            }
        }
    }
    return true;
}

static painter_device_t      display;
static painter_font_handle_t mcs_font;
static deferred_token        display_task_token;
static char                  strbuffer[32];
static uint32_t              frame_counter = 0;

void draw_text_centered(const char *text, uint16_t y) {
    uint16_t width = qp_textwidth(mcs_font, text);
    qp_drawtext(display, (OLED_WIDTH - width) / 2, y, mcs_font, text);
}

uint32_t draw_frame(uint32_t trigger_time, void *cb_arg) {
    qp_rect(display, 0, 0, OLED_WIDTH, OLED_HEIGHT, 0, 0, 0, true);

    for (uint8_t i = 0; i < OLED_WIDTH; i++) {
        qp_setpixel(display, i, sin((i + frame_counter++) / 5.0) * 8 + 8, 255, 255, 255);
    }
    draw_text_centered("Sofle", 4);
    snprintf(strbuffer, 32, "Lyr: %d", get_highest_layer(layer_state));
    draw_text_centered((const char *)&strbuffer, 28);

    draw_text_centered("WPM:", 50);
    snprintf(strbuffer, 32, "%d", get_current_wpm());
    draw_text_centered((const char *)&strbuffer, 60);
    qp_flush(display);
    return 250;
}

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(17);
    gpio_write_pin_high(17);

    // i2c address usually either 0x3C or 0x3D
    display = qp_sh1106_make_i2c_device(OLED_HEIGHT, OLED_WIDTH, 0x3C); // width and height are swapped before rotation
    qp_init(display, QP_ROTATION_90);
    qp_clear(display);
    mcs_font = qp_load_font_mem(font_minecraft_standard);
}

void keyboard_post_init_kb(void) {
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    display_task_token = defer_exec(1500, draw_frame, NULL);
}

void suspend_power_down_user() {
    rgb_matrix_set_suspend_state(true);
    cancel_deferred_exec(display_task_token);
}

void suspend_wakeup_init_user() {
    rgb_matrix_set_suspend_state(false);
    display_task_token = defer_exec(1500, draw_frame, NULL);
}

void housekeeping_task_user(void) {
}
