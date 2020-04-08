#pragma once

#include "AppState.h"
#include "DisplayController.h"

class Display;
class DisplayController;

class AppController {
public:
	AppController(AppState *state, Display *display);
	AppController(AppState *state);
	void setDisplay(Display *display);
	void update();
	void run();
	void pause();
	void reset();
	void displayMouseMove(const wxPoint& position);
	void displayLeftDown(const wxPoint& position);
	void displayLeftUp(const wxPoint& position);
private:
	AppState *appState;
	DisplayController *displayController;
};
