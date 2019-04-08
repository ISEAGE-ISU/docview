#include "stdafx.h"
#include "DocFrame.h"
#include "patientInfo.h"


patientInfo::patientInfo(wxWindow *parent, int id, int age, 
	std::string gender, int weight, std::string history, 
	std::string ailment, int dbid)
	: wxPanel(parent, id)
{
	this->SetBackgroundColour(wxColor(255, 45, 0));
	this->grid = new wxGridSizer(1);

	this->age = new wxTextCtrl(this, AGEID, std::to_string(age));
	this->weight = new wxTextCtrl(this, WEIGHTID, std::to_string(weight));
	this->gender = new wxTextCtrl(this, GENDERID, gender);
	this->history = new wxTextCtrl(this, HISTORYID, history);
	this->ailment = new wxTextCtrl(this, AILMENTID, ailment);

	this->push("Age", this->age);
	this->push("Weight", this->weight);
	this->push("Gender", this->gender);
	this->push("history", this->history);
	this->push("ailment", this->ailment);

	this->grid->Add(new wxButton(this, 100+this->dbid, "save"));
	Bind(wxEVT_BUTTON, &patientInfo::save, this, 100 + this->dbid);
	this->dbid = dbid;

	SetSizerAndFit(this->grid);
	this->Layout();
}


patientInfo::~patientInfo()
{
}

void
patientInfo::push(std::string label, wxTextCtrl *entry)
{
	wxStaticText *t = new wxStaticText(this, wxID_ANY, label);
	t->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _("Comic Sans MS")));
	t->SetForegroundColour(wxColor(0, 255, 20));
	wxBoxSizer *b = new wxBoxSizer(wxHORIZONTAL);
	b->Add(t);
	b->AddSpacer(15);
	b->Add(entry);
	this->grid->Add(b);
}

void
patientInfo::save(wxCommandEvent&)
{
	try {
		const auto db = tao::pq::connection::create("user=postgres password=chris host=192.168.0.20 dbname=hospitalsite");
		db->execute("UPDATE hospitalsite_profile SET age = $1, gender = $2, weight = $3, history = $4, current_ailment = $5 WHERE id = $6",
			this->age->GetValue().ToStdString(), this->gender->GetValue().ToStdString(), this->weight->GetValue().ToStdString(), this->history->GetValue().ToStdString(), this->ailment->GetValue().ToStdString(), this->dbid);
		wxMessageBox(L"SAVE COMPLETED, Thanks for using DOCVIEW™ :)");
	}
	catch (const std::exception&){
		wxMessageBox(L"Save Failed :(");
	}
}