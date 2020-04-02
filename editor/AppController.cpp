#include "AppController.h"

AppController::AppController(AppState *state, Display *display)
	: appState(state) {
	displayController = new DisplayController(state->getDisplayState(), display);
}

void AppController::update() {
	displayController->update();
}
