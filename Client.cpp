#include "Client.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	std::string port;
	std::string fileName;
	std::string fileText;
	
	Client_Impl client_impl;

	RZDClient::Client client(&client_impl, &port, &fileName, &fileText);

	Application::Run(% client);

}