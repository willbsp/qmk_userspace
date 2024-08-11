/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "keycodes.h"
#include "oled_driver.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

#define LAYER_BASE 0
#define LAYER_NAVIGATION 1
#define LAYER_MOUSE 2
#define LAYER_MEDIA 3
#define LAYER_NUMBER 4
#define LAYER_SYMBOL 5
#define LAYER_FUNCTION 6
#define LAYER_GAME 7

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[LAYER_BASE] = LAYOUT_split_3x6_3(
        KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TG(7),
        QK_LEAD, MT(MOD_LALT,KC_A), MT(MOD_LGUI,KC_S), MT(MOD_LCTL,KC_D), MT(MOD_LSFT,KC_F), KC_G, KC_H, MT(MOD_LSFT | MOD_RSFT,KC_J), MT(MOD_LCTL | MOD_RCTL,KC_K), MT(MOD_LGUI,KC_L), MT(MOD_LALT | MOD_RALT,KC_SCLN), KC_NO,
        KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TG(4),
        LT(3,KC_ESC), LT(1,KC_SPC), LT(2,KC_TAB), LT(5,KC_ENT), LT(4,KC_BSPC), LT(6,KC_DEL)
    ),
	[LAYER_NAVIGATION] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_CAPS, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_PGDN, KC_PGUP, KC_HOME, KC_END, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_ENT, KC_BSPC, KC_DEL
    ),
	[LAYER_MOUSE] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_NO, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2
    ),
	[LAYER_MEDIA] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_VAD, RGB_VAI, RGB_MOD, RGB_TOG, KC_NO,
        KC_NO, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_MSTP, KC_MPLY, KC_MUTE
    ),
	[LAYER_NUMBER] = LAYOUT_split_3x6_3(
        KC_NO, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_QUOT, KC_4, KC_5, KC_6, KC_EQL, KC_NO, KC_RSFT, KC_RCTL, KC_RGUI, KC_RALT, KC_NO,
        KC_NO, KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(4),
        KC_DOT, KC_0, KC_MINS, KC_ENT, KC_BSPC, KC_DEL
    ),
	[LAYER_SYMBOL] = LAYOUT_split_3x6_3(
        KC_NO, S(KC_LBRC), S(KC_7), S(KC_8), S(KC_9), S(KC_RBRC), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, S(KC_QUOT), S(KC_4), S(KC_5), S(KC_6), S(KC_EQL), KC_NO, KC_RSFT, KC_RCTL, KC_RGUI, KC_RALT, KC_NO, KC_NO, S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_BSLS), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        S(KC_9), S(KC_0), S(KC_MINS), KC_ENT, KC_BSPC, KC_DEL
    ),
	[LAYER_FUNCTION] = LAYOUT_split_3x6_3(
        KC_NO, KC_F12, KC_F7, KC_F8, KC_F9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F11, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_RSFT, KC_RCTL, KC_RGUI, KC_RALT, KC_NO,
        KC_NO, KC_F10, KC_F1, KC_F2, KC_F3, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO
    ),
	[LAYER_GAME] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TG(7),
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LALT, KC_SPC, KC_TAB, KC_ENT, KC_BSPC, KC_DEL
    ),
};
// clang-format on

enum which_key_page {
    BASE,
    GIT,
    NIX,
    SEARCH,
};

os_variant_t        os_detection = OS_UNSURE;
enum which_key_page macro_page   = BASE;

#ifdef LEADER_ENABLE

