#include "MainForm.h"

namespace lvceditor
{
	MainForm::MainForm(void)
	{
		InitializeComponent();
		manager = gcnew FileManager();
		openFileDialog1->Filter = "(*.xml)|*.xml";
		saveFileDialog1->Filter = "(*.xml)|*.xml";
		area = gcnew Area(pictureBox->Size);
		pictureBox->Image = area->image;
		buttonMove->Select();
	}
	//*******************************
	//������
	//*******************************
	//���������� ���� ���������
	void MainForm::UpdateData()
	{
		area->Paint();
		pictureBox->Refresh();
	}
	//��������� ������ �� �������� ���������
	void MainForm::ChangeText()
	{
		if (obj != nullptr && edit_text!=nullptr)
		{
			obj->text = edit_text->Text;
			Controls->Remove(edit_text);
			UpdateData();
		}
	}
	//����� ������ ������
	void MainForm::ResetStyle()
	{
		buttonMove->BackColor = System::Drawing::SystemColors::ActiveCaption;
		EntityButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		RelationButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		ConnectionButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		buttonRemove->BackColor = System::Drawing::SystemColors::ActiveCaption;
		buttonAttribute->BackColor = System::Drawing::SystemColors::ActiveCaption;
	}
	//�������� TextBox � ���������� ����������� ��� �������������� ������ �������
	TextBox^ MainForm::CreateTextBox(Figure^ object)
	{
		//�������� �������� TextBox ��� �������������� �����
		TextBox^ textbox = gcnew TextBox();
		//����������� ��������� TextBox �� ������������ �������
		textbox->Text = object->text;
		Point loc;
		loc.X = object->Location.X + pictureBox->Location.X - textbox->Width / 2;
		loc.Y = object->Location.Y + pictureBox->Location.Y - 15;
		textbox->Location = loc;
		//��������� ������� TextBox
		textbox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &lvceditor::MainForm::OnKeyDown);
		textbox->Leave += gcnew System::EventHandler(this, &lvceditor::MainForm::OnLeave);
		this->Controls->Add(textbox);
		//���������
		textbox->BringToFront();//����������� �� �������� ����� �����
		textbox->Select();//��������� ������
		return textbox;
	}
	//�������� ����������� ���� �������������� �����
	void MainForm::EditRelation(RhombObject^ r)
	{
		RelationDialog^ dialog = gcnew RelationDialog(r->text, r->r1, r->r2);
		dialog->ShowDialog();
		Data d = dialog->data;
		r->text = d.text;
		r->SetRelation(d.r1, d.r2);
		dialog->Close();
	}
	//*******************************
	//��������� ������� �� PictureBox
	//*******************************
	//���� �����
	System::Void MainForm::pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//���� ����� �������
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			switch (type)
			{
				//���������� ��������
			case ButtonType::AddEntity:
			{
				area->AddFigure(e->Location, ObjectType::_Rectangle);
				UpdateData();
				break;
			}
			//���������� �����
			case ButtonType::AddRelation:
			{
				area->AddFigure(e->Location, ObjectType::Rhomb);
				UpdateData();
				break;
			}
			//���������� ��������
			case ButtonType::AddAttribute:
			{
				area->AddFigure(e->Location, ObjectType::Ellipse);
				UpdateData();
				break;
			}
			//���������� ����������
			case ButtonType::AddConnection:
			{
				Figure^ f = area->GetFigure(e->Location);
				if (f != nullptr)
				{
					//���������� ������ ����������
					if (!isconnect)
					{
						line = gcnew Line(f, e->Location, "");
					}
					//���������� ����� ����������
					else
					{
						line->ConnectFigure(f);
					}
					isconnect = area->AddLine(line);
					UpdateData();
				}
				break;
			}
			//��������� ��������, ��� ��������� ������ "�������"
			case ButtonType::Delete:
			{
				area->RemoveObject(e->Location);
				UpdateData();
				break;
			}
			}
		}
		//���� ������ �������
		else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			//������ ���������� ����������
			if (isconnect && line != nullptr)
			{
				isconnect = false;
				area->RemoveLine(line);
				UpdateData();
			}
		}
	}
	//������� ������ ����
	System::Void MainForm::pictureBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			switch (type)
			{
				//���������� �������� ������, ���� ��� ���� �������
			case ButtonType::Move:
			{
				obj = area->GetFigure(e->Location);
				if (obj != nullptr) { ismove = true; }
				break;
			}
			}
			//�������� ������� �������������� ������
			//����� ����� ��� ������
			if (edit_text != nullptr)
			{
				Controls->Remove(edit_text);
			}
		}
	}
	//���������� ������ ����
	System::Void MainForm::pictureBox_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		ismove = false;
		this->Cursor = Cursors::Default;
	}
	//�������� ������� ����
	System::Void MainForm::pictureBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//�������� ������
		if (obj != nullptr && ismove)
		{
			obj->Location = e->Location;
			this->Cursor = Cursors::Hand;
		}
		//�������� ����� ���������� �����
		if (line != nullptr && isconnect)
		{
			line->FlowPoint = e->Location;
		}
		//���������� ������
		if (ismove || isconnect)
		{
			UpdateData();
		}
	}
	//������� ���� �����
	System::Void MainForm::pictureBox_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		switch (e->Button)
		{
			//���� ����� ������� ����
		case System::Windows::Forms::MouseButtons::Left:
		{
			//�������������� �������� ����
			obj = area->GetFigure(e->Location);
			if (obj != nullptr && type == ButtonType::Move)
			{
				if (obj->GetType() == RhombObject::typeid)
				{
					EditRelation((RhombObject^)obj);
				}
				else
				{
					edit_text = CreateTextBox(obj);
				}
				UpdateData();
			}
			break;
		}
		//���� ������ ������� ����
		case System::Windows::Forms::MouseButtons::Right:
		{
			//�������� ���������� �������
			area->RemoveObject(e->Location);
			UpdateData();
		}
		}
	}
	//��������� ������� PictureBox
	System::Void MainForm::pictureBox_SizeChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox->Image = area->Resize(pictureBox->Size);
		pictureBox->Refresh();
		UpdateData();
	}
	//*******************************
	//��������� ������� ������� ������
	//*******************************
	//������� ������ "�����������"
	System::Void MainForm::buttonMove_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::Move;
		ResetStyle();
		buttonMove->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "�������� ��������"
	System::Void MainForm::EntityButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddEntity;
		ResetStyle();
		EntityButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "�������� �����"
	System::Void MainForm::RelationButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddRelation;
		ResetStyle();
		RelationButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "�������� �������"
	System::Void MainForm::buttonAttribute_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddAttribute;
		ResetStyle();
		buttonAttribute->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "�������� ����������"
	System::Void MainForm::ConnectionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddConnection;
		ResetStyle();
		ConnectionButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "������� ������"
	System::Void MainForm::buttonRemove_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::Delete;
		ResetStyle();
		buttonRemove->BackColor = Color::FromArgb(194, 224, 255);
	}
	//������� ������ "������� ���"
	System::Void MainForm::buttonRemoveAll_Click(System::Object^ sender, System::EventArgs^ e) {
		area->Clear();
		UpdateData();
	}
	//*******************************
	//��������� ������ �������
	//*******************************
	//����� ������ TextBox, � ������� �������� �������������� �������������� �������
	void MainForm::OnLeave(System::Object^ sender, System::EventArgs^ e)
	{
		this->Controls->Remove(edit_text);
	}
	//������� ������ ������������� ������������������ ������ �������
	void MainForm::OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
		{
			ChangeText();
		}
	}

	System::Void MainForm::buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = saveFileDialog1->FileName;
				if (!manager->Save(area, url))
				{
					throw gcnew Exception(manager->message_error);
				}
				UpdateData();
				MessageBox::Show("������ ���������", "�����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch(Exception ^error)
			{
				MessageBox::Show(error->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	System::Void MainForm::buttonLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			try
			{
				String^ url = openFileDialog1->FileName;
				Area^ new_area = manager->Load(url);
				if (new_area ==nullptr)
				{
					throw gcnew Exception(manager->message_error);
				}
				area = new_area;
				UpdateData();
			}
			catch (Exception^ error)
			{
				MessageBox::Show(error->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

}
