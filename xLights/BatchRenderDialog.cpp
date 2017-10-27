#include "BatchRenderDialog.h"

//(*InternalHeaders(BatchRenderDialog)
#include <wx/sizer.h>
#include <wx/checklst.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include <wx/dir.h>
#include <wx/menu.h>

//(*IdInit(BatchRenderDialog)
const long BatchRenderDialog::ID_CHECKLISTBOX_SEQUENCES = wxNewId();
//*)

BEGIN_EVENT_TABLE(BatchRenderDialog,wxDialog)
	//(*EventTable(BatchRenderDialog)
	//*)
END_EVENT_TABLE()

BatchRenderDialog::BatchRenderDialog(wxWindow* parent)
{
	//(*Initialize(BatchRenderDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Batch Render"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxCLOSE_BOX, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	SequenceList = new wxCheckListBox(this, ID_CHECKLISTBOX_SEQUENCES, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX_SEQUENCES"));
	SequenceList->SetMinSize(wxDLG_UNIT(this,wxSize(150,200)));
	FlexGridSizer1->Add(SequenceList, 1, wxALL|wxEXPAND, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();
	//*)
    
    
    Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&BatchRenderDialog::OnPreviewRightDown, nullptr,this);
}

void BatchRenderDialog::OnPreviewRightDown(wxMouseEvent& event) {
    wxMenu mnu;
    mnu.Append(1, "Select All");
    mnu.Append(2, "Select None");

    mnu.Connect(wxEVT_MENU, (wxObjectEventFunction)&BatchRenderDialog::OnPopupCommand, nullptr, this);
    PopupMenu(&mnu);
}

void BatchRenderDialog::OnPopupCommand(wxCommandEvent &event) {
    for (int x = 0; x < SequenceList->GetCount(); x++) {
        SequenceList->Check(x, event.GetId() == 1);
    }
}


wxArrayString BatchRenderDialog::GetFileList() {
    wxArrayString lst;
    for (int x = 0; x < SequenceList->GetCount(); x++) {
        if (SequenceList->IsChecked(x)) {
            lst.push_back(SequenceList->GetString(x));
            
        }
    }
    return lst;
}

bool BatchRenderDialog::Prepare(const wxString &showDir) {
    wxArrayString files;
    wxDir::GetAllFiles(showDir, &files, "*.xml");
    files.Sort();
    for (int x = 0; x < files.size(); x++) {
        wxString name = files[x].SubString(showDir.length(), files[x].size());
        if (name[0] == '/' || name[0] == '\\') {
            name = name.SubString(1, name.size());
        }
        if (!name.StartsWith("xlights_") && !name.StartsWith("Backup/") && !name.StartsWith("Backup\\")) {
            SequenceList->Append(name);
        }
    }
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    return SequenceList->GetCount() > 0;
}

BatchRenderDialog::~BatchRenderDialog()
{
	//(*Destroy(BatchRenderDialog)
	//*)
}
