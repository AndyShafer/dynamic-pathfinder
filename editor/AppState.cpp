#include "AppState.h"

AppState::AppState() {
	displayState = new DisplayState();
}

DisplayState * AppState::getDisplayState() {
	return displayState;
}
