#ifndef ESPLORA_H
#define ESPLORA_H

class esploraTft {
public:
	void begin(void);

	void background(int r, int g, int b);

	void stroke(int r, int g, int b);
	void noStroke(void);

	void fill(int r, int g, int b);
	void noFill(void);

	void point(int x, int y);
	void line(int x1, int y1, int x2, int y2);
	void rect(int x, int y, int w, int h);
	void circle(int x, int y, int radius);

	int width(void);
	int height(void);

	void text(const char *str, int x, int y);
	void setTextSize(int size); // 1<=size<=5.
};

// Global EsploraTFT variable to emulate the esplora library
esploraTft EsploraTFT;

enum TemperatureScale {
	DEGREES_C,
	DEGREES_F
};

enum Axis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

enum Button {
	SWITCH_1,
	SWITCH_DOWN,
	SWITCH_2,
	SWITCH_LEFT,
	SWITCH_3,
	SWITCH_UP,
	SWITCH_4,
	SWITCH_RIGHT,
 
 	JOYSTICK_BASE,
	JOYSTICK_DOWN,
	JOYSTICK_LEFT,
	JOYSTICK_UP,
	JOYSTICK_RIGHT

};

enum DigitalOutput {
	LOW,
	HIGH
};

class esplora {
public:

	int readSlider();
	int readLightSensor();
	int readTemperature(TemperatureScale scale);
	int readMicrophone();
	int readJoystickSwitch();
	int readAccelerometer(Axis axis);
	DigitalOutput readButton(Button b);
	int readJoystickX();
	int readJoystickY();
	void writeRGB(int red, int green, int blue);
	void writeRed(int brightness);
	void writeGreen(int brightness);
	void writeBlue(int brightness);
	int readRed();
	int readGreen();
	int readBlue();
	void tone(int pin, unsigned int frequency, unsigned long duration);
	// A call to tone without a duration keeps the buzzer
	// going until noTone is called
	void tone(int pin, unsigned int frequency); 
	void noTone(int pin);
};

esplora Esplora;


#endif