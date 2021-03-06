#pragma once

#include "UPCCodeScanner.h"
#include "CodeNeunUndDreizig.h"

//Diese Klasse wurde automatisch von Visual Studio generiert
namespace AVPRGProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Zusammenfassung f�r GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
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

		//Die Methode MarshalString stammt vom Microsoft Developer Network(MSDN)
		void MarshalString ( String ^ s, std::string& os );
		void onStart();
		void onLoad();

	private: System::Windows::Forms::ComboBox^  comboBoxBarcode;
	private: System::Windows::Forms::Label^  ResultLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  labelResult;

			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->laden = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->barcodeImage = (gcnew System::Windows::Forms::PictureBox());
			this->comboBoxBarcode = (gcnew System::Windows::Forms::ComboBox());
			this->ResultLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelResult = (gcnew System::Windows::Forms::Label());
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
			this->comboBoxBarcode->TabIndex = 3;
			// 
			// ResultLabel
			// 
			this->ResultLabel->Location = System::Drawing::Point(0, 0);
			this->ResultLabel->Name = L"ResultLabel";
			this->ResultLabel->Size = System::Drawing::Size(100, 23);
			this->ResultLabel->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(549, 388);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 18);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Ergebnis:";
			// 
			// labelResult
			// 
			this->labelResult->AutoSize = true;
			this->labelResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelResult->Location = System::Drawing::Point(622, 388);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(0, 18);
			this->labelResult->TabIndex = 6;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(784, 424);
			this->Controls->Add(this->labelResult);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ResultLabel);
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
				comboBoxBarcode->SelectedIndex = 0;
			 }
	private: System::Void startButton_Click(System::Object^  sender, System::EventArgs^  e) {
				onStart();
			 }
	private: System::Void laden_Click(System::Object^  sender, System::EventArgs^  e) {
				onLoad();
			 }
	};
}
