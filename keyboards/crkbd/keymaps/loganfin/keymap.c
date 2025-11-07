#include QMK_KEYBOARD_H

// Notes:
// - Try to minimize inner column and pinky column use in layers other than the alpha layer
// -
//
// TODO:
// - [ ] Shift isn't del during capsword, or make del a different key
// - [ ] Change shifted forms of , and . to / and ?
// - [ ] Create mouse layer for use with trackpoint
// - [ ] Find a good place for home, end, pg_up, pg_dn
//      - For arrow keys, maybe ignore the position of the real hjkl keys
// - [ ] Numword
// - [ ] Investigate the usefulness of the alternatie repeat key as a "magic" key
// - [ ] Disable shift on symbol layer keys

typedef enum {
    _Alpha,
    _Symbol,
    _Number,
    _Navigation,
    _Function,
    _Mouse,
    _Control,
} LayerNames;

////////////////////////////////////////////////////////////////////////////////
// Home-row macros

#define HR_R LGUI_T(KC_R)
#define HR_T LALT_T(KC_T)
#define HR_S LCTL_T(KC_S)

#define HR_H RCTL_T(KC_H)
#define HR_A RALT_T(KC_A)
#define HR_E RGUI_T(KC_E)

////////////////////////////////////////////////////////////////////////////////
// Thumb cluster macros

#define TH_ENT LT(_Navigation, KC_ENT)
#define TH_SFT TD(TD_SFT_CAPS)
#define TH_REP QK_REP
#define TH_SPC KC_SPC

////////////////////////////////////////////////////////////////////////////////
// Non-thumb key layer switch macros

#define SYM_C LT(_Symbol, KC_C)
#define SYM_F LT(_Symbol, KC_F)
#define NUM_M LT(_Number, KC_M)

////////////////////////////////////////////////////////////////////////////////
// Key overrides

key_override_t const shift_delete_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
key_override_t const shift_comma_override  = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SLSH);
key_override_t const shift_dot_override    = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);

// The shifted versions of these keys are already available on the symbol
// layer, so they don't need a shifted version.
key_override_t const shift_grave_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_NO);
key_override_t const shift_minus_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_NO);
key_override_t const shift_left_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_NO);
key_override_t const shift_right_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_NO);
key_override_t const shift_slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_NO);
key_override_t const shift_back_slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, KC_NO);

key_override_t const* key_overrides[] = {
    &delete_key_override,
    &shift_comma_override,
    &shift_dot_override,
    &shift_grave_override,
    &shift_minus_override,
    &shift_left_bracket_override,
    &shift_right_bracket_override,
    &shift_slash_override,
    &shift_back_slash_override
};

////////////////////////////////////////////////////////////////////////////////
// Tap dance
// TODO: does this need the typedef?
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
} TapDanceState;

typedef struct {
    bool          is_press_action;
    TapDanceState state;
} TapDanceTap;

static TapDanceTap shift_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_tap_dance_finished, shift_tap_dance_reset),
};

TapDanceState cur_ance(tap_dance_state_t* state);
void          shift_tap_dance_finished(tap_dance_state_t* state, void* user_data);
void          shift_tap_dance_reset(tap_dance_state_t* state, void* user_data);

enum {
    TD_SFT_CAPS = 0,
};

////////////////////////////////////////////////////////////////////////////////
// Combos

uint16_t const PROGMEM backspace_combo[] = {KC_H, KC_A, COMBO_END};
uint16_t const PROGMEM escape_combo[]    = {KC_T, KC_S, COMBO_END};
uint16_t const PROGMEM tab_combo[]       = {KC_R, KC_T, COMBO_END};
uint16_t const PROGMEM delete_combo[]    = {KC_A, KC_E, COMBO_END};

combo_t key_combos[] = {
    COMBO(backspace_combo, KC_BSPC),
    COMBO(escape_combo, KC_ESC),
    COMBO(tab_combo, KC_TAB),
    COMBO(delete_combo, KC_DEL),
};

