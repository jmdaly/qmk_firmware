#include "dz60.h"

#define __x__ KC_NO

enum {
  // Layers
  _L1,
  _L2,
  _L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_L1] = KEYMAP(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, 
		CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
		KC_LSPO, __x__, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, MO(_L2), 
		MO(_L2), KC_LGUI, KC_LALT, KC_ENT, KC_SPC, KC_SPC, KC_RALT, __x__, KC_NO, __x__, KC_RCTL),

	[_L2] = KEYMAP( /* Function layer */
		KC_TRNS, KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5, KC_F6,   KC_F7,   KC_F8, KC_F9,    KC_F10,  KC_F11,   KC_F12, KC_TRNS, KC_INS,  \
		__x__,   KC_MUTE, KC_VOLU, __x__, __x__, __x__, __x__,   __x__,   __x__, __x__,    __x__,   KC_PGUP, __x__,   KC_INS, \
		KC_TRNS, __x__,   __x__,   __x__, __x__, __x__, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_HOME, KC_END,  __x__,   \
		KC_TRNS, __x__,   KC_VOLD, __x__, __x__, __x__, __x__,   __x__,   __x__, __x__,    __x__,   KC_PGDN, KC_TRNS, KC_TRNS,  \
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_L3)
	    ),

	[_L3] = KEYMAP(
		RESET, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL, 
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
};
