#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

#define KEYMAP( \
    K00, K01, \
    K10, K11 \
) { \
    { KC_##K00, KC_##K01 }, \
    { KC_##K10, KC_##K11 } \
}

#endif
