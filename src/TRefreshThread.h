//---------------------------------------------------------------------------

#ifndef TRefreshThreadH
#define TRefreshThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TRefreshThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TRefreshThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
