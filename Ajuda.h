//---------------------------------------------------------------------------

#ifndef AjudaH
#define AjudaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmAjuda : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
private:	// User declarations
public:		// User declarations
	__fastcall TFrmAjuda(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmAjuda *FrmAjuda;
//---------------------------------------------------------------------------
#endif
