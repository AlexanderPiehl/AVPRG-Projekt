#pragma once

#include "UPCCodeScanner.h"
#include "CodeNeunUndDreizig.h"

namespace AVPRGProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Zusammenfassung für GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  laden;
	private: System::Windows::Forms::Button^  startButton;

	private: System::Windows::Forms::PictureBox^  barcodeImage;

	protected: 

	private:
		String^ path;
	private: System::Windows::Forms::ComboBox^  comboBoxBarcode;
	private: System::Windows::Forms::Label^  resultLabel;

			 System::ComponentModel::Container ^components;
		void MarshalString ( String ^ s, std::string& os );

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->laden = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->barcodeImage = (gcnew System::Windows::Forms::PictureBox());
			this->comboBoxBarcode = (gcnew System::Windows::Forms::ComboBox());
			this->resultLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->barcodeImage))->BeginInit();
			this->SuspendLayout();
			// 
			// laden
			// 
			this->laden->Location = System::Drawing::Point(28, 388);
			this->laden->Name = L"laden";
			this->laden->Size = System::Drawing::Size(160, 30);
			this->laden->TabIndex = 0;
			this->laden->Text = L"Laden";
			this->laden->UseVisualStyleBackColor = true;
			this->laden->Click += gcnew System::EventHandler(this, &GUI::laden_Click);
			// 
			// startButton
			// 
			this->startButton->Enabled = false;
			this->startButton->Location = System::Drawing::Point(221, 388);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(160, 30);
			this->startButton->TabIndex = 1;
			this->startButton->Text = L"Start";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &GUI::startButton_Click);
			// 
			// barcodeImage
			// 
			this->barcodeImage->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"barcodeImage.InitialImage")));
			this->barcodeImage->Location = System::Drawing::Point(28, 12);
			this->barcodeImage->Name = L"barcodeImage";
			this->barcodeImage->Size = System::Drawing::Size(698, 331);
			this->barcodeImage->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->barcodeImage->TabIndex = 2;
			this->barcodeImage->TabStop = false;
			// 
			// comboBoxBarcode
			// 
			this->comboBoxBarcode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxBarcode->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"UPC-Code", L"Code39"});
			this->comboBoxBarcode->Location = System::Drawing::Point(404, 388);
			this->comboBoxBarcode->Name = L"comboBoxBarcode";
			this->comboBoxBarcode->Size = System::Drawing::Size(139, 21);
			this->comboBoxBarcode->TabIndex = 0;
			// 
			// resultLabel
			// 
			this->resultLabel->AutoSize = true;
			this->resultLabel->Location = System::Drawing::Point(579, 388);
			this->resultLabel->Name = L"resultLabel";
			this->resultLabel->Size = System::Drawing::Size(0, 13);
			this->resultLabel->TabIndex = 4;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 424);
			this->Controls->Add(this->resultLabel);
			this->Controls->Add(this->comboBoxBarcode);
			this->Controls->Add(this->barcodeImage);
			this->Controls->Add(this->startButton);
			this->Controls->Add(this->laden);
			this->Name = L"GUI";
			this->Text = L"Barcode Leser";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->barcodeImage))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
	  
			 }
	private: System::Void startButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 int barcodeIndex = comboBoxBarcode->SelectedIndex;
				 CodeScanner *scanner;
				 switch(barcodeIndex)
				 {
				 case 0:
					 {
					 scanner = new UPCCodeScanner();
					 MarshalString(path, scanner->path);
					 scanner->readBarcode();
					 if(scanner->result.length() > 0)
					 {
						String^ labeltext = gcnew String(scanner->result.c_str());
						resultLabel->Text = labeltext;
					 }
					 delete scanner;
					 break;
					 }
				 case 1:
					 {
					 scanner = new CodeNeunUndDreizig();
					 MarshalString(path, scanner->path);
					 scanner->readBarcode();
					 if(scanner->result.length() > 0)
					 {
						String^ labeltext = gcnew String(scanner->result.c_str());
						resultLabel->Text = labeltext;
					 }
					 delete scanner;
					 break;
					 }
				 }	
			 }
	private: System::Void laden_Click(System::Object^  sender, System::EventArgs^  e) {
				 Stream^ myStream;
      OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

      openFileDialog1->InitialDirectory = "c:\\";
      openFileDialog1->Filter = "png files (*.png)|*.png|jpg files (*.jpg)|*.jpg|All files (*.*)|*.*";
      openFileDialog1->FilterIndex = 2;
      openFileDialog1->RestoreDirectory = true;

      if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
      {
         if ( (myStream = openFileDialog1->OpenFile()) != nullptr )
         {
			 try
			 {
				path = openFileDialog1->FileName;
				barcodeImage->Image->FromFile(path);
				barcodeImage->Image = System::Drawing::Image::FromFile(path);
				startButton->Enabled = true;
				myStream->Close();
			 }
			 catch(System::Exception^ ex)
			 {
				  MessageBox::Show("Das Bild konnte leider nicht geladen werden. Bitte wählen Sie ein anderes Bild aus.","Warnung");
			 }
         }
      }
	}
};
}
