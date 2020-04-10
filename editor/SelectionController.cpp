#include "SelectionController.h"

SelectionController::SelectionController(DisplayState *ds)
	: displayState(ds) {
	selectionState = new SelectionState();
}

void SelectionController::leftDown(const wxPoint& position) {
	Vec2f envPosition = displayState->convertToEnvPos(position);
	if(displayState->isRunning()) {
		selectionState->selectionType = None;
	} else if (selectionState->shifted) {
		Environment *env = displayState->getEnvironment();
		env->walls.push_back(Wall(Point(envPosition, Vec2f(0, 0)),
					Point(envPosition, Vec2f(0, 0))));
		selectionState->selectionType = WallEndpoint;
		selectionState->wallIdx = env->walls.size()-1;
		selectionState->wallEndpoint = 1;
	} else {
		const Environment *env = displayState->getEnvironmentConst();
		if((env->start - envPosition).mag() <= SELECTION_DISTANCE) {
			selectionState->selectionType = Start;
		} else if((env->end - envPosition).mag() <= SELECTION_DISTANCE) {
			selectionState->selectionType = End;
		} else {
			selectionState->selectionType = None;
			for(int i = 0; i < env->walls.size(); i++) {
				if((env->walls[i].start.startPos - envPosition).mag() <= SELECTION_DISTANCE) {
					selectionState->selectionType = WallEndpoint;
					selectionState->wallIdx = i;
					selectionState->wallEndpoint = 0;
					break;
				} else if((env->walls[i].end.startPos - envPosition).mag() <= SELECTION_DISTANCE) {
					selectionState->selectionType = WallEndpoint;
					selectionState->wallIdx = i;
					selectionState->wallEndpoint = 1;
					break;
				}
			}
		}
	}
	selectionState->prevPosition = envPosition;
	selectionState->dragging = true;
}

void SelectionController::leftUp(const wxPoint& position) {
	selectionState->dragging = false;	
}

void SelectionController::mouseMove(const wxPoint& position) {
	Vec2f envPosition = displayState->convertToEnvPos(position);
	if(displayState->isRunning()) {
		selectionState->selectionType = None;
	} else {
		if(selectionState->selectionType != None && selectionState->dragging) {
			Environment *env = displayState->getEnvironment();
			switch(selectionState->selectionType) {
			case Start:
				env->start += envPosition - selectionState->prevPosition;
				break;
			case End:
				env->end += envPosition - selectionState->prevPosition;
				break;
			case WallEndpoint:
				if(selectionState->wallEndpoint == 0)
					env->walls[selectionState->wallIdx].start.startPos +=
						envPosition - selectionState->prevPosition;
				else if(selectionState->wallEndpoint == 1)
					env->walls[selectionState->wallIdx].end.startPos +=
						envPosition - selectionState->prevPosition;
				break;
			}
		}
	}
	selectionState->prevPosition = envPosition;
}

void SelectionController::shiftDown() {
	selectionState->shifted = true;
}

void SelectionController::shiftUp() {
	selectionState->shifted = false;
}
