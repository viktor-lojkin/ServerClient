#pragma once

#include "RZD_Client_Impl.h"


namespace RZDClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Client : public System::Windows::Forms::Form
	{
	public:
		explicit Client(Client_Impl* client_impl , std::string* port , std::string* fileName , std::string* fileText)
		:               client_impl_(client_impl),        port_(port),    fileName_(fileName),    fileText_(fileText)
		{
			InitializeComponent();
		}

	protected:
		~Client()
		{
			if (components) { delete components; }
			if (is_connected) { client_impl_->Shutdown(); }
		}

	private: System::Windows::Forms::Label^ File_Name_Label;
	private: System::Windows::Forms::Label^ File_Text_Label;
	private: System::Windows::Forms::Label^ Server_Adress_Label;
	private: System::Windows::Forms::Label^ Path_Hint;


	private: System::Windows::Forms::Button^ Connect;
	private: System::Windows::Forms::Button^ Create_File;

	private: System::Windows::Forms::TextBox^ Server_Port;
	private: System::Windows::Forms::TextBox^ File_Name;
	private: System::Windows::Forms::TextBox^ File_Text;
	private: System::Windows::Forms::Label^ Port_Hint;


	private:
		System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Connect = (gcnew System::Windows::Forms::Button());
			this->Create_File = (gcnew System::Windows::Forms::Button());
			this->Server_Port = (gcnew System::Windows::Forms::TextBox());
			this->File_Name = (gcnew System::Windows::Forms::TextBox());
			this->File_Text = (gcnew System::Windows::Forms::TextBox());
			this->File_Name_Label = (gcnew System::Windows::Forms::Label());
			this->File_Text_Label = (gcnew System::Windows::Forms::Label());
			this->Server_Adress_Label = (gcnew System::Windows::Forms::Label());
			this->Path_Hint = (gcnew System::Windows::Forms::Label());
			this->Port_Hint = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Connect
			// 
			this->Connect->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Connect->Location = System::Drawing::Point(256, 43);
			this->Connect->Name = L"Connect";
			this->Connect->Size = System::Drawing::Size(128, 26);
			this->Connect->TabIndex = 0;
			this->Connect->Text = L"Connect";
			this->Connect->UseVisualStyleBackColor = true;
			this->Connect->Click += gcnew System::EventHandler(this, &Client::Connect_Click);
			// 
			// Create_File
			// 
			this->Create_File->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Create_File->Location = System::Drawing::Point(540, 151);
			this->Create_File->Name = L"Create_File";
			this->Create_File->Size = System::Drawing::Size(88, 80);
			this->Create_File->TabIndex = 1;
			this->Create_File->Text = L"Create File";
			this->Create_File->UseVisualStyleBackColor = true;
			this->Create_File->Click += gcnew System::EventHandler(this, &Client::Create_File_Click);
			// 
			// Server_Port
			// 
			this->Server_Port->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Server_Port->Location = System::Drawing::Point(13, 43);
			this->Server_Port->MaxLength = 15;
			this->Server_Port->Name = L"Server_Port";
			this->Server_Port->Size = System::Drawing::Size(224, 26);
			this->Server_Port->TabIndex = 2;
			// 
			// File_Name
			// 
			this->File_Name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->File_Name->Location = System::Drawing::Point(13, 151);
			this->File_Name->MaxLength = 100;
			this->File_Name->Name = L"File_Name";
			this->File_Name->Size = System::Drawing::Size(502, 26);
			this->File_Name->TabIndex = 3;
			// 
			// File_Text
			// 
			this->File_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->File_Text->Location = System::Drawing::Point(13, 205);
			this->File_Text->MaxLength = 400;
			this->File_Text->Name = L"File_Text";
			this->File_Text->Size = System::Drawing::Size(502, 26);
			this->File_Text->TabIndex = 4;
			// 
			// File_Name_Label
			// 
			this->File_Name_Label->AutoSize = true;
			this->File_Name_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->File_Name_Label->Location = System::Drawing::Point(13, 128);
			this->File_Name_Label->Name = L"File_Name_Label";
			this->File_Name_Label->Size = System::Drawing::Size(80, 20);
			this->File_Name_Label->TabIndex = 5;
			this->File_Name_Label->Text = L"File Name";
			// 
			// File_Text_Label
			// 
			this->File_Text_Label->AutoSize = true;
			this->File_Text_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->File_Text_Label->Location = System::Drawing::Point(12, 182);
			this->File_Text_Label->Name = L"File_Text_Label";
			this->File_Text_Label->Size = System::Drawing::Size(68, 20);
			this->File_Text_Label->TabIndex = 6;
			this->File_Text_Label->Text = L"File Text";
			// 
			// Server_Adress_Label
			// 
			this->Server_Adress_Label->AutoSize = true;
			this->Server_Adress_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->Server_Adress_Label->Location = System::Drawing::Point(13, 20);
			this->Server_Adress_Label->Name = L"Server_Adress_Label";
			this->Server_Adress_Label->Size = System::Drawing::Size(88, 20);
			this->Server_Adress_Label->TabIndex = 7;
			this->Server_Adress_Label->Text = L"Server Port";
			// 
			// Path_Hint
			// 
			this->Path_Hint->AutoSize = true;
			this->Path_Hint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Path_Hint->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->Path_Hint->Location = System::Drawing::Point(100, 128);
			this->Path_Hint->Name = L"Path_Hint";
			this->Path_Hint->Size = System::Drawing::Size(194, 20);
			this->Path_Hint->TabIndex = 8;
			this->Path_Hint->Text = L"relative path to executable";
			// 
			// Port_Hint
			// 
			this->Port_Hint->AutoSize = true;
			this->Port_Hint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Port_Hint->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->Port_Hint->Location = System::Drawing::Point(100, 20);
			this->Port_Hint->Name = L"Port_Hint";
			this->Port_Hint->Size = System::Drawing::Size(109, 20);
			this->Port_Hint->TabIndex = 9;
			this->Port_Hint->Text = L"wait for 27015";
			// 
			// Client
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(640, 261);
			this->Controls->Add(this->Port_Hint);
			this->Controls->Add(this->Path_Hint);
			this->Controls->Add(this->Server_Adress_Label);
			this->Controls->Add(this->File_Text_Label);
			this->Controls->Add(this->File_Name_Label);
			this->Controls->Add(this->File_Text);
			this->Controls->Add(this->File_Name);
			this->Controls->Add(this->Server_Port);
			this->Controls->Add(this->Create_File);
			this->Controls->Add(this->Connect);
			this->Name = L"Client";
			this->Text = L"Client";
			this->Load += gcnew System::EventHandler(this, &Client::Client_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
		private: bool is_connected{ false };

		private: Client_Impl *client_impl_;

		private: std::string *port_;
		private: std::string *fileName_;
		private: std::string *fileText_;

		// Преобразуем String^ в std::string
		private: System::Void Convert_to_std_String(String^ str, std::string* std_str) {
			for each (char c in str) {		
				std_str->push_back(c);
			}
		}
		private: System::Void Connect_Click(System::Object^ sender, System::EventArgs^ e) {
			
			String^ server_address = this->Server_Port->Text;
			if (String::IsNullOrWhiteSpace(server_address)) {
				std::cout << "Server port is empty. Please, fill in with 27015" << std::endl;
			}
			else if (server_address != "27015") {
				std::cout << "Server port is incorrect. Please, fill in with 27015" << std::endl;
			}

			Convert_to_std_String(server_address, port_);

			client_impl_->Set_Port(*port_); 
			int res = client_impl_->Connect();
			if (!res) { is_connected = true; }
		}

		private: System::Void Create_File_Click(System::Object^ sender, System::EventArgs^ e) {
			
			String^ fileName = this->File_Name->Text;
			if (String::IsNullOrWhiteSpace(fileName)) {
				std::cout << "File name is empty, write something" << std::endl;
			}

			String^ fileText = this->File_Text->Text;
			if (String::IsNullOrWhiteSpace(fileText)) {
				std::cout << "File is empty, write something" << std::endl;
			}

			Convert_to_std_String(fileName, fileName_);
			Convert_to_std_String(fileText, fileText_);

			client_impl_->Set_fileName(*fileName_);
			client_impl_->Set_fileText(*fileText_);

			client_impl_->Create_File();
		}


		private: System::Void Client_Load(System::Object^ sender, System::EventArgs^ e) {
		}
};
}
