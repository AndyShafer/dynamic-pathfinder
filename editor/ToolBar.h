#pragma once

#include "Frame.h"
#include "BoundFloatCtrl.h"

class Frame;
class SelectionController;

class ToolBar {
public:
	ToolBar(Frame *frame, AppState *state);
	wxToolBar *getToolBar();
	void update();
	BoundFloatCtrl *getFocusedInput();
	BoundFloatCtrl *getXInput();
	BoundFloatCtrl *getYInput();
	BoundFloatCtrl *getVxInput();
	BoundFloatCtrl *getVyInput();
	BoundFloatCtrl *getSpeedInput();
	BoundFloatCtrl *getTimeStepInput();
private:
	wxToolBar *toolBar;
	BoundFloatCtrl *xInput;
	BoundFloatCtrl *yInput;
	BoundFloatCtrl *vxInput;
	BoundFloatCtrl *vyInput;
	BoundFloatCtrl *speedInput;
	BoundFloatCtrl *timeStepInput;
};
