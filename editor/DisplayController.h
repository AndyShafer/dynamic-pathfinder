#pragma once

#include "DisplayState.h"

class DisplayController {
public:
	DisplayController(DisplayState *state);
	void update();
private:
	DisplayState *displayState;
};
