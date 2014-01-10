#include "GUI.h"

using namespace AVPRGProjekt;
//Methode wurde von Microsoft übernommen http://msdn.microsoft.com/de-de/library/1b4az623.aspx
//Zugriif am 08.01.2014
void GUI::MarshalString ( String ^ s, std::string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void GUI::onStart()
{
	int barcodeIndex = comboBoxBarcode->SelectedIndex;
	int result = 0;
	CodeScanner *scanner;
	labelResult->Text = "";
	switch(barcodeIndex)
	{
	case 0:
		{
		scanner = new UPCCodeScanner();
		MarshalString(path, scanner->path);
		result =  scanner->readBarcode();
		break;
		}
	case 1:
		{
		scanner = new CodeNeunUndDreizig();
		MarshalString(path, scanner->path);
		result = scanner->readBarcode();
					 
		break;
		}
	}
	if(1 == result)
	{
		String ^labelText = gcnew String(scanner->result.c_str());
		labelResult->Text = labelText;
	}
	else if( 0 > result)
	{
		MessageBox::Show("Es konnte leider kein Barcode ermittelt werden.","Warnung");
	}
	delete scanner;
}

void GUI::onLoad()
{
	Stream^ fileSteam;
	OpenFileDialog^ openImageDialog = gcnew OpenFileDialog;

	openImageDialog->InitialDirectory = "C:\\Users\\%USERNAME%\\";
	openImageDialog->Filter = "PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg|All files (*.*)|*.*";
	openImageDialog->FilterIndex = 2;
	openImageDialog->RestoreDirectory = true;

	if ( openImageDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK )
	{
		if ( (fileSteam = openImageDialog->OpenFile()) != nullptr )
		{
			try
			{
				path = openImageDialog->FileName;
				barcodeImage->Image = System::Drawing::Image::FromFile(path);
				startButton->Enabled = true;
				fileSteam->Close();
				labelResult->Text = "";
			}
			catch(System::Exception^ ex)
			{
				MessageBox::Show("Das Bild konnte leider nicht geladen werden. Bitte wählen Sie ein anderes Bild aus.","Warnung");
			}
		}
	}
}