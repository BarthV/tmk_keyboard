#include "ch.h"
#include "hal.h"
#include "backlight.h"

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
  24000000,           /* 24MHz PWM clock frequency.   */
  12000,              /* Initial PWM period 1ms     */
  pwmpcb,
  {
    {PWM_OUTPUT_DISABLED, pwmc0cb},
    {PWM_OUTPUT_DISABLED, NULL}
  }
};

void backlight_init_ports() {
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

  pwmEnableChannel(&PWM_DRIVER, 0, PWM_PERCENTAGE_TO_WIDTH(&PWM_DRIVER,7000));
}

void backlight_set(uint8_t level) {
}

void backlight_switch_enable() {
}

void backlight_switch_disable() {
}
