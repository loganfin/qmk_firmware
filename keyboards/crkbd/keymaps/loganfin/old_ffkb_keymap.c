#include "keycode.h"
#include QMK_KEYBOARD_H

#ifdef ENCODER_ENABLE
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
#endif

typedef struct {
    bool is_press_action;
    int state;
} tap;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _COLEMAK,
    //_COLEMAK_WINDOWS,
    _QWERTY,
    //_QWERTY_WINDOWS,

    _MED,
    _NAV,
    _SYM,
    _NUM,
    _FUN,
    //_MOUSE_M, // enabled by movement of trackpad

    _ADJUST
};

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4
};

enum {
    SFT_CAPS = 0,
    NAV_RPRN = 1
};

bool caps_is_active = false;
bool windows_is_active = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record -> event.pressed) {
                register_code(KC_CAPS);
                caps_is_active = !caps_is_active;
                if (caps_is_active) {
                }
                else if (caps_is_active) {
                    unregister_code(KC_CAPS);
                }
            }
            return false;
            break;
            /*
        case CG_SWAP:
            if (record -> event.pressed) {
                tap_code(CG_SWAP);
                windows_is_active = true;  // when macos is default layer
            }
            break;
        case CG_NORM:
            if (record -> event.pressed) {
                tap_code(CG_NORM);
                windows_is_active = false;
            }
            break;
            */
    }
    return true;
}

