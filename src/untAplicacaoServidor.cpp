//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "untAplicacaoServidor.h"
#include "TRefreshThread.h"
#include <map>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmServidor *FrmServidor;
//TStringList *Online, *Lista1, *Lista2;
//map <String, String> Online, <String, *TIdContext> Lista1, <String, *TIdContext> Lista2;
//---------------------------------------------------------------------------
__fastcall TFrmServidor::TFrmServidor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//DESCONECTA TODOS OS CLIENTES ANTES DE DESATIVAR O SERVIDOR-----------------
void LoopDesconectarTodos()
{
    TList *Clientes = FrmServidor->IdTCPServer->Contexts->LockList();

	if(FrmServidor->Online.size() != 0 || Clientes->Count != 0){
		FrmServidor->Online.clear();
		FrmServidor->Lista1.clear();
		FrmServidor->Lista2.clear();
		FrmServidor->ListViewJogando->Clear();
		FrmServidor->ListViewOnline->Clear();
		for(int i=0 ; i < Clientes->Count ; i++){
			TIdContext *Atual = (TIdContext*)(Clientes->Items[i]);
			Atual->Connection->Socket->WriteLn("#++EXT");
			Atual->Connection->Disconnect();
			Atual->Connection->IOHandler->InputBuffer->Clear();
		}
	}

    FrmServidor->IdTCPServer->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

//ATIVA/DESATIVA O SERVIDOR--------------------------------------------------
void __fastcall TFrmServidor::TglSwitchAtivarClick(TObject *Sender)
{
	if(IdTCPServer->Active == false) //SE O SERVIDOR ESTIVER DESATIVADO
	{
		try
		{
			IdTCPServer->Active = true;
			TglSwitchAtivar->State = tssOn;
            TglSwitchAtivar->Color = clLime;
			SbStatusServidor->Panels->Items[1]->Text = "EXECUTANDO";
			TRefreshThread *NewRefreshThread = new TRefreshThread(true);
			NewRefreshThread->Priority = tpHigher;
			NewRefreshThread->Start();
		}
		catch(Exception &E)
		{
			MessageDlg("NÃO FOI POSSÍVEL ATIVAR O SERVIDOR!", mtError, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else //SE O SERVIDOR ESTIVER ATIVADO
	{
		try //TENTA DESATIVAR O SERVIDOR
		{
            LoopDesconectarTodos();
			IdTCPServer->Active = false;
			TglSwitchAtivar->State = tssOff;
			TglSwitchAtivar->Color = clGray;
			SbStatusServidor->Panels->Items[1]->Text = "DESATIVADO";
			SbStatusServidor->Panels->Items[2]->Text = "";
		}
		catch(Exception &E) //SE ACONTECER ALGUM ERRO UMA MENSAGEM SERÁ EXIBIDA
		{
			MessageDlg("NÃO FOI POSSÍVEL DESATIVAR O SERVIDOR!", mtError, TMsgDlgButtons() << mbOK, 0);
		}
	}
}
//---------------------------------------------------------------------------

//ACONTECE ENAQUANTO O SERVIDOR SE ENCONTRA ATIVO----------------------------
void __fastcall TFrmServidor::IdTCPServerExecute(TIdContext *AContext)
{
	String Solicitacao;
	Solicitacao = AContext->Connection->Socket->ReadLn();
	//MemHistorico->Lines->Add(Solicitacao);

	if (Solicitacao == "#++MOV" || Solicitacao == "#++VIT" || Solicitacao == "#++EMP")
	{
		String Jogou = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
		String IraJogar = (Lista1.count(Jogou)) ? Lista1[Jogou] : Lista2[Jogou];
		String Botao = AContext->Connection->Socket->ReadLn();
		MemHistorico->Lines->Add("[" + Online[Jogou] + "] Clicou: " + Botao);
		TList *Lista = IdTCPServer->Contexts->LockList();
		for(int i=0 ; i < Lista->Count ; i++)
		{
			TIdContext *Atual = (TIdContext*)(Lista->Items[i]);
			if((Atual->Binding->PeerIP + ":" + Atual->Binding->PeerPort) == IraJogar)
			{
				Atual->Connection->Socket->WriteLn(Solicitacao);
				Atual->Connection->Socket->WriteLn(Botao);
				break;
			}
		}
		IdTCPServer->Contexts->UnlockList();

		if(Solicitacao == "#++VIT" || Solicitacao == "#++EMP"){
			Lista1.erase(Jogou);
			Lista1.erase(IraJogar);
			Lista2.erase(Jogou);
			Lista2.erase(IraJogar);
		}
	}
	else if(Solicitacao == "#++MSG")
	{
		String Remetente = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
        String Destinatario = (Lista1.count(Remetente)) ? Lista1[Remetente] : Lista2[Remetente];
		String Mensagem = AContext->Connection->Socket->ReadLn();
		MemHistorico->Lines->Add("[" + Online[Remetente] + "] PARA " + "[" + Online[Destinatario] + "]: " + Mensagem);
		TList *Lista = IdTCPServer->Contexts->LockList();
		for(int i=0 ; i < Lista->Count ; i++)
		{
			TIdContext *Atual = (TIdContext*)(Lista->Items[i]);
			if((Atual->Binding->PeerIP + ":" + Atual->Binding->PeerPort) == Destinatario)
			{
                Atual->Connection->Socket->WriteLn("#++MSG");
				Atual->Connection->Socket->WriteLn(Online[Remetente]+": "+Mensagem);
                break;
            }
		}
        IdTCPServer->Contexts->UnlockList();
	}
	else if(Solicitacao == "#++CBB")
	{
        String Cliente = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
		AContext->Connection->Socket->WriteLn("#++CBB");
		AContext->Connection->Socket->WriteLn(IntToStr(IdTCPServer->Contexts->LockList()->Count-1));
		for(auto p=Online.begin() ; p != Online.end() ; p++)
		{
			if(p->first != Cliente)
			{
				AContext->Connection->Socket->WriteLn(p->second);
			}
		}
		IdTCPServer->Contexts->UnlockList();
	}
	else if(Solicitacao == "#++CNV")
	{
		String NickConvidado = AContext->Connection->Socket->ReadLn();
		String JogadorConvidou = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
		String JogadorConvidado;
		String RespostaConvidado;
		for(auto p = Online.begin() ; p != Online.end() ; p++)
		{
			if(p->second == NickConvidado)
			{
                JogadorConvidado = p->first;
			}
		}

		if(Lista1.count(JogadorConvidado) == 0 && Lista2.count(JogadorConvidado) == 0)
		{
			Lista1[JogadorConvidou] = JogadorConvidado;
			Lista2[JogadorConvidado] = JogadorConvidou;
			TList *Lista = IdTCPServer->Contexts->LockList();
			for(int i=0 ; i < Lista->Count ; i++)
			{
				TIdContext *Atual = (TIdContext*) Lista->Items[i];
				if(Atual->Binding->PeerIP + ":" + Atual->Binding->PeerPort == JogadorConvidado)
				{
					Atual->Connection->Socket->WriteLn("#++CNV");
					Atual->Connection->Socket->WriteLn(Online[JogadorConvidou]);
					break;
				}
			}
			IdTCPServer->Contexts->UnlockList();
		}
		else
		{
            TList *Lista = IdTCPServer->Contexts->LockList();
			for(int i=0 ; i < Lista->Count ; i++)
			{
				TIdContext *Atual = (TIdContext*) Lista->Items[i];
				if(Atual->Binding->PeerIP + ":" + Atual->Binding->PeerPort == JogadorConvidou)
				{
					Atual->Connection->Socket->WriteLn("#++OCP");
					break;
				}
			}
			IdTCPServer->Contexts->UnlockList();
        }
	}
	else if(Solicitacao == "#++RSP")
	{
		String JogadorRespondeu, JogadorConvidou, Resposta;
        Resposta = AContext->Connection->Socket->ReadLn();
		JogadorRespondeu = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
		JogadorConvidou = Lista2[JogadorRespondeu];
    	TList *Lista = IdTCPServer->Contexts->LockList();
		for(int j=0 ; j < Lista->Count ; j++)
		{
			TIdContext *Atual = (TIdContext*) Lista->Items[j];
			if(Atual->Binding->PeerIP+":"+Atual->Binding->PeerPort == Lista2[JogadorRespondeu])
			{
				Atual->Connection->Socket->WriteLn(Resposta);
				break;
			}
		}
		IdTCPServer->Contexts->UnlockList();

		if(Resposta == "#++NAO"){
			Lista1.erase(JogadorConvidou);
			Lista2.erase(JogadorRespondeu);
		}
	}
//	else if(Solicitacao == "#++FIM")
//	{
//		String JogadorDesistiu, Oponente;
//		JogadorDesistiu = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
//		if()
//	}
}
//---------------------------------------------------------------------------

//ACONTECE QUANDO UM CLIENTE SE CONECTA AO SERVIDOR--------------------------
void __fastcall TFrmServidor::IdTCPServerConnect(TIdContext *AContext)
{
	AContext->Connection->Socket->WriteLn("Conectado");
	String Endereco = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
	MemHistorico->Lines->Add("Cliente: [" + Endereco + "] Conectado");
	Online[Endereco] = AContext->Connection->Socket->ReadLn();
}
//---------------------------------------------------------------------------

//ACONTECE QUANDO UM CLIENTE SE DESCONECTA DO SERVIDOR-----------------------
void EncerrarPartida(String Oponente){
	TList *Clientes = FrmServidor->IdTCPServer->Contexts->LockList();
	for(int i=0 ; i<Clientes->Count ; i++)
	{
		TIdContext *Atual = (TIdContext*) Clientes->Items[i];
		if(Atual->Binding->PeerIP + ":" + Atual->Binding->PeerPort == Oponente)
		{
			Atual->Connection->Socket->WriteLn("#++FIM");
            break;
		}
	}
    FrmServidor->IdTCPServer->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

//ACONTECE QUANDO UM CLIENTE SE DESCONECTA DO SERVIDOR-----------------------
void __fastcall TFrmServidor::IdTCPServerDisconnect(TIdContext *AContext)
{
	String Cliente, Oponente;
	Cliente = AContext->Binding->PeerIP + ":" + AContext->Binding->PeerPort;
	MemHistorico->Lines->Add("Cliente: [" + Cliente + "] Desconectado");
	Online.erase(Cliente);

	if(Lista1.count(Cliente)) //EXCLUI O CLIENTE DA LISTA DE PESSOAS QUE ESTÃO JOGANDO
	{
		Lista2.erase(Lista1[Cliente]);
        Oponente = Lista1[Cliente];
        Lista1.erase(Cliente);
	}
	else if(Lista2.count(Cliente))
	{
		Lista1.erase(Lista2[Cliente]);
        Oponente = Lista2[Cliente];
		Lista2.erase(Cliente);
	}

	EncerrarPartida(Oponente);
	AContext->Connection->Socket->WriteLn("#++EXT");
}
//---------------------------------------------------------------------------

//ENVIA UMA MENSAGEM PARA TODOS OS CLIENTES CONECTADOS-----------------------
void __fastcall TFrmServidor::BtnEnviarMsgClick(TObject *Sender)
{
	TList *Clientes = IdTCPServer->Contexts->LockList();

	for(int i=0 ; i < Clientes->Count ; i++){
		TIdContext *Atual = (TIdContext*)(Clientes->Items[i]);
		Atual->Connection->IOHandler->WriteLn("#++SVR");
		Atual->Connection->IOHandler->WriteLn(EdtMsgGlobal->Text);
	}
    EdtMsgGlobal->Clear();
    IdTCPServer->Contexts->UnlockList();
}
//---------------------------------------------------------------------------

//LIMPA O HISTÓRICO DO CHAT--------------------------------------------------
void __fastcall TFrmServidor::BitBtnLimparClick(TObject *Sender)
{
    MemHistorico->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFrmServidor::FormClose(TObject *Sender, TCloseAction &Action)
{
	LoopDesconectarTodos();
	IdTCPServer->Active = false;
}
//---------------------------------------------------------------------------
