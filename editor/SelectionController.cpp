#include "SelectionController.h"

SelectionController::SelectionController(DisplayState *ds)
	: displayState(ds) {}

void SelectionController::leftDown(const wxPoint& position) {
	Vec2f envPosition = displayState->convertToEnvPos(position);
	const Environment *env = displayState->getEnvironmentConst();
	if(displayState->isRunning()) {
		selectionType = None;
	} else {
		if((env->start - envPosition).mag() <= SELECTION_DISTANCE) {
			selectionType = Start;
		} else if((env->end - envPosition).mag() <= SELECTION_DISTANCE) {
			selectionType = End;
		} else {
			selectionType = None;
			for(int i = 0; i < env->walls.size(); i++) {
				if((env->walls[i].start.startPos - envPosition).mag() <= SELECTION_DISTANCE) {
					selectionType = WallEndpoint;
					wallIdx = i;
					wallEndpoint = 0;
					break;
				} else if((env->walls[i].end.startPos - envPosition).mag() <= SELECTION_DISTANCE) {
					selectionType = WallEndpoint;
					wallIdx = i;
					wallEndpoint = 1;
					break;
				}
			}
		}
	}
	prevPosition = envPosition;
	dragging = true;
}

void SelectionController::leftUp(const wxPoint& position) {
	dragging = false;	
}

void SelectionController::mouseMove(const wxPoint& position) {
	Vec2f envPosition = displayState->convertToEnvPos(position);
	if(displayState->isRunning()) {
		selectionType = None;
	} else {
		if(selectionType != None && dragging) {
			Environment *env = displayState->getEnvironment();
			switch(selectionType) {
			case Start:
				env->start += envPosition - prevPosition;
				break;
			case End:
				env->end += envPosition - prevPosition;
				break;
			case WallEndpoint:
				if(wallEndpoint == 0)
					env->walls[wallIdx].start.startPos += envPosition - prevPosition;
				else if(wallEndpoint == 1)
					env->walls[wallIdx].end.startPos += envPosition - prevPosition;
				break;
			}
		}
	}
	prevPosition = envPosition;
}
