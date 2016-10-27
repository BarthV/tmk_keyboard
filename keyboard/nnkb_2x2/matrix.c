#include "ch.h"
#include "hal.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "backlight.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/*
 * NNKB 2x2 Prototype Pinusage:
 * Row pins are input with internal pull-down. Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { TEENSY_PIN0, TEENSY_PIN1 }
 *     row: { TEENSY_PIN2, TEENSY_PIN3 }
 *
 *    Row
 *     ^
 *    2|
 *     |
 *     |
 *     |
 *    0+-----------> Col
 *     0          2
 *
 * Backlight PWM pin : TEENSY_PIN23
 */
/* matrix state(1:on, 0:off) */

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

#define LED_ON()    do { palSetPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13) ;} while (0)
#define LED_OFF()   do { palClearPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); } while (0)
#define LED_TGL()   do { palTogglePad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); } while (0)

void matrix_init(void)
{
  // initialize row and col
  unselect_rows();
  init_cols();
  pwm_init();
  rgb_init();
  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  //debug
  debug_matrix = false;
}

uint8_t matrix_scan(void)
{
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(10);  // without this wait read unstable value. (30us default)
    for (uint8_t i=0; i < 1; i++) { // Loop for very short delay, wait_us is returning a 1ms delay
      LED_TGL(); // toggle the onboard LED attached to pin 13
    }
    matrix_row_t cols = read_cols();
    if (matrix_debouncing[i] != cols) {
      matrix_debouncing[i] = cols;
      if (debouncing) {
        debug("bounce!: "); debug_hex(debouncing); debug("\n");
      }
      debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }
  return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row); print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

/* Column pin configuration
 */
static void  init_cols(void)
{
  // internal pull-up
  palSetPadMode(TEENSY_PIN0_IOPORT, TEENSY_PIN0, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(TEENSY_PIN1_IOPORT, TEENSY_PIN1, PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
  return ((palReadPad(TEENSY_PIN0_IOPORT, TEENSY_PIN0)==PAL_HIGH) ? 0 : (1<<0))
       | ((palReadPad(TEENSY_PIN1_IOPORT, TEENSY_PIN1)==PAL_HIGH) ? 0 : (1<<1));
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
  palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_INPUT); // hi-Z
}

static void select_row(uint8_t row)
{
  (void)row;
  // Output low to select
  switch (row) {
    case 0:
      palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN2_IOPORT, TEENSY_PIN2);
      break;
    case 1:
      palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN3_IOPORT, TEENSY_PIN3);
      break;
  }
}

/*
 * PWM Driver Code 
 */

#define PWM_DRIVER PWMD1
uint8_t currentBacklightLevel = 0;
bool RGB_enabled = true;
uint16_t currentRlevel = 0;
uint16_t currentGlevel = 0;
uint16_t currentBlevel = 0;

static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  if (currentBacklightLevel == 0) {
    palClearPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
  } else {
    palSetPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
  }
  if (RGB_enabled == false) {
    palClearPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20);
    palClearPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21);
    palClearPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22);
  } else {
    if (currentRlevel == 0) {
      palClearPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20);
    } else {
      palSetPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20);
    }
    if (currentGlevel == 0) {
      palClearPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21);
    } else {
      palSetPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21);
    }
    if (currentBlevel == 0) {
      palClearPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22);
    } else {
      palSetPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22);
    }
  }
};

static void bckc0cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
};

static void rgbc0cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN20_IOPORT, TEENSY_PIN20);
};

static void rgbc1cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN21_IOPORT, TEENSY_PIN21);
};

static void rgbc2cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN22_IOPORT, TEENSY_PIN22);
};

static PWMConfig pwmcfg = {
  24000000,           /* 24MHz PWM clock frequency. */
  24000,              /* Initial PWM period 1ms (24000 clock ticks) */
  pwmpcb,
  {
    {PWM_OUTPUT_DISABLED, bckc0cb},
    {PWM_OUTPUT_DISABLED, rgbc0cb},
    {PWM_OUTPUT_DISABLED, rgbc1cb},
    {PWM_OUTPUT_DISABLED, rgbc2cb}
  }
};

void pwm_init(void) {
  pwmStart(&PWM_DRIVER, &pwmcfg);
}

void rgb_set(uint8_t red, uint8_t green, uint8_t blue) {
    if (red == 0) {
      currentRlevel=0;
    } else {
      currentRlevel=red;
      pwmEnableChannel(&PWM_DRIVER, 1, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, red * 100));
      pwmEnableChannelNotification(&PWM_DRIVER, 1);
    }
    if (green == 0) {
      currentGlevel=0;
    } else {
      currentGlevel=green;
      pwmEnableChannel(&PWM_DRIVER, 2, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, green * 100));
      pwmEnableChannelNotification(&PWM_DRIVER, 2);
    }
    if (blue == 0) {
      currentBlevel=0;
    } else {
      currentBlevel=blue;
      pwmEnableChannel(&PWM_DRIVER, 3, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, blue * 100));
      pwmEnableChannelNotification(&PWM_DRIVER, 3);
    }
}

void set_bkl(uint8_t level, uint16_t brightness) {
  currentBacklightLevel = level;
  if (level != 0) {
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, brightness));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  }
}

void backlight_set(uint8_t level) {
    pwmEnablePeriodicNotification(&PWM_DRIVER);
  if (level == 0) {
    set_bkl(level, 0);
  } else if (level == 1) {
    set_bkl(level, 2000);
  } else if (level == 2) {
    set_bkl(level, 4000);
  } else if (level == 3) {
    set_bkl(level, 6000);
  } else if (level == 4) {
    set_bkl(level, 8000);
  } else if (level == 5) {
    set_bkl(level, 10000);
  }
}
