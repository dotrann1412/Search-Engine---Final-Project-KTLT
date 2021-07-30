#pragma once
#include <atlstr.h>
#include <string.h>
#include <cstring>

#include "function/InputBox.h"
#include "misc/Declaration.h"
#include "misc/LinkedList.h"
#include "function/Conversion.h"
#include "function/InOut.h"
#include "preprocess/FileTreeMaker.h"
#include "preprocess/Metadata.h"

using namespace std;

namespace UpdateData {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for UpdateDataForm
	/// </summary>
	public ref class UpdateDataForm : public System::Windows::Forms::Form
	{

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

	public:
		UpdateDataForm(Library* libpointer, System::String^ libPath, FileRank** filerank) {
			InitializeComponent(libpointer, libPath, filerank);
		}
		UpdateDataForm() {
			InitializeComponent();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateDataForm()
		{
			/*if (changed) {
				char dir[MAX] = "\0";
				strcpy(dir, (LPCSTR)(CStringA(sysSLibPath)));
				int ttfile = (int)totalfile;
				optimizeFileTree(dir, *library, *ranklist, ttfile, *stuff);
			}*/
			if (components)
			{
				delete components;
			}
		}


	protected:

	protected:

	private: System::Boolean changed = false;
	private: Library* library = nullptr;
	private: System::String^ sysSLibPath;
	private: FileRank** rankinglist = nullptr;

	private: System::Windows::Forms::Button^ btnAdd;
	private: System::Windows::Forms::ComboBox^ foldercbbox;

	private: System::Windows::Forms::CheckedListBox^ newfilelist;
	private: System::Windows::Forms::Button^ sltAllBtn;


	private: System::Windows::Forms::Button^ deleteBtn;



	private: System::Windows::Forms::Button^ btnAddFolder;


	private: System::Windows::Forms::Button^ btnRemoveFolder;



		   //#pragma region Windows Form Designer generated code
				   /// <summary>
				   /// Required method for Designer support - do not modify
				   /// the contents of this method with the code editor.
				   /// </summary>
		   void InitializeComponent(Library* libpointer, System::String^ libpath, FileRank** filerank)
		   {
			   InitializeComponent();

			   this->library = libpointer;
			   sysSLibPath = libpath;
			   rankinglist = filerank;

			   array<System::Object^>^ cbbItems = gcnew cli::array<System::Object^>(library->totalfolder);
			   Node* cur = (libpointer->folderlist).head;
			   for (int i = 0; cur; ++i, cur = cur->next) {
				   cbbItems[i] = gcnew System::String(cur->data);
			   }
			   foldercbbox->Items->AddRange(cbbItems);
			   foldercbbox->SelectedIndex = 0;
		   }


		   //for debugging
		   void InitializeComponent()
		   {
			   this->btnAdd = (gcnew System::Windows::Forms::Button());
			   this->foldercbbox = (gcnew System::Windows::Forms::ComboBox());
			   this->newfilelist = (gcnew System::Windows::Forms::CheckedListBox());
			   this->sltAllBtn = (gcnew System::Windows::Forms::Button());
			   this->deleteBtn = (gcnew System::Windows::Forms::Button());
			   this->btnAddFolder = (gcnew System::Windows::Forms::Button());
			   this->btnRemoveFolder = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // btnAdd
			   // 
			   this->btnAdd->Location = System::Drawing::Point(344, 93);
			   this->btnAdd->Name = L"btnAdd";
			   this->btnAdd->Size = System::Drawing::Size(154, 41);
			   this->btnAdd->TabIndex = 2;
			   this->btnAdd->Text = L"Add File";
			   this->btnAdd->UseVisualStyleBackColor = true;
			   this->btnAdd->Click += gcnew System::EventHandler(this, &UpdateDataForm::btnAddFileOnClick);
			   // 
			   // foldercbbox
			   // 
			   this->foldercbbox->FormattingEnabled = true;
			   this->foldercbbox->Location = System::Drawing::Point(21, 12);
			   this->foldercbbox->Name = L"foldercbbox";
			   this->foldercbbox->Size = System::Drawing::Size(296, 21);
			   this->foldercbbox->TabIndex = 3;
			   this->foldercbbox->SelectedIndexChanged += gcnew System::EventHandler(this, &UpdateDataForm::foldercbbox_SelectedIndexChanged);
			   // 
			   // newfilelist
			   // 
			   this->newfilelist->FormattingEnabled = true;
			   this->newfilelist->Location = System::Drawing::Point(21, 46);
			   this->newfilelist->Name = L"newfilelist";
			   this->newfilelist->Size = System::Drawing::Size(296, 229);
			   this->newfilelist->TabIndex = 4;
			   // 
			   // sltAllBtn
			   // 
			   this->sltAllBtn->Location = System::Drawing::Point(344, 234);
			   this->sltAllBtn->Name = L"sltAllBtn";
			   this->sltAllBtn->Size = System::Drawing::Size(154, 41);
			   this->sltAllBtn->TabIndex = 5;
			   this->sltAllBtn->Text = L"Select All";
			   this->sltAllBtn->UseVisualStyleBackColor = true;
			   this->sltAllBtn->Click += gcnew System::EventHandler(this, &UpdateDataForm::sltAllBtn_Click);
			   // 
			   // deleteBtn
			   // 
			   this->deleteBtn->Location = System::Drawing::Point(344, 187);
			   this->deleteBtn->Name = L"deleteBtn";
			   this->deleteBtn->Size = System::Drawing::Size(154, 41);
			   this->deleteBtn->TabIndex = 6;
			   this->deleteBtn->Text = L"Remove File";
			   this->deleteBtn->UseVisualStyleBackColor = true;
			   this->deleteBtn->Click += gcnew System::EventHandler(this, &UpdateDataForm::deleteBtn_Click);
			   // 
			   // btnAddFolder
			   // 
			   this->btnAddFolder->Location = System::Drawing::Point(344, 46);
			   this->btnAddFolder->Name = L"btnAddFolder";
			   this->btnAddFolder->Size = System::Drawing::Size(154, 41);
			   this->btnAddFolder->TabIndex = 8;
			   this->btnAddFolder->Text = L"Add Folder";
			   this->btnAddFolder->UseVisualStyleBackColor = true;
			   this->btnAddFolder->Click += gcnew System::EventHandler(this, &UpdateDataForm::BtnAddFolderOnClick);
			   // 
			   // btnRemoveFolder
			   // 
			   this->btnRemoveFolder->Location = System::Drawing::Point(344, 140);
			   this->btnRemoveFolder->Name = L"btnRemoveFolder";
			   this->btnRemoveFolder->Size = System::Drawing::Size(154, 41);
			   this->btnRemoveFolder->TabIndex = 9;
			   this->btnRemoveFolder->Text = L"Remove Folder";
			   this->btnRemoveFolder->UseVisualStyleBackColor = true;
			   this->btnRemoveFolder->Click += gcnew System::EventHandler(this, &UpdateDataForm::btnRemoveFolder_Click);
			   // 
			   // UpdateDataForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->ClientSize = System::Drawing::Size(518, 289);
			   this->Controls->Add(this->btnRemoveFolder);
			   this->Controls->Add(this->btnAddFolder);
			   this->Controls->Add(this->deleteBtn);
			   this->Controls->Add(this->sltAllBtn);
			   this->Controls->Add(this->newfilelist);
			   this->Controls->Add(this->foldercbbox);
			   this->Controls->Add(this->btnAdd);
			   this->MaximizeBox = false;
			   this->MinimizeBox = false;
			   this->Name = L"UpdateDataForm";
			   this->Text = L"Update Data";
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: void clean() {
		this->newfilelist->Sorted;
	}

		   void contentloader() {
			   newfilelist->Items->Clear();
			   int idx = foldercbbox->SelectedIndex;
			   char dir[MAX_PATH];
			   strcpy(dir, (LPCSTR)(CStringA(sysSLibPath + "\\" + foldercbbox->SelectedItem)));


			   LinkedList fileinside;
			   initialize(fileinside);
			   int temp = -1;
			   listFileInside(dir, fileinside, temp);
			   array<System::Object^>^ newfilelistitems = gcnew cli::array<System::Object^>(fileinside.size);
			   Node* node = fileinside.head;
			   for (int i = 0; node; node = node->next, ++i) {
				   newfilelistitems[i] = gcnew System::String(node->data);
			   }
			   newfilelist->Items->AddRange(newfilelistitems);
			   clean();
		   }
	private: System::Void btnAddFileOnClick(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		ofd->Multiselect = true;
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			changed = true;
			int count = ofd->FileNames->Length;
			for (int i = 0; i < count; ++i) {
				CStringA cstringsource = CStringA(ofd->FileNames[i]),
					cslibdir = CStringA(sysSLibPath),
					csfoldername = CStringA(foldercbbox->SelectedItem->ToString());
				char dir[MAX_PATH], charsource[MAX_PATH];

				strcpy(dir, (LPCSTR)(cslibdir + "\\"));
				strcat(dir, (LPCSTR)csfoldername);
				strcpy(charsource, (LPCSTR)cstringsource);
				filecopy(charsource, dir);
				char filename[MAX_PATH]; char folder[MAX_PATH];
				for (int j = strlen(charsource) - 1; j >= 0; --j) {
					if (charsource[j] == '\\') {
						strcpy(filename, charsource + j + 1);
						break;
					}
				}
				strcpy(folder, (LPCSTR)csfoldername);
				addFile(folder, filename, *library);

			}
		}
		contentloader();
	}

	private: System::Void sltAllBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		static boolean check = true;
		for (int i = 0; i < newfilelist->Items->Count; ++i) {
			newfilelist->SetItemChecked(i, check);
		}
		check = 1 - check;
	}

	private: System::Void foldercbbox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		contentloader();
	}
	private: System::Void deleteBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ deletelist = gcnew System::String(L"");

