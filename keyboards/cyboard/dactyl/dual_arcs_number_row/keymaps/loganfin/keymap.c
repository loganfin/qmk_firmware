#include QMK_KEYBOARD_H

enum LayerNames {
    _Base,
    _Navigation,
    _Symbol,
    _Function,
    _Effects, // LEDs and haptics
};

// HR_*: Homerow modifier
// LT_*: layer tap
// LF_*: custom loganfin stuff

//// Dvorak

#define HR_O LGUI_T(KC_O)
#define HR_E LALT_T(KC_E)
#define HR_U LCTL_T(KC_U)

#define HR_H RCTL_T(KC_H)
#define HR_T RALT_T(KC_T)
#define HR_N RGUI_T(KC_N)

//// Thumb cluser

// Common
#define LF_SFT TD(TD_SFT_CAPS)

// Left
#define LT_ENT LT(_QNAV, KC_ENT)
#define LT_TAB LT(_FUN, KC_TAB)

// Right
#define LT_BSPC KC_BSPC
#define LT_SPC KC_SPC

////////////////////////////////////////////////////////////////////////////////
// Tap dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

static td_tap_t shift_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

td_state_t cur_dance(tap_dance_state_t* state);
void       shift_tap_dance_finished(tap_dance_state_t* state, void* user_data);
void       shift_tap_dance_reset(tap_dance_state_t* state, void* user_data);

enum {
    TD_SFT_CAPS = 0,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_tap_dance_finished, shift_tap_dance_reset),
};
////////////////////////////////////////////////////////////////////////////////
// Keymaps
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_Base] = LAYOUT_dual_arcs_num(
        KC_NO,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_NO,  KC_QUOT,    KC_COMM,    KC_DOT,    KC_P,    KC_Y,                                KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_NO,
        KC_NO, KC_A,    HR_O,    HR_E,    HR_U,    KC_I,                                KC_D,    HR_H,    HR_T,    HR_N,    KC_S, KC_NO,
        KC_NO, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                                KC_B,    KC_M,    KC_W, KC_V,  KC_Z, KC_NO,
        KC_NO,   KC_NO, KC_NO,   KC_NO,   LF_SFT, KC_ENT, KC_ESC,           KC_BSPC,  KC_SPC,  LF_SFT, KC_LBRC,  KC_RBRC, KC_LEFT, KC_RIGHT,
                                                      MO(_Effects),    KC_TAB,           KC_CAPS,  KC_NO
    ),

    [_Navigation] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [_Symbol] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, KC_HOME, KC_UP,   KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [_Function] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [_Effects] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           RM_HUED, RM_SATD, RM_SATU, RM_HUEU, _______, _______,
        _______, _______, _______, _______, RM_TOGG, _______,                           RM_PREV, RM_VALD, RM_VALU, RM_NEXT, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, RM_SPDD, RM_SPDU, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [5] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [6] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [7] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [8] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    ),

    [9] = LAYOUT_dual_arcs_num(
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______,         _______, _______
    )
};

// clang-format on

// bool qwerty_active = true;
//
// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state | default_layer_state)) {
//         case _QWERTY:
//             qwerty_active = true;
//             break;
//         case _DVORAK:
//             qwerty_active = false;
//             break;
//     }
//     return state;
// }

uint8_t mod_state = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    mod_state = get_mods();

    switch (keycode) {
        case KC_BSPC:
            static bool del_registered = false;

            if (record->event.pressed) { // Pressed event
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    del_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else { // Released event
                if (del_registered) {
                    unregister_code(KC_DEL);
                    del_registered = false;
                    return false;
                }
            }

            return true;
    }
    return true;
}

td_state_t cur_dance(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->pressed) {
            return TD_SINGLE_HOLD;
        } else {
            return TD_SINGLE_TAP;
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    } else {
        return TD_UNKNOWN;
    }
}

void shift_tap_dance_finished(tap_dance_state_t* state, void* user_data) {
    shift_tap_state.state = cur_dance(state);

    switch (shift_tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            // tap_code(KC_CAPS);
            caps_word_on();
            break;
        default:
            break;
    }
}

void shift_tap_dance_reset(tap_dance_state_t* state, void* user_data) {
    switch (shift_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            clear_oneshot_mods();
            unregister_code(KC_LSFT);
            break;
        default:
            break;
    }
    shift_tap_state.state = 0;
}

// Override default implementation to disable shifting of '-'
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_MINS:
            // I believe I did this because I also had a dedicated underscore key on the symbols layer.
            // if (!qwerty_active) {
            // add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            //}
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
