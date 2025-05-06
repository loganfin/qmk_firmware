#include QMK_KEYBOARD_H
#include <stdio.h>

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

static td_tap_t shift_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

td_state_t cur_dance(tap_dance_state_t* state);
void shift_tap_dance_finished(tap_dance_state_t* state, void* user_data);
void shift_tap_dance_reset(tap_dance_state_t* state, void* user_data);

enum {
    TD_SFT_CAPS = 0,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_tap_dance_finished, shift_tap_dance_reset),
};

// HR_*: Homerow modifier
// LT_*: layer tap
// LF_*: custom loganfin stuff

//// Common
#define LT_A LT(_NUM, KC_A)

//// Qwerty
// Left Alphas
#define HR_S LGUI_T(KC_S)
#define HR_D LALT_T(KC_D)
#define HR_F LCTL_T(KC_F)

// Right Alphas
#define HR_J RCTL_T(KC_J)
#define HR_K RALT_T(KC_K)
#define HR_L RGUI_T(KC_L)
#define LT_SCLN LT(_SYM, KC_SCLN)

//// Dvorak

#define HR_O LGUI_T(KC_O)
#define HR_E LALT_T(KC_E)
#define HR_U LCTL_T(KC_U)

#define HR_H RCTL_T(KC_H)
#define HR_T RALT_T(KC_T)
#define HR_N RGUI_T(KC_N)
#define LT_S LT(_SYM, KC_SCLN)

////

// Left Thumb Cluster
#define LF_LSFT TD(TD_SFT_CAPS)
#define LT_ENT LT(_QNAV, KC_ENT)
#define LT_TAB LT(_FUN, KC_TAB)

// Right Thumb Cluster
#define LT_BSPC KC_BSPC
#define LT_SPC KC_SPC
#define LF_RSFT TD(TD_SFT_CAPS)

enum Layers {
    _QWERTY = 0,
    _DVORAK = 1,
    _NUM    = 2,
    _SYM    = 3,
    _FUN    = 4,
    _QNAV    = 5,
    _DNAV    = 6,
};

// TODO:
// - oneshot shift + bspc doesn't emit delete

