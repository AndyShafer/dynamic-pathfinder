#pragma once

#include "DisplayState.h"
#include "Display.h"

class DisplayController {
public:
	DisplayController(DisplayState *state, Display *display);
	void update();
	void run();
	void pause();
	void reset();
private:
	DisplayState *displayState;
	Display *display;
};
