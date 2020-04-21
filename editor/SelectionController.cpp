#include "SelectionController.h"

SelectionController::SelectionController(DisplayState *ds)
	: displayState(ds) {
	selectionState = new SelectionState();
}

void SelectionController::setToolBar(ToolBar *tb) {
	toolBar = tb;
}

void SelectionController::leftDown(wxMouseEvent& evt) {
	wxPoint position = evt.GetPosition();
	Vec2f envPosition = displayState->convertToEnvPos(position);
	if(displayState->isRunning()) {
		selectionState->selectionType = None;
	} else if (evt.ShiftDown()) {
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
	updateToolBar();
	toolBar->update();
}

void SelectionController::leftUp(wxMouseEvent& evt) {
	selectionState->dragging = false;	
	toolBar->update();
}

void SelectionController::mouseMove(wxMouseEvent& evt) {
	wxPoint position = evt.GetPosition();
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
	toolBar->update();
}

void SelectionController::deletePressed() {
	if(selectionState->selectionType == WallEndpoint) {
		Environment *env = displayState->getEnvironment();
		env->walls.erase(env->walls.begin() + selectionState->wallIdx);
		selectionState->selectionType = None;
		updateToolBar();
	}
}

void SelectionController::checkToolBar() {
	if(toolBar) {
		BoundFloatCtrl *inputBox = toolBar->getFocusedInput();
		if(inputBox) {
			if(inputBox->updateBoundValue()) {
				displayState->setPathDirty(true);
			}
		}
	}
}

void SelectionController::updateToolBar() {
	switch(selectionState->selectionType) {
	case None:	
		toolBar->getXInput()->unbind();
		toolBar->getYInput()->unbind();
		toolBar->getVxInput()->unbind();
		toolBar->getVyInput()->unbind();
		break;
	case Start:
		toolBar->getXInput()->bind(&displayState->getEnvironment()->start.x);
		toolBar->getYInput()->bind(&displayState->getEnvironment()->start.y);
		toolBar->getVxInput()->unbind();
		toolBar->getVyInput()->unbind();
		break;
	case End:
		toolBar->getXInput()->bind(&displayState->getEnvironment()->end.x);
		toolBar->getYInput()->bind(&displayState->getEnvironment()->end.y);
		toolBar->getVxInput()->unbind();
		toolBar->getVyInput()->unbind();
		break;
	case WallEndpoint:
		Point *p;
		if(selectionState->wallEndpoint == 0)
			p = &displayState->getEnvironment()->walls[selectionState->wallIdx].start;
		else
			p = &displayState->getEnvironment()->walls[selectionState->wallIdx].end;

		toolBar->getXInput()->bind(&p->startPos.x);
		toolBar->getYInput()->bind(&p->startPos.y);
		toolBar->getVxInput()->bind(&p->velocity.x);
		toolBar->getVyInput()->bind(&p->velocity.y);
		break;
	}
}

void SelectionController::envLoaded() {
	selectionState->selectionType = None;
	updateToolBar();
	Environment *env = displayState->getEnvironment();
	toolBar->getSpeedInput()->bind(&env->speed);
	toolBar->getTimeStepInput()->bind(&env->timeStep);
}
