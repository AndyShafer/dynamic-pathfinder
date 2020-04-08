#include "DisplayController.h"

DisplayController::DisplayController(DisplayState *state, Display *display)
	: displayState(state), display(display) {
	selectionController = new SelectionController(displayState);
}

void DisplayController::update() {
	if(displayState->isRunning()) {
		displayState->incrementTime(1.0f);
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

void DisplayController::mouseMove(const wxPoint& position) {
	displayState->mouseMove(position);
	selectionController->mouseMove(position);
}

void DisplayController::leftDown(const wxPoint& position) {
	selectionController->leftDown(position);
}

void DisplayController::leftUp(const wxPoint& position) {
	selectionController->leftUp(position);
}

void DisplayController::rightDown(const wxPoint& position) {
	displayState->startPan(position);
}

void DisplayController::rightUp(const wxPoint& position) {
	displayState->stopPan();
}
