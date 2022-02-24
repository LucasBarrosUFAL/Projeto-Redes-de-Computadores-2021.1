//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "untAplicacaoCliente.h"
#include "TReadThread.h"
#include "untIP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmCliente *FrmCliente;
//---------------------------------------------------------------------------

TReadThread *NewReadThread;

__fastcall TFrmCliente::TFrmCliente(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::BtnConectarClick(TObject *Sender)
{
	if(CbbIPServidor->Text == ""){
		MessageDlg("ESCOLHA O SERVIDOR!", mtWarning, TMsgDlgButtons() << mbOK, 0);
		CbbIPServidor->SetFocus();
		return;
	}

	if(EdtNickname->Text == ""){
		MessageDlg("VOCÊ DEVE INSERIR UM NICKNAME!", mtWarning, TMsgDlgButtons() << mbOK, 0);
		EdtNickname->SetFocus();
		return;
	}

	if(!IdTCPClient->Connected()){
		try{
			//IdTCPClient->RemoteHost = "1.1.1.1";
			IdTCPClient->Port = 5000;
			IdTCPClient->Host = IPServidor;
			IdTCPClient->Connect();
			IdTCPClient->Socket->WriteLn(EdtNickname->Text);
			EdtNickname->Enabled = false;
			CbbIPServidor->Enabled = false;
			PnlX1->Enabled = true;
			NewReadThread = new TReadThread(true);
			NewReadThread->Priority = tpHigher;
			NewReadThread->Start();
		}
		catch(Exception &E){
			MessageDlg("NÃO FOI POSSÍVEL SE CONECTAR AO SERVIDOR!", mtError, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else if(IdTCPClient->Connected()){
		try{
			IdTCPClient->Disconnect();
			EdtNickname->Enabled = true;
			CbbIPServidor->Enabled = true;
			EdtNickname->Clear();

            NewReadThread->AtualizaCliente();

//			EdtNickname->Enabled = true;
//			CbbIPServidor->Enabled = true;
//			CbListaDeJogadores->Clear();
//			MemChat->Clear();
//
//			for(int i=0 ; i < PnlTabuleiro->ControlCount ; i++)
//			{
//				if(PnlTabuleiro->Controls[i]->ClassName() == "Btn"+IntToStr(i+1))
//				{
//					TButton *BtnParaLimpar = dynamic_cast<TButton *>(PnlTabuleiro->Controls[i]);
//					BtnParaLimpar->Caption = "";
//				}
//			}
//
//			PnlTabuleiro->Enabled = false;
//			PnlComunicacao->Enabled = false;
//			PnlX1->Enabled = false;
//			SttsBrCliente->Panels->Items[2]->Text = "";
		}
		catch(Exception &E){
			MessageDlg("NÃO FOI POSSÍVEL DESCONECTAR DO SERVIDOR!", mtError, TMsgDlgButtons() << mbOK, 0);
		}
	}
}
//---------------------------------------------------------------------------

bool VerificaVitoria()
{
	int i, j, k, vert=0, hori=0, d_pri=0, d_sec=0;
	TButton *Btn;

	for(i=1 ; i<=3 ; i++){
		for(j=1 ; j<=3 ; j++){
			Btn = (TButton*)(FrmCliente->FindComponent("Btn" + IntToStr(((i-1)*3)+j)));
			hori += (Btn->Caption == "X") ? 1 : 0;

            Btn = (TButton*)(FrmCliente->FindComponent("Btn" + IntToStr(((j-1)*3)+i)));
			vert += (Btn->Caption == "X") ? 1 : 0;

			d_pri += (Btn->Caption == "X" && i == j) ? 1 : 0;

			d_sec += (Btn->Caption == "X" && (i+j) == 4) ? 1 : 0;
		}

		if(vert==3 || hori==3){
			return true;
		}
		else{
			vert = 0;
			hori = 0;
		}
	}

    if(d_pri==3 || d_sec==3) return true;
	else return false;
}

bool VerificaEmpate(){
	for(int i=0 ; i<9 ; i++){
		TButton *Btn = dynamic_cast<TButton*>(FrmCliente->PnlTabuleiro->Controls[i]);
        if(Btn->Enabled == true) return false;
	}
    return true;
}

void __fastcall TFrmCliente::BtnTabuleiroClick(TObject *Sender)
{
    TButton *BotaoPressionado = dynamic_cast<TButton *>(Sender);
	BotaoPressionado->Caption = "X";
	BotaoPressionado->Enabled = false;
	PnlTabuleiro->Enabled = false;

	bool JogadorVenceu = VerificaVitoria(), Empatou = VerificaEmpate();

	if(JogadorVenceu || Empatou)
    {
		(JogadorVenceu) ? (MessageDlg("PARABÉNS!!!\nVOCÊ VENCEU!!!", mtInformation, TMsgDlgButtons() << mbOK, 0),
						   IdTCPClient->Socket->WriteLn("#++VIT"))
						: (MessageDlg("FIM DE JOGO!\nEMPATE!", mtInformation, TMsgDlgButtons() << mbOK, 0),
						   IdTCPClient->Socket->WriteLn("#++EMP"));

        FrmCliente->MemChat->Clear();
        CbListaDeJogadores->Clear();
		PnlComunicacao->Enabled = false;
        SttsBrCliente->Panels->Items[2]->Text = "";
		PnlX1->Enabled = true;

		for(int i=0 ; i<9 ; i++)
		{
			TButton *Btn = dynamic_cast<TButton*>(PnlTabuleiro->Controls[i]);
			Btn->Caption = "";
            Btn->Enabled = true;
		}
	}
	else IdTCPClient->Socket->WriteLn("#++MOV");

	IdTCPClient->Socket->WriteLn(BotaoPressionado->Name);
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::BtnEnviarClick(TObject *Sender)
{
	if(EdtMsg->Text != ""){
        IdTCPClient->Socket->WriteLn("#++MSG");
		IdTCPClient->Socket->WriteLn(EdtMsg->Text);
		MemChat->Lines->Add("VOCÊ: "+ EdtMsg->Text);
		EdtMsg->Clear();
	}
	else if(EdtMsg->Text == ""){
		EdtMsg->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::FormDestroy(TObject *Sender)
{
    IdTCPClient->Disconnect();
}
//---------------------------------------------------------------------------


void __fastcall TFrmCliente::FormClose(TObject *Sender, TCloseAction &Action)
{
    IdTCPClient->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::IdTCPClientConnected(TObject *Sender)
{
	BtnConectar->Caption = "DESCONECTAR";
	SttsBrCliente->Panels->Items[1]->Text = UpperCase(IdTCPClient->Socket->ReadLn());
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::IdTCPClientDisconnected(TObject *Sender)
{
    SttsBrCliente->Panels->Items[1]->Text = "DESCONECTADO";
	BtnConectar->Caption = "CONECTAR";
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::BtnConvidarJogadorClick(TObject *Sender)
{
	IdTCPClient->Socket->WriteLn("#++CNV");
	IdTCPClient->Socket->WriteLn(CbListaDeJogadores->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::CbListaDeJogadoresDropDown(TObject *Sender)
{
    CbListaDeJogadores->Items->Clear();
	IdTCPClient->Socket->WriteLn("#++CBB");
    IdTCPClient->Socket->WriteLn(EdtNickname->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::BitBtnLimparClick(TObject *Sender)
{
	MemChat->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::Button1Click(TObject *Sender)
{
	//frmIP->ShowModal();
    ShowMessage(IPServidor);

}
//---------------------------------------------------------------------------

void __fastcall TFrmCliente::CbbIPServidorSelect(TObject *Sender)
{
    switch(CbbIPServidor->ItemIndex){
		case 0:
			IPServidor = "127.0.0.1";
			break;
		case 1:
			frmIP->Show();
			break;
	}
}
//---------------------------------------------------------------------------

