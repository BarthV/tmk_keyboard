#include "keymap_common.h"
#include "backlight.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0:
     * .-----.-----.-----.-----.
     * | No  | FN0 | FN1 | FN2 |
     * :-----+-----+-----+-----:
     * :-----+-----+-----+-----:
     * | Nml |  /  |  *  |  -  |
     * :-----+-----+-----+-----:
     * |  7  |  8  |  9  | No  |
     * :-----+-----+-----+-----:
     * |  4  |  5  |  6  |  +  |
     * :-----+-----+-----+-----:
     * |  1  |  2  |  3  | No  |
     * :-----+-----+-----+-----:
     * |  0  |  No |  .  | Ent |
     * '-----'-----'-----'-----'
     */
    KEYMAP(  NO,  FN0,  FN1,  FN2, \
           NLCK, PSLS, PAST, PMNS, \
             P7,   P8,   P9,   NO, \
             P4,   P5,   P6, PPLS, \
             P1,   P2,   P3,   NO, \
             P0,   NO, PDOT, PENT ),
    /* 1 (Fn0):
     * .-----.-----.-----.-----.
     * |     | FN0 |     |     |
     * :-----+-----+-----+-----:
     * :-----+-----+-----+-----:
     * |     |     |     |     |
     * :-----+-----+-----+-----:
     * |     |     |     |     |
     * :-----+-----+-----+-----:
     * |     |     |     |     |
     * :-----+-----+-----+-----:
     * |     |     |     |     |
     * :-----+-----+-----+-----:
     * |     |     |     |     |
     * '-----'-----'-----'-----'
     */
    KEYMAP(  NO,  FN0,   NO,   NO, \
             NO,   NO,   NO,   NO, \
             NO,   NO,   NO,   NO, \
             NO,   NO,   NO,   NO, \
             NO,   NO,   NO,   NO, \
             NO,   NO,   NO,   NO )
};

const action_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1),
  [1] = ACTION_BACKLIGHT_TOGGLE(),
  [2] = ACTION_BACKLIGHT_STEP()
};
