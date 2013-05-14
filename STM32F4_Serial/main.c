/* Basic USART example for printing */

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#define PrintS2(x)    SendString(&SD2, x);	/* for example 4 */
static void SendString(SerialDriver *sdp, const char *string); /* for example 3 */
static void print(char *p);
static void println(char *p);
static void printn(uint32_t n);


static SerialConfig sd2cfg = {
   115200,									/* 115200 baud rate */
   0,
   USART_CR2_STOP1_BITS | USART_CR2_LINEN,
   0
};

int main(void) {

	halInit();
	chSysInit();

	/*
	* Activates the serial driver 2 using the driver sd2cfg configuration.
	* PA2(TX) and PA3(RX) are routed to USART2.
	* PAL_MODE_ALTERNATE is the value that you pass from Table 8. Alternate function mapping
	* in DM00037051 - STM32F405xx/STM32F407xx Datasheet
	*/
	sdStart(&SD2, &sd2cfg);
	// sdStart(&SD2, NULL); /* for default configuration */
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

	while (TRUE){
		static uint8_t temp;
		temp = 7;
	    if (palReadPad(GPIOA, GPIOA_BUTTON))
	    	sdWrite(&SD2, (uint8_t *)"Button Pressed!\r\n", 17);
	    sdWrite(&SD2, (uint8_t *)"Example: 1\r\n", 12);
		chprintf((BaseSequentialStream *)&SD2, "Example: %d\r\n", 2);
		SendString(&SD2, "Example: 3\r\n");
		PrintS2("Example: 4\r\n");
		print("Example: 5\r\n");
		println("Example 6");
		print("Example: "); printn(temp); print("\r\n");
		chThdSleepMilliseconds(500); /* Sleep the processor for 500 milliseconds */
	}
}

static void print(char *p) {

  while (*p) {
    chSequentialStreamPut(&SD2, *p++);
  }
}

static void println(char *p) {

  while (*p) {
    chSequentialStreamPut(&SD2, *p++);
  }
  chSequentialStreamWrite(&SD2, (uint8_t *)"\r\n", 2);
}

static void printn(uint32_t n) {
  char buf[16], *p;

  if (!n)
    chSequentialStreamPut(&SD2, '0');
  else {
    p = buf;
    while (n)
      *p++ = (n % 10) + '0', n /= 10;
    while (p > buf)
      chSequentialStreamPut(&SD2, *--p);
  }
}

/* for example 3 */
static void SendString(SerialDriver *sdp, const char *string){
  uint8_t i;
  for (i=0; string[i]!='\0'; i++)
    sdPut(sdp, string[i]);
}

