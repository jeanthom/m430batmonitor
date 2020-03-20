#include <stdint.h>
#include <msp430g2452.h>

static void hwInit(void) {
	/* Init clock */
	DCOCTL = 0;
	BCSCTL1 &= ~0xF;

	/* Init LED port */
	P2OUT = 0x00;
	P2REN = 0x00;
	P2SEL = 0x00;
	P2SEL2 = 0x00;
	P2DIR = 0x00;

	/* Init ADC */
	ADC10CTL0 = ADC10ON | SREF_1 | ADC10SR | REF2_5V | REFON | ENC | ADC10SHT_2;
	ADC10CTL1 = ADC10SSEL_0 | INCH0 | ADC10DIV2;

	/* Init timer A */
	TACTL = TAIE | TASSEL_2 | MC_2;
}

static uint16_t readAdcVoltage(void) {
	ADC10CTL0 |= ADC10SC;
	while (ADC10CTL1 & ADC10BUSY);
	return ADC10MEM;
}

static void updateBargraph(void) {
	const uint8_t dir_values[] = {
		0x01, 0x03, 0x07, 0x0F,
		0x1F, 0x3F, 0x7F, 0xFF
	};
	const uint16_t ref_values[] = {
		938, 954, 966, 977, 989, 1003, 1024
	};
	static uint16_t prev_adc = 1023;
	uint8_t i;
	uint16_t adc_voltage = readAdcVoltage();
	prev_adc = prev_adc/10+adc_voltage*9/10;

	for (i = 0; i < 8; i++) {
		if (prev_adc < ref_values[i]) {
			P2DIR = dir_values[i];
			return;
		}
	}
}

int main(void) {
	hwInit();
	_BIS_SR(GIE);

	while (1) {
		WDTCTL = WDTPW | WDTCNTCL;
	}

	return 0;
}

void __attribute__((interrupt(TIMER0_A1_VECTOR))) timerA_irq() {
	updateBargraph();
	TACTL &= ~TAIFG;
}
