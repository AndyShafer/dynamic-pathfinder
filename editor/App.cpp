#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	Frame *frame = new Frame("Path Editor", wxPoint(50, 50), wxSize(450, 340));

	display = new Display( (wxFrame*) frame );
	sizer->Add(display, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);

	frame->Show(true);
	return true;
}
