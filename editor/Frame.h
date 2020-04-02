#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "AppState.h"
#include "AppController.h"
#include "UpdateTimer.h"

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
		AppController *appController;
		UpdateTimer *timer;

		wxDECLARE_EVENT_TABLE();
};
