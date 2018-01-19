// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL

#include "SSD1306.h"

int reading = 100;

SSD1306  display(0x3c, D3, D5);

void getVal() {
	reading += analogRead(A0);
}

void setup() {
	Serial.begin(115200);

	display.init();
	display.flipScreenVertically();;

}

void drawValue() {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_16);
		display.drawString(0, 10, "Reading: ");
		display.setFont(ArialMT_Plain_24);
		display.drawString(0, 30, String(reading));
		display.display();
}
int count = 0;
void loop() {
	getVal();
	drawValue();
}
