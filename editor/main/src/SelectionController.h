#pragma once

#include "DisplayState.h"
#include "SelectionState.h"
#include "ToolBar.h"

#define SELECTION_DISTANCE 5

class ToolBar;

class SelectionController {
public:
	SelectionController(DisplayState *ds);
	void setToolBar(ToolBar *tb);
	void leftDown(wxMouseEvent& evt);
	void leftUp(wxMouseEvent& evt);
	void mouseMove(wxMouseEvent& evt);
	void deletePressed();
	void checkToolBar();
	void envLoaded();
private:
	void updateToolBar();
	SelectionState *selectionState;
	DisplayState *displayState;
	ToolBar *toolBar = nullptr;
};
