#include "WProgram.h"

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWriteFast(13, HIGH);
    delay(1000);
    digitalWriteFast(13, LOW);
    delay(1000);
}

extern "C" int main(void) {
    setup();
    while (1) { loop(); }
}
