#pragma once

#include "Environment.h"

class DisplayState {
public:
	DisplayState();
	double getOriginX() const;
	double getOriginY() const;
	double getScaleX() const;
	double getScaleY() const;
	Environment * getEnvironment();
private:
	double originX = 0.0, originY = 0.0;
	double scaleX = 1.0, scaleY = 1.0;
	Environment env;
};
