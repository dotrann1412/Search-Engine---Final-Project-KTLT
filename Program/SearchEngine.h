#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <atlstr.h>
#include <string.h>
#include <cstring>

#include "UpdateDataForm.h"

#include "misc/Declaration.h"
#include "misc/Structure.h"
#include "misc/LinkedList.h"

#include "preprocess/Metadata.h"

#include "function/Conversion.h"
#include "function/DataExtract.h"
#include "function/InOut.h"

#include "search/Ranking.h"

namespace SearchEngine {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	internal: System::Windows::Forms::Button^ btnFileChooser;
	private:

	private:
	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ updateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::Label^ label3;

	public: System::String^ UserInput;
	public: System::String^ LibPath;
	public: Library* libpointer = nullptr;
	public: FileRank** rankinglist = nullptr;
	public: ExtractComponents* stuffpointer = nullptr;
	private: System::Windows::Forms::ToolStripMenuItem^ optimizeToolStripMenuItem;
	public:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnFileChooser = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->updateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optimizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->textBox1->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->textBox1->Location = System::Drawing::Point(110, 35);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(468, 24);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Choose library path";
			// 
			// btnFileChooser
			// 
			this->btnFileChooser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11));
			this->btnFileChooser->Location = System::Drawing::Point(598, 35);
			this->btnFileChooser->Name = L"btnFileChooser";
			this->btnFileChooser->Size = System::Drawing::Size(63, 24);
			this->btnFileChooser->TabIndex = 1;
			this->btnFileChooser->Text = L"...";
			this->btnFileChooser->UseCompatibleTextRendering = true;
			this->btnFileChooser->UseVisualStyleBackColor = true;
			this->btnFileChooser->Click += gcnew System::EventHandler(this, &MainForm::btnFileChooser_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->label1->Location = System::Drawing::Point(14, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 18);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Library Path:";
			// 
			// textBox2
			// 
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Enabled = false;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->textBox2->Location = System::Drawing::Point(372, 109);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(289, 24);
			this->textBox2->TabIndex = 3;
			// 
			// btnSearch
			// 
			this->btnSearch->Enabled = false;
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->btnSearch->Location = System::Drawing::Point(372, 139);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(289, 67);
			this->btnSearch->TabIndex = 4;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &MainForm::btnSearch_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(17, 109);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(333, 290);
			this->listBox1->TabIndex = 5;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listBox1_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->label2->Location = System::Drawing::Point(138, 85);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 18);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Related Result";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->updateToolStripMenuItem,
					this->resetToolStripMenuItem, this->optimizeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// updateToolStripMenuItem
			// 
			this->updateToolStripMenuItem->Name = L"updateToolStripMenuItem";
			this->updateToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->updateToolStripMenuItem->Text = L"Update";
			this->updateToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::updateToolStripMenuItem_Click);
			// 
			// resetToolStripMenuItem
			// 
			this->resetToolStripMenuItem->Name = L"resetToolStripMenuItem";
			this->resetToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->resetToolStripMenuItem->Text = L"Reset";
			this->resetToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::resetToolStripMenuItem_Click);
			// 
			// optimizeToolStripMenuItem
			// 
			this->optimizeToolStripMenuItem->Name = L"optimizeToolStripMenuItem";
			this->optimizeToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->optimizeToolStripMenuItem->Text = L"Optimize";
			this->optimizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::optimizeToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(28, 28);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->aboutToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(678, 24);
			this->menuStrip1->TabIndex = 7;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->label3->Location = System::Drawing::Point(438, 376);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(212, 25);
			this->label3->TabIndex = 8;
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(678, 426);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnFileChooser);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Search Engine";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		void UpdateListBoxItems() {
			listBox1->Items->Clear();

			array<System::Object^>^ lstBoxItems = gcnew cli::array<System::Object^>(libpointer->totalfolder);

			for (int i = 0; i < libpointer->totalfolder; ++i) lstBoxItems[i] = gcnew System::String((libpointer->charfolderlist)[i]);

			listBox1->Items->AddRange(lstBoxItems);
		}

	private: System::Boolean preLoad()
	{
		/// Load a new path
		ExtractComponents stuff;
		initialize(stuff);
		if (stuffpointer == nullptr) {
			loadingComponents(stuff);
			stuffpointer = new ExtractComponents(stuff);
		}
		else stuff = *stuffpointer;


		if (libpointer != nullptr) {
			deleteAll(*libpointer);
			libpointer = nullptr;
		}

		if (rankinglist != nullptr) {
			delete[](*rankinglist);
		}


		CStringA csStringPath(LibPath);
		char mainFolderPath[MAX + 1];
		strcpy(mainFolderPath, (LPCSTR)csStringPath);

		Library lib;
		initialize(lib);

		FileRank* _rankinglist = nullptr;
		dataUpdate(mainFolderPath, lib, _rankinglist, stuff);
		libpointer = new Library(lib);
		rankinglist = new FileRank * (_rankinglist);
		;

		if (lib.totalfile > 0 && lib.totalfolder > 0) {

			UpdateListBoxItems();

			return true;
		}
		else
			return false;

	}

	private: System::Void Searching()
	{

		Library lib = *libpointer;
		ExtractComponents stuff = *stuffpointer;

		WCHAR wcharuserinput[MAX + 1];
		CStringW cstringuserinput(UserInput);
		wcscpy(wcharuserinput, (LPCWSTR)cstringuserinput);
		uint16_t* userinput;
		wcharToInt16(wcharuserinput, userinput);

		FileRank* _rankinglist = *rankinglist;

		int len = wcslen(wcharuserinput);
		int size = len * sizeof(uint16_t);
		dataExtract(userinput, size, stuff);
		len = size / sizeof(uint16_t);

		searchFile(userinput, len, _rankinglist, lib.totalfile, stuff);

		char charlibpath[MAX_PATH];
		CStringA csstringdir(LibPath);
		strcpy(charlibpath, (LPCSTR)csstringdir);

		int numfile = 0;
		for (int i = 0; i < lib.totalfile; ++i) {
			if (_rankinglist[i].score != 0 && numfile < 20) ++numfile; else break;
		}

		listBox1->Items->Clear();
		array<System::Object^>^ lstBoxItems = gcnew cli::array<System::Object^>(numfile);
		char buffer[MAX];
		for (int i = 0; i < numfile; ++i) {
			itoa(i + 1, buffer, 10);
			strcat(buffer, ". ");
			strcat(buffer, lib.charfilelist[_rankinglist[i].fileindex]);
			lstBoxItems[i] = gcnew System::String(buffer);
		}
		listBox1->Items->AddRange(lstBoxItems);
		label3->Text = L"Done!";
		label3->Refresh();
	}
	private: System::Void btnFileChooser_Click(System::Object^ sender, System::EventArgs^ e) {
		//__Choose Lib Folder


		FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
		fbd->Description = L"Chọn đường dẫn thư viện";
		if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->LibPath = gcnew System::String(fbd->SelectedPath);
			this->label3->Text = L"Loading library...";
			this->label3->Refresh();
			if (preLoad()) {
				this->label3->Text = L"Loading completed";
				this->label3->Refresh();
				UserInput = "";
				textBox1->Text = fbd->SelectedPath;
				textBox2->Enabled = true;
				this->btnSearch->Enabled = true;
			}
			else System::Windows::Forms::MessageBox::Show(L"Đường dẫn phù hợp là đường dẫn của thư mục cha.\nThư mục cha là thư mục chứa các thư mục con được đặt tên theo các chủ đề.\nBên trong mỗi thư mục con này có các văn bản của chủ đề tương ứng.", L"Đường dẫn không phù hợp");
		}
		else System::Windows::Forms::MessageBox::Show(L"Chọn các folder chứa tài liệu để tìm kiếm dễ dàng", L"Gợi ý!");
	}
	private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		//when user click [search]
		this->label3->Text = L"";
		this->label3->Refresh();
		UserInput = textBox2->Text;
		this->textBox2->Text = "";
		if (UserInput == "") {
			System::Windows::Forms::MessageBox::Show(L"Thử một vài từ khoá khác như: Con bo cuoi, con tho, ...", L"Từ khoá không hợp lệ");
		}
		else {
			label3->Text = "Searching...";
			label3->Refresh();
			Searching();

		}
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		//exit button 
		System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(L"Thoát chương trình", L"", MessageBoxButtons::YesNo);
		if (dr == System::Windows::Forms::DialogResult::Yes)
			this->~MainForm();
		else;
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		//choose on listbox

		Library lib = *libpointer;

		if (UserInput == "")
			System::Windows::Forms::MessageBox::Show(listBox1->SelectedItem->ToString(), L"Đã chọn");
		else {
			int idx = listBox1->SelectedIndex;
			CStringW cstringLibPath(LibPath);
			WCHAR wcharlibpath[MAX + 1];
			wcscpy(wcharlibpath, (LPCWSTR)cstringLibPath);
			char path[MAX + 1] = "\0";
			wcharToChar(wcharlibpath, path);
			FileRank* _rankinglist = *rankinglist;


			strcat(path, "\\\0");
			strcat(path, lib.charfolderlist[_rankinglist[idx].folderindex]);
			strcat(path, "\\\0");
			strcat(path, lib.charfilelist[_rankinglist[idx].fileindex]);
			strcat(path, "\0");

			int maxscore = max(_rankinglist[0].score, 1);
			int filechoosedscore = min(100, _rankinglist[idx].score * 100 / maxscore);

			WCHAR* content = nullptr;
			int temp = 200;
			loadFileContent(path, content, temp);
			System::String^ sysslibpath = gcnew System::String(LibPath);
			System::String^ sysscontent = gcnew System::String(content);
			//System::String^ syssfilechoosedscore = gcnew System::String(parseInt(filechoosedscore));
			if (content) {
				System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(sysscontent + L"......)\n" + "Score: " + filechoosedscore, sysslibpath);
				if (dr == System::Windows::Forms::DialogResult::OK) {
					//System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(sysscontent + L"......(Nhấn [OK] để thêm chi tiết.)\n" + "Score: " + filechoosedscore, sysslibpath);
				}
				else;
			}

		}
	}
	private: System::Void resetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		//reset button
		if (libpointer == nullptr) {
			System::Windows::Forms::MessageBox::Show(L"Chương trình đã ở trạng thái mặc định", L"Reset");
			return;
		}
		System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(L"Xoá tất cả dữ liệu và đưa chương trình về trạng thái mặc định ?", L"Reset", MessageBoxButtons::YesNo);
		if (dr == System::Windows::Forms::DialogResult::Yes) {
			remove(MetadataPath);
			remove(IndexPath);
			if (libpointer != nullptr) deleteAll(*libpointer);
			libpointer = nullptr;
			if (rankinglist != nullptr) {
				delete[](*rankinglist);
				rankinglist = nullptr;
			}

			listBox1->Items->Clear();
			textBox1->Text = L"Choose library path";
			textBox2->Enabled = false;
			this->btnSearch->Enabled = false;
			this->label3->Text = "";
		}
		else;
	}
	private: System::Void updateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		//Application::Run(gcnew UpdateData::UpdateDataForm(charfolderlist, folderlistcount));
		if (libpointer == nullptr) {
			System::Windows::Forms::MessageBox::Show(L"Vui lòng chọn thư viện trước khi sử dụng chức năng này", L"Update");
		}
		else {
			this->Enabled = false;
			int totalfile = libpointer->totalfile;


			this->label3->Text = L"Updating data";
			this->label3->Refresh();
			UpdateData::UpdateDataForm^ frm = gcnew UpdateData::UpdateDataForm(libpointer, LibPath, rankinglist);
			frm->ShowDialog();

			this->label3->Text = L"Optimizing library";
			this->label3->Refresh();
			char charlibpath[MAX] = "\0";
			CStringA csstringdir(LibPath);
			strcpy(charlibpath, (LPCSTR)csstringdir);
			FileRank* rankinglistClone = *rankinglist;

			ExtractComponents stuff = *stuffpointer;

			optimizeFileTree(charlibpath, *libpointer, rankinglistClone, totalfile, stuff);

			UpdateListBoxItems();
			this->Enabled = true;

			this->label3->Text = L"Ready to use!";
			this->label3->Refresh();
		}
	}
	private: System::Void instruction_menu_click(System::Object^ sender, System::EventArgs^ e) {
		//instruction
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		//load
		FILE* in = fopen(IndexPath, "r");
		if (in) {
			fclose(in);
			this->label3->Text = L"Loading session...";
			this->label3->Refresh();

			ExtractComponents stuff;
			initialize(stuff);
			loadingComponents(stuff);
			stuffpointer = new ExtractComponents(stuff);

			char mainFolderPath[MAX + 1];
			Library lib;
			initialize(lib);

			FileRank* _rankinglist = nullptr;

			loadSession(mainFolderPath, lib, _rankinglist);
			LibPath = gcnew System::String(mainFolderPath);
			libpointer = new Library(lib);
			rankinglist = new FileRank * (_rankinglist);

			UserInput = "";
			textBox1->Text = LibPath;
			textBox2->Enabled = true;
			this->btnSearch->Enabled = true;

			listBox1->Items->Clear();

			array<System::Object^>^ lstBoxItems = gcnew cli::array<System::Object^>(lib.totalfolder);

			for (int i = 0; i < lib.totalfolder; ++i) lstBoxItems[i] = gcnew System::String(lib.charfolderlist[i]);

			listBox1->Items->AddRange(lstBoxItems);
			this->label3->Text = L"Loading completed";
			this->label3->Refresh();
		}
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		if (libpointer != nullptr) {
			System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(L"Bạn có muốn lưu lại dữ liệu thư viện không?", L"Thoát chương trình", MessageBoxButtons::YesNo);
			if (dr == System::Windows::Forms::DialogResult::Yes) {
				CStringA csStringPath(LibPath);
				char mainFolderPath[MAX + 1];
				strcpy(mainFolderPath, (LPCSTR)csStringPath);

				Library lib = *libpointer;
				FileRank* _rankinglist = *rankinglist;
				saveSession(mainFolderPath, lib, _rankinglist);
			}
			else {
				remove(IndexPath);
				remove(MetadataPath);
			}
			if (stuffpointer != nullptr) {
				deleteAll(*stuffpointer);
				stuffpointer = nullptr;
			}

			if (libpointer != nullptr) {
				deleteAll(*libpointer);
				libpointer = nullptr;
			}

			if (rankinglist != nullptr) {
				delete[] * rankinglist;
				rankinglist = nullptr;
			}
		}
	}
	private: System::Void optimizeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (libpointer == nullptr) {
			System::Windows::Forms::MessageBox::Show(L"Vui lòng chọn thư viện trước khi sử dụng chức năng này", L"Optimize");
			return;
		}
		System::Windows::Forms::DialogResult dr = System::Windows::Forms::MessageBox::Show(L"Tối ưu dữ liệu ?", L"Optimize", MessageBoxButtons::YesNo);
		if (dr == System::Windows::Forms::DialogResult::Yes) {
			this->label3->Text = L"Optimize library...";
			this->label3->Refresh();
			preLoad();
			this->label3->Text = L"Optimize completed";
			this->label3->Refresh();
		}
		else;
	}
	private: System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	};
}