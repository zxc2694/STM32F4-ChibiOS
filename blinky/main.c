/*
 * A Simple LED blinking example
 */

#include "ch.h"
#include "hal.h"

int main(void) {

    halInit();
    chSysInit();

    palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_OUTPUT_PUSHPULL);

    while (TRUE) {
        palTogglePad(GPIOD, GPIOD_LED3);
        chThdSleepMilliseconds(500);
    }

    return 0;
}
