#include "BoundFloatCtrl.h"
#include <iostream>

BoundFloatCtrl::BoundFloatCtrl(DisplayState *state, wxWindow *parent, wxWindowID id, const wxString& value)
	: displayState(state), wxTextCtrl(parent, id, value, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER) {
	SetEditable(false);
}

/*
wxBEGIN_EVENT_TABLE(BoundFloatCtrl, wxTextCtrl)
	EVT_TEXT(ID_TEXT, BoundFloatCtrl::onTextChange)
wxEND_EVENT_TABLE()
*/

void BoundFloatCtrl::bind(float *var) {
	boundVar = var;
	SetValue(wxString::Format(wxT("%f"), *boundVar));
	SetEditable(true);
}

void BoundFloatCtrl::unbind() {
	SetValue(wxEmptyString);
	SetEditable(false);
}

void BoundFloatCtrl::update() {
	if(boundVar) {
		SetValue(wxString::Format(wxT("%f"), *boundVar));
	}
}

// TODO: Trigger this using EVT_TEXT event
bool BoundFloatCtrl::updateBoundValue(/*wxCommandEvent & evt*/) {
	double val;
	if(GetValue().ToDouble(&val) && boundVar && *boundVar != (float)val) {
		*boundVar = (float)val;
		return true;
	}
	return false;
}
