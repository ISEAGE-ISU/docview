#pragma once
#include <wx/wx.h>

enum {
	NAMEID,
	HISTORYID,
	AILMENTID,
	GENDERID,
	WEIGHTID,
	AGEID,
	SAVEID,
};

class patientInfo :
	public wxPanel
{
public:
	patientInfo(wxWindow *parent, int id, int age, std::string gender, int weight, std::string history, std::string ailment, int dbid);
	~patientInfo();

	int dbid;
	wxGridSizer *grid;

	wxTextCtrl *name, *history, *ailment, *gender, *age, *weight;

	void push(std::string label, wxTextCtrl*);
	void save(wxCommandEvent&);
};

