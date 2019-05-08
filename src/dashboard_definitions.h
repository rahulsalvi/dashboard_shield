#ifndef DASHBOARD_DEFINITIONS_H
#define DASHBOARD_DEFINITIONS_H

#define RGB_LED_MASK_OFF 0x00

#define RGB_LED_0_MASK_RED 0x40
#define RGB_LED_0_MASK_GRN 0x20
#define RGB_LED_0_MASK_BLU 0x02

#define RGB_LED_1_MASK_RED 0x10
#define RGB_LED_1_MASK_GRN 0x80
#define RGB_LED_1_MASK_BLU 0x01

#define RGB_LED_2_MASK_RED 0x40
#define RGB_LED_2_MASK_GRN 0x20
#define RGB_LED_2_MASK_BLU 0x10

#define RGB_LED_3_MASK_RED 0x20
#define RGB_LED_3_MASK_GRN 0x80
#define RGB_LED_3_MASK_BLU 0x40

#define NOP __asm("NOP\n");
#define NOP2                                                                                       \
    NOP;                                                                                           \
    NOP;
#define NOP4                                                                                       \
    NOP2;                                                                                          \
    NOP2;
#define NOP8                                                                                       \
    NOP4;                                                                                          \
    NOP4;
#define NOP16                                                                                      \
    NOP8;                                                                                          \
    NOP8;
#define NOP32                                                                                      \
    NOP16;                                                                                         \
    NOP16;

#endif // DASHBOARD_DEFINITIONS_H
