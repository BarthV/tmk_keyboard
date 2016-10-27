#include "keymap_common.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0:
     * .-----.-----.
     * |  Q  | FN3 |
     * :-----+-----:
     * | Maj | FN0 |
     * '-----'-----'
     */
    KEYMAP(   Q, FN3, \
           LSFT, FN0),
    /* 1 (Fn0):
     * .-----.-----.
     * | Bst | FN7 |
     * :-----+-----:
     * | BTo | FN0 |
     * '-----'-----'
     */
    KEYMAP(FN2, FN7, \
           FN1, FN0),

    /* 2 (Fn3):
     * .-----.-----.
     * | Red | FN3 |
     * :-----+-----:
     * | Gre | Blu |
     * '-----'-----'
     */
    KEYMAP(FN4, FN3, \
           FN5, FN6)
};

const action_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1),
  [1] = ACTION_BACKLIGHT_TOGGLE(),
  [2] = ACTION_BACKLIGHT_STEP(),
  [3] = ACTION_LAYER_MOMENTARY(2),
  [4] = ACTION_RGB_RED_STEP(),
  [5] = ACTION_RGB_GREEN_STEP(),
  [6] = ACTION_RGB_BLUE_STEP(),
  [7] = ACTION_RGB_TOGGLE()
};
