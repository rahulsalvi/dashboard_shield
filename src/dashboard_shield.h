#ifndef DASHBOARD_SHIELD_H
#define DASHBOARD_SHIELD_H

#include <stdint.h>

#define DS_PIXELS_PER_CHANNEL 32
#define DS_PIXEL_CHANNELS 4
#define DS_RGB_LEDS 4

#define DS_RGB_OFF 0
#define DS_RGB_RED 1
#define DS_RGB_GRN 2
#define DS_RGB_BLU 3

namespace dashboard_shield {

    typedef struct pixel_t {
        uint8_t red;
        uint8_t grn;
        uint8_t blu;
        uint8_t wht;
    } pixel_t;

    typedef struct pixel_channel_t {
        pixel_t pixels[DS_PIXELS_PER_CHANNEL];
    } pixel_channel_t;

    typedef uint8_t rgb_led_t;

    typedef struct dashboard_t {
        pixel_channel_t pixel_channels[DS_PIXEL_CHANNELS];
        rgb_led_t       rgb_leds[DS_RGB_LEDS];
    } dashboard_t;

    typedef uint8_t button_state_t;

    void           begin();
    button_state_t update(dashboard_t& data);

    bool get_button(int index, button_state_t& data);

} // namespace dashboard_shield

#endif // DASHBOARD_SHIELD_H
