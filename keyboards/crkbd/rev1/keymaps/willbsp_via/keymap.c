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
#include "host.h"
#include "keycode_config.h"
#include "keycodes.h"
#include "oled_driver.h"
#include "os_detection.h"
#include "process_dynamic_macro.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include "send_string_keycodes.h"
#include QMK_KEYBOARD_H

#define LAYER_BASE 0
#define LAYER_NAVIGATION 1
#define LAYER_MOUSE 2
#define LAYER_MEDIA 3
#define LAYER_NUMBER 4
#define LAYER_SYMBOL 5
#define LAYER_FUNCTION 6
#define LAYER_GAME 7

enum custom_keycodes {
    // os keycodes, e.g. cmd / ctrl + c
    OS_SEARCH = SAFE_RANGE,
};

enum which_key_page {
    BASE,
    GIT,
    NIX,
    SEARCH,
    WINDOW,
};

os_variant_t        os_detection    = OS_UNSURE;
enum which_key_page macro_page      = BASE;
uint8_t             macro_recording = 0;

void td_select_all_copy_on_double_tap(tap_dance_state_t *state, void *user_data) {
    bool use_cmd = os_detection == OS_MACOS || os_detection == OS_IOS;
    if (state->count == 1) {
        if (use_cmd) {
            SEND_STRING(SS_LCMD("c"));
        } else {
            SEND_STRING(SS_LCTL("c"));
        }
    } else if (state->count == 2) {
        if (use_cmd) {
            SEND_STRING(SS_LCMD("ac"));
        } else {
            SEND_STRING(SS_LCTL("ac"));
        }
    }
    reset_tap_dance(state);
}

void td_select_all_paste_on_double_tap(tap_dance_state_t *state, void *user_data) {
    bool use_cmd = os_detection == OS_MACOS || os_detection == OS_IOS;
    if (state->count == 1) {
        if (use_cmd) {
            SEND_STRING(SS_LCMD("v"));
        } else {
            SEND_STRING(SS_LCTL("v"));
        }
    } else if (state->count == 2) {
        if (use_cmd) {
            SEND_STRING(SS_LCMD("av"));
        } else {
            SEND_STRING(SS_LCTL("av"));
        }
    }
    reset_tap_dance(state);
}

void td_dynamic_macro(tap_dance_state_t *state, void *user_data) {
    keyrecord_t kr;
    if (state->count == 1) {
        kr.event.pressed = false;
        process_dynamic_macro(QK_DYNAMIC_MACRO_PLAY_1, &kr);
    } else if (state->count == 2) {
        kr.event.pressed = true;
        process_dynamic_macro(QK_DYNAMIC_MACRO_RECORD_STOP, &kr);
    } else if (state->count == 3) {
        kr.event.pressed = false;
        process_dynamic_macro(QK_DYNAMIC_MACRO_RECORD_START_1, &kr);
    }
    reset_tap_dance(state);
}

enum tap_dance_keys {
    TD_OS_COPY,
    TD_OS_PASTE,
    TD_DYN_MACRO,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_OS_COPY]   = ACTION_TAP_DANCE_FN(td_select_all_copy_on_double_tap),
    [TD_OS_PASTE]  = ACTION_TAP_DANCE_FN(td_select_all_paste_on_double_tap),
    [TD_DYN_MACRO] = ACTION_TAP_DANCE_FN(td_dynamic_macro),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 500;
        default:
            return TAPPING_TERM;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[LAYER_BASE] = LAYOUT_split_3x6_3(
        TD(TD_OS_COPY), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(TD_DYN_MACRO),
        QK_LEAD, MT(MOD_LALT,KC_A), MT(MOD_LGUI,KC_S), MT(MOD_LCTL,KC_D), MT(MOD_LSFT,KC_F), KC_G, KC_H, MT(MOD_LSFT | MOD_RSFT,KC_J), MT(MOD_LCTL | MOD_RCTL,KC_K), MT(MOD_LGUI,KC_L), MT(MOD_LALT | MOD_RALT,KC_SCLN), OS_SEARCH,
        TD(TD_OS_PASTE), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TG(7),
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
        KC_NO, KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
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

// TODO enable tap dance so 2x user_copy will select all (ctrl/cmd + a) then copy
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OS_SEARCH:
            if (record->event.pressed) {
                switch (os_detection) {
                    case OS_MACOS:
                    case OS_IOS:
                        SEND_STRING(SS_LCMD(" "));
                        break;
                    case OS_WINDOWS:
                        SEND_STRING(SS_LGUI());
                        break;
                    case OS_LINUX:
                        SEND_STRING(SS_LGUI("d"));
                        break;
                    default:
                        SEND_STRING(SS_LGUI());
                        break;
                }
            }
            break;
    }
    return true;
};