		for (int i = 0; i < newfilelist->CheckedItems->Count && i < 10; ++i)
			(deletelist += newfilelist->CheckedItems[i]) += "\n";
		deletelist += "...";

		if (System::Windows::Forms::MessageBox::Show(L"Remove: \n" + deletelist, L"Confirm Message", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
			changed = true;
			for (int i = 0; i < newfilelist->CheckedItems->Count; ++i) {
				CStringA tmp = CStringA(sysSLibPath + "\\" + foldercbbox->SelectedItem + "\\" + newfilelist->CheckedItems[i]);
				char removefile[MAX] = "";
				strcpy(removefile, (LPCSTR)tmp);
				remove(removefile);
				char filename[MAX_PATH]; char folder[MAX_PATH];
				CStringA csfoldername(foldercbbox->SelectedItem->ToString());
				CStringA csfilename(newfilelist->CheckedItems[i]->ToString());
				strcpy(folder, (LPCSTR)csfoldername);
				strcpy(filename, (LPCSTR)csfilename);
				deleteFile(folder, filename, *library, *rankinglist);
			}
		}
		contentloader();
	}
	private: System::Void BtnAddFolderOnClick(System::Object^ sender, System::EventArgs^ e) {
		char* foldername = InputBox("Enter folder name", "Add Folder", "");
		if (foldername != "") {
			char directory[MAX_PATH];
			CStringA libpath(sysSLibPath + "\\");
			strcpy(directory, libpath);
			strcat(directory, foldername);

			CreateDirectoryA(directory, NULL);
			addFolder(foldername, *library);

			foldercbbox->Items->Clear();
			array<System::Object^>^ cbbItems = gcnew cli::array<System::Object^>(library->totalfolder);
			Node* cur = (library->folderlist).head;
			for (int i = 0; cur; ++i, cur = cur->next) {
				cbbItems[i] = gcnew System::String(cur->data);
			}
			foldercbbox->Items->AddRange(cbbItems);
			foldercbbox->SelectedIndex = 0;
			System::Windows::Forms::MessageBox::Show("Added folder \"" + gcnew String(foldername) + "\"", L"Add Folder");
		}
		else;

		contentloader();
	}
	private: System::Void btnRemoveFolder_Click(System::Object^ sender, System::EventArgs^ e) {

		int index = foldercbbox->SelectedIndex;
		if (System::Windows::Forms::MessageBox::Show(L"Remove: " + foldercbbox->SelectedItem + " from current library?\n", L"Confirm Message", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
			changed = true;
			char dir[MAX] = "", foldername[MAX] = "";
			//System::String^ selecteditem = gcnew System::String(foldercbbox->SelectedItem->ToString());
			strcpy(dir, (LPCSTR)(CStringA(sysSLibPath + "\\" + foldercbbox->SelectedItem)));
			strcpy(foldername, (LPCSTR)(CStringA("" + foldercbbox->SelectedItem)));

			FileRank* a = *rankinglist;
			removedirectory(dir);
			deleteFolder(foldername, *library, a);
			foldercbbox->Items->RemoveAt(foldercbbox->SelectedIndex);
			System::Windows::Forms::MessageBox::Show(L"Done\n", L"System Message", MessageBoxButtons::OK);
			if (foldercbbox->Items->Count != 0) foldercbbox->SelectedIndex = 0;
		}
	}
	};
}