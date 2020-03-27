#include "Frame.h"

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size, AppState *state)
	: wxFrame(NULL, wxID_ANY, title, pos, size), appState(state) {
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_SAVE);
	menuFile->Append(wxID_SAVEAS, "Save As");
	menuFile->Append(wxID_OPEN);
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );
	SetMenuBar( menuBar );
	CreateStatusBar();
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
	EVT_MENU(wxID_ABOUT, Frame::OnAbout)
	EVT_MENU(wxID_SAVE, Frame::OnSave)
	EVT_MENU(wxID_SAVEAS, Frame::OnSaveAs)
	EVT_MENU(wxID_OPEN, Frame::OnOpen)
wxEND_EVENT_TABLE()

void Frame::OnExit(wxCommandEvent& event) {
	Close( true );
}
void Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox( "", "", wxOK | wxICON_INFORMATION );
}

void Frame::OnSave(wxCommandEvent& event) {
	DisplayState *displayState = appState->getDisplayState();
	if(displayState->getEnvironmentConst() == nullptr) return;
	if(displayState->getEnvFilePath() == "") {
		wxFileDialog saveFileDialog(this, "Save file", "", "",
				"", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		if(saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		displayState->setEnvFilePath(saveFileDialog.GetPath().ToStdString());
	}
	displayState->getEnvironmentConst()->save(displayState->getEnvFilePath().c_str());
}

void Frame::OnSaveAs(wxCommandEvent& event) {
	DisplayState *displayState = appState->getDisplayState();
	if(displayState->getEnvironmentConst() == nullptr) return;
	wxFileDialog saveFileDialog(this, "Save file", "", "",
		"", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if(saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	displayState->setEnvFilePath(saveFileDialog.GetPath().ToStdString());
	displayState->getEnvironmentConst()->save(displayState->getEnvFilePath().c_str());
}

void Frame::OnOpen(wxCommandEvent& event) {
	DisplayState *displayState = appState->getDisplayState();
	wxFileDialog openFileDialog(this, "Open file", "", "",
			"", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if(openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	displayState->setEnvironment(Environment::load(openFileDialog.GetPath().ToStdString().c_str()));
	displayState->setEnvFilePath(openFileDialog.GetPath().ToStdString());
}
