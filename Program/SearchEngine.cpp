#define _CRT_SECURE_NO_WARNINGS
#include "SearchEngine.h"
#include "UpdateDataForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

int main(array<String^>^ argv) {
	Application::SetCompatibleTextRenderingDefault(0);	
	Application::EnableVisualStyles();
	SearchEngine::MainForm frm;
	Application::Run(% frm);
	return 0;
}