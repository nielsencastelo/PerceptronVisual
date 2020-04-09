//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TFrmPrincipal : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TImage *Image1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *EditBias;
	TEdit *EditX1;
	TEdit *EditX2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *BtnTreinar;
	TButton *BtnTestar;
	TEdit *EditW0;
	TEdit *EditW1;
	TEdit *EditW2;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *EditY;
	TToolBar *ToolBar1;
	TLabel *Label4;
	TComboBox *CbGate;
	TSpeedButton *SpeedButton1;
	TStyleBook *StyleBook1;
	TComboBox *CbAlgorithm;
	TLabel *Label12;
	void __fastcall BtnTreinarClick(TObject *Sender);
	void __fastcall BtnTestarClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	double e [4][7];
//	{
//			{ 0, 0, 0, 0, 1, 1, 0 },
//			{ 0, 1, 1, 0, 0, 1, 1 },
//			{ 1, 0, 1, 0, 0, 1, 1 },
//			{ 1, 1, 1, 1, 0, 0, 0 }
//			};
	double w[3];
	double y;
	double N;
	int BIAS;
	int MAX_EPOCAS;
	int operacao;
	double erro_max;
	double erro_global;
	double eqm_ant, eqm_atual;
		
public:		// User declarations
	__fastcall TFrmPrincipal(TComponent* Owner);
	void corrigirPeso(int exemplo, int saida);
	int executar(int x1, int x2);
	double eqm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmPrincipal *FrmPrincipal;
//---------------------------------------------------------------------------
#endif
