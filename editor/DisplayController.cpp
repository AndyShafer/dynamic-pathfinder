#include "DisplayController.h"

DisplayController::DisplayController(DisplayState *state, Display *display)
	: displayState(state), display(display) {}

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
