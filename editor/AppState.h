#pragma once

#include "DisplayState.h"

class AppState {
public:
	AppState();
	DisplayState * getDisplayState();
private:
	DisplayState displayState;
};
