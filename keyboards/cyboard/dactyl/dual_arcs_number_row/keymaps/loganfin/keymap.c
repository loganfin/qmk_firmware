#include QMK_KEYBOARD_H

// Keyamp notes:
//
// - Think about adding chording to increase the number of key outputs without increasing the number of layers
// - Think about switching to laery X from Layer Y without having to go back to the base layer. i.e symbols -> num / num -> symbols
// - Is one shift key enough? Maybe top left thumb key on left side could be something else and also a MO key.
// - Add layers to shift keys? Is it understandable to ever have to hold the key down?
//
//
// TODO:
// - move the symbol layer to a different key? it would be nice if I could hit enter or space while still in the symbol layer
// - add a question mark to the symbol layer?
// - only enable vibration on layer changes
// - replace the _______ with KC_NO to prevent fallthrough
//
// - A dedicated underscore key in the symbol layer and disable shifting '-' in capsword
// - Find a good place for home, end, pg_up, pg_dn
// auto const foo_arr[] = {2, 3, 4, 5}

#include "drivers/haptic/drv2605l.h"

enum LayerNames {
    _Base,
    _Navigation,
    _Symbol,
    _Function,
    _Effects, // LEDs and haptics
    _Number,
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

#define HR_LEFT RCTL_T(KC_LEFT)

//// Thumb cluser

// Common
#define LF_SFT TD(TD_SFT_CAPS)

// Left
#define LT_ENT LT(_Navigation, KC_ENT)
#define LT_TAB LT(_FUN, KC_TAB)

// Right
#define LT_BSPC KC_BSPC
// #define LT_SPC LT(_Navigation, KC_SPC)
#define LT_SPC KC_SPC

#define SYM_K LT(_Symbol, KC_K)
#define SYM_M LT(_Symbol, KC_M)

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
// Combos
const uint16_t PROGMEM comm_dot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM j_k_combo[]      = {KC_J, SYM_K, COMBO_END};

combo_t key_combos[] = {
    // , + . = ?
    COMBO(comm_dot_combo, KC_QUESTION),
    // j + k = /
    COMBO(j_k_combo, KC_SLSH),
};

////////////////////////////////////////////////////////////////////////////////
// Keymaps
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ,-----------------------------------------------.             ,-----------------------------------------------.
//      |       |   `   |   <   |   >   |   -   |       |             |       |   ^   |   {   |   }   |   $   |       |
//      |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
//      |       |   !   |   *   |   /   |   =   |       |             |       |   &   |   (   |   )   |   %   |       |
//      |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
//      |       |   ~   |   +   |   #   |   |   |       |             |       |   @   |   [   |   ]   |   \   |       |
//      `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
//                                   ,-----------------------.   ,-----------------------.
//                                   |       |       |       |   |       |       |       |
//                                   `-----------------------'   `-----------------------'


    [_Base] = LAYOUT_dual_arcs_num(
        KC_NO,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
        KC_NO,  KC_QUOT,    KC_COMM,    KC_DOT,    KC_P,    KC_Y,                                KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_NO,
        KC_NO, KC_A,    HR_O,    HR_E,    HR_U,    KC_I,                                KC_D,    HR_H,    HR_T,    HR_N,    KC_S, KC_NO,
        KC_NO, KC_SCLN,    KC_Q,    KC_J,    SYM_K,    KC_X,                                KC_B,    SYM_M,    KC_W, KC_V,  KC_Z, KC_NO,
        KC_NO,   KC_NO, KC_NO,   KC_NO,   LF_SFT, LT_ENT, KC_ESC,           LT_BSPC,  LT_SPC, LF_SFT, KC_NO,  KC_NO, KC_NO, KC_NO,
                                                      MO(_Function),    KC_NO,           KC_TAB,  MO(_Effects)
    ),

    [_Navigation] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_RIGHT, KC_NO,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                           KC_NO, HR_LEFT, KC_RALT, KC_RGUI, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_DOWN, KC_UP, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO,   KC_NO,   LF_SFT, LT_ENT, KC_ESC,           LT_BSPC,  LT_SPC, LF_SFT, KC_NO,  KC_NO, KC_NO, KC_NO,
                                                      MO(_Function),    KC_NO,           KC_TAB,  MO(_Effects)
    ),

    [_Symbol] = LAYOUT_dual_arcs_num(
        KC_NO,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
        KC_NO, KC_GRV, KC_LABK, KC_RABK, KC_MINS, KC_NO,                           KC_NO, KC_AMPR, KC_LCBR, KC_RCBR, KC_DLR, KC_NO,
        KC_NO, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL, KC_NO,                           KC_UNDS, KC_CIRC, KC_LPRN, KC_RPRN, KC_PERC, KC_NO,
        KC_NO, KC_TILD, KC_PLUS, KC_HASH, KC_PIPE, KC_NO,                           KC_NO, KC_AT, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
        KC_NO,   KC_NO, KC_NO,   KC_NO,   LF_SFT, LT_ENT, KC_ESC,           LT_BSPC,  LT_SPC, LF_SFT, KC_NO,  KC_NO, KC_NO, KC_NO,
                                                      MO(_Function),    KC_NO,           KC_TAB,  MO(_Effects)
    ),

    [_Function] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_F1, KC_F2, KC_F3, KC_F12, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
    ),

    [_Effects] = LAYOUT_dual_arcs_num(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           RM_HUED, RM_SATD, RM_SATU, RM_HUEU, KC_NO, KC_NO,
        KC_NO, KC_NO, HF_PREV, KC_NO, KC_NO, HF_NEXT,                           RM_PREV, RM_VALD, RM_VALU, RM_NEXT, KC_NO, KC_NO,
        KC_NO, KC_NO, HF_TOGG, KC_NO, KC_NO, KC_NO,                           KC_NO, RM_SPDD, RM_SPDU, RM_TOGG, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
    ),

    [_Number] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_ASTR, KC_7, KC_8, KC_9, KC_SLSH, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_PERC, KC_4, KC_5, KC_6, KC_DOT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, MO(_Symbol), KC_NO,                     KC_PLUS, KC_1, KC_2, KC_3, KC_MINS, KC_NO,
        KC_NO,   KC_NO, KC_NO,   KC_NO,   LF_SFT, LT_ENT, KC_ESC,           LT_BSPC,  LT_SPC, KC_0, KC_NO,  KC_NO, KC_NO, KC_NO,
                                                      MO(_Function),    KC_NO,           KC_TAB,  MO(_Effects)
    ),

    [6] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
    ),

    [7] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
    ),

    [8] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
    ),

    [9] = LAYOUT_dual_arcs_num(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                     KC_NO, KC_NO,         KC_NO, KC_NO
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

uint8_t mod_state         = 0;
uint8_t oneshot_mod_state = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    mod_state         = get_mods();
    oneshot_mod_state = get_oneshot_mods();

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
                } else if (oneshot_mod_state & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    del_registered = true;
                    // We don't need to reset the mod since we've fulfilled the oneshot
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

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_MINS:
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

void set_led_indicator(auto color, bool true)

void caps_word_set_user(bool active) {
    set_led_indicator(LED_CAPS_WORD_ACTIVE, active); // Example custom function
}

// void keyboard_post_init_user(void) {
//   // Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
//   debug_keyboard=true;
//   //debug_mouse=true;
// }
