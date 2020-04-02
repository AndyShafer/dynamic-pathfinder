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
