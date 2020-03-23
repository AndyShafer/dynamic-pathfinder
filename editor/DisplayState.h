#pragma once

#include "Environment.h"

class DisplayState {
public:
	DisplayState();
	double getShiftX() const;
	double getShiftY() const;
	double getScaleX() const;
	double getScaleY() const;
	Environment * getEnvironment();
private:
	double shiftX = 50, shiftY = 50;
	double scaleX = 1.0, scaleY = 1.0;
	Environment env;
};
