#ifndef BACKLIGHT_H
#define BACKLIGHT_H

void backlight_init_ports(void);
void backlight_set(uint8_t level);
void backlight_switch_enable(void);
void backlight_switch_disable(void);

#endif // BACKLIGHT_H
