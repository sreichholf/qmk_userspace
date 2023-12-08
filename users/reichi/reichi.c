#include "quantum.h"

#if 1

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(0x01,0xc6,0xff);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        RGB configColor = hsv_to_rgb(rgb_matrix_config.hsv);
        uint8_t layer = get_highest_layer(layer_state);
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                keypos_t keypos = {col,row};

                if (index >= led_min && index < led_max && index != NO_LED) {
                  if (keymap_key_to_keycode(layer, keypos) > KC_TRNS) {
                    switch(layer) {
                        case 1:
                            rgb_matrix_set_color(index, RGB_RED);
                            break;
                        case 2:
                            rgb_matrix_set_color(index, 0xa2, 0x00, 0xff);
                            break;
                        case 3:
                            rgb_matrix_set_color(index, RGB_BLUE);
                            break;
                        default:
                            rgb_matrix_set_color(index, RGB_OFF);
                            break;
                    }

                  } else if (keymap_key_to_keycode(layer, keypos) == KC_TRNS) {
                    rgb_matrix_set_color(index, configColor.r, configColor.g, configColor.b);
                  } else if (keymap_key_to_keycode(layer, keypos) == KC_NO) {
                    rgb_matrix_set_color(index, RGB_OFF);
                  }
                }
            }
        }
    }
    return false;
}
#endif
