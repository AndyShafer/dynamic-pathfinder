#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	Frame *frame = new Frame("Path Editor", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}
