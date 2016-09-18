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

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    //debug
    debug_matrix = true;
    LED_ON();
    wait_ms(500);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_TGL();
    wait_ms(50);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        //wait_us(30);  // without this wait read unstable value.
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

#define PWM_DRIVER PWMD1

static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  palSetPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
};

static void pwmc0cb(PWMDriver *pwmp) {
  (void)pwmp;
  palClearPad(TEENSY_PIN23_IOPORT, TEENSY_PIN23);
};

static PWMConfig pwmcfg = {
  24000000,           /* 24MHz PWM clock frequency. */
  12000,              /* Initial PWM period 1ms (12000 clock ticks) */
  pwmpcb,
  {
    {PWM_OUTPUT_DISABLED, pwmc0cb},
    {PWM_OUTPUT_DISABLED, NULL}
  }
};

void backlight_set(uint8_t level) {
  /*
   * Initialize the PWM driver.
   */
  pwmStart(&PWM_DRIVER, &pwmcfg);
  pwmEnablePeriodicNotification(&PWM_DRIVER);

  /*
   * Starts the PWM channel 0; turn the LED off.
   */
  pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER, 0));
  pwmEnableChannelNotification(&PWM_DRIVER, 0); // MUST be before EnableChannel...

  pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER,5000));
}
