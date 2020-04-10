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

void AppController::displayMouseMove(const wxPoint& position) {
	displayController->mouseMove(position);
}

void AppController::displayLeftDown(const wxPoint& position) {
	displayController->leftDown(position);
}

void AppController::displayLeftUp(const wxPoint& position) {
	displayController->leftUp(position);
}

void AppController::displayRightDown(const wxPoint& position) {
	displayController->rightDown(position);
}

void AppController::displayRightUp(const wxPoint& position) {
	displayController->rightUp(position);
}

void AppController::shiftDown() {
	displayController->shiftDown();
}

void AppController::shiftUp() {
	displayController->shiftUp();
}
