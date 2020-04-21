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

DisplayController *AppController::getDisplayController() {
	return displayController;
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

void AppController::displayMouseMove(wxMouseEvent& evt) {
	displayController->mouseMove(evt);
}

void AppController::displayLeftDown(wxMouseEvent& evt) {
	displayController->leftDown(evt);
}

void AppController::displayLeftUp(wxMouseEvent& evt) {
	displayController->leftUp(evt);
}

void AppController::displayRightDown(wxMouseEvent& evt) {
	displayController->rightDown(evt);
}

void AppController::displayRightUp(wxMouseEvent& evt) {
	displayController->rightUp(evt);
}

void AppController::deletePressed() {
	displayController->deletePressed();
}

void AppController::envLoaded() {
	displayController->envLoaded();
}
