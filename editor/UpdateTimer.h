#pragma once

#include "AppState.h"
#include "AppController.h"
#include <iostream>

class UpdateTimer : public wxTimer {
public:
	UpdateTimer(AppController *controller);
	void Notify();
	void start();
private:
	AppController *appController;
};

