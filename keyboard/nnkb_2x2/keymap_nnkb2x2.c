#include "keymap_common.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0:
     * .-----.-----.
     * |  Q  |  B  |
     * :-----+-----:
     * | Maj | FN0 |
     * '-----'-----'
     */
    KEYMAP(   Q, B, \
           LSFT, FN0),
    /* 1 (Fn0):
     * .-----.-----.
     * | Bst | No  |
     * :-----+-----:
     * | BTo | FN0 |
     * '-----'-----'
     */
    KEYMAP(FN2, NO, \
           FN1, FN0)
};

const action_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1),
  [1] = ACTION_BACKLIGHT_TOGGLE(),
  [2] = ACTION_BACKLIGHT_STEP()
};
