#include "AppController.h"

AppController::AppController(AppState *state)
	: appState(state) {
	displayController = new DisplayController(state->getDisplayState());
}

void AppController::update() {
	displayController->update();
}
