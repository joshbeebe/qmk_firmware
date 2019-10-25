/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

#define ALT_TAB_TIMEOUT 1000u    /* Timeout for single key alt-tab */
bool is_alt_tab_active = FALSE; /* For single key alt-tab */
uint16_t alt_tab_timer = 0u;    /* For single key alt-tab */

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ENTER,
  _ENTER2,
  _NUMPAD
};


enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ALT_TAB,
  DYNAMIC_MACRO_RANGE
};
#include "dynamic_macro.h"
#define M1_REC DYN_REC_START1
#define M2_REC DYN_REC_START2
#define M1_PLAY DYN_MACRO_PLAY1
#define M2_PLAY DYN_MACRO_PLAY2
#define M_STOP DYN_REC_STOP

#ifdef AUDIO_ENABLE
    #include "audio.h"
    float tone_macro1_record[][2]     = SONG(CAPS_LOCK_ON_SOUND);
    float tone_macro2_record[][2]     = SONG(SCROLL_LOCK_ON_SOUND);
    float tone_macro_record_stop[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
#endif
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,               KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,               KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                KC_H,               KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                KC_N,               KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  \
  KC_LCTL, ALT_TAB, KC_LGUI, KC_LALT, LOWER,   LT(_ENTER2,KC_SPC),  LT(_ENTER,KC_SPC),  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  TG(_NUMPAD), DYN_REC_START1, DYN_REC_STOP, DYN_MACRO_PLAY1, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_BSPC, \
  _______,     _______, _______, _______, _______, _______, _______, KC_EQL,  _______, _______, _______, KC_DEL,  \
  KC_CAPS,     KC_LCBR, KC_LBRC, KC_LT,   KC_LPRN, KC_MINS, KC_PLUS, KC_RPRN, KC_GT,   KC_RBRC, KC_RCBR, KC_PIPE, \
  _______,     _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END, _______, \
  _______,     _______, _______, _______, _______, _______, KC_UNDS, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, KC_UNDS, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_ENTER] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______, _______, _______  \
),
[_ENTER2] = LAYOUT_preonic_grid( \
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
  _______, _______, _______, M2_REC,  M1_REC,  M_STOP,  _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, M2_PLAY, M1_PLAY, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______, _______  \
),
[_NUMPAD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,  \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_7,    KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_4,    KC_KP_5,     KC_KP_6,        KC_KP_PLUS, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_1,    KC_KP_2,     KC_KP_3,        KC_KP_ENTER, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_0,    KC_KP_0,     KC_KP_DOT,      KC_KP_ENTER  \
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ALT_TAB) {
        /* Single key alt-tab */
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = TRUE;
                register_code(KC_LALT);
            }
            wait_ms(100); /* Wait so windows has time to register alt before tab */
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        return false;
    } else {
        /* Stop single key alt-tab if a new key is pressed. */
        if (is_alt_tab_active) {
            is_alt_tab_active = FALSE;
            unregister_code(KC_LALT);
        }
    }
    if (!process_record_dynamic_macro(keycode, record)) {
// Play sound on Macro stop
#ifdef AUDIO_ENABLE
        switch (keycode) {
            case DYN_REC_STOP:
                if (record->event.pressed) {
                    PLAY_SONG(tone_macro_record_stop);
                }
                break;
            case DYN_REC_START1:
                if (record->event.pressed) {
                    PLAY_SONG(tone_macro1_record);
                }
                break;
            case DYN_REC_START2:
                if (record->event.pressed) {
                    PLAY_SONG(tone_macro2_record);
                }
                break;
        }
#endif
        return false;
    }
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > ALT_TAB_TIMEOUT) {
            unregister_code(KC_LALT);
            is_alt_tab_active = FALSE;
        }
    }
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
