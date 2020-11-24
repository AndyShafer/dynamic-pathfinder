#pragma once

#include "DisplayState.h"


class BoundFloatCtrl : public wxTextCtrl {
public:
	BoundFloatCtrl(DisplayState *state, wxWindow *parent, wxWindowID id, const wxString& value = wxEmptyString);
	void bind(float *var);
	void unbind();
	void update();

	bool updateBoundValue(/*wxCommandEvent& evt*/);
private:
	float *boundVar = nullptr;
	DisplayState *displayState;
	//wxDECLARE_EVENT_TABLE();
};

/*
enum {
	ID_TEXT = 40
};
*/
