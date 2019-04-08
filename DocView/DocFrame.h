#pragma once

#include <tao/pq.hpp>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include "patientBook.h"

class DocFrame : public wxCustomBackgroundWindow<wxFrame>
{
public:
	DocFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
	~DocFrame();

	void scrape(void);

	void insert(const char *name, int age, char gender, int weight, const char *history, const char *ailment);
	tao::pq::result get(int id);

	wxStaticBitmap *image;
	wxGridSizer *grid;
	std::shared_ptr<tao::pq::connection> db;
	patientBook *pb;
};

