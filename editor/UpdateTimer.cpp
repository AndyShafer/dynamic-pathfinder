#include "UpdateTimer.h"

UpdateTimer::UpdateTimer(AppController *controller)
	: wxTimer(), appController(controller) {}

void UpdateTimer::Notify() {
	appController->update();
}

void UpdateTimer::start() {
	wxTimer::Start(10);
}