////////////////////////////////////////////////////////////////////////////////
// Layers
// clang-format off

uint16_t const PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ,-----------------------------------------------.             ,-----------------------------------------------.
    // |       |   B   |   L   |   D   |   W   |   V   |             |   Z   |   Y   |   O   |   U   |  ,//  |       |
    // |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
    // |       |   N   |   R   |   T   |   S   |   G   |             |   P   |   H   |   A   |   E   |   I   |       |
    // |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
    // |       |   Q   |   X   |   M   |   C   |   J   |             |   K   |   F   |  '/"  |  ;/:  |  ./?  |       |
    // `-----------------------------------------------'             `-----------------------------------------------'
    //                              ,-----------------------.   ,-----------------------.
    //                              |       | enter | shift |   | repeat| space |       |
    //                              `-----------------------'   `-----------------------'

    [_Alpha] = LAYOUT_split_3x6_3(
        KC_NO, KC_B, KC_L, KC_D, KC_W, KC_V,                        KC_Z, KC_Y, KC_O, KC_U, KC_COMM, KC_NO,
        KC_NO, KC_N, HR_R, HR_T, HR_S, KC_G,                        KC_P, HR_H, HR_A, HR_E, KC_I, KC_NO,
        KC_NO, KC_Q, KC_X, NUM_M, SYM_C, KC_J,                      KC_K, SYM_F, KC_QUOT, KC_SCLN, KC_DOT, KC_NO,
                                KC_NO, TH_ENT, TH_SFT       TH_REP, TH_SPC, KC_NO
    ),

    [_Symbol] = LAYOUT_split_3x6_3(
        KC_NO, KC_GRV, KC_LABK, KC_RABK, KC_MINS, KC_NO,            KC_NO, KC_AMPR, KC_LCBR, KC_RCBR, KC_KC_DLR, KC_NO,
        KC_NO, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL, KC_UNDS,          KC_NO, KC_CIRC, KC_KC_LPRN, KC_RPRN, KC_PERC, KC_NO,
        KC_NO, KC_TILD, KC_PLUS, KC_HASH, KC_PIPE, KC_NO,           KC_NO, KC_AT, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
                                KC_NO, TH_ENT, TH_SFT,        TH_REP, TH_SPC, KC_NO
    ),

    [_Number] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_4, KC_5, KC_6, KC_0, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_SYM, KC_NO,                  KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,
                                KC_NO, TH_ENT, TH_SFT,        TH_REP, TH_SPC, KC_NO
    ),

    [_Navigation] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,             KC_NO, KC_LFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    [_Function] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,             KC_NO, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_F1, KC_F2, KC_F3, KC_F12, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    // [_Mouse] = LAYOUT_split_3x6_3(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, MS_BTN1, MS_BTN2, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, MS_WHLD, MS_WHLU, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                             KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    // ),

    [_Mouse] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                KC_NO, MS_BTN1, MS_BTN2,        KC_NO, KC_NO, KC_NO
    ),

    [_Control] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, RM_HUED, RM_SATD, RM_SATU, RM_HUEU, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, RM_PREV, RM_VALD, RM_VALU, RM_NEXT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, RM_SPDD, RM_SPDU, RM_TOGG, KC_NO, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    // [_Symbol] = LAYOUT_split_3x6_3(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                             KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    // ),
};

// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Tap dance implementation

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

////////////////////////////////////////////////////////////////////////////////
// Caps word

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

// void set_led_indicator(auto color, bool true) {}
//
// void caps_word_set_user(bool active) {
//     set_led_indicator(LED_CAPS_WORD_ACTIVE, active); // Example custom function
// }

////////////////////////////////////////////////////////////////////////////////
// Debug code

// #define MY_DEBUG
#ifdef MY_DEBUG

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
}

#endif // MY_DEBUG
