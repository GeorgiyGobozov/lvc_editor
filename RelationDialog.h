#pragma once
#include "Objects.h"

namespace lvceditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//Блок изменяемых данных
	public value struct Data
	{
		String^ text;//Изменяемый текст
		Relation r1;//Тип связи с первой фигурой
		Relation r2;//Тип связи со второй фигурой
		Data(String^ text, Relation r1, Relation r2);
	};

	public ref class RelationDialog : public System::Windows::Forms::Form
	{
	private:
		//Установка типа связи
		void ChooseType(Relation r1, Relation r2);
	public:
		Data data;//Данные
		RelationDialog(String^ Name, Relation r1, Relation r2);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~RelationDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textRelation;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::RadioButton^ radioButton4;
	private: System::Windows::Forms::Button^ buttonSaveDialog;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textRelation = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->buttonSaveDialog = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textRelation
			// 
			this->textRelation->Location = System::Drawing::Point(109, 19);
			this->textRelation->Name = L"textRelation";
			this->textRelation->Size = System::Drawing::Size(208, 26);
			this->textRelation->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Название";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(109, 73);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(140, 24);
			this->radioButton1->TabIndex = 2;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Один к одному";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &RelationDialog::radioButton1_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(20, 75);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Тип связи";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(109, 103);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(149, 24);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Один ко многим";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &RelationDialog::radioButton2_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(109, 133);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(155, 24);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Многие к одному";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &RelationDialog::radioButton3_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(109, 163);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(164, 24);
			this->radioButton4->TabIndex = 2;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Многие ко многим";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &RelationDialog::radioButton4_CheckedChanged);
			// 
			// buttonSaveDialog
			// 
			this->buttonSaveDialog->Location = System::Drawing::Point(109, 193);
			this->buttonSaveDialog->Name = L"buttonSaveDialog";
			this->buttonSaveDialog->Size = System::Drawing::Size(208, 31);
			this->buttonSaveDialog->TabIndex = 3;
			this->buttonSaveDialog->Text = L"Сохранить";
			this->buttonSaveDialog->UseVisualStyleBackColor = true;
			this->buttonSaveDialog->Click += gcnew System::EventHandler(this, &RelationDialog::buttonSaveDialog_Click);
			// 
			// RelationDialog
			// 
			this->AcceptButton = this->buttonSaveDialog;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(337, 231);
			this->Controls->Add(this->buttonSaveDialog);
			this->Controls->Add(this->radioButton4);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textRelation);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->MaximizeBox = false;
			this->Name = L"RelationDialog";
			this->Text = L"Параметры связи";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
//****************************
//ОБРАБОТКА СОБЫТИЙ
//****************************
//Сохранение изменений
private: System::Void buttonSaveDialog_Click(System::Object^ sender, System::EventArgs^ e);
//Выбор типа связи
//Один к одному
private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
//Один ко многим
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
//Многие к одному
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
//Многие ко многим
private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