bool leader_add_user() {
    if (leader_sequence_one_key(KC_G)) {
        macro_page = GIT;
    } else if (leader_sequence_one_key(KC_N)) {
        macro_page = NIX;
    } else if (leader_sequence_one_key(KC_S)) {
        macro_page = SEARCH;
    }
    // git macros
    else if (leader_sequence_two_keys(KC_G, KC_C)) {
        SEND_STRING("git commit -m ");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_K)) {
        SEND_STRING("git push");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_J)) {
        SEND_STRING("git pull");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_L)) {
        SEND_STRING("git log");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_D)) {
        SEND_STRING("git diff");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_S)) {
        SEND_STRING("git status");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_A)) {
        SEND_STRING("git add ");
        return true;
    } else if (leader_sequence_two_keys(KC_G, KC_C)) {
        SEND_STRING("git clone ");
        return true;
    }
    // nixos macros
    else if (leader_sequence_two_keys(KC_N, KC_S)) {
        SEND_STRING("sudo nixos-rebuild switch");
        return true;
    }
    // search macros
    else if (leader_sequence_two_keys(KC_S, KC_R)) {
        SEND_STRING("site:reddit.com");
        return true;
    }
    return false; // leader did not conclude here
}

void leader_end_user() {
    macro_page = BASE;
}

#    ifdef OLED_ENABLE
static void oled_render_which_key(void) {
    switch (macro_page) {
        case BASE:
            oled_write_ln_P(PSTR("    --- Leader ---"), false);
            oled_write_ln_P(PSTR("(G)it (N)ix (S)earch"), false);
            break;
        case GIT:
            oled_write_ln_P(PSTR("(C)ommit (C)lone"), false);
            oled_write_ln_P(PSTR("Pull(J) Push(K)"), false);
            oled_write_ln_P(PSTR("(A)dd (D)iff"), false);
            oled_write_ln_P(PSTR("(L)og (S)tatus"), false);
            break;
        case NIX:
            oled_write_ln_P(PSTR("(S)witch"), false);
            break;
        case SEARCH:
            oled_write_ln_P(PSTR("(R)eddit"), false);
            break;
    }
}
#    endif // OLED_ENABLE
#endif     // LEADER_ENABLE

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
    os_detection = detected_os;
    return true;
}
#    ifdef OLED_ENABLE
static void oled_render_detected_os(os_variant_t detected_os) {
    oled_write_P(PSTR("Detected OS: "), false);
    switch (detected_os) {
        case OS_MACOS:
            oled_write_ln(PSTR("MacOS"), false);
            break;
        case OS_LINUX:
            oled_write_ln(PSTR("Linux"), false);
            break;
        case OS_WINDOWS:
            oled_write_ln(PSTR("Windows"), false);
            break;
        case OS_IOS:
            oled_write_ln(PSTR("iOS"), false);
            break;
        case OS_UNSURE:
            oled_write_ln(PSTR("Unknown"), false);
            break;
    }
}
#    endif // OLED_ENABLE
#endif     // OS_DETECTION_ENABLE

#ifdef WPM_ENABLE
#    ifdef OLED_ENABLE
static void oled_render_wpm(void) {
    uint8_t wpm = get_current_wpm();
    oled_write_P(PSTR("WPM: "), false);
    char buf[sizeof(wpm) * 4 + 1];
    sprintf(buf, "%d", wpm);
    oled_write_ln(PSTR(buf), false);
}
#    endif // OLED_ENABLE
#endif     // WPM_ENABLE

#ifdef OLED_ENABLE
static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case LAYER_BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case LAYER_NAVIGATION:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case LAYER_MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case LAYER_MEDIA:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case LAYER_NUMBER:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case LAYER_SYMBOL:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case LAYER_FUNCTION:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case LAYER_GAME:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

__attribute__((weak)) void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_clear();
#    ifdef LEADER_ENABLE
        if (!leader_sequence_active()) {
#    endif // LEADER_ENABLE
            oled_render_layer_state();
#    ifdef WPM_ENABLE
            oled_render_wpm();
#    endif
#    ifdef OS_DETECTION_ENABLE
            oled_render_detected_os(os_detection);
#    endif
#    ifdef LEADER_ENABLE
        } else {
            oled_render_which_key();
        }
#    endif // LEADER_ENABLE

    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
