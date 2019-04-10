#include "stdafx.h"
#include <wx/wx.h>
#include "patientBook.h"
#include "patientInfo.h"


patientBook::patientBook(wxWindow *parent)
	: wxPanel(parent, wxID_ANY)
{
	nb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
	this->Show(true);
}

patientBook::~patientBook()
{
}

void
patientBook::add(std::string name, int age, std::string gender, int weight, std::string history, std::string ailment, int dbid, std::string connectstring)
{
	patientInfo *page = new patientInfo(this->nb, wxID_ANY, age, gender, weight, history, ailment, dbid, connectstring);
	nb->AddPage(page, name);
	nb->Layout();
}

