#include "roadkit.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum {
  // Layers
  _NP,
  _L1,
  _L2,

  // Macros
  _TMUX_LAST_WINDOW,
  _TMUX_LAST_SESSION,
  _WORKSPACE_1,
  _WORKSPACE_2,
  _MOD_TAB,
  _TMUX_PREFIX,
  _SEARCH_HIST,

  // Tap dance declarations
  TD_TMUX_PGUP,
  TD_LAYER_CHANGE
};

// Macro name shortcuts
#define NUMPAD M(_NP)
#define LAYER1 M(_L1)
#define LAYER2 M(_L2)

#define TX_LW   M(_TMUX_LAST_WINDOW)
#define TX_LS   M(_TMUX_LAST_SESSION)
#define WS_1    M(_WORKSPACE_1)
#define WS_2    M(_WORKSPACE_2)
#define MOD_TAB M(_MOD_TAB)
#define TX_PFX  M(_TMUX_PREFIX)
#define SEARCH  M(_SEARCH_HIST)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NP] = /* Numpad */
    SINGLES_KEYMAP(KC_KP_7, KC_KP_8,   KC_KP_9,             KC_KP_MINUS, \
                   KC_KP_4, KC_KP_5,   KC_KP_6,             KC_KP_PLUS,  \
                   KC_KP_1, KC_KP_2,   KC_KP_3,             KC_KP_ENTER, \
                   KC_KP_0, KC_KP_DOT, TD(TD_LAYER_CHANGE), KC_BSPC),

  [_L1] = /* LAYER 1 */
    SINGLES_KEYMAP(WS_1,    WS_2,    TX_LW,   TD(TD_TMUX_PGUP), \
                   MOD_TAB, KC_UP,   TX_LS,   KC_PGDOWN,        \
                   SEARCH,  KC_TRNS, TX_PFX,  KC_TRNS,          \
                   MO(_L2), KC_TRNS, KC_TRNS, KC_TRNS),

  [_L2] = /* LAYER 2 */
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
        case _WORKSPACE_1:
          if (record->event.pressed) {
            return MACRO( I(10), D(LGUI), T(1), U(LGUI), END );
          }
          break;
        case _WORKSPACE_2:
          if (record->event.pressed) {
            return MACRO( I(10), D(LGUI), T(2), U(LGUI), END );
          }
          break;
        case _MOD_TAB:
          if (record->event.pressed) {
            return MACRO( I(10), D(LGUI), T(TAB), U(LGUI), END );
          }
          break;
        case _TMUX_PREFIX:
          if (record->event.pressed) {
            return MACRO( I(10), D(LCTRL), T(B), U(LCTRL), END );
          }
          break;
        case _SEARCH_HIST:
          if (record->event.pressed) {
            return MACRO( I(10), D(LCTRL), T(R), U(LCTRL), END );
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

// This function is used to switch between layers using
// tap dance. The number of taps corresponds to the layer
// number to change to.
static void tap_dance_layer_change (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    persistant_default_layer_set(1UL<<_NP);
  } else if (state->count == 2) {
    persistant_default_layer_set(1UL<<_L1);
  } else {
    persistant_default_layer_set(1UL<<_L2);
  }
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap twice for CTRL-B followed by page up, once for page up
  [TD_TMUX_PGUP] = ACTION_TAP_DANCE_FN(tap_dance_tmux_page_up),
  [TD_LAYER_CHANGE] = ACTION_TAP_DANCE_FN(tap_dance_layer_change)
};
