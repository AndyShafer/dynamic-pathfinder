#pragma once

#include "AppState.h"
#include "AppController.h"

class UpdateTimer : public wxTimer {
public:
	UpdateTimer(AppController *controller);
	void Notify();
	void start();
private:
	AppController *appController;
};

