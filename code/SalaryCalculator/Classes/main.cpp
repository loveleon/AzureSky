#include "Header.h"
#include "../UI.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	SalaryCalculator::UI ui;
	ui.ShowDialog();

	return 0;
}