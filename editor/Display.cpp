#include "Display.h"

BEGIN_EVENT_TABLE(Display, wxPanel)

EVT_PAINT(Display::paintEvent)
EVT_LEFT_DOWN(Display::onLeftDown)
EVT_LEFT_UP(Display::onLeftUp)
EVT_RIGHT_DOWN(Display::onRightDown)
EVT_RIGHT_UP(Display::onRightUp)
EVT_MOTION(Display::onMouseMove)
EVT_KEY_DOWN(Display::onKeyDown)
EVT_KEY_UP(Display::onKeyUp)

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

void Display::onRightDown(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayRightDown(mousePos);
}

void Display::onRightUp(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayRightUp(mousePos);
}

void Display::onMouseMove(wxMouseEvent & evt) {
	wxPoint mousePos = evt.GetPosition();
	controller->displayMouseMove(mousePos);
}

void Display::onKeyDown(wxKeyEvent & evt) {
	int code = evt.GetKeyCode();
	if(code == WXK_SHIFT)
		controller->shiftDown();
	else if(code == WXK_BACK || code == WXK_DELETE)
		controller->deletePressed();
}

void Display::onKeyUp(wxKeyEvent & evt) {
	int code = evt.GetKeyCode();
	if(code == WXK_SHIFT)
		controller->shiftUp();
}
