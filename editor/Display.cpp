#include "Display.h"

BEGIN_EVENT_TABLE(Display, wxPanel)

EVT_PAINT(Display::paintEvent)

END_EVENT_TABLE()

Display::Display(wxFrame* parent, DisplayState *ds) :
wxPanel(parent), displayState(ds) {}

void Display::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void Display::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void Display::render(wxDC&  dc)
{
	dc.SetLogicalOrigin(-displayState->getShiftX(), -displayState->getShiftY());
	dc.SetLogicalScale(displayState->getScaleX(), displayState->getScaleY());
	displayState->render(dc, 0);
}

