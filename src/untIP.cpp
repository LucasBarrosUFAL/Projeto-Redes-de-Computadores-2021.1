//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "untIP.h"
#include "untAplicacaoCliente.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmIP *frmIP;
//---------------------------------------------------------------------------

__fastcall TfrmIP::TfrmIP(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmIP::SpdBtnCancelarClick(TObject *Sender)
{
    FrmCliente->CbbIPServidor->ItemIndex = -1;
	frmIP->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmIP::SpdBtnVerificarClick(TObject *Sender)
{
	String ExpReg = "^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$";

	if(TRegEx::IsMatch(EdtIP->Text, ExpReg))
	{
		FrmCliente->IPServidor = "127.0.0.1";//EdtIP->Text;
        frmIP->Close();
	}
	else
	{
		MessageDlg("ENDEREÇO IP INVÁLIDO!!!\nSIGA O FORMATO \"000.000.000.000\"!",
					mtError, TMsgDlgButtons() << mbOK, 0);
        EdtIP->Clear();
		EdtIP->SetFocus();
		//ShowMessage("IP inválido!");
	}
}
//---------------------------------------------------------------------------
