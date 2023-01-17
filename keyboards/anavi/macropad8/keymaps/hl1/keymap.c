#include QMK_KEYBOARD_H

#define _MEDIA 0
#define _LTSPICE 1
#define _MAIN 2

#define KC_X0 LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MEDIA] = LAYOUT_ortho_2x4(
     KC_MUTE, KC_MPLY, KC_NO, KC_G,
     KC_VOLD, KC_VOLU, KC_NO, TO(_LTSPICE)
  ),

  [_LTSPICE] = LAYOUT_ortho_2x4(
     KC_ESC, KC_F2, KC_F3, KC_G,
     KC_F5,  KC_F7, KC_NO, TO(_MAIN)
  ),

  [_MAIN] = LAYOUT_ortho_2x4(
     G(KC_D), KC_UP,   C(KC_C), C(KC_V),
     KC_LEFT, KC_DOWN, KC_RGHT, TO(_MEDIA)
  ),

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  static char tmp[26] = {0};
  switch (get_highest_layer(layer_state)) {
    case _MEDIA:
      snprintf(tmp, sizeof(tmp), "      %c%c%c%c%c%c%c", 128, 129, 129, 129, 129, 129, 130);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "      %cMedia%c", 134, 135);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "      %c%c%c%c%c%c%c", 131, 132, 132, 132, 132, 132, 133);
      oled_write_ln(tmp, false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("Mute  Play"), false);
      oled_write_ln_P(PSTR(""), false);
      snprintf(tmp, sizeof(tmp), "Down  Up           %c", 26);
      oled_write_ln(tmp, false);
      break;
    case _LTSPICE:
      snprintf(tmp, sizeof(tmp), "      %c%c%c%c%c%c%c%c%c", 128, 129, 129, 129, 129, 129, 129, 129, 130);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "      %cLTSpice%c", 134, 135);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "      %c%c%c%c%c%c%c%c%c", 131, 132, 132, 132, 132, 132, 132, 132, 133);
      oled_write_ln(tmp, false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("ESC  Cmp   Wire  GND"), false);
      oled_write_ln_P(PSTR(""), false);
      snprintf(tmp, sizeof(tmp), "Del  Move          %c", 26);
      oled_write_ln(tmp, false);
      break;
    case _MAIN:
      snprintf(tmp, sizeof(tmp), "       %c%c%c%c%c%c", 128, 129, 129, 129, 129, 130);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "       %cMain%c", 134, 135);
      oled_write_ln(tmp, false);
      snprintf(tmp, sizeof(tmp), "       %c%c%c%c%c%c", 131, 132, 132, 132, 132, 133);
      oled_write_ln(tmp, false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR("WinD                "), false);
      oled_write_ln_P(PSTR(""), false);
      snprintf(tmp, sizeof(tmp), "                   %c", 26);
      oled_write_ln(tmp, false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }

  return false;
}
#endif
