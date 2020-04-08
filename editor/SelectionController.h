#pragma once

#include "DisplayState.h"
#include "SelectionState.h"

#define SELECTION_DISTANCE 5

class SelectionController {
public:
	SelectionController(DisplayState *ds);
	void leftDown(const wxPoint& position);
	void leftUp(const wxPoint& position);
	void mouseMove(const wxPoint& position);
private:
	SelectionState *selectionState;
	DisplayState *displayState;
};