#ifdef DYNAMIC_MACRO_ENABLE
void dynamic_macro_record_start_user(int8_t direction) {
    macro_recording = direction;
}
void dynamic_macro_record_end_user(int8_t direction) {
    macro_recording = 0;
}
#    ifdef OLED_ENABLE
static void oled_render_dynamic_macro(void) {
    if (macro_recording == 1) {
        oled_write_ln_P(PSTR("Recording 1"), false);
    } else if (macro_recording == 2) {
        oled_write_ln_P(PSTR("Recording 2"), false);
    }
}
#    endif // OLED_ENABLE
#endif     // DYNAMIC_MACRO_ENABLE

#ifdef LEADER_ENABLE
bool leader_add_user() {
    if (leader_sequence_one_key(KC_G)) {
        macro_page = GIT;
    } else if (leader_sequence_one_key(KC_N)) {
        macro_page = NIX;
    } else if (leader_sequence_one_key(KC_S)) {
        macro_page = SEARCH;
    } else if (leader_sequence_one_key(KC_W)) {
        macro_page = WINDOW;
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
    } else if (leader_sequence_two_keys(KC_G, KC_O)) {
        SEND_STRING("git clone ");
        return true;
    }
    // nixos macros
    else if (leader_sequence_two_keys(KC_N, KC_S)) {
        SEND_STRING("sudo nixos-rebuild switch");
        return true;
    } else if (leader_sequence_two_keys(KC_N, KC_U)) {
        SEND_STRING("sudo nix flake update /etc/nixos");
        return true;
    }
    // search macros
    else if (leader_sequence_two_keys(KC_S, KC_R)) {
        SEND_STRING("site:reddit.com");
        return true;
    }
    // window macros
    else if (leader_sequence_two_keys(KC_W, KC_Q)) {
        switch (os_detection) {
            case OS_LINUX:
                SEND_STRING(SS_LGUI(SS_LSFT("q")));
                break;
            case OS_WINDOWS:
                SEND_STRING(SS_LALT(SS_TAP(X_F4)));
                break;
            case OS_MACOS:
                SEND_STRING(SS_LCMD("q"));
                break;
            case OS_IOS:
                SEND_STRING(SS_LCMD("m"));
                break;
            default:
                break;
        }
        return true;
    }
    return false; // leader did not conclude here
}

void leader_end_user() {
    macro_page = BASE;
}

// TODO add braces for dynamic macros

#    ifdef OLED_ENABLE
static void oled_render_which_key(void) {
    switch (macro_page) {
        case BASE:
            oled_write_ln_P(PSTR("    --- Leader ---"), false);
            oled_write_ln_P(PSTR("(G)it (N)ix (S)earch"), false);
            oled_write_ln_P(PSTR("(W)indow"), false);
            break;
        case GIT:
            oled_write_ln_P(PSTR("(C)ommit Cl(o)ne"), false);
            oled_write_ln_P(PSTR("Pull(J) Push(K)"), false);
            oled_write_ln_P(PSTR("(A)dd (D)iff"), false);
            oled_write_ln_P(PSTR("(L)og (S)tatus"), false);
            break;
        case NIX:
            oled_write_ln_P(PSTR("(S)witch (U)pdate"), false);
            break;
        case SEARCH:
            oled_write_ln_P(PSTR("(R)eddit"), false);
            break;
        case WINDOW:
            oled_write_ln_P(PSTR("(Q)uit"), false);
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
    oled_write_P(PSTR("OS: "), false);
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

static void oled_render_caps_state(void) {
    if (host_keyboard_led_state().caps_lock) {
        oled_write_ln_P("CAPS LOCK", false);
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
#    ifdef OS_DETECTION_ENABLE
            oled_render_detected_os(os_detection);
#    endif
#    ifdef DYNAMIC_MACRO_ENABLE
            oled_render_dynamic_macro();
#    endif
            oled_render_caps_state();
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
