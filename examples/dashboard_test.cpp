#include "WProgram.h"
#include "dashboard_shield.h"

using dashboard_shield::dashboard_t;

static dashboard_t dashboard;

void setup() {
    dashboard_shield::begin();
}

void loop() {
    dashboard_shield::update(dashboard);
}

extern "C" int main(void) {
    setup();
    while (1) { loop(); }
}

