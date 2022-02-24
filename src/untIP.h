//---------------------------------------------------------------------------

#ifndef untIPH
#define untIPH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Buttons.hpp>
#include <System.RegularExpressions.hpp>
//---------------------------------------------------------------------------
class TfrmIP : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TSpeedButton *SpdBtnVerificar;
	TSpeedButton *SpdBtnCancelar;
	TEdit *EdtIP;
	void __fastcall SpdBtnCancelarClick(TObject *Sender);
	void __fastcall SpdBtnVerificarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmIP(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmIP *frmIP;
//---------------------------------------------------------------------------
#endif