// Ideas:
// - [x] shift + bspc = del?
// - Media controls (including mic mute, etc)
// - Replace one of the shifts with ESC?
// - Nav layer based on base layer

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        /*
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |       |   q   |   w   |   e   |   r   |   t   |                   |   y   |   u   |   i   |   o   |   p   |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |  esc  |   a   |   s   |   d   |   f   |   g   |                   |   h   |   j   |   k   |   l   |   ;   |   '   |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |   z   |   x   |   c   |   v   |   b   |                   |   n   |   m   |   ,   |   .   |   /   |       |
        `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                        | shift | enter |  tab  |   | bspc  | space | shift |
                                        `-----------------------'   `-----------------------'
        */
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_NO,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_ESC ,  LT_A,    HR_S,    HR_D,    HR_F,    KC_G,                         KC_H,    HR_J,    HR_K,    HR_L,   LT_SCLN, KC_QUOT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_NO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_NO,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               LF_LSFT,  LT_ENT,  LT_TAB,     LT_BSPC,  LT_SPC, LF_RSFT
                                            //`--------------------------'  `--------------------------'
    ),
    [_DVORAK] = LAYOUT_split_3x6_3(
        /*
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |       |   '   |   ,   |   .   |   p   |   y   |                   |   f   |   g   |   c   |   r   |   l   |   /   |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |  esc  |   a   |   o   |   e   |   u   |   i   |                   |   d   |   h   |   t   |   n   |   s   |   -   |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |   ;   |   q   |   j   |   k   |   x   |                   |   b   |   m   |   w   |   v   |   z   |       |
        `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                        | shift | enter | shift |   | bspc  | space | shift |
                                        `-----------------------'   `-----------------------'
        */
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_NO,  KC_QUOT, KC_COMM,  KC_DOT,   KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_SLSH,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_ESC,   LT_A,    HR_O,    HR_E,    HR_U,    KC_I,                         KC_D,    HR_H,    HR_T,    HR_N,    LT_S,  KC_MINUS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_NO,  KC_SCLN,   KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,    KC_NO,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               LF_LSFT,  LT_ENT,  LT_TAB,     LT_BSPC,  LT_SPC, LF_RSFT
                                            //`--------------------------'  `--------------------------'
    ),
    [_NUM] = LAYOUT_split_3x6_3(
        /*
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |       |       |       |       |       |       |                   |   +   |   7   |   8   |   9   |   0   |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       | _____ |  gui  |  alt  |  ctl  |       |                   |   =   |   4   |   5   |   6   |   .   |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |                   |   -   |   1   |   2   |   3   |   _   |       |
        `-------------------------------+-------+-------+-------.   .-------+-------+-------+-------------------------------'
                                        | shift | enter |  tab  |   | bspc  | space | shift |
                                        `-----------------------'   `-----------------------'
        */
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_PLUS,    KC_7,    KC_8,    KC_9,   KC_0,    KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_NO , KC_TRNS, KC_LGUI, KC_LALT, KC_LCTL,   KC_NO,                       KC_EQL,    KC_4,    KC_5,    KC_6,  KC_DOT,   KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_MINUS,   KC_1,    KC_2,    KC_3, KC_UNDS,   KC_NO,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               LF_LSFT,  LT_ENT,  LT_TAB,     LT_BSPC,  LT_SPC, LF_RSFT
                                            //`--------------------------'  `--------------------------'
    ),
    [_SYM] = LAYOUT_split_3x6_3(
        /*
         *
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |   \   |   @   |   #   |   {   |   }   |   *   |                   |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |   |   |   ^   |   $   |   (   |   )   |   &   |                   |       |  ctl  |  alt  |  gui  | _____ |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |   `   |   !   |   %   |   [   |   ]   |   ~   |                   |       |       |       |       |       |       |
        `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                        | shift | enter |  tab  |   | bspc  | space | shift |
                                        `-----------------------'   `-----------------------'
        */
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
           KC_BSLS,  KC_AT,  KC_HASH, KC_LCBR, KC_RCBR, KC_ASTR,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_PIPE, KC_CIRC, KC_DLR,  KC_LPRN, KC_RPRN, KC_AMPR,                        KC_NO, KC_RCTL, KC_RALT, KC_RGUI, KC_TRNS,   KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           KC_GRV,  KC_EXLM, KC_PERC, KC_LBRC, KC_RBRC, KC_TILD,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               LF_LSFT,  LT_ENT,  LT_TAB,     LT_BSPC,  LT_SPC, LF_RSFT
                                            //`--------------------------'  `--------------------------'
    ),
    [_FUN] = LAYOUT_split_3x6_3(
        /*
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |       |       |       |       |       |       |                   |       |  F7   |  F8   |  F9   |  F10  |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |                   |       |  F4   |  F5   |  F6   |  F11  |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |                   |       |  F1   |  F2   |  F3   |  F12  |       |
        `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                        |       |       | _____ |   |       |       |       |
                                        `-----------------------'   `-----------------------'
        */
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_F7,   KC_F8,   KC_F9,  KC_F12,  KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_F4,   KC_F5,   KC_F6,  KC_F11,  KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_F1,   KC_F2,   KC_F3,  KC_F10,  KC_NO,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_NO,   KC_NO,  KC_TRNS,      KC_NO,   KC_NO,   KC_NO
                                            //`--------------------------'  `--------------------------'
    ),
    //[_QNAV] = LAYOUT_split_3x6_3(
        /*
        ,-----------------------------------------------.                   ,-----------------------------------------------.
        |       |       |       |       |       |       |                   | home  |pgdown | pgup  | end   |       |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |                   | left  | down  |  up   | right |       |       |
        |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |                   |       |       |       |       |       |       |
        `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                        |       | _____ |       |   |       |       |       |
                                        `-----------------------'   `-----------------------'
        */
    //),
};
// clang-format on

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
            //tap_code(KC_CAPS);
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
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
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
            return false;  // Deactivate Caps Word.
    }
}