int cur_dance(qk_tap_dance_state_t *state) {
    if (state -> count == 1) {
        if (state -> pressed) return SINGLE_HOLD;
        else return SINGLE_TAP;
    }
    else if (state -> count == 2) {
        if (state -> pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else return 8;
}

static tap sfttap_state = {
    .is_press_action = true,
    .state = 0
};

void sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    sfttap_state.state = cur_dance(state);
    switch (sfttap_state.state) {
        case SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case DOUBLE_TAP:
            //caps_no_delay();
            //register_code(KC_CAPS);
            //register_code(KC_X);
            //SEND_STRING(KC_CAPS);
            tap_code(KC_CAPS);
            //SS_TAP(KC_CAPS);
            break;
        case DOUBLE_HOLD:
            //register_code(KC_CAPS);
            break;
    }
}
void sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (sfttap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            clear_oneshot_mods();
            unregister_code(KC_LSFT);
            break;
        case DOUBLE_TAP:
            //clear_oneshot_mods();
            //unregister_code(KC_LSFT);
            //unregister_code(KC_CAPS);
            //unregister_code(KC_X);
            break;
        case DOUBLE_HOLD:
            // unregister_code(KC_CAPS);
            break;
    }
    sfttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Colemak-dh
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |  TAB  |   Q   |   W   |   F   |   P   |   B   |             |   J   |   L   |   U   |   Y   |   ;   | BKSPC |   // do I use " ' " more often or " : " ?
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |  ESC  |   A   |   R   |   S   |   T   |   G   |   |      |  |   M   |   N   |   E   |   I   |   O   |   '   |
     * |-------+-------+-------+-------+-------+-------|   `------'  |-------+-------+-------+-------+-------+-------|
     * |       |   Z   | X/CTL | C/ALT | D/CMD |   V   |             |   K   | H/CMD | ,/ALT | ./CTL |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       | Enter | SHIFT |   | BKSPC | Space |       |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
     */

    [_COLEMAK] = LAYOUT_ffkb(
            KC_TAB,  KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         KC_J,    KC_L,         KC_U,         KC_Y,         KC_SCLN,          KC_BSPC,
            KC_ESC,  KC_A,         LCTL_T(KC_R), LALT_T(KC_S), LGUI_T(KC_T), KC_G,         KC_M,    RGUI_T(KC_N), RALT_T(KC_E), RCTL_T(KC_I), KC_O,             KC_QUOT,
            KC_NO,   KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,         KC_K,    KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,          KC_NO,
            KC_MUTE,    LT(_NUM, KC_NO), LT(_SYM, KC_ENT), TD(SFT_CAPS),      LT(_MED, KC_BSPC), LT(_NAV, KC_SPC),  KC_NO,       KC_MPLY,
            LALT(KC_TAB)
            ),

    /* Colemak-dh Windows
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |       |   Q   |   W   |   F   |   P   |   B   |             |   J   |   L   |   U   |   Y   |   '   |       |   // do I use " ' " more often or " : " ?
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |   A   |   R   |   S   |   T   |   G   |   |ALTTAB|  |   M   |   N   |   E   |   I   |   O   |       |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |   Z   | X/GUI | C/ALT | D/CTL |   V   |             |   K   | H/CTL | ,/ALT | ./GUI |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |  ESC  | Enter | SHIFT |   | BKSPC | Space |  TAB  |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
     */

    /*
    [_COLEMAK_WINDOWS] = LAYOUT_ffkb(
            KC_NO,  KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         KC_J,    KC_L,         KC_U,         KC_Y,         KC_QUOT,          KC_NO,
            KC_NO,  KC_A,         KC_R,         KC_S,         KC_T,         KC_G,         KC_M,    KC_N,         KC_E,         KC_I,         KC_O,             KC_NO,
            KC_NO,  KC_Z,         LGUI_T(KC_X), LALT_T(KC_C), LCTL_T(KC_D), KC_V,         KC_K,    RCTL_T(KC_H), RALT_T(KC_COMM), RGUI_T(KC_DOT), KC_SLSH,     KC_NO,
            KC_MUTE,    LT(_MED, KC_ESC), LT(_NAV, KC_ENT), TD(SFT_CAPS),      LT(_SYM, KC_BSPC), LT(_NUM, KC_SPC), LT(_FUN, KC_TAB),       KC_MPLY,
            LALT(KC_TAB)
            ),
    */

    /* Qwerty
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |  TAB  |   Q   |   W   |   E   |   R   |   T   |             |   Y   |   U   |   I   |   O   |   P   | BKSPC |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |  ESC  |   A   |   S   |   D   |   F   |   G   |   |ALTTAB|  |   H   |   J   |   K   |   L   |   ;   |   '   |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |   Z   | X/CTL | C/ALT | V/CMD |   B   |             |   N   | M/CMD | ,/ALT | ./CTL |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       | Enter | SHIFT |   | BKSPC | Space |       |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
     */

    [_QWERTY] = LAYOUT_ffkb(
            KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,             KC_BSPC,
            KC_ESC,  KC_A,         LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), KC_G,         KC_H,    RGUI_T(KC_J), RALT_T(KC_K), RCTL_T(KC_L), KC_SCLN,          KC_QUOT,
            KC_NO,   KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,          KC_NO,
            KC_MUTE,    LT(_NUM, KC_NO), LT(_SYM, KC_ENT), TD(SFT_CAPS),      LT(_MED, KC_BSPC), LT(_NAV, KC_SPC),  KC_NO,       KC_MPLY,
            LALT(KC_TAB)
            ),

    /* Qwerty Windows
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |       |   Q   |   W   |   E   |   R   |   T   |             |   Y   |   U   |   I   |   O   |   P   |       |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |   A   |   S   |   D   |   F   |   G   |   |ALTTAB|  |   H   |   J   |   K   |   L   |   ;   |   '   |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |   Z   | X/GUI | C/ALT | V/CTL |   B   |             |   N   | M/CTL | ,/ALT | ./GUI |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |  ESC  | Enter | SHIFT |   | BKSPC | Space |  TAB  |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
     */

    /*
    [_QWERTY_WINDOWS] = LAYOUT_ffkb(
            KC_NO,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,             KC_NO,
            KC_NO,  KC_A,         KC_S,         KC_D,         KC_F,         KC_G,         KC_H,    KC_J,         KC_K,         KC_L,         KC_SCLN,          KC_QUOT,
            KC_NO,  KC_Z,         LGUI_T(KC_X), LALT_T(KC_C), LCTL_T(KC_V), KC_B,         KC_N,    RCTL_T(KC_M), RALT_T(KC_COMM), RGUI_T(KC_DOT), KC_SLSH,     KC_NO,
            //KC_MUTE,    LT(_MED_W, KC_ESC), LT(_NAV_W, KC_ENT), OSM(MOD_LSFT),      LT(_SYM_W, KC_BSPC), LT(_NUM_W,KC_SPC), LT(_FUN_W, KC_TAB),       KC_MPLY,
            KC_MUTE,    LT(_MED, KC_ESC), LT(_NAV, KC_ENT), TD(SFT_CAPS),      LT(_SYM, KC_BSPC), LT(_NUM, KC_SPC), LT(_FUN, KC_TAB),       KC_MPLY,
            LALT(KC_TAB)
            ),
    */

    /* Media
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |       |       |       |       |       |       |             |   J   |   L   |   U   |   Y   |   '   |       |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       |   |ALTTAB|  |   M   |   N   |   E   |   I   |   O   |       |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |       |  CTL  |  ALT  |  CMD  |       |             |   K   | H/CMD | ,/ALT | ./CTL |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       |       |       |   | BKSPC | Space |  TAB  |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
     */

    [_MED] = LAYOUT_ffkb(
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_M,         KC_E,         KC_D,         KC_NO,             KC_NO,
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
            LALT(KC_TAB)
            ),

    /*
       [_MED_W] = LAYOUT_ffkb(
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_M,         KC_E,         KC_D,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
       LALT(KC_TAB)
       ),
       */

    /* Navigation
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |  TAB  |  F15  |  FN7  |  FN8  |  FN9  |  F12  |             |       |       |       |       |       |       |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |  ESC  |       |  FN4  |  FN5  |  FN6  |  F11  |   |      |  |   <   |   V   |   ^   |   >   |       |       |
     * |-------+-------+-------+-------+-------+-------|   `------'  |-------+-------+-------+-------+-------+-------|
     * |       |       |  FN1  |  FN2  |  FN3  |  F10  |             |       |       |       |       |       |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       |       |       |   |       |       |       |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
    */

    [_NAV] = LAYOUT_ffkb(
            KC_TAB,  KC_F13,       KC_F7,        KC_F8,         KC_F9,        KC_F12,          KC_NO,    KC_NO,          KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_ESC,  KC_NO,        LCTL_T(KC_F4),LALT_T(KC_F5), LGUI_T(KC_F6),KC_F11,          KC_LEFT,  RGUI_T(KC_DOWN),RALT_T(KC_UP), RCTL_T(KC_RIGHT),      KC_NO,             KC_NO,
            KC_NO,   KC_NO,        KC_F1,        KC_F2,         KC_F3,        KC_F10,          KC_NO,    KC_NO,          KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_NO,                               KC_NO,         _______,      KC_NO,           KC_NO,    _______,        KC_NO,         KC_NO,
            KC_NO
            ),

    /*
       [_NAV_W] = LAYOUT_ffkb(
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_N,         KC_A,         KC_V,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
       KC_NO
       ),
       */

    /* Symbol
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |  TAB  |   $   |   @   |   !   |   &   |       |             |   -   |   #   |   %   |   ^   |   +   | BKSPC |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |  ESC  |   `   |   [   |   {   |   (   |   ~   |   |ALTTAB|  |   =   |   )   |   }   |   ]   |   *   |  DEL  |
     * |-------+-------+-------+-------+-------+-------|   `------'  |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       |             |       |   _   |   |   |   \   |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       |       |       |   | BKSPC | SPACE |       |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
    */

    [_SYM] = LAYOUT_ffkb(
            KC_TAB,  KC_DLR,        KC_AT,        KC_EXLM,       KC_AMPR,         KC_NO,              KC_MINS,    KC_HASH,      KC_PERC,        KC_CIRC,       KC_PLUS,           KC_BSPC,
            KC_ESC,  KC_GRV,        LCTL_T(KC_LBRC),      LALT_T(KC_LCBR),       LGUI_T(KC_LPRN),         KC_TILD,            KC_EQL,     RGUI_T(KC_RPRN),      RALT_T(KC_RCBR),        RCTL_T(KC_RBRC),       KC_ASTR,           KC_DEL,
            KC_NO,   KC_NO,         KC_NO,        KC_NO,         KC_NO,           KC_NO,              KC_NO,      KC_UNDS,      KC_PIPE,        KC_BSLS,       KC_SLSH,           KC_NO,
            KC_NO,                       KC_NO,         _______,         KC_NO,         KC_ENT,    LT(_NAV, KC_SPC),         KC_RSFT,         KC_NO,
            KC_NO
            ),

    /*
       [_SYM_W] = LAYOUT_ffkb(
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_S,         KC_Y,         KC_M,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
       KC_NO
       ),
       */

    /* Number
     *
     * ,-----------------------------------------------.             ,-----------------------------------------------.
     * |       |       |       |       |       |       |             |   -   |   7   |   8   |  9    |   +   | BKSPC |
     * |-------+-------+-------+-------+-------+-------|   ,------.  |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       |   |      |  |   =   |   4   |   5   |  6    |   *   |   .   |
     * |-------+-------+-------+-------+-------+-------|   `------'  |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       |             |   0   |   1   |   2   |  3    |   /   |       |
     * `-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------'
     *              ,------.        ,-----------------------.   ,-----------------------.        ,------.
     *              | MUTE |        |       |       |       |   | ENTER | SPACE |       |        | PLAY |
     *              `------'        `-----------------------'   `-----------------------'        `------'
    */

    [_NUM] = LAYOUT_ffkb(
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,            KC_MINS,    KC_7,          KC_8,         KC_9,        KC_PLUS,         KC_BSPC,
            KC_NO,  KC_NO,         LCTL_T(KC_NO),         LALT_T(KC_NO),         LGUI_T(KC_NO),         KC_NO,            KC_EQL,     RGUI_T(KC_4),          RALT_T(KC_5),         RCTL_T(KC_6),        KC_ASTR,         KC_DOT,
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,            KC_0,       KC_1,          KC_2,         KC_3,        KC_SLSH,         KC_NO,
                                 KC_NO,         _______,         KC_NO,         KC_NO,            KC_ENT,    LT(_NAV, KC_SPC),        KC_NO,         KC_NO,
            KC_NO
            ),

    /*
       [_NUM_W] = LAYOUT_ffkb(
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_N,         KC_U,         KC_M,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
       KC_NO
       ),
       */

    /* Function
    */

    [_FUN] = LAYOUT_ffkb(
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_F,         KC_U,         KC_N,         KC_NO,             KC_NO,
            KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
            KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
            KC_NO
            ),

    /*
       [_FUN_W] = LAYOUT_ffkb(
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_F,         KC_U,         KC_N,         KC_NO,             KC_NO,
       KC_NO,  KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,    KC_NO,         KC_NO,         KC_NO,         KC_NO,             KC_NO,
       KC_NO,         KC_NO,         _______,         KC_NO,         KC_NO,    _______,         KC_NO,         KC_NO,
       KC_NO
       ),
       */

    /* Adjust (Lower + Raise)

     * ,-----------------------------------------.             ,-----------------------------------------.
     * |      | RGB_T| RGB_R| RGB_F|      |QWERTY|             |   F1 |  F2  |  F3  |  F4  |  F5  |      |
     * |------+------+------+------+------+------|   ,------.  |------+------+------+------+------+------|
     * |      | SPD_I| HUE_I| SAT_I| VAL_I|COLEMK|   |ALTTAB|  |   F6 |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+------|   `------'  |------+------+------+------+------+------|
     * |      | SPD_D| HUE_D| SAT_D| VAL_D|      |             |  F11 |  F12 |      |      | Reset|      |
     * `-----------------------------------------'             `-----------------------------------------'
     *          ,------.        ,--------------------.    ,--------------------.        ,------.
     *          | MUTE |        |   \  | Enter| LOWER|    | RAISE| Space| Del  |        | DELW |
     *          `------'        `--------------------'    `--------------------.        `------'
     */
    [_ADJUST] =  LAYOUT_ffkb(
            _______, RGB_TOG, RGB_RMOD, RGB_MOD, _______, TO(_QWERTY),       KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,  _______,
            _______, RGB_SPI, RGB_HUI,  RGB_SAI, RGB_VAI, TO(_COLEMAK),      KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10, _______,
            _______, RGB_SPD, RGB_HUD,  RGB_SAD, RGB_VAD, CG_SWAP,           CG_NORM,  KC_F12,  _______, _______,  RESET,  _______,
            _______, _______, _______, _______,           _______, _______, _______, _______,
            _______
            )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _SYM, _ADJUST);
}

