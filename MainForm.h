#pragma once
#include "Objects.h"
#include "RelationDialog.h"
#include "FileManager.h"


namespace lvceditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	
	//��� ������� ������
	enum ButtonType
	{
		Move,//������ ��������
		AddEntity,//������ ���������� ��������
		AddRelation,//������ ���������� �����
		AddAttribute,//������ ���������� ��������
		AddConnection,//������ ���������� ����������
		Delete//������ �������� �������
	};

	public ref class MainForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::PictureBox^ HeadPicture;
	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel3;
	private: System::Windows::Forms::ToolStripButton^ buttonRemoveAll;
	private:
		FileManager ^manager;
		Area^ area;//���� ���������
		TextBox^ edit_text;//���� ��� ����� �������������� ������
		ButtonType type;//��� ������� ������
		//
		//������� ��� ����������� �����
		bool ismove = false;//���� ������� ������ ����������� �����
		Figure^ obj;//��������� ������ �� ���� ���������
		//������� ��� ���������� �����
		bool isconnect = false;//���� ���������� � �������
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
		   Line^ line;//����������
	public:
		MainForm(void);
		//���������� ������
		void UpdateData();
		//��������� ������ �������
		void ChangeText();
		//����� ������
		void ResetStyle();
		//�������� TextBox � ���������� ����������� ��� �������������� ������ �������
		TextBox^ CreateTextBox(Figure^ object);
		//�������� ����������� ���� �������������� �����
		void EditRelation(RhombObject ^r);

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ buttonSave;
	private: System::Windows::Forms::ToolStripMenuItem^ buttonLoad;


	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel1;
	private: System::Windows::Forms::ToolStripButton^ EntityButton;
	private: System::Windows::Forms::ToolStripButton^ RelationButton;
	private: System::Windows::Forms::ToolStripButton^ ConnectionButton;



	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel2;
	private: System::Windows::Forms::ToolStripButton^ buttonRemove;




	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::ToolStripLabel^ toolStripLabel4;
	private: System::Windows::Forms::ToolStripButton^ buttonMove;
	private: System::Windows::Forms::ToolStripButton^ buttonAttribute;











	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->buttonSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->buttonLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel4 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonMove = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->EntityButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->RelationButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonAttribute = (gcnew System::Windows::Forms::ToolStripButton());
			this->ConnectionButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonRemove = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripLabel3 = (gcnew System::Windows::Forms::ToolStripLabel());
			this->buttonRemoveAll = (gcnew System::Windows::Forms::ToolStripButton());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->HeadPicture = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HeadPicture))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->AutoSize = false;
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->����ToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(120, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1071, 43);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->buttonSave,
					this->buttonLoad
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(57, 39);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// buttonSave
			// 
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(180, 24);
			this->buttonSave->Text = L"���������";
			this->buttonSave->Click += gcnew System::EventHandler(this, &MainForm::buttonSave_Click);
			// 
			// buttonLoad
			// 
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(180, 24);
			this->buttonLoad->Text = L"���������";
			this->buttonLoad->Click += gcnew System::EventHandler(this, &MainForm::buttonLoad_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Left;
			this->toolStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(100, 60);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->toolStripLabel4,
					this->buttonMove, this->toolStripLabel1, this->EntityButton, this->RelationButton, this->buttonAttribute, this->ConnectionButton,
					this->toolStripLabel2, this->buttonRemove, this->toolStripLabel3, this->buttonRemoveAll
			});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Table;
			this->toolStrip1->Location = System::Drawing::Point(0, 43);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Padding = System::Windows::Forms::Padding(0, 10, 1, 0);
			this->toolStrip1->Size = System::Drawing::Size(123, 590);
			this->toolStrip1->TabIndex = 2;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripLabel4
			// 
			this->toolStripLabel4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStripLabel4->Name = L"toolStripLabel4";
			this->toolStripLabel4->Size = System::Drawing::Size(122, 21);
			this->toolStripLabel4->Text = L"�����������";
			// 
			// buttonMove
			// 
			this->buttonMove->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonMove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonMove.Image")));
			this->buttonMove->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonMove->Name = L"buttonMove";
			this->buttonMove->Size = System::Drawing::Size(104, 64);
			this->buttonMove->Text = L"toolStripButton1";
			this->buttonMove->Click += gcnew System::EventHandler(this, &MainForm::buttonMove_Click);
			// 
			// toolStripLabel1
			// 
			this->toolStripLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStripLabel1->Margin = System::Windows::Forms::Padding(0, 10, 0, 2);
			this->toolStripLabel1->Name = L"toolStripLabel1";
			this->toolStripLabel1->Size = System::Drawing::Size(113, 21);
			this->toolStripLabel1->Text = L"�����������";
			// 
			// EntityButton
			// 
			this->EntityButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->EntityButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"EntityButton.Image")));
			this->EntityButton->Name = L"EntityButton";
			this->EntityButton->Size = System::Drawing::Size(104, 64);
			this->EntityButton->Text = L"toolStripButton1";
			this->EntityButton->Click += gcnew System::EventHandler(this, &MainForm::EntityButton_Click);
			// 
			// RelationButton
			// 
			this->RelationButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->RelationButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"RelationButton.Image")));
			this->RelationButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->RelationButton->Name = L"RelationButton";
			this->RelationButton->Size = System::Drawing::Size(104, 64);
			this->RelationButton->Text = L"toolStripButton2";
			this->RelationButton->Click += gcnew System::EventHandler(this, &MainForm::RelationButton_Click);
			// 
			// buttonAttribute
			// 
			this->buttonAttribute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonAttribute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonAttribute.Image")));
			this->buttonAttribute->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonAttribute->Name = L"buttonAttribute";
			this->buttonAttribute->Size = System::Drawing::Size(104, 64);
			this->buttonAttribute->Text = L"toolStripButton1";
			this->buttonAttribute->Click += gcnew System::EventHandler(this, &MainForm::buttonAttribute_Click);
			// 
			// ConnectionButton
			// 
			this->ConnectionButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->ConnectionButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ConnectionButton.Image")));
			this->ConnectionButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ConnectionButton->Name = L"ConnectionButton";
			this->ConnectionButton->Size = System::Drawing::Size(104, 64);
			this->ConnectionButton->Text = L"toolStripButton3";
			this->ConnectionButton->Click += gcnew System::EventHandler(this, &MainForm::ConnectionButton_Click);
			// 
			// toolStripLabel2
			// 
			this->toolStripLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStripLabel2->Margin = System::Windows::Forms::Padding(0, 0, 0, 2);
			this->toolStripLabel2->Name = L"toolStripLabel2";
			this->toolStripLabel2->Size = System::Drawing::Size(88, 21);
			this->toolStripLabel2->Text = L"     �������";
			// 
			// buttonRemove
			// 
			this->buttonRemove->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonRemove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonRemove.Image")));
			this->buttonRemove->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonRemove->Name = L"buttonRemove";
			this->buttonRemove->Size = System::Drawing::Size(104, 64);
			this->buttonRemove->Text = L"toolStripButton4";
			this->buttonRemove->Click += gcnew System::EventHandler(this, &MainForm::buttonRemove_Click);
			// 
			// toolStripLabel3
			// 
			this->toolStripLabel3->Name = L"toolStripLabel3";
			this->toolStripLabel3->Size = System::Drawing::Size(103, 21);
			this->toolStripLabel3->Text = L"  ������� ���";
			// 
			// buttonRemoveAll
			// 
			this->buttonRemoveAll->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->buttonRemoveAll->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonRemoveAll.Image")));
			this->buttonRemoveAll->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonRemoveAll->Name = L"buttonRemoveAll";
			this->buttonRemoveAll->Size = System::Drawing::Size(104, 64);
			this->buttonRemoveAll->Text = L"toolStripButton1";
			this->buttonRemoveAll->Click += gcnew System::EventHandler(this, &MainForm::buttonRemoveAll_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox.InitialImage")));
			this->pictureBox->Location = System::Drawing::Point(123, 43);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(948, 590);
			this->pictureBox->TabIndex = 4;
			this->pictureBox->TabStop = false;
			this->pictureBox->SizeChanged += gcnew System::EventHandler(this, &MainForm::pictureBox_SizeChanged);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseClick);
			this->pictureBox->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseDoubleClick);
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseDown);
			this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseMove);
			this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseUp);
			// 
			// HeadPicture
			// 
			this->HeadPicture->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"HeadPicture.BackgroundImage")));
			this->HeadPicture->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->HeadPicture->Location = System::Drawing::Point(0, 0);
			this->HeadPicture->Name = L"HeadPicture";
			this->HeadPicture->Size = System::Drawing::Size(123, 43);
			this->HeadPicture->TabIndex = 3;
			this->HeadPicture->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1071, 633);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->HeadPicture);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MainForm";
			this->Text = L"�������� �������������� ���� � ������� ����";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HeadPicture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	//*******************************
	//��������� ������� �� PictureBox
	//*******************************
	//���� ����� (���������� � �������� ��������)
	private: System::Void pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	//������� ������ ���� (�����������)
	private: System::Void pictureBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	//���������� ������ ���� (�����������)
	private: System::Void pictureBox_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	//�������� ������� ���� (�����������)
	private: System::Void pictureBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	//������� ���� ����� (��������������)
	private: System::Void pictureBox_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	//��������� ������� PictureBox
	private: System::Void pictureBox_SizeChanged(System::Object^ sender, System::EventArgs^ e);

	//*******************************
	//��������� ������� ������� ������
	//*******************************
	//������� ������ "�����������"
	private: System::Void buttonMove_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "�������� ��������"
	private: System::Void EntityButton_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "�������� �����"
	private: System::Void RelationButton_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "�������� �������"
	private: System::Void buttonAttribute_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "�������� ����������"
	private: System::Void ConnectionButton_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "������� ������"
	private: System::Void buttonRemove_Click(System::Object^ sender, System::EventArgs^ e);
	//������� ������ "������� ���"
	private: System::Void buttonRemoveAll_Click(System::Object^ sender, System::EventArgs^ e);
	
	//*******************************
	//��������� ������� �������������� ������ �������� ���������
	//*******************************
	//����� ������ TextBox, � ������� �������� �������������� �������������� �������
	private: void MainForm::OnLeave(System::Object^ sender, System::EventArgs^ e);
	//������� ������ ������������� ������������������ ������ �������
	private: void lvceditor::MainForm::OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
   
	private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonLoad_Click(System::Object^ sender, System::EventArgs^ e);
};
}
