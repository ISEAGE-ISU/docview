#include "stdafx.h"
#include <wx/wx.h>
#include "DocView.h"
#include "DocFrame.h"

const char* backimage = "C:\\back.png";

DocFrame::DocFrame(const wxString &title, const wxPoint &pos,const wxSize &size)
{
	Create(NULL, wxID_ANY, title, pos, size);
	wxInitAllImageHandlers();
	SetBackgroundBitmap(wxBitmap(backimage, wxBITMAP_TYPE_PNG));
	this->Show(true);
	this->Maximize();

	this->grid = new wxGridSizer(1, wxSize(10, 10));

	this->pb = new patientBook(this);

	this->grid->Add(this->pb);

	connectstring = std::string("user=postgres dbname=hospitalsite host=");

	wxTextEntryDialog entry = wxTextEntryDialog(this, "Connection info", "PLEASE ENTER YOUR DB IP");
	if (entry.ShowModal() != wxID_OK) {
		exit(1);
	}


	connectstring += entry.GetValue().ToStdString();

	try { this->db = tao::pq::connection::create(connectstring); }
	catch (const std::runtime_error&) { 
		wxMessageBox("Could not connect to db\nPlease check your connection and try again");  
		exit(1);
	}

	this->scrape();
	SetSizerAndFit(this->grid);
	this->Layout();
}

DocFrame::~DocFrame()
{
	delete image;
}

void
DocFrame::scrape(void)
{
	try {
		const auto res = this->db->execute("SELECT id, name, age, gender, weight, history, current_ailment from hospitalsite_profile");
		for (const auto& row : res) {
			this->pb->add(row[1].as<std::string>(),
				row[2].as<int>(),
				row[3].as<std::string>(),
				row[4].as<int>(),
				row[5].as<std::string>(),
				row[6].as<std::string>(),
				row[0].as<int>(),
				this->connectstring);

		}
	}
	catch (const std::exception& e) {
		wxMessageBox("Error reading from DB");
		std::cout << e.what() << "\n";
	}
}

void
DocFrame::insert(const char *name, int age, char gender, int weight, const char *history, const char *ailment)
{
	try {
		this->db->execute("INSERT INTO hospitalsite_profile VALUES ( $1, $2, $3, $4, $5, $6, $7, $8 )",
			1, name, 18, gender , weight, history, ailment, 1);
	}
	catch (const std::exception& e) {
		wxMessageBox("Insert failed");
		std::cout << e.what() << "\n";
	}
}

tao::pq::result
DocFrame::get(int id)
{
	try {
		return this->db->execute("SELECT age, gender, weight, history, current_ailment FROM hospitalsite_profile WHERE id = $1", id);
	}
	catch (const std::exception&) {
		wxMessageBox("Error pulling values for patient");
	}
}


std::string
DocFrame::getdbstring(void) {
	return std::string(this->connectstring);
}