#ifdef ENCODER_ENABLE

void press_super_alt_tab(bool shift) {
    if (shift) {
        register_code(KC_LSHIFT);
    }
    if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
    }
    alt_tab_timer = timer_read();
    tap_code(KC_TAB);
    if (shift) {
        unregister_code(KC_LSHIFT);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    // default behavior if undefined
    if (index == 0) {
        // Conditional to reverse the direction of encoder number 1
        // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
#ifdef ENCODERS_A_REVERSE
        if (!clockwise) {
#else
            if (clockwise) {
#endif
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
        else if (index == 1) {
            // Conditional to reverse the direction of encoder number 1
            // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
#ifdef ENCODERS_B_REVERSE
            if (!clockwise) {
#else
                if (clockwise) {
#endif
                    tap_code16(C(KC_RGHT));
                }
                else{
                    tap_code16(C(KC_LEFT));
                }
            }
            else if (index == 2) {
#ifdef ENCODERS_C_REVERSE
                if (!clockwise) {
#else
                    if (clockwise) {
#endif
                        press_super_alt_tab(true);
                    } else {
                        press_super_alt_tab(false);
                    }
                }

                return true;
            }
#endif

#ifdef OLED_ENABLE


            oled_rotation_t oled_init_user(oled_rotation_t rotation) {
                return OLED_ROTATION_180;
            }


            // Commenting out logo as it takes up a lot of space :(
            static void render_logo(void) {
                // ffkb logo, 128x64px
                static const char PROGMEM ffkb_logo[] = {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
                    0xfe, 0x02, 0x02, 0x02, 0x82, 0x06, 0x0e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff, 0xff, 0x0f, 0x07, 0x0f, 0x1f, 
                    0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
                    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 
                    0x1f, 0x0f, 0x07, 0x0f, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x02, 0x82, 
                    0x82, 0xc2, 0xe2, 0xde, 0x0e, 0x0e, 0x06, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                    0xff, 0x02, 0x02, 0x07, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0xf8, 0xfc, 0x7e, 
                    0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 
                    0x7e, 0xfc, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x1f, 
                    0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
                    0x07, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0xff, 0x7f, 0x1f, 0x87, 0x83, 0x80, 0x80, 
                    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
                    0x80, 0x80, 0x83, 0x87, 0x1f, 0x7f, 0xff, 0xf8, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x04, 
                    0x04, 0x05, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
                    0xe0, 0x20, 0x20, 0x20, 0x20, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x08, 0x18, 0x3c, 0x3e, 0x7f, 0xff, 0xff, 0xff, 0xef, 0xcf, 0x8f, 0x87, 0x07, 0x07, 0x07, 0x07, 
                    0x07, 0xe7, 0xe7, 0xe7, 0xc7, 0x07, 0x07, 0x0f, 0x3f, 0xfe, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xfe, 0x3f, 0x0f, 0x07, 0x07, 0xc7, 0xe7, 0xe7, 0xe7, 0x07, 
                    0x07, 0x07, 0x07, 0x07, 0x87, 0x8f, 0xcf, 0xef, 0xef, 0xff, 0xff, 0x7f, 0x3e, 0x3c, 0x18, 0x08, 
                    0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x20, 0x20, 
                    0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                    0xff, 0x20, 0x20, 0x70, 0xf8, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x1f, 0x1e, 0x3e, 0x7c, 
                    0xf8, 0xf1, 0xf1, 0xe1, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
                    0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe1, 0xf1, 0xf1, 0xf8, 
                    0x7c, 0x3e, 0x1e, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x20, 
                    0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
                    0x7f, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7e, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x3c, 
                    0x3c, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7e, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x40, 0x40, 
                    0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0e, 
                    0x0e, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

                };
                oled_write_raw_P(ffkb_logo, sizeof(ffkb_logo));

            }

            /*
               static void render_status(void) {
               oled_write_P(PSTR("    Layer: "), false);
               switch (get_highest_layer(layer_state|default_layer_state)) {
               case _ALPHA_ALT:
               oled_write_P(PSTR("Alphalt   "), false);
               break;
               case _ALPHA:
               oled_write_P(PSTR("Alpha     "), false);
               break;
               case _NAVIGATION:
               oled_write_P(PSTR("Nav       "), false);
               break;
               case _SYMBOLS:
               oled_write_P(PSTR("Symbols   "), false);
               break;
               case _FUNCTION:
               oled_write_P(PSTR("Function  "), false);
               break;
               case _MEDIA:
               oled_write_P(PSTR("Media     "), false);
               break;
               case _MOUSE:
               oled_write_P(PSTR("Mouse     "), false);
               break;
               default:
               oled_write_P(PSTR("Unkn      "), false);
               break;
               }

            // // Write host Keyboard LED Status to OLEDs
            // led_t led_usb_state = host_keyboard_led_state();
            // oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
            // oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
            // oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

            // ffkb logo, 128x48px
            static const char ffkb_logo_small [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 
            0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
            0xc0, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0xf8, 0xfe, 0x8e, 0xdc, 0xf0, 0x70, 0x60, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
            0x30, 0x70, 0xf0, 0xd8, 0x9c, 0x9e, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 
            0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 
            0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
            0x40, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x10, 
            0x18, 0x3c, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
            0xff, 0x10, 0x10, 0x18, 0x3c, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x78, 0x7c, 
            0xff, 0xd7, 0x9b, 0x18, 0x78, 0x78, 0x18, 0x30, 0x70, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x30, 
            0x18, 0x58, 0x78, 0x18, 0x99, 0x9b, 0xf7, 0xfc, 0x78, 0x30, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x38, 0x78, 0xfc, 0xfc, 0xfe, 0xff, 0xf8, 0xf0, 
            0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
            0x10, 0x10, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xe7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
            0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x01, 0x01, 0x01, 0x03, 0x07, 0x0e, 0x0c, 0x18, 0x3f, 0x7f, 0x68, 0x68, 0x3f, 0x3f, 0x0c, 
            0x0c, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
            0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x00, 0x01, 0x0b, 0x0f, 0x0f, 0x0f, 0x0f, 
            0x0f, 0x0f, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
            0x08, 0x08, 0x0c, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            };
            oled_write_raw_P(ffkb_logo_small, sizeof(ffkb_logo_small));
            }
            */

            bool oled_task_user(void) {
                // If you don't want to display the logo, switch
                if (false) {
                    //render_status();
                } else if (true) {
                    render_logo();
                } else {
                    //render_logo_text();
                }
                return true;
            }

#endif
