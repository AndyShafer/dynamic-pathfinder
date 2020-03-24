#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../src/Environment.h"
#include "../src/Wall.h"
#include "../src/Point.h"
#include "../src/Path.h"
#include "../src/Solver.h"

class DisplayState {
public:
	DisplayState();
	double getShiftX() const;
	double getShiftY() const;
	double getScaleX() const;
	double getScaleY() const;
	Environment * getEnvironment(); // Using this will cause the path to be recalculated.
	const Environment * getEnvironmentConst(); // Will not cause path to be recalculated.
	void render(wxDC& dc, float t);
private:
	Vec2f pathPosAt(float t);
	Path path;
	bool pathDirty = true;
	double shiftX = 50, shiftY = 50;
	double scaleX = 1.0, scaleY = 1.0;
	Environment * env;
};
