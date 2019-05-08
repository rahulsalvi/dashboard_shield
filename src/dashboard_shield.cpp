#include "WProgram.h"

#include "dashboard_shield.h"

#define NOP __asm("NOP\n");
#define NOP4                                                                                       \
    NOP;                                                                                           \
    NOP;                                                                                           \
    NOP;                                                                                           \
    NOP;
#define NOP8                                                                                       \
    NOP4;                                                                                          \
    NOP4;
#define NOP16                                                                                      \
    NOP8;                                                                                          \
    NOP8;
#define NOP32                                                                                      \
    NOP16;                                                                                         \
    NOP16;

namespace dashboard_shield {

    static uint8_t rgb_led_mask_0[4] = {0x00, 0x40, 0x20, 0x02};
    static uint8_t rgb_led_mask_1[4] = {0x00, 0x10, 0x80, 0x01};
    static uint8_t rgb_led_mask_2[4] = {0x00, 0x40, 0x20, 0x10};
    static uint8_t rgb_led_mask_3[4] = {0x00, 0x20, 0x80, 0x40};

    void update_rgb_leds(rgb_led_t data[DS_RGB_LEDS]) {
        GPIOD_PTOR = (GPIOD_PDOR & 0xFF) ^ (rgb_led_mask_0[data[0]] | rgb_led_mask_1[data[1]]);
        GPIOC_PTOR = (GPIOC_PDOR & 0xFF) ^ (rgb_led_mask_2[data[2]] | rgb_led_mask_3[data[3]]);
    }

    void write_bits_bank0_00() {
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x0C;
        NOP32;
    };
    void write_bits_bank0_01() {
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x08;
        NOP32;
        GPIOD_PCOR = 0x04;
        NOP32;
    };
    void write_bits_bank0_10() {
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x08;
        NOP32;
        GPIOD_PCOR = 0x04;
        NOP32;
    };
    void write_bits_bank0_11() {
        GPIOD_PSOR = 0x0C;
        NOP32;
        GPIOD_PCOR = 0x0C;
        NOP32;
    };

    void latch_bits_bank0() { delayMicroseconds(6); };

    void update_pixels_bank0(pixel_channel_t data[2]) {
        for (int i = 0; i < 32; i++) {
            uint8_t* pixel0 = (uint8_t*)&data[0].pixels[i];
            uint8_t* pixel1 = (uint8_t*)&data[1].pixels[i];
            for (int j = 0; j < 4; j++) {
                uint8_t byte0 = *(pixel0 + j);
                uint8_t byte1 = *(pixel1 + j);
                for (int k = 0; k < 8; k++) {
                    uint8_t bit0 = byte0 && (1 << (7 - k));
                    uint8_t bit1 = byte1 && (1 << (7 - k));
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
        latch_bits_bank0();
    }
    void update_pixels_bank1(pixel_channel_t data[2]) {}

    void update_pixels(pixel_channel_t data[DS_PIXEL_CHANNELS]) {
        update_pixels_bank0(data);
        update_pixels_bank1(data + 2);
    }

    button_state_t update(dashboard_t& data) {
        update_rgb_leds(data.rgb_leds);
        update_pixels(data.pixel_channels);
        return 0;
    }

} // namespace dashboard_shield
