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
class esploraTft EsploraTFT;

#endif