#include "AppController.h"

AppController::AppController(AppState *state, Display *display)
	: appState(state) {
	displayController = new DisplayController(state->getDisplayState(), display);
}

AppController::AppController(AppState *state)
	: appState(state) {}

void AppController::setDisplay(Display *display) {
	delete displayController;
	displayController = new DisplayController(appState->getDisplayState(), display);
}

void AppController::update() {
	displayController->update();
}

void AppController::run() {
	displayController->run();
}

void AppController::pause() {
	displayController->pause();
}

void AppController::reset() {
	displayController->reset();
}
