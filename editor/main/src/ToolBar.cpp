#include "ToolBar.h"

ToolBar::ToolBar(Frame *frame, AppState *appState) {
	toolBar = frame->CreateToolBar();
	wxStaticText *xLabel = new wxStaticText(toolBar, 40, "x:");
	xInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	wxStaticText *yLabel = new wxStaticText(toolBar, -1, "y:");
	yInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	wxStaticText *vxLabel = new wxStaticText(toolBar, -1, "vx:");
	vxInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	wxStaticText *vyLabel = new wxStaticText(toolBar, -1, "vy:");
	vyInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	wxStaticText *speedLabel = new wxStaticText(toolBar, -1, "speed:");
	speedInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	wxStaticText *timeStepLabel = new wxStaticText(toolBar, -1, "time step:");
	timeStepInput = new BoundFloatCtrl(appState->getDisplayState(), toolBar, -1);
	speedInput->bind(&appState->getDisplayState()->getEnvironment()->speed);
	timeStepInput->bind(&appState->getDisplayState()->getEnvironment()->timeStep);

	toolBar->AddControl(xLabel);
	toolBar->AddControl(xInput);
	toolBar->AddControl(yLabel);
	toolBar->AddControl(yInput);
	toolBar->AddControl(vxLabel);
	toolBar->AddControl(vxInput);
	toolBar->AddControl(vyLabel);
	toolBar->AddControl(vyInput);
	toolBar->AddControl(speedLabel);
	toolBar->AddControl(speedInput);
	toolBar->AddControl(timeStepLabel);
	toolBar->AddControl(timeStepInput);
}

wxToolBar *ToolBar::getToolBar() {
	return toolBar;
}

void ToolBar::update() {
	xInput->update();
	yInput->update();
	vxInput->update();
	vyInput->update();
	speedInput->update();
	timeStepInput->update();
}

BoundFloatCtrl *ToolBar::getFocusedInput() {
	if(xInput->HasFocus()) return xInput;
	if(yInput->HasFocus()) return yInput;
	if(vxInput->HasFocus()) return vxInput;
	if(vyInput->HasFocus()) return vyInput;
	if(speedInput->HasFocus()) return speedInput;
	if(timeStepInput->HasFocus()) return timeStepInput;
	return nullptr;
}

BoundFloatCtrl *ToolBar::getXInput() {
	return xInput;
}

BoundFloatCtrl *ToolBar::getYInput() {
	return yInput;
}

BoundFloatCtrl *ToolBar::getVxInput() {
	return vxInput;
}

BoundFloatCtrl *ToolBar::getVyInput() {
	return vyInput;
}

BoundFloatCtrl *ToolBar::getSpeedInput() {
	return speedInput;
}

BoundFloatCtrl *ToolBar::getTimeStepInput() {
	return timeStepInput;
}
