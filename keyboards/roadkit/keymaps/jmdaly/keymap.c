#include "roadkit.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _NP 0
#define _L1 1
#define _L2 2

#define _TMUX_LAST_WINDOW 10
#define _TMUX_LAST_SESSION 11

// Tap dance declarations
enum {
  TD_TMUX_PGUP = 20
};

// Macro name shortcuts
#define NUMPAD M(_NP)
#define LAYER1 M(_L1)
#define LAYER2 M(_L2)

#define TX_LW M(_TMUX_LAST_WINDOW)
#define TX_LS M(_TMUX_LAST_SESSION)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NP] = /* Numpad */
    SINGLES_KEYMAP(KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_MINUS,  \
                   KC_KP_4, KC_KP_5,   KC_KP_6, KC_KP_PLUS, \
                   KC_KP_1, KC_KP_2,   KC_KP_3, KC_BSPC, \
                   KC_KP_0, KC_KP_DOT, TG(_L1), KC_KP_ENTER),

  [_L1] = /* LAYER 1 */
    SINGLES_KEYMAP(KC_NUMLOCK, KC_TRNS, TX_LW,    TD(TD_TMUX_PGUP),   \
                   KC_TRNS,    KC_UP,   TX_LS,    KC_PGDOWN, \
                   KC_LEFT,    KC_DOWN, KC_RIGHT, KC_TRNS,   \
                   MO(_L2),    KC_TRNS, KC_TRNS,  KC_TRNS),

  [_L2] = /* LAYER 1 */
    SINGLES_KEYMAP(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                   RESET,   KC_TRNS, KC_TRNS, KC_TRNS, \
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _L1:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_L1);
          }
          break;
        case _L2:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_L2);
          }
          break;
        case _NP:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_NP);
          }
          break;
        case _TMUX_LAST_WINDOW:
          if (record->event.pressed) {
            return MACRO( I(10), D(LCTRL), D(B), W(10), U(B), U(LCTRL), T(L), END );
          }
          break;
        case _TMUX_LAST_SESSION:
          if (record->event.pressed) {
            return MACRO( I(10), D(LCTRL), D(B), W(10), U(B), U(LCTRL), D(LSHIFT), T(L), U(LSHIFT), END );
          }
          break;
      }
    return MACRO_NONE;
}

// This function is used to send the tmux CTRL-B prefix followed
// by PageUp when the key is tapped twice. When the key is tapped
// once, it just sends PageUp. This is to get tmux into the mode
// where page up works.
static void tap_dance_tmux_page_up (qk_tap_dance_state_t *state, void *user_data) {
  uint8_t kc = KC_PGUP;

  if (state->count >= 2) {
    // Send tmux prefix on double-tap:
    register_code(KC_LCTL);
    register_code(KC_B);

    unregister_code(KC_LCTL);
    unregister_code(KC_B);
  }

  register_code(kc);
  unregister_code(kc);
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap twice for CTRL-B followed by page up, once for page up
  [TD_TMUX_PGUP] = ACTION_TAP_DANCE_FN(tap_dance_tmux_page_up)
};
