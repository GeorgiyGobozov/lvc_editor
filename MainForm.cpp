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
	//Методы
	//*******************************
	//Обновление поля рисования
	void MainForm::UpdateData()
	{
		area->Paint();
		pictureBox->Refresh();
	}
	//Изменение тектса на объектах рисования
	void MainForm::ChangeText()
	{
		if (obj != nullptr && edit_text!=nullptr)
		{
			obj->text = edit_text->Text;
			Controls->Remove(edit_text);
			UpdateData();
		}
	}
	//Сброс стилей кнопок
	void MainForm::ResetStyle()
	{
		buttonMove->BackColor = System::Drawing::SystemColors::ActiveCaption;
		EntityButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		RelationButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		ConnectionButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
		buttonRemove->BackColor = System::Drawing::SystemColors::ActiveCaption;
		buttonAttribute->BackColor = System::Drawing::SystemColors::ActiveCaption;
	}
	//Создание TextBox с кастомными настройками для редактирования текста объекта
	TextBox^ MainForm::CreateTextBox(Figure^ object)
	{
		//Создание элемента TextBox для редактирования теста
		TextBox^ textbox = gcnew TextBox();
		//Определение положения TextBox по расположению объекта
		textbox->Text = object->text;
		Point loc;
		loc.X = object->Location.X + pictureBox->Location.X - textbox->Width / 2;
		loc.Y = object->Location.Y + pictureBox->Location.Y - 15;
		textbox->Location = loc;
		//Установка событий TextBox
		textbox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &lvceditor::MainForm::OnKeyDown);
		textbox->Leave += gcnew System::EventHandler(this, &lvceditor::MainForm::OnLeave);
		this->Controls->Add(textbox);
		//Настройка
		textbox->BringToFront();//Отображение на переднем плане формы
		textbox->Select();//Выделение текста
		return textbox;
	}
	//Открытие диалогового окна редактирования связи
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
	//Обработка событий на PictureBox
	//*******************************
	//Клик мышью
	System::Void MainForm::pictureBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//Клик левой кнопкой
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			switch (type)
			{
				//Добавление сущности
			case ButtonType::AddEntity:
			{
				area->AddFigure(e->Location, ObjectType::_Rectangle);
				UpdateData();
				break;
			}
			//Добавление связи
			case ButtonType::AddRelation:
			{
				area->AddFigure(e->Location, ObjectType::Rhomb);
				UpdateData();
				break;
			}
			//Добавление атрибута
			case ButtonType::AddAttribute:
			{
				area->AddFigure(e->Location, ObjectType::Ellipse);
				UpdateData();
				break;
			}
			//Добавление соединения
			case ButtonType::AddConnection:
			{
				Figure^ f = area->GetFigure(e->Location);
				if (f != nullptr)
				{
					//Добавление начала соединения
					if (!isconnect)
					{
						line = gcnew Line(f, e->Location, "");
					}
					//Добавление конца соединения
					else
					{
						line->ConnectFigure(f);
					}
					isconnect = area->AddLine(line);
					UpdateData();
				}
				break;
			}
			//Обработка действий, при выбранной кнопке "Удалить"
			case ButtonType::Delete:
			{
				area->RemoveObject(e->Location);
				UpdateData();
				break;
			}
			}
		}
		//Клик правой кнопкой
		else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			//Отмена проведения соединения
			if (isconnect && line != nullptr)
			{
				isconnect = false;
				area->RemoveLine(line);
				UpdateData();
			}
		}
	}
	//Нажатие кнопки мыши
	System::Void MainForm::pictureBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			switch (type)
			{
				//Разрешение движения фигуры, если она была выбрана
			case ButtonType::Move:
			{
				obj = area->GetFigure(e->Location);
				if (obj != nullptr) { ismove = true; }
				break;
			}
			}
			//Удаление объекта редактирования текста
			//после ввода или отмены
			if (edit_text != nullptr)
			{
				Controls->Remove(edit_text);
			}
		}
	}
	//Отпускание кнопки мышм
	System::Void MainForm::pictureBox_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		ismove = false;
		this->Cursor = Cursors::Default;
	}
	//Движение курсора мыши
	System::Void MainForm::pictureBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		//Движение фигуры
		if (obj != nullptr && ismove)
		{
			obj->Location = e->Location;
			this->Cursor = Cursors::Hand;
		}
		//Движение конца соединения фигур
		if (line != nullptr && isconnect)
		{
			line->FlowPoint = e->Location;
		}
		//Обновление данных
		if (ismove || isconnect)
		{
			UpdateData();
		}
	}
	//Двойной клик мышью
	System::Void MainForm::pictureBox_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		switch (e->Button)
		{
			//Клик левой кнопкой мыши
		case System::Windows::Forms::MouseButtons::Left:
		{
			//Редактирование объектов поля
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
		//Клик правой кнопкой мыши
		case System::Windows::Forms::MouseButtons::Right:
		{
			//Удаление выбранного объекта
			area->RemoveObject(e->Location);
			UpdateData();
		}
		}
	}
	//Изменение размера PictureBox
	System::Void MainForm::pictureBox_SizeChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox->Image = area->Resize(pictureBox->Size);
		pictureBox->Refresh();
		UpdateData();
	}
	//*******************************
	//Обработка событий нажатия кнопок
	//*******************************
	//Нажатие кнопки "Переместить"
	System::Void MainForm::buttonMove_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::Move;
		ResetStyle();
		buttonMove->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Добавить сущность"
	System::Void MainForm::EntityButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddEntity;
		ResetStyle();
		EntityButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Добавить связь"
	System::Void MainForm::RelationButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddRelation;
		ResetStyle();
		RelationButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Добавить атрибут"
	System::Void MainForm::buttonAttribute_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddAttribute;
		ResetStyle();
		buttonAttribute->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Добавить соединение"
	System::Void MainForm::ConnectionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::AddConnection;
		ResetStyle();
		ConnectionButton->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Удалить объект"
	System::Void MainForm::buttonRemove_Click(System::Object^ sender, System::EventArgs^ e) {
		type = ButtonType::Delete;
		ResetStyle();
		buttonRemove->BackColor = Color::FromArgb(194, 224, 255);
	}
	//Нажатие кнопки "Удалить все"
	System::Void MainForm::buttonRemoveAll_Click(System::Object^ sender, System::EventArgs^ e) {
		area->Clear();
		UpdateData();
	}
	//*******************************
	//Обработка других событий
	//*******************************
	//Смена фокуса TextBox, с помощью которого осуществляется редактирование объекта
	void MainForm::OnLeave(System::Object^ sender, System::EventArgs^ e)
	{
		this->Controls->Remove(edit_text);
	}
	//Нажание кнопки подтверждения отредактированного текста объекта
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
				MessageBox::Show("Данные сохранены", "Уведомление", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch(Exception ^error)
			{
				MessageBox::Show(error->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
				MessageBox::Show(error->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

}
