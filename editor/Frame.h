#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "AppState.h"

class Frame : public wxFrame {
	public:
		Frame(const wxString& title, const wxPoint& pos, const wxSize& size, AppState *state);
	private:
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);

		AppState *appState;

		wxDECLARE_EVENT_TABLE();
};
