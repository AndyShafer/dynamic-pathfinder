#include "DisplayState.h"

DisplayState::DisplayState() {
	env = new Environment(Vec2f(0, 0), Vec2f(100, 0), std::vector<Wall>(), 1, .1);
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
	return env;
}

const Environment * DisplayState::getEnvironmentConst() {
	pathDirty = true;
	return env;
}

void DisplayState::setEnvironment(Environment *e) {
	pathDirty = true;
	env = e;
}

void DisplayState::render(wxDC& dc, float t) {
	auto wallPen = *wxBLACK_PEN;
	wallPen.SetWidth(2);
	dc.SetPen(wallPen);
	for(Wall& w : env->walls) {
		dc.DrawLine(w.getStart().getPos(t).x, w.getStart().getPos(t).y,
				w.getEnd().getPos(t).x, w.getEnd().getPos(t).y);
	}
	dc.SetPen(wxNullPen);
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(env->start.x, env->start.y, 6);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(env->end.x, env->end.y, 6);
	Vec2f pos = pathPosAt(t);
	dc.SetBrush(*wxBLUE_BRUSH);
	dc.DrawCircle(pos.x, pos.y, 3);
}

std::string DisplayState::getEnvFilePath() const {
	return envFilePath;
}

void DisplayState::setEnvFilePath(std::string filePath) {
	envFilePath = filePath;
}

Vec2f DisplayState::pathPosAt(float t) {
	if(pathDirty) {
		pathDirty = false;
		Solver solver(env);
		path = solver.solve();	
	}
	return path.getPos(t);
}
