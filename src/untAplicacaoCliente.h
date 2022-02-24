//---------------------------------------------------------------------------

#ifndef untAplicacaoClienteH
#define untAplicacaoClienteH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdSocksServer.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <IdTelnet.hpp>
#include <IdCmdTCPClient.hpp>
#include <IdIRC.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerStream.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <IdIPWatch.hpp>
//---------------------------------------------------------------------------
class TFrmCliente : public TForm
{
__published:	// IDE-managed Components
	TPanel *PnlTabuleiro;
	TButton *Btn1;
	TButton *Btn5;
	TButton *Btn8;
	TButton *Btn2;
	TButton *Btn4;
	TButton *Btn9;
	TButton *Btn6;
	TButton *Btn3;
	TButton *Btn7;
	TIdTCPClient *IdTCPClient;
	TPanel *PnlComunicacao;
	TStatusBar *SttsBrCliente;
	TMemo *MemChat;
	TPanel *PnlConexao;
	TLabel *Label2;
	TEdit *EdtNickname;
	TButton *BtnConectar;
	TPanel *PnlX1;
	TLabel *Label1;
	TComboBox *CbListaDeJogadores;
	TButton *BtnConvidarJogador;
	TEdit *EdtMsg;
	TButton *BtnEnviar;
	TBitBtn *BitBtnLimpar;
	TBalloonHint *BlnHintMsg;
	TLabel *Label3;
	TComboBox *CbbIPServidor;
	void __fastcall BtnTabuleiroClick(TObject *Sender);
	void __fastcall BtnEnviarClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnConectarClick(TObject *Sender);
	void __fastcall IdTCPClientConnected(TObject *Sender);
	void __fastcall IdTCPClientDisconnected(TObject *Sender);
	void __fastcall BtnConvidarJogadorClick(TObject *Sender);
	void __fastcall CbListaDeJogadoresDropDown(TObject *Sender);
	void __fastcall BitBtnLimparClick(TObject *Sender);
	void __fastcall CbbIPServidorSelect(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmCliente(TComponent* Owner);
	bool StatusJogando = false;
    String IPServidor = "127.0.0.1";
};

//---------------------------------------------------------------------------
extern PACKAGE TFrmCliente *FrmCliente;
//---------------------------------------------------------------------------
#endif
