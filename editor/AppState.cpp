#include "AppState.h"

AppState::AppState() {}

DisplayState * AppState::getDisplayState() {
	return &displayState;
}
