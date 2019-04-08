// DocView.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <wx/wx.h>
#include "DocView.h"
#include "DocFrame.h"


IMPLEMENT_APP(docView)

bool
docView::OnInit(void)
{
	if(!wxApp::OnInit())
		return false;

	DocFrame *df = new DocFrame("DocView", wxPoint(50, 50), wxDefaultSize);

	return true;
}

int
docView::OnExit(void)
{
	return wxApp::OnExit();
}