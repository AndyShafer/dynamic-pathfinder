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
	DisplayController *getDisplayController();
	void update();
	void run();
	void pause();
	void reset();
	void displayMouseMove(wxMouseEvent& evt);
	void displayLeftDown(wxMouseEvent& evt);
	void displayLeftUp(wxMouseEvent& evt);
	void displayRightDown(wxMouseEvent& evt);
	void displayRightUp(wxMouseEvent& evt);
	void deletePressed();
	void envLoaded();
private:
	AppState *appState;
	DisplayController *displayController;
};
