#pragma once

#include "DisplayState.h"

#define SELECTION_DISTANCE 5

enum SelectionType { None, Start, End, WallEndpoint };

class SelectionController {
public:
	SelectionController(DisplayState *ds);
	void leftDown(const wxPoint& position);
	void leftUp(const wxPoint& position);
	void mouseMove(const wxPoint& position);
private:
	Vec2f prevPosition;
	SelectionType selectionType;
	int wallIdx;
	int wallEndpoint;
	bool dragging = false;
	DisplayState *displayState;
};
