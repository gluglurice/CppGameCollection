#include "Solution.h"

#include <windows.h>

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return CSolution::GetInstance()->WinRun(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}
