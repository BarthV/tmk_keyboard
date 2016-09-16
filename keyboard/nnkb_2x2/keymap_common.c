#include "keymap_common.h"


/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
      return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
      return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
