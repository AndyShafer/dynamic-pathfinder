#include "DisplayController.h"

DisplayController::DisplayController(DisplayState *state, Display *display)
	: displayState(state), display(display) {
	selectionController = new SelectionController(displayState);
}

SelectionController *DisplayController::getSelectionController() {
	return selectionController;
}

void DisplayController::update() {
	if(displayState->isRunning()) {
		displayState->incrementTime(1.0f);
	} else {
		selectionController->checkToolBar();
	}
	display->Refresh();
	display->Update();
}

void DisplayController::run() {
	if(displayState->isRunning())
		displayState->resetTime();
	else
		displayState->run();
}

void DisplayController::pause() {
	displayState->pause();
}

void DisplayController::reset() {
	displayState->resetTime();
	pause();
}

void DisplayController::mouseMove(wxMouseEvent& evt) {
	displayState->mouseMove(evt.GetPosition());
	selectionController->mouseMove(evt);
}

void DisplayController::leftDown(wxMouseEvent& evt) {
	selectionController->leftDown(evt);
}

void DisplayController::leftUp(wxMouseEvent& evt) {
	selectionController->leftUp(evt);
}

void DisplayController::rightDown(wxMouseEvent& evt) {
	displayState->startPan(evt.GetPosition());
}

void DisplayController::rightUp(wxMouseEvent& evt) {
	displayState->stopPan();
}

void DisplayController::deletePressed() {
	selectionController->deletePressed();
}

void DisplayController::envLoaded() {
	selectionController->envLoaded();
}
