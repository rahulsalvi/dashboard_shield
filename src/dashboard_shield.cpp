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

    void write_bits(uint8_t bank0, uint8_t bank1) {
        __disable_irq();
        GPIOD_PSOR = 0x0C;
        GPIOC_PSOR = 0x18;
        NOPN(0, 1, 7);
        GPIOD_PCOR = ((~(bank0 << 2)) & 0x0C);
        GPIOC_PCOR = ((~(bank1 << 3)) & 0x18);
        __enable_irq();
        NOPN(0, 4, 4);
        GPIOD_PCOR = 0x0C;
        GPIOC_PCOR = 0x18;
        NOPN(0, 0, 2);
    }

    void update_pixels(pixel_channel_t data[DS_PIXEL_CHANNELS]) {
        for (int i = 0; i < DS_PIXELS_PER_CHANNEL; i++) {
            uint8_t* pixel0 = (uint8_t*)&data[0].pixels[i];
            uint8_t* pixel1 = (uint8_t*)&data[1].pixels[i];
            uint8_t* pixel2 = (uint8_t*)&data[2].pixels[i];
            uint8_t* pixel3 = (uint8_t*)&data[3].pixels[i];
            for (int j = 0; j < 4; j++) { // 4 bytes per pixel
                uint8_t byte0 = *(pixel0 + j);
                uint8_t byte1 = *(pixel1 + j);
                uint8_t byte2 = *(pixel2 + j);
                uint8_t byte3 = *(pixel3 + j);
                for (int k = 7; k > -1; k--) { // 8 bits per byte
                    uint8_t bit0 = ((byte0 & (1 << k)) >> k);
                    uint8_t bit1 = ((byte1 & (1 << k)) >> k);
                    uint8_t bit2 = ((byte2 & (1 << k)) >> k);
                    uint8_t bit3 = ((byte3 & (1 << k)) >> k);

                    uint8_t bank0 = (bit1 << 1) | (bit0);
                    uint8_t bank1 = (bit3 << 1) | (bit2);

                    write_bits(bank0, bank1);
                }
            }
        }
        delayMicroseconds(10);
    }

    button_state_t read_buttons() { return GPIOB_PDIR & 0x0F; }

    bool get_button(int index, button_state_t& data) {
        switch (index) {
            case 0:
                return !(data & (1 << 2));
            case 1:
                return !(data & (1 << 3));
            case 2:
                return !(data & (1 << 0));
            case 3:
                return !(data & (1 << 1));
            default:
                return false;
        }
    }

    button_state_t update(dashboard_t& data) {
        update_rgb_leds(data.rgb_leds);
        update_pixels(data.pixel_channels);
        return read_buttons();
    }

    void begin() {
        PORTB_PCR0 = PCR_MUX(1) | PCR_PE | PCR_PS;
        PORTB_PCR1 = PCR_MUX(1) | PCR_PE | PCR_PS;
        PORTB_PCR2 = PCR_MUX(1) | PCR_PE | PCR_PS;
        PORTB_PCR3 = PCR_MUX(1) | PCR_PE | PCR_PS;

        PORTC_PCR0 = PCR_MUX(1);
        PORTC_PCR1 = PCR_MUX(1);
        PORTC_PCR2 = PCR_MUX(1);
        PORTC_PCR3 = PCR_MUX(1);
        PORTC_PCR4 = PCR_MUX(1);
        PORTC_PCR5 = PCR_MUX(1);
        PORTC_PCR6 = PCR_MUX(1);
        PORTC_PCR7 = PCR_MUX(1);

        PORTD_PCR0 = PCR_MUX(1);
        PORTD_PCR1 = PCR_MUX(1);
        PORTD_PCR2 = PCR_MUX(1);
        PORTD_PCR3 = PCR_MUX(1);
        PORTD_PCR4 = PCR_MUX(1);
        PORTD_PCR5 = PCR_MUX(1);
        PORTD_PCR6 = PCR_MUX(1);
        PORTD_PCR7 = PCR_MUX(1);

        GPIOB_PDDR &= 0xFFFFFFF0;
        GPIOC_PDDR |= 0x000000FF;
        GPIOD_PDDR |= 0x000000FF;
    }

} // namespace dashboard_shield
