#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "AppState.h"
#include "AppController.h"
#include "UpdateTimer.h"
#include "ToolBar.h"

class ToolBar;
class AppController;

class Frame : public wxFrame {
	public:
		Frame(const wxString& title, const wxPoint& pos, const wxSize& size, AppState *state,
				AppController *controller);
		ToolBar *getToolBar();
	private:
		ToolBar *toolBar;
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);
		void OnRun(wxCommandEvent& event);
		void OnPause(wxCommandEvent& event);
		void OnReset(wxCommandEvent& event);

		AppState *appState;
		AppController *appController;

		wxDECLARE_EVENT_TABLE();
};

enum {
	ID_RUN= 1,
	ID_PAUSE= 2,
	ID_RESET= 3
};
