#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "util.h"

#include "backlight.h"
#include "led.h"

static PWMConfig pwmcfg = {
  200000, /* 200Khz PWM clock frequency*/
  1024, /* PWM period of 1024 ticks ~ 0.005 second */
  NULL, /* No callback */
  /* Only channel 1 enabled */
  {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL}
  }
};

void backlight_init_ports()
{
  // Enables PWM output on PIN23
  palSetPadMode(TEENSY_PIN23_IOPORT, TEENSY_PIN23, PAL_MODE_ALTERNATE_PUSHPULL);

  pwmStart(&PWMD1, &pwmcfg);
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH (&PWMD1, 5000));

}

void backlight_set(uint8_t level)
{
}

void backlight_switch_enable()
{
}

void backlight_switch_disable()
{
}

void backlight_switch_invert()
{
}
