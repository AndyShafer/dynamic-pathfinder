#include "DisplayState.h"

DisplayState::DisplayState() {
}

double DisplayState::getShiftX() const {
	return shiftX;
}

double DisplayState::getShiftY() const {
	return shiftY;
}

double DisplayState::getScaleX() const {
	return scaleX;
}

double DisplayState::getScaleY() const {
	return scaleY;
}

Environment * DisplayState::getEnvironment() {
	return &env;
}
