#include "Display.h"

BEGIN_EVENT_TABLE(Display, wxPanel)

EVT_PAINT(Display::paintEvent)

END_EVENT_TABLE()

Display::Display(wxFrame* parent) :
wxPanel(parent)
{
}

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
    dc.DrawText(wxT("Testing"), 40, 60);
}

