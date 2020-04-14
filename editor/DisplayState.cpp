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

float DisplayState::getTime() const {
	return time;
}

void DisplayState::resetTime() {
	time = 0;
}

void DisplayState::incrementTime(float dt) {
	time += dt;
	if(time < 0) time = 0;
	if(time > path.getArriveTime()) time = path.getArriveTime();
}

bool DisplayState::isRunning() const {
	return running;
}

void DisplayState::run() {
	if(pathDirty) {
		pathDirty = false;
		Solver solver(env);
		path = solver.solve();	
	}
	running = true;
}

void DisplayState::pause() {
	running = false;
}

void DisplayState::startPan(const wxPoint& mousePos) {
	panning = true;
	prevMousePos = mousePos;
}

void DisplayState::stopPan() {
	panning = false;
}

void DisplayState::mouseMove(const wxPoint& mousePos) {
	if(panning) {
		shiftX += mousePos.x - prevMousePos.x;
		shiftY += mousePos.y - prevMousePos.y;
	}
	prevMousePos = mousePos;
}

Environment * DisplayState::getEnvironment() {
	pathDirty = true;
	resetTime();
	pause();
	return env;
}

const Environment * DisplayState::getEnvironmentConst() {
	return env;
}

void DisplayState::setEnvironment(Environment *e) {
	pathDirty = true;
	resetTime();
	pause();
	env = e;
}

void DisplayState::render(wxDC& dc) {
	auto wallPen = *wxBLACK_PEN;
	wallPen.SetWidth(2);
	dc.SetPen(wallPen);
	for(Wall& w : env->walls) {
		dc.DrawLine(w.getStart().getPos(time).x, w.getStart().getPos(time).y,
				w.getEnd().getPos(time).x, w.getEnd().getPos(time).y);
	}
	dc.SetPen(wxNullPen);
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(env->start.x, env->start.y, 6);
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(env->end.x, env->end.y, 6);
	Vec2f pos = pathPosAt(time);
	dc.SetBrush(*wxBLUE_BRUSH);
	dc.DrawCircle(pos.x, pos.y, 3);
}

std::string DisplayState::getEnvFilePath() const {
	return envFilePath;
}

void DisplayState::setEnvFilePath(std::string filePath) {
	envFilePath = filePath;
}

Vec2f DisplayState::convertToEnvPos(const wxPoint& position) const {
	Vec2f envPos(position.x - shiftX, position.y - shiftY);
	return envPos;
}

Vec2f DisplayState::pathPosAt(float t) {
	if(t == 0) {
		return env->start;
	}
	if(pathDirty) {
		pathDirty = false;
		Solver solver(env);
		path = solver.solve();	
	}
	return path.getPos(t);
}
