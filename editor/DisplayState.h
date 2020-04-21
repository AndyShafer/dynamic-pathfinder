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
	float getTime() const;
	void resetTime();
	void incrementTime(float dt);
	bool isRunning() const;
	void run();
	void pause();
	void startPan(const wxPoint& mousePos);
	void stopPan();
	void mouseMove(const wxPoint& mousePos);
	Environment * getEnvironment(); // Using this will cause the path to be recalculated.
	const Environment * getEnvironmentConst(); // Will not cause path to be recalculated.
	void setEnvironment(Environment *e);
	void setPathDirty(bool b);
	void render(wxDC& dc);
	std::string getEnvFilePath() const;
	void setEnvFilePath(std::string filePath);
	Vec2f convertToEnvPos(const wxPoint& position) const;
private:
	std::string envFilePath = "";
	Vec2f pathPosAt(float t);
	Path path;
	bool pathDirty = true;
	bool running = false;
	bool panning = false;
	wxPoint prevMousePos;
	float time = 0;
	double shiftX = 50, shiftY = 50;
	double scaleX = 1.0, scaleY = 1.0;
	Environment * env;
};
