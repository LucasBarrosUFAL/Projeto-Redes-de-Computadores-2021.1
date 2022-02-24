//---------------------------------------------------------------------------

#ifndef TReadThreadH
#define TReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TReadThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TReadThread(bool CreateSuspended);
    void __fastcall AtualizaCliente();
};
//---------------------------------------------------------------------------
#endif
