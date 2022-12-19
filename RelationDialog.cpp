#include "RelationDialog.h"

namespace lvceditor
{
	//****************************
	//МЕТОДЫ
	//****************************
	Data::Data(String^ text, Relation r1, Relation r2)
	{
		this->text = text;
		this->r1 = r1;
		this->r2 = r2;
	}
	//Установка типа связи
	void RelationDialog::ChooseType(Relation r1, Relation r2)
	{
		//Один к одному
		if (r1 == Relation::One && r2 == Relation::One)
		{
			radioButton1->Checked = true;
		}
		//Один ко многим
		else if (r1 == Relation::One && r2 == Relation::Many)
		{
			radioButton2->Checked = true;
		}
		//Многие к одному
		else if (r1 == Relation::Many && r2 == Relation::One)
		{
			radioButton3->Checked = true;
		}
		//Многие ко многим
		else if (r1 == Relation::Many && r2 == Relation::Many)
		{
			radioButton4->Checked = true;
		}
	}
	//****************************
	//ОБРАБОТКА СОБЫТИЙ
	//****************************
	RelationDialog::RelationDialog(String^ Name, Relation r1, Relation r2)
	{
		InitializeComponent();
		data = Data(Name, r1, r2);
		this->textRelation->Text = Name;
		ChooseType(r1, r2);
	}
	//Сохранение изменений
	System::Void RelationDialog::buttonSaveDialog_Click(System::Object^ sender, System::EventArgs^ e) {
		data.text = this->textRelation->Text;
		this->Hide();
	}
	//Один к одному
	System::Void RelationDialog::radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::One;
		data.r2 = Relation::One;
	}
	//Один ко многим
	System::Void RelationDialog::radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::One;
		data.r2 = Relation::Many;
	}
	//Многие к одному
	System::Void RelationDialog::radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::Many;
		data.r2 = Relation::One;
	}
	//Многие ко многим
	System::Void RelationDialog::radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::Many;
		data.r2 = Relation::Many;
	}
}
