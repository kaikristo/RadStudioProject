//---------------------------------------------------------------------------

#ifndef Form1UnitH
#define Form1UnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TPanel *AddPanel;
	TLabeledEdit *AddName;
	TLabeledEdit *AddX;
	TLabeledEdit *AddY;
	TButton *AddOk;
	TButton *AddDelete;
	TTimer *Draw;
	TTimer *Phys;
	TMemo *Help;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall AddOkClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DrawTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall AddXKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AddYKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PhysTimer(TObject *Sender);
	void __fastcall AddDeleteClick(TObject *Sender);

private:	// User declarations
public:		// User declarations

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
