#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "DisplayState.h"

class Display : public wxPanel
{
public:
	Display(wxFrame* parent, DisplayState *ds);
	
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	
	void render(wxDC& dc);
	
	DECLARE_EVENT_TABLE()
private:
	DisplayState *displayState;
};
