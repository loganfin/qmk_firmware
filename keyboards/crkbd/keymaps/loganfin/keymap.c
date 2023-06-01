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

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4
};

enum {
    SFT_CAPS,
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
enum {
    TD_LSFT_CAPS = 0,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
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
                                    | shift | enter |  tab  |   | bspc  | space | shift |
                                    `-----------------------'   `-----------------------'
    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,  KC_QUOT, KC_COMM, KC_DOT,   KC_P,    KC_Y,                          KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,  KC_A,    LGUI_T(KC_O),    LALT_T(KC_E),   LCTL_T(KC_U),    KC_I,         KC_D,    RCTL_T(KC_H),    RALT_T(KC_T),    RGUI_T(KC_N), KC_S, KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_SCLN,   KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,    KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TD(TD_LSFT_CAPS), LT(_NUM, KC_ENT), KC_TAB,     KC_BSPC, LT(_SYM, KC_SPC), OSM(MOD_RSFT)
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
    |       |       |       |       |       |       |                   |   *   |   7   |   8   |   9   |   /   |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       | meta  |  alt  | ctrl  |       |                   |   +   |   4   |   5   |   6   |   -   |       |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |       |       |       |       |       |                   |   =   |   1   |   2   |   3   |       |       |
    `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                    |       |       |       |   |   .   |   0   | shift |
                                    `-----------------------'   `-----------------------'
    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_ASTR,    KC_7,    KC_8,    KC_9,   KC_SLSH,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,  KC_LGUI, KC_LALT, KC_LCTL,  KC_NO,                       KC_PLUS,    RCTL_T(KC_4),    RALT_T(KC_5),    RGUI_T(KC_6),   KC_MINUS,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_EQL,    KC_1,    KC_2,    KC_3,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_NO,  _______,  KC_NO,     KC_DOT,   KC_0, OSM(MOD_RSFT)
                                      //`--------------------------'  `--------------------------'
  ),

  // need to use tap dance for mod tap functionality on shifted characters
  [_SYM] = LAYOUT_split_3x6_3(
    /*
    ,-----------------------------------------------.                   ,-----------------------------------------------.
    |       |   ~   |   <   |   >   |   $   |   \   |                   |   |   |   ^   |   {   |   }   | right |   /   |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |  esc  |   !   |   @   |   #   |   :   |   =   |                   |   &   | left  |   (   |   )   |   %   |   _   |
    |-------+-------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------+-------|
    |       |   `   |       | down  |  up   |       |                   |       |       |   [   |   ]   |       |       |
    `-------+-------+-------+-------+-------+-------+-------.   .-------+-------+-------+-------+-------+-------+-------'
                                    | shift | enter |  tab  |   |       | _____ |       |
                                    `-----------------------'   `-----------------------'
    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,  KC_TILD, KC_LABK, KC_RABK,  KC_DLR, KC_BSLS,                      KC_NO, KC_CIRC, KC_LCBR, KC_RCBR, KC_RGHT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH, KC_COLN,  KC_EQL,                      KC_NO, KC_LEFT, KC_LPRN, KC_RPRN, KC_PERC, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_GRV,   KC_NO, KC_DOWN,   KC_UP,   KC_NO,                        KC_NO, KC_AMPR, KC_LBRC, KC_RBRC,   KC_PIPE,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT,  KC_ENT,  KC_TAB,      KC_NO, _______,  KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_RIGHT,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,   LCTL_T(KC_NO),   LALT_T(KC_NO),   LGUI_T(KC_NO),   KC_NO,                        KC_NO, RGUI_T(KC_LEFT),   RALT_T(KC_NO),   RCTL_T(KC_NO),   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_NO,   KC_NO,   KC_NO, KC_DOWN,   KC_UP,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_NO,   KC_NO,   KC_NO,     _______,  KC_NO,   KC_NO
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
#endif // OLED_ENABLE
