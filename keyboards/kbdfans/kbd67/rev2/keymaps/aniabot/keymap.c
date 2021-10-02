/* Copyright 2018 'mechmerlin'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  KC_GHOSTLY = SAFE_RANGE,
  KC_POLSKA,
  KC_CMYK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Home|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |PgUp|
   * |----------------------------------------------------------------|
   * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgDn|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|End |
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |AAPL |        Space         |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[0] = LAYOUT_65_ansi(
  KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT, KC_PGDN,  \
  KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,           \
  KC_LCTL, KC_LALT, KC_LGUI,              KC_SPC,                          KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap Fn Layer
   * ,----------------------------------------------------------------.
   * |~ `|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |rbw|   |   |   |PSc|SLk|Pau|Up |wht|plska|cmyk|
   * |----------------------------------------------------------------|
   * |      |Lef|Dow|Rig|   |   |   |   |Hom|PUp|Lef|Rig|        |    |
   * |----------------------------------------------------------------|
   * |        |tog|mod|pln|   |   |   |   |End|PDn|Dow|      |PUp|    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |Hom|PDn|End |
   * `----------------------------------------------------------------'
   */
[1] = LAYOUT_65_ansi(
   KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,          KC_DEL,KC_INS, \
   _______,_______,  KC_UP,_______, RGB_M_R,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,  KC_UP,KC_GHOSTLY, KC_POLSKA,KC_CMYK,   \
      _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,_______,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,            _______,_______, \
           _______,RGB_TOG,RGB_MOD,RGB_M_P,_______,_______,_______,_______, KC_END,KC_PGDN,KC_DOWN,       _______,KC_PGUP,_______, \
    _______,  _______,  _______,                     _______,                     _______,_______,_______,KC_HOME,KC_PGDN, KC_END),

};

#ifdef WPM_ENABLE // begin WOMP
void totally_awful_wpm_function(uint16_t keycode, keyrecord_t *record) {
  // change erratically depending on wpm range
  if (record->event.pressed) {
    uint8_t wpm = get_current_wpm();
    if (wpm <= 50) {
      rgblight_sethsv_range(HSV_CYAN, 0, RGBLED_NUM);
    } else if (wpm > 50  && wpm <= 100) {
      rgblight_sethsv_range(HSV_GOLDENROD, 0, RGBLED_NUM);
    } else {
      rgblight_sethsv_range(HSV_RED, 0, RGBLED_NUM);
    }
  }
}

void slightly_less_awful_wpm_function(uint16_t keycode, keyrecord_t *record) {
  // wakey wakey if typing quickly
  if (record->event.pressed) {
    rgblight_sethsv_range(255, 255, get_current_wpm(), 0, RGBLED_NUM);
  }
}
#endif // end WOMP!

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // some fancy modes
  switch (keycode) {
    // polish candy cane mode
    case KC_POLSKA:
      if (record->event.pressed) {
        uint16_t a = 0;
        for (a = 0; a < RGBLED_NUM; a = a+2) {
          rgblight_sethsv_at(HSV_RED, a);
          rgblight_sethsv_at(HSV_WHITE, a+1);
        }
      } else {
        // when released
      }
      break;

    // completely white
    case KC_GHOSTLY:
      if (record->event.pressed) {
        rgblight_sethsv_range(HSV_WHITE, 0, RGBLED_NUM);
      } else {
        // when released
      }
      break;

    case KC_CMYK:
      if (record->event.pressed) {
        rgblight_mode(RGBLIGHT_MODE_TWINKLE);
        uint16_t a = 0;
        for (a = 0; a < RGBLED_NUM; a = a+3) {
          rgblight_sethsv_at(HSV_CYAN, a);
          rgblight_sethsv_at(HSV_YELLOW, a+1);
          rgblight_sethsv_at(HSV_MAGENTA, a+2);
        }
      } else {
        // when released
      }
      break;
  }
  return true;
}
