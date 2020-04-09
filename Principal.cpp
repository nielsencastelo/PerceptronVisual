//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Principal.h"
#include "Ajuda.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.NmXhdpiPh.fmx", _PLAT_ANDROID)
#pragma resource ("*.LgXhdpiTb.fmx", _PLAT_ANDROID)

#include <ctime>
#include <cstdlib>

TFrmPrincipal *FrmPrincipal;
//---------------------------------------------------------------------------
__fastcall TFrmPrincipal::TFrmPrincipal(TComponent* Owner)
	: TForm(Owner)
{
	y = 0;
	N = 0.1;
	BIAS =  StrToInt(EditBias->Text);   // Pega o valor do bias no Edit
	MAX_EPOCAS = 1000; // Pega o valor da Época
	operacao = 0;
	e[0][0] = 0, e[0][1] = 0, e[0][2] = 0, e[0][3] = 0, e[0][4] = 1, e[0][5] = 1, e[0][6] = 0,
	e[1][0] = 0, e[1][1] = 1, e[1][2] = 1, e[1][3] = 0, e[1][4] = 0, e[1][5] = 1, e[1][6] = 1,
	e[2][0] = 1, e[2][1] = 0, e[2][2] = 1, e[2][3] = 0, e[2][4] = 0, e[2][5] = 1, e[2][6] = 1,
	e[3][0] = 1, e[3][1] = 1, e[3][2] = 1, e[3][3] = 1, e[3][4] = 0, e[3][5] = 0, e[3][6] = 0;

	erro_max    = 1E-9;
}

//---MINHAS FUNÇÕES---------------------------------------------------------------------
void TFrmPrincipal::corrigirPeso(int exemplo, int saida)
{

	w[0] = w[0] + (N * (e[exemplo][operacao] - saida) * (BIAS));
	w[1] = w[1] + (N * (e[exemplo][operacao] - saida) * e[exemplo][0]);
	w[2] = w[2] + (N * (e[exemplo][operacao] - saida) * e[exemplo][1]);
}
int TFrmPrincipal::executar(int x1, int x2)
{
	// Somatorio NET
	y = ((BIAS) * w[0]) + (x1 * w[1]) + (x2 * w[2]);
	// Funcao de Transferencia
	if (y > 0)
	{
		return 1;
	}
	return 0;
}
double TFrmPrincipal::eqm()
{
    double er = 0;
    double u[4];

    for (int i = 0; i < 4; i++)
    {
        u[i] = ((BIAS) * w[0]) + (e[i][0] * w[1]) + (e[i][1] * w[2]);
        er = er + pow(e[i][operacao] - u[i], 2);
    }
    return er /4;
}

void __fastcall TFrmPrincipal::BtnTreinarClick(TObject *Sender)
{
	// Verifica qual o algoritmo
	if (CbAlgorithm->ItemIndex == 0)   // PERCEPTRON
	{
		// Perceptron
		bool treinou;
		int epoca = 0;
		BIAS =  StrToInt(EditBias->Text);
		int op = CbGate->ItemIndex;

		srand( (unsigned)time(NULL) );

		if ((op >= 0) && (op < 5))
		{
			operacao = op + 2;
		}
		for (int i = 0; i < 3; i++)
		{
			w[i] = -1 + ( rand() % 1 ); // [-1,1]
		}

		do
		{
			treinou = true;
			for (int i = 0; i < 4; i++)
			{
				int s = executar(e[i][0], e[i][1]);
				if (s != e[i][operacao])
				{
					corrigirPeso(i, s);
					treinou = false;
				}
			}
			epoca++;
		} while ((treinou == false) && (epoca < MAX_EPOCAS));

		ShowMessage("Trained with " + IntToStr(epoca) + " epochs!");

		if (treinou == false)
		{
			ShowMessage("The algorithm could not converge!");
		}

		// Set os W's
		EditW0->Text = FormatFloat("0.00",w[0]);
		EditW1->Text = FormatFloat("0.00",w[1]);
		EditW2->Text = FormatFloat("0.00",w[2]);
	}
	else if (CbAlgorithm->ItemIndex == 1) // ADALINE
	{
        int epoca = 0;
		bool treinou;
		BIAS =  StrToInt(EditBias->Text);
		int op = CbGate->ItemIndex;

		srand( (unsigned)time(NULL) );

		if ((op >= 0) && (op < 5))
		{
			operacao = op + 2;
		}
		for (int i = 0; i < 3; i++)
		{
			w[i] = -1 + ( rand() % 1 ); // [-1,1]
		}

		while(true)
		{
			eqm_ant = eqm();
			for (int i = 0; i < 4; i++)
			{
				int s = executar(e[i][0], e[i][1]);
				if (s != e[i][operacao])
				{
					corrigirPeso(i, s);
					treinou = false;
				}
			}
			epoca++;
			eqm_atual = eqm();
			erro_global = pow((eqm_atual - eqm_ant),2);


			if (erro_global < erro_max)
			{
				treinou = true;
				break;
			}

			if (epoca == MAX_EPOCAS)
				break;
		}

    	ShowMessage("The algorithm trained " + IntToStr(epoca) + " epochs...");

		if (treinou == false)
		{
			ShowMessage("The algorithm could not converge...");
		}
		// Set os W's
		EditW0->Text = FormatFloat("0.00",w[0]);
		EditW1->Text = FormatFloat("0.00",w[1]);
		EditW2->Text = FormatFloat("0.00",w[2]);

	}

}
//---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::BtnTestarClick(TObject *Sender)
{
	int y = executar(StrToInt(EditX1->Text), StrToInt(EditX2->Text));
	EditY->Text = IntToStr(y);
}
//---------------------------------------------------------------------------




void __fastcall TFrmPrincipal::SpeedButton1Click(TObject *Sender)
{
	TFrmAjuda *FrmAjuda =  new TFrmAjuda(Application);
	FrmAjuda->Show();
}
//---------------------------------------------------------------------------

