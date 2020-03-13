#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Frame : public wxFrame {
	public:
		Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
	private:
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();
};


