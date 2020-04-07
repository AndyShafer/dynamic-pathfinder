#pragma once

#include "AppState.h"
#include "DisplayController.h"
#include "Display.h"

class AppController {
public:
	AppController(AppState *state, Display *display);
	AppController(AppState *state);
	void setDisplay(Display *display);
	void update();
	void run();
	void pause();
	void reset();
private:
	AppState *appState;
	DisplayController *displayController;
};
