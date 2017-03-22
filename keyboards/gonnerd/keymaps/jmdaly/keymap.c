#include "gonnerd.h"

#define __x__ KC_NO

enum {
  // Layers
  _L1,
  _L2,
  _L3
};

// Keymap layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L1] = KEYMAP_60( /* Base */
    KC_ESC,        KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,        KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, __x__,   KC_ENT,  \
    KC_LSFT,       __x__,   KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, __x__,   \
    MO(_L2),       KC_LGUI, KC_LALT,                           KC_SPC,                       KC_RALT, KC_RGUI, MO(_L3), KC_RCTL  \
  ),

  [_L2] = KEYMAP_60( /* Function layer */
      KC_GRV,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,   KC_F7,   KC_F8, KC_F9,    KC_F10,  __x__,   __x__,   __x__,  \
      __x__,   __x__, __x__, __x__, __x__, __x__, __x__,   __x__,   __x__, __x__,    __x__,   KC_PGUP, __x__,   KC_INS, \
      KC_TRNS, __x__, __x__, __x__, __x__, __x__, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_HOME, KC_END,  __x__,   __x__,  \
      KC_TRNS, __x__, __x__, __x__, __x__, __x__, __x__,   __x__,   __x__, __x__,    __x__,   KC_PGDN, KC_TRNS, __x__,  \
      KC_TRNS, __x__, __x__,                      __x__,                             __x__,   __x__,   KC_TRNS, __x__  \
  ),

  [_L3] = KEYMAP_60( /* System layer to have access to RESET button */
      RESET,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,   __x__, \
      __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,   __x__, \
      __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,   __x__, \
      __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,  __x__,   __x__, \
      __x__,  __x__,  __x__,                  __x__,                                  __x__,  __x__,  KC_TRNS, __x__  \
  ),
};

const uint16_t PROGMEM fn_actions[] = {

};
