#include "DisplayState.h"

DisplayState::DisplayState() {
}

double DisplayState::getOriginX() const {
	return originX;
}

double DisplayState::getOriginY() const {
	return originY;
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
