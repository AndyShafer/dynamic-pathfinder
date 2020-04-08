#include "Display.h"

BEGIN_EVENT_TABLE(Display, wxPanel)

EVT_PAINT(Display::paintEvent)
EVT_LEFT_DOWN(Display::onLeftDown)
EVT_LEFT_UP(Display::onLeftUp)
EVT_MOTION(Display::onMouseMove)

END_EVENT_TABLE()

Display::Display(wxFrame* parent, DisplayState *ds, AppController *ac) :
wxPanel(parent), displayState(ds), controller(ac) {}

void Display::paintEvent(wxPaintEvent & evt) {
	wxPaintDC dc(this);
	render(dc);
}

void Display::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

void Display::render(wxDC&  dc) {
	dc.SetLogicalOrigin(-displayState->getShiftX(), -displayState->getShiftY());
	dc.SetLogicalScale(displayState->getScaleX(), displayState->getScaleY());
	displayState->render(dc);
}

void Display::onLeftDown(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayLeftDown(mousePos);
}

void Display::onLeftUp(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayLeftUp(mousePos);
}

void Display::onMouseMove(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayMouseMove(mousePos);
}
