#pragma once

#include "AppState.h"
#include "DisplayController.h"
#include "Display.h"

class AppController {
public:
	AppController(AppState *state, Display *display);
	void update();
private:
	AppState *appState;
	DisplayController *displayController;
};
