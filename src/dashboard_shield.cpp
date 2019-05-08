#include "WProgram.h"

#include "dashboard_definitions.h"
#include "dashboard_shield.h"

namespace dashboard_shield {

    static const uint8_t rgb_led_mask_0[] = {RGB_LED_MASK_OFF,
                                             RGB_LED_0_MASK_RED,
                                             RGB_LED_0_MASK_GRN,
                                             RGB_LED_0_MASK_BLU};
    static const uint8_t rgb_led_mask_1[] = {RGB_LED_MASK_OFF,
                                             RGB_LED_1_MASK_RED,
                                             RGB_LED_1_MASK_GRN,
                                             RGB_LED_1_MASK_BLU};
    static const uint8_t rgb_led_mask_2[] = {RGB_LED_MASK_OFF,
                                             RGB_LED_2_MASK_RED,
                                             RGB_LED_2_MASK_GRN,
                                             RGB_LED_2_MASK_BLU};
    static const uint8_t rgb_led_mask_3[] = {RGB_LED_MASK_OFF,
                                             RGB_LED_3_MASK_RED,
                                             RGB_LED_3_MASK_GRN,
                                             RGB_LED_3_MASK_BLU};

    void update_rgb_leds(rgb_led_t data[DS_RGB_LEDS]) {
        GPIOD_PTOR = (GPIOD_PDOR & 0xFF) ^ (rgb_led_mask_0[data[0]] | rgb_led_mask_1[data[1]]);
        GPIOC_PTOR = (GPIOC_PDOR & 0xFF) ^ (rgb_led_mask_2[data[2]] | rgb_led_mask_3[data[3]]);
    }

    void write_bits_bank0_00() {
        __disable_irq();
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x0C;
        __enable_irq();
        NOP32;
    };
    void write_bits_bank0_01() {
        __disable_irq();
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x08;
        __enable_irq();
        NOP32;
        GPIOD_PCOR = 0x04;
        NOP32;
    };
    void write_bits_bank0_10() {
        __disable_irq();
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x04;
        __enable_irq();
        NOP32;
        GPIOD_PCOR = 0x08;
        NOP32;
    };
    void write_bits_bank0_11() {
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x0C;
        NOP32;
    };

    void latch_bits() { delayMicroseconds(6); };

    void update_pixels_bank0(pixel_channel_t data[2]) {
        for (int i = 0; i < DS_PIXELS_PER_CHANNEL; i++) {
            uint8_t* pixel0 = (uint8_t*)&data[0].pixels[i];
            uint8_t* pixel1 = (uint8_t*)&data[1].pixels[i];
            for (int j = 0; j < 4; j++) { // 4 bytes per pixel
                uint8_t byte0 = *(pixel0 + j);
                uint8_t byte1 = *(pixel1 + j);
                for (int k = 0; k < 8; k++) { // 8 bits per byte
                    uint8_t bit0 = byte0 & (1 << (7 - k));
                    uint8_t bit1 = byte1 & (1 << (7 - k));
                    if (!bit1 && !bit0) {
                        write_bits_bank0_00();
                    } else if (!bit1 && bit0) {
                        write_bits_bank0_01();
                    } else if (bit1 && !bit0) {
                        write_bits_bank0_10();
                    } else if (bit1 && bit0) {
                        write_bits_bank0_11();
                    }
                }
            }
        }
    }

    void update_pixels_bank1(pixel_channel_t data[2]) {}

    void update_pixels(pixel_channel_t data[DS_PIXEL_CHANNELS]) {
        update_pixels_bank0(data);
        update_pixels_bank1(data + 2);
        latch_bits();
    }

    button_state_t update(dashboard_t& data) {
        update_rgb_leds(data.rgb_leds);
        update_pixels(data.pixel_channels);
        return 0;
    }

    void begin() { return; }

} // namespace dashboard_shield
