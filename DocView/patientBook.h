#pragma once

#include <wx/notebook.h>

class patientBook : public wxPanel
{
public:
	patientBook(wxWindow *parent);
	~patientBook(void);

	void add(std::string name, int age, std::string gender, int weight, std::string history, std::string ailment, int id, std::string connectstring);

	wxNotebook *nb;

};

