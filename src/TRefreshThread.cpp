//---------------------------------------------------------------------------

#include <System.hpp>
#include <vcl.h>
#pragma hdrstop

#include "TRefreshThread.h"
#include "untAplicacaoServidor.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TRefreshThread::TRefreshThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TRefreshThread::Execute()
{
	FreeOnTerminate = true;
	int UltimaLeitura, ClientesJogando=0, ClientesOnline=0, ContJogando, ContOnline;

	while(FrmServidor->IdTCPServer->Active == true){
		TList *Lista = FrmServidor->IdTCPServer->Contexts->LockList();
		UltimaLeitura = Lista->Count;

		if(FrmServidor->Online.size() != ClientesOnline){
            ClientesOnline = FrmServidor->Online.size();
			FrmServidor->ListViewOnline->Clear();
            ContOnline = 1;
			for(auto it : FrmServidor->Online){
				TListItem *NewItem = FrmServidor->ListViewOnline->Items->Add();
				NewItem->Caption = ContOnline;
				NewItem->SubItems->Add(it.second);
				NewItem->SubItems->Add(">");
				NewItem->SubItems->Add(it.first);
				ContOnline++;
			}
		}

        if(FrmServidor->Lista1.size() != ClientesJogando){
			ClientesJogando = FrmServidor->Lista1.size();
			FrmServidor->ListViewJogando->Clear();
			ContJogando = 1;

			for(auto it : FrmServidor->Lista1){
				TListItem *NewItem = FrmServidor->ListViewJogando->Items->Add();
				NewItem->Caption = ContJogando;
				NewItem->SubItems->Add(FrmServidor->Online[it.first]);
				NewItem->SubItems->Add("X");
				NewItem->SubItems->Add(FrmServidor->Online[it.second]);
                ContJogando++;
			}
		}

		FrmServidor->SbStatusServidor->Panels->Items[2]->Text = "  " +
				IntToStr(UltimaLeitura) +
				" CLIENTES CONECTADOS";
		FrmServidor->IdTCPServer->Contexts->UnlockList();
	}
}
//---------------------------------------------------------------------------
