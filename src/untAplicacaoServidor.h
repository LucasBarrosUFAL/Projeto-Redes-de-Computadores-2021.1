//---------------------------------------------------------------------------

#ifndef untAplicacaoServidorH
#define untAplicacaoServidorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
#include <IdSocketHandle.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
class TFrmServidor : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStatusBar *SbStatusServidor;
	TButton *BtnEnviarMsg;
	TEdit *EdtMsgGlobal;
	TMemo *MemHistorico;
	TIdTCPServer *IdTCPServer;
	TBitBtn *BitBtnLimpar;
	TListView *ListViewJogando;
	TLabel *Label1;
	TListView *ListViewOnline;
	TLabel *Label2;
	TToggleSwitch *TglSwitchAtivar;
	void __fastcall IdTCPServerExecute(TIdContext *AContext);
	void __fastcall IdTCPServerConnect(TIdContext *AContext);
	void __fastcall IdTCPServerDisconnect(TIdContext *AContext);
	void __fastcall BtnEnviarMsgClick(TObject *Sender);
	void __fastcall BitBtnLimparClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TglSwitchAtivarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmServidor(TComponent* Owner);
	map <String,String> Online;
	map <String,String> Lista1;
	map <String,String> Lista2;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmServidor *FrmServidor;
//---------------------------------------------------------------------------
#endif
