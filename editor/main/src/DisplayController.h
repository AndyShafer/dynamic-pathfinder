#pragma once

#include "DisplayState.h"
#include "Display.h"
#include "SelectionController.h"

class Display;

class SelectionController;

class DisplayController {
public:
	DisplayController(DisplayState *state, Display *display);
	SelectionController *getSelectionController();
	void update();
	void run();
	void pause();
	void reset();
	void mouseMove(wxMouseEvent& evt);
	void leftDown(wxMouseEvent& evt);
	void leftUp(wxMouseEvent& evt);
	void rightDown(wxMouseEvent& evt);
	void rightUp(wxMouseEvent& evt);
	void deletePressed();
	void envLoaded();
private:
	DisplayState *displayState;
	SelectionController *selectionController;
	Display *display;
};
