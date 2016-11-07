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
 *     col: { TEENSY_PIN0, TEENSY_PIN1, TEENSY_PIN2, TEENSY_PIN3 }
 *     row: { TEENSY_PIN4, TEENSY_PIN5, TEENSY_PIN6, TEENSY_PIN7, TEENSY_PIN8, TEENSY_PIN9 }
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
      // LED_TGL(); // toggle the onboard LED attached to pin 13
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
  palSetPadMode(TEENSY_PIN2_IOPORT, TEENSY_PIN2, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(TEENSY_PIN3_IOPORT, TEENSY_PIN3, PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
  return ((palReadPad(TEENSY_PIN0_IOPORT, TEENSY_PIN0)==PAL_HIGH) ? 0 : (1<<0))
       | ((palReadPad(TEENSY_PIN1_IOPORT, TEENSY_PIN1)==PAL_HIGH) ? 0 : (1<<1))
       | ((palReadPad(TEENSY_PIN2_IOPORT, TEENSY_PIN2)==PAL_HIGH) ? 0 : (1<<2))
       | ((palReadPad(TEENSY_PIN3_IOPORT, TEENSY_PIN3)==PAL_HIGH) ? 0 : (1<<3));
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
  palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8, PAL_MODE_INPUT); // hi-Z
  palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9, PAL_MODE_INPUT); // hi-Z
}

static void select_row(uint8_t row)
{
  (void)row;
  // Output low to select
  switch (row) {
    case 0:
      palSetPadMode(TEENSY_PIN4_IOPORT, TEENSY_PIN4, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN4_IOPORT, TEENSY_PIN4);
      break;
    case 1:
      palSetPadMode(TEENSY_PIN5_IOPORT, TEENSY_PIN5, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN5_IOPORT, TEENSY_PIN5);
      break;
    case 2:
      palSetPadMode(TEENSY_PIN6_IOPORT, TEENSY_PIN6, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN6_IOPORT, TEENSY_PIN6);
      break;
    case 3:
      palSetPadMode(TEENSY_PIN7_IOPORT, TEENSY_PIN7, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN7_IOPORT, TEENSY_PIN7);
      break;
    case 4:
      palSetPadMode(TEENSY_PIN8_IOPORT, TEENSY_PIN8, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN8_IOPORT, TEENSY_PIN8);
      break;
    case 5:
      palSetPadMode(TEENSY_PIN9_IOPORT, TEENSY_PIN9, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(TEENSY_PIN9_IOPORT, TEENSY_PIN9);
      break;
  }
}

/*
 * PWM Driver Code 
 */

#define PWM_DRIVER PWMD1
uint8_t currentBacklightLevel = 0;

static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  if (currentBacklightLevel == 0) {
    palClearPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
  } else {
    palSetPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
  }
};

static void pwmc0cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
};

static PWMConfig pwmcfg = {
  24000000,           /* 24MHz PWM clock frequency. */
  24000,              /* Initial PWM period 1ms (24000 clock ticks) */
  pwmpcb,
  {
    {PWM_OUTPUT_ACTIVE_LOW, pwmc0cb},
    {PWM_OUTPUT_DISABLED, NULL}
  }
};

void pwm_init(void) {
  pwmStart(&PWM_DRIVER, &pwmcfg);
}

void backlight_set(uint8_t level) {
    pwmEnablePeriodicNotification(&PWM_DRIVER);
  if (level == 0) {
    currentBacklightLevel = 0;
  } else if (level == 1) {
    currentBacklightLevel = 1;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 1000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 2) {
    currentBacklightLevel = 2;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 2000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 3) {
    currentBacklightLevel = 3;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 3000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 4) {
    currentBacklightLevel = 4;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 4000));
    pwmDisableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 5) {
    currentBacklightLevel = 5;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 5000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 6) {
    currentBacklightLevel = 6;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 6000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 7) {
    currentBacklightLevel = 7;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 7000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 8) {
    currentBacklightLevel = 8;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 8000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 9) {
    currentBacklightLevel = 9;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 9000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  } else if (level == 10) {
    currentBacklightLevel = 10;
    pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 10000));
    pwmEnableChannelNotification(&PWM_DRIVER, 0);
  }
}
