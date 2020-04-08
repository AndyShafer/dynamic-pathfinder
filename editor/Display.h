#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "DisplayState.h"
#include "AppController.h"

class AppController;

class Display : public wxPanel
{
public:
	Display(wxFrame* parent, DisplayState *ds, AppController *ac);
	
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	
	void render(wxDC& dc);

	void onLeftDown(wxMouseEvent & evt);
	void onLeftUp(wxMouseEvent & evt);
	void onRightDown(wxMouseEvent & evt);
	void onRightUp(wxMouseEvent & evt);
	void onMouseMove(wxMouseEvent & evt);
	
	DECLARE_EVENT_TABLE()
private:
	DisplayState *displayState;
	AppController *controller;
};
