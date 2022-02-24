//---------------------------------------------------------------------------

#include <System.hpp>
#include <vcl.h>
#pragma hdrstop

#include "TReadThread.h"
#include "untAplicacaoCliente.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TReadThread::TReadThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------

void __fastcall TReadThread::AtualizaCliente(){
	// Reseta as propriedades visíveis do cliente para o estado inicial----
	FrmCliente->BtnConectar->Caption = "CONECTAR";
    FrmCliente->SttsBrCliente->Panels->Items[1]->Text = "DESCONECTADO";
	//---------------------------------------------------------------------

	// Limpa os campos alterados enquanto o cliente estava online----------
	FrmCliente->EdtNickname->Enabled = true;
    FrmCliente->CbbIPServidor->Enabled = true;
	FrmCliente->CbListaDeJogadores->Clear();
	FrmCliente->MemChat->Clear();
	//---------------------------------------------------------------------

	// Reseta os botões do tabuleiro---------------------------------------
	for(int i=0 ; i < 9 ; i++)
	{
		TButton *BtnParaLimpar = dynamic_cast<TButton *>(FrmCliente->PnlTabuleiro->Controls[i]);
		BtnParaLimpar->Caption = "";
        BtnParaLimpar->Enabled = true;
	}
	//---------------------------------------------------------------------

	// Desativa todos os componentes de cada painel------------------------
	FrmCliente->PnlTabuleiro->Enabled = false;
	FrmCliente->PnlComunicacao->Enabled = false;
	FrmCliente->PnlX1->Enabled = false;
    FrmCliente->SttsBrCliente->Panels->Items[2]->Text = "";
	//---------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void __fastcall TReadThread::Execute()
{
	FreeOnTerminate = true;
	String Msg;

	while(FrmCliente->IdTCPClient->Connected())
	{
		Msg = FrmCliente->IdTCPClient->Socket->ReadLn();

		if(Msg == "#++CBB") //Cliente solicitou a lista de jogadores online
		{
			int JogadoresOnline = StrToInt(FrmCliente->IdTCPClient->Socket->ReadLn());

			for(int i=0 ; i < JogadoresOnline ; i++)
			{
				FrmCliente->CbListaDeJogadores->Items->Add(FrmCliente->IdTCPClient->Socket->ReadLn());
			}
		}
		else if(Msg == "#++CNV") //Cliente recebeu um convite para jogar
		{
			String JogadorConvidou = FrmCliente->IdTCPClient->Socket->ReadLn();
            int Resposta;
			Resposta = MessageDlg("[" + JogadorConvidou + "]" + " convida você para uma partida!\nDeseja aceitar?",
								  mtConfirmation, TMsgDlgButtons() << mbNo << mbYes, 0);

			if(Resposta == mrYes)
			{
				FrmCliente->IdTCPClient->Socket->WriteLn("#++RSP");
				FrmCliente->IdTCPClient->Socket->WriteLn("#++SIM");
				FrmCliente->PnlComunicacao->Enabled = true;
				FrmCliente->PnlX1->Enabled = false;
                FrmCliente->SttsBrCliente->Panels->Items[2]->Text = "JOGANDO";
			}
			else if(Resposta == mrNo)
			{
                FrmCliente->IdTCPClient->Socket->WriteLn("#++RSP");
                FrmCliente->IdTCPClient->Socket->WriteLn("#++NAO");
            }
		}
		else if(Msg == "#++SIM") //Convite do cliente foi aceito pelo outro cliente
		{
            MessageDlg("O JOGADOR ACEITOU O SEU CONVITE!", mtInformation, TMsgDlgButtons() << mbOK, 0);
			FrmCliente->PnlComunicacao->Enabled = true;
			FrmCliente->PnlTabuleiro->Enabled = true;
			FrmCliente->PnlX1->Enabled = false;
            FrmCliente->SttsBrCliente->Panels->Items[2]->Text = "JOGANDO";
		}
		else if(Msg == "#++NAO") //Convite do cliente foi rejeitado pelo outro cliente
		{
			MessageDlg("O JOGADOR REJEITOU O SEU CONVITE!", mtInformation, TMsgDlgButtons() << mbOK, 0);
		}
		else if(Msg == "#++OCP") //Jogador convidado está em outra partida
		{
        	MessageDlg("O JOGADOR JÁ ESTÁ EM OUTRA PARTIDA!", mtInformation, TMsgDlgButtons() << mbOK, 0);
		}
		else if(Msg == "#++MSG") //Cliente recebeu uma mensagem de outro cliente
		{
			FrmCliente->MemChat->Lines->Add(FrmCliente->IdTCPClient->Socket->ReadLn());
		}
		else if(Msg == "#++SVR") //Cliente recebeu uma mensagem do servidor
		{
			FrmCliente->MemChat->Lines->Add("MENSAGEM DO SERVIDOR: " + FrmCliente->IdTCPClient->Socket->ReadLn());
		}
		else if(Msg == "#++MOV") //Cliente recebeu dados da jogada do oponente
		{
			String BtnEscolhido = FrmCliente->IdTCPClient->Socket->ReadLn();
			TButton *BtnParaMudar = (TButton*)(FrmCliente->FindComponent(BtnEscolhido));
			BtnParaMudar->Caption = "O";
			BtnParaMudar->Enabled = false;
			FrmCliente->PnlTabuleiro->Enabled = true;
		}
		else if(Msg == "#++VIT" || Msg == "#++EMP") //Oponente venceu
		{
        	String BtnEscolhido = FrmCliente->IdTCPClient->Socket->ReadLn();
			TButton *BtnParaMudar = (TButton*)(FrmCliente->FindComponent(BtnEscolhido));
            BtnParaMudar->Caption = "O";
			BtnParaMudar->Enabled = false;

			(Msg == "#++EMP") ? MessageDlg("FIM DE JOGO!\nEMPATE!", mtInformation, TMsgDlgButtons() << mbOK, 0)
							  : MessageDlg("FIM DE JOGO!\nVOCÊ PERDEU!", mtInformation, TMsgDlgButtons() << mbOK, 0);

			for(int i=0 ; i<9 ; i++)
			{
				TButton *Btn = dynamic_cast<TButton*>(FrmCliente->PnlTabuleiro->Controls[i]);
				Btn->Caption = "";
				Btn->Enabled = true;
			}

            FrmCliente->MemChat->Clear();
			FrmCliente->CbListaDeJogadores->Clear();
			FrmCliente->PnlComunicacao->Enabled = false;
			FrmCliente->PnlX1->Enabled = true;
            FrmCliente->SttsBrCliente->Panels->Items[2]->Text = "";
		}
		else if(Msg == "#++FIM") //Oponente se desconectou/desistiu da partida
		{
			MessageDlg("DESCULPE!\nSEU OPONENTE DESISTIU DA PARTIDA!", mtInformation, TMsgDlgButtons() << mbOK, 0);
			for(int i=0 ; i<9 ; i++)
			{
				TButton *Btn = dynamic_cast<TButton*>(FrmCliente->PnlTabuleiro->Controls[i]);
				Btn->Caption = "";
				Btn->Enabled = true;
			}
			FrmCliente->PnlTabuleiro->Enabled = false;
            FrmCliente->PnlComunicacao->Enabled = false;
			FrmCliente->CbListaDeJogadores->Clear();
			FrmCliente->PnlX1->Enabled = true;
			FrmCliente->MemChat->Clear();
            FrmCliente->SttsBrCliente->Panels->Items[2]->Text = "";
		}
		else if(Msg == "#++EXT") //Servidor desconectou o cliente(Interrompe a thread para evitar erros)
		{
			break;
		}
	}

	Synchronize(AtualizaCliente);
}
//---------------------------------------------------------------------------
