#include "RelationDialog.h"

namespace lvceditor
{
	//****************************
	//������
	//****************************
	Data::Data(String^ text, Relation r1, Relation r2)
	{
		this->text = text;
		this->r1 = r1;
		this->r2 = r2;
	}
	//��������� ���� �����
	void RelationDialog::ChooseType(Relation r1, Relation r2)
	{
		//���� � ������
		if (r1 == Relation::One && r2 == Relation::One)
		{
			radioButton1->Checked = true;
		}
		//���� �� ������
		else if (r1 == Relation::One && r2 == Relation::Many)
		{
			radioButton2->Checked = true;
		}
		//������ � ������
		else if (r1 == Relation::Many && r2 == Relation::One)
		{
			radioButton3->Checked = true;
		}
		//������ �� ������
		else if (r1 == Relation::Many && r2 == Relation::Many)
		{
			radioButton4->Checked = true;
		}
	}
	//****************************
	//��������� �������
	//****************************
	RelationDialog::RelationDialog(String^ Name, Relation r1, Relation r2)
	{
		InitializeComponent();
		data = Data(Name, r1, r2);
		this->textRelation->Text = Name;
		ChooseType(r1, r2);
	}
	//���������� ���������
	System::Void RelationDialog::buttonSaveDialog_Click(System::Object^ sender, System::EventArgs^ e) {
		data.text = this->textRelation->Text;
		this->Hide();
	}
	//���� � ������
	System::Void RelationDialog::radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::One;
		data.r2 = Relation::One;
	}
	//���� �� ������
	System::Void RelationDialog::radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::One;
		data.r2 = Relation::Many;
	}
	//������ � ������
	System::Void RelationDialog::radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::Many;
		data.r2 = Relation::One;
	}
	//������ �� ������
	System::Void RelationDialog::radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		data.r1 = Relation::Many;
		data.r2 = Relation::Many;
	}
}
