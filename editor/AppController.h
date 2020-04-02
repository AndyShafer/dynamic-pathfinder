#pragma once

#include "AppState.h"
#include "DisplayController.h"

class AppController {
public:
	AppController(AppState *state);
	void update();
private:
	AppState *appState;
	DisplayController *displayController;
};
