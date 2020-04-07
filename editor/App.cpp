#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	AppState *state = new AppState();

	appController = new AppController(state);
	Frame *frame = new Frame("Path Editor", wxPoint(50, 50), wxSize(450, 340), state, appController);
	display = new Display( (wxFrame*) frame, state->getDisplayState());
	timer = new UpdateTimer(appController);
	appController->setDisplay(display);

	sizer->Add(display, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);

	frame->Show(true);
	timer->start();
	return true;
}
