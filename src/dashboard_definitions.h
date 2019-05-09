#ifndef DASHBOARD_DEFINITIONS_H
#define DASHBOARD_DEFINITIONS_H

#define PCR_MUX(x) (x << 8)

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

// clang-format off
#define NOP __asm("NOP\n");

#define REP0(x)
#define REP1(x)  x
#define REP2(x)  REP1(x) x
#define REP3(x)  REP2(x) x
#define REP4(x)  REP3(x) x
#define REP5(x)  REP4(x) x
#define REP6(x)  REP5(x) x
#define REP7(x)  REP6(x) x
#define REP8(x)  REP7(x) x
#define REP9(x)  REP8(x) x
#define REP10(x) REP9(x) x

#define REP(hundreds,tens,ones,x) \
    REP##hundreds(REP10(REP10(x))) \
    REP##tens(REP10(x)) \
    REP##ones(x)

#define NOPN(hundreds,tens,ones) REP(hundreds,tens,ones,NOP)
// clang-format on

#endif // DASHBOARD_DEFINITIONS_H
