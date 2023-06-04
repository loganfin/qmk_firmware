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

/* ## TEMPLATES ## */
    /*
    ,-----------------------------------------------.                   ,-----------------------------------------------.
    |       |       |       |       |       |       |                   |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |                   |       |       |       |       |       |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |                   |       |       |       |       |       |       |
    `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                    |       |       |       |   |       |       |       |
                                    `-----------------------'   `-----------------------'
    */

    /*
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
    */

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layer_names {
    _DVORAK,
    _QWERTY,
    _NUM,
    _SYM,
    _NAV,
    _MED,
    _FUN,
    _ADJUST
};

/* tap_hold */

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record)
{
    switch(keycode) {
        case LT(_SYM, KC_SPC):
            return 0;
        default:
            return QUICK_TAP_TERM;
            break;
    }
}

/* tap_dance */
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

enum {
    TD_LSFT_CAPS = 0,
    TD_RSFT_CAPS,
};

td_state_t cur_dance(tap_dance_state_t *state);
void rsft_finished(tap_dance_state_t *state, void *user_data);
void rsft_reset(tap_dance_state_t *state, void *user_date);

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsft_finished, rsft_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
#define HOME_A LT(_SYM, KC_A)
#define HOME_O LGUI_T(KC_O)
#define HOME_E LALT_T(KC_E)
#define HOME_U LCTL_T(KC_U)
    #define T_ENT LT(_NUM, KC_ENT)
    #define T_LSFT OSM(MOD_LSFT)

    #define HOME_H LCTL_T(KC_H)
    #define HOME_T LALT_T(KC_T)
    #define HOME_N LGUI_T(KC_N)
    #define HOME_S LT(_SYM, KC_S)
#define T_BSPC KC_BSPC
#define T_SPC LT(_NAV, KC_SPC)
#define T_RSFT TD(TD_RSFT_CAPS)

  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_QUOT, KC_COMM,  KC_DOT,   KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,  HOME_A,  HOME_O,  HOME_E,  HOME_U,   KC_I,                         KC_D,   HOME_H,  HOME_T,  HOME_N,  HOME_S, KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_SCLN,   KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,    KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          T_LSFT,   T_ENT,   KC_TAB,      T_BSPC,  T_SPC,   T_RSFT
                                      //`--------------------------'  `--------------------------'

  ),
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

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_Z,LCTL_T(KC_X),LALT_T(KC_C),LGUI_T(KC_V),    KC_B,           XXXXXXX, KC_N,RGUI_T(KC_M),RALT_T(KC_COMM),RCTL_T(KC_DOT), KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, LT(_NUM, KC_ENT), KC_LSFT,     LT(_NUM, KC_BSPC),  LT(_SYM, KC_SPC), XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUM] = LAYOUT_split_3x6_3(
    /*
    ,-----------------------------------------------.                   ,-----------------------------------------------.
    |       |       |   <   |   >   |   @   |   #   |                   |   \   |   7   |   8   |   9   |       |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |  esc  |   !   |   -   |   +   |   =   |   .   |                   |   |   |   4   |   5   |   6   |   0   |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       |   /   |   *   |   ^   |   `   |                   |   ~   |   1   |   2   |   3   |       |       |
    `-------------------------------+-------+-------+-------.   .-------+-------+-------+-------------------------------'
                                    |       | _____ |       |   | bspc  | space | shift |
                                    `-----------------------'   `-----------------------'
    */
#define H_MINUS KC_MINUS
#define H_PLUS KC_PLUS
#define H_EQL KC_EQL

#define HOME_4 RCTL_T(KC_4)
#define HOME_5 RALT_T(KC_5)
#define HOME_6 RGUI_T(KC_6)

  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_NO,  KC_LABK,  KC_RABK, KC_AT,  KC_HASH,                       KC_BSLS,  KC_7,    KC_8,    KC_9,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_EXLM, H_MINUS,  H_PLUS,  H_EQL,  KC_DOT,                        KC_PIPE, HOME_4,  HOME_5,  HOME_6,  KC_0,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   KC_NO,  KC_SLSH,  KC_ASTR, KC_CIRC, KC_GRV,                       KC_TILD,  KC_1,    KC_2,    KC_3,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           T_LSFT,  KC_TRNS, KC_NO,      KC_BSPC, KC_SPC,   T_RSFT
                                      //`--------------------------'  `--------------------------'
  ),

  // need to use tap dance for mod tap functionality on shifted characters
  [_SYM] = LAYOUT_split_3x6_3(
    /*
    ,-----------------------------------------------.                   ,-----------------------------------------------.
    |       |       |   <   |   >   |   @   |   #   |                   |   \   |   &   |   {   |   }   |       |   /   |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |  esc  |   !   |   -   |   +   |   =   |   .   |                   |   |   |   :   |   (   |   )   |   %   |   _   |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       |   /   |   *   |   ^   |   `   |                   |   ~   |   $   |   [   |   ]   |       |       |
    `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                    | shift | enter |  tab  |   | bspc  |  spc  | shift |
                                    `-----------------------'   `-----------------------'
    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,  KC_NO,  KC_LABK,  KC_RABK, KC_AT,  KC_HASH,                       KC_BSLS, KC_AMPR, KC_LCBR, KC_RCBR, KC_NO,  KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_EXLM, H_MINUS,  H_PLUS,  H_EQL,  KC_DOT,                        KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   KC_NO,  KC_SLSH,  KC_ASTR, KC_CIRC, KC_GRV,                       KC_TILD, KC_DLR, KC_LBRC, KC_RBRC,   KC_NO,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           T_LSFT,  KC_ENT,  KC_TAB,     KC_BSPC, KC_SPC,  T_RSFT
                                      //`--------------------------'  `--------------------------'
  ),

#define H_LEFT LCTL_T(KC_LEFT)
  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_RIGHT, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   KC_NO,  KC_LGUI, KC_LALT, KC_LCTL,  KC_NO,                        KC_NO,   H_LEFT, KC_RALT, KC_RGUI,  KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   KC_NO,   KC_NO,  KC_DOWN,  KC_UP,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NO,   KC_NO,   KC_NO,      KC_NO,  KC_TRNS,  KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [_MED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}

td_state_t cur_dance(tap_dance_state_t *state)
{
    if (state->count == 1) {
        if (state->pressed) return TD_SINGLE_HOLD;
        else return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN;
}

static td_tap_t rsfttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void rsft_finished(tap_dance_state_t *state, void *user_data)
{
    rsfttap_state.state = cur_dance(state);
    switch (rsfttap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_RSFT));
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_RSFT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_CAPS);
            break;
        default:
            break;
    }
}

void rsft_reset(tap_dance_state_t *state, void *user_date)
{
    switch (rsfttap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            clear_oneshot_mods();
            unregister_code(KC_RSFT);
            break;
        default:
            break;
    }
    rsfttap_state.state = 0;
}
#endif // OLED_ENABLE
