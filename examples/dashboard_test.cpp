#include "WProgram.h"
#include "dashboard_shield.h"

using dashboard_shield::dashboard_t;

static dashboard_t dashboard;

void setup() {
    dashboard_shield::begin();

    dashboard.rgb_leds[0] = DS_RGB_RED;
    dashboard.rgb_leds[1] = DS_RGB_GRN;
    dashboard.rgb_leds[2] = DS_RGB_BLU;
    dashboard.rgb_leds[3] = DS_RGB_RED;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            dashboard.pixel_channels[i].pixels[j].red = 0;
            dashboard.pixel_channels[i].pixels[j].grn = 0;
            dashboard.pixel_channels[i].pixels[j].blu = 0;
            dashboard.pixel_channels[i].pixels[j].wht = 0;
        }
    }
}

static int counter = 0;

void loop() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            dashboard.pixel_channels[i].pixels[j].red = (counter == 0) * 255;
            dashboard.pixel_channels[i].pixels[j].grn = (counter == 1) * 255;
            dashboard.pixel_channels[i].pixels[j].blu = (counter == 2) * 255;
            dashboard.pixel_channels[i].pixels[j].wht = (counter == 3) * 255;
        }
    }
    dashboard_shield::update(dashboard);
    counter = (counter + 1 > 3) ? (0) : (counter + 1);
    delay(1000);
}

extern "C" int main(void) {
    setup();
    while (1) { loop(); }
}

