// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vector>

#include "Form1Unit.h"
#include "PathFinder2D.h"
#include "Map.h"
#include "Character.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//map size N*N cells
const int N = 20;
//size of cells M*M
const int M = 20;

// -------------------

//
void ShowPanel(bool status);
void DrawMap(int* map, int cols, int rows);
void SetAddField();
bool IsValidFields();
Character* SelectCharacter(int x, int y);

// ------------------------

TForm1 *Form1;
// ----------------

//global mouse coordinate
int iMouseX, iMouseY;

//buffer image
auto* Image = new Graphics::TBitmap();

//obstacle map
Map* map = new Map(N, N);

//all characters on the screen
std::vector<Character*>vCharacters;

//current character to move or editing
Character* pSelectedCharacter = nullptr;

// variable to right panel(adding panel)
bool isShow = true;

// validation Edits on Adding Panel
bool IsValidFields() {


	if (Form1->AddName->Text.IsEmpty()) {
		ShowMessage("Error:Name is empty");
		return false;
	}
	else if (Form1->AddName->Text[1] >= '0' && Form1->AddName->Text[1] <= '9') {
		ShowMessage("Error:Name can't begin with a number.");
		return false;
	}
	if (Form1->AddX->Text.IsEmpty())
		Form1->AddX->Text = "0";
	if (Form1->AddY->Text.IsEmpty())
		Form1->AddY->Text = "0";

	return true;
}

//click on map to select character or to reset current selection
Character* SelectCharacter(int x, int y) {

	for (auto&i : vCharacters) {
		if (i->GetX() == x && i->GetY() == y)
			return i;
	}
	return nullptr;
}
//show/hide right panel(adding panel)
void ShowPanel(bool status) {

	if (status) {
		Form1->AddPanel->Width = 0;
		Form1->Button1->Left = Form1->ClientWidth - Form1->Button1->Width;
	}
	else {
		Form1->AddPanel->Width = Form1->ClientWidth / 6;
		Form1->Button1->Left = Form1->ClientWidth - Form1->Button1->Width -
			Form1->AddPanel->Width; ;
		SetAddField();
	}
	isShow = !isShow;
}

void SetAddField() {
    //setup adding panel
	if (pSelectedCharacter != NULL) {
		Form1->AddName->Text = pSelectedCharacter->GetName().c_str();
		Form1->AddX->Text = pSelectedCharacter->GetX();
		Form1->AddY->Text = pSelectedCharacter->GetY();
		Form1->AddDelete->Visible = true;
		Form1->AddOk->Caption = "Save Editing";
	}
	else {
		Form1->AddDelete->Visible = false;
		Form1->AddOk->Caption = "Add character";

	}
}

void DrawMap(int* map, int cols, int rows) {
	// draw obstacles

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++) {
			if (map[y * cols + x] == -1) {
				Image->Canvas->Brush->Color = clRed;
			}
			else {
				Image->Canvas->Brush->Color = clLime;
			}
			Image->Canvas->Rectangle(x*M, y*M, x*M + M, y*M + M);
		}

	// draw all characters;
	Form1->Caption = vCharacters.size();
	for (auto&i : vCharacters) {
		Image->Canvas->Brush->Color = clAqua;
		Image->Canvas->Ellipse(i->GetX()*M, i->GetY()*M, i->GetX()*M + M,
			i->GetY()*M + M);
	}
    //draw selected char
	if (pSelectedCharacter != nullptr) {
		Image->Canvas->Brush->Color = clYellow;
		Image->Canvas->Ellipse(pSelectedCharacter->GetX()*M,
			pSelectedCharacter->GetY()*M, pSelectedCharacter->GetX()*M + M,
			pSelectedCharacter->GetY()*M + M);
	}

	Form1->Canvas->Draw(0, 0, Image);
}

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
	ShowPanel(isShow);

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::AddOkClick(TObject *Sender) {

	if (IsValidFields()) {
		// create new Char
		if (pSelectedCharacter == nullptr) {

			int x = AddX->Text.ToInt();
			int y = AddY->Text.ToInt();
			std::wstring s = AddName->Text.w_str();
			Character* tmp = new Character(x, y, AddName->Text.w_str(), map);
			vCharacters.push_back(tmp);

		}
		else {
            //editing existing char
			int x = AddX->Text.ToInt();
			int y = AddY->Text.ToInt();
			pSelectedCharacter->SetXY(x, y);
			pSelectedCharacter->SetName(AddName->Text.w_str());
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action) {
	delete Image;
	for (auto &i: vCharacters)
	delete i;
    delete map;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::DrawTimer(TObject *Sender) {
	DrawMap(map->GetMap(), N, N);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender) {

	map->RandomMap(33);

	Image->Width = M * N;
	Image->Height = M * N;

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)

{
	iMouseX = X;
	iMouseY = Y;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::AddXKeyPress(TObject *Sender, System::WideChar &Key) {
	if (!((Key >= '0' && Key <= '9') || Key == VK_BACK))
		Key = 0x00;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::AddYKeyPress(TObject *Sender, System::WideChar &Key) {
	if (!((Key >= '0' && Key <= '9') || Key == VK_BACK))
		Key = 0x00;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y) {

	//is click on image?
	if (iMouseX < N * M && iMouseY < N * M) {
		if (Button == mbLeft) {
		//select
			pSelectedCharacter = SelectCharacter(iMouseX / M, iMouseY / M);
			SetAddField();

		}
		else {
        //move
			if (Button == mbRight && pSelectedCharacter != nullptr) {
				pSelectedCharacter->CalculatePathTo(iMouseX / M, iMouseY / M);
			}
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::PhysTimer(TObject *Sender) {
    //move every character in game
	for (auto&i : vCharacters) {
		i->Move();
	}
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::AddDeleteClick(TObject *Sender)
{
int i;
for(i=0;i<vCharacters.size();i++)
if(vCharacters[i]==pSelectedCharacter)
break;
pSelectedCharacter = nullptr;
vCharacters.erase(vCharacters.begin()+i);
SetAddField();

}
//---------------------------------------------------------------------------

