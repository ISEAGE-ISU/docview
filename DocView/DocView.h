#pragma once

class wxApp;

class docView : public wxApp {

	public:
		virtual bool OnInit();
		virtual int OnExit();

};


DECLARE_APP(docView)