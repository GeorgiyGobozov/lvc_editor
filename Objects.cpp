#include "Objects.h"

//************************************
// СВОЙСТВА ОБЪЕКТОВ
//************************************
//Свойства отрисовки объектов
Property::Property()
{
	//Установка значений по умолчанию
	this->main_brush = gcnew SolidBrush(Color::Black);
	this->bright_brush = gcnew SolidBrush(Color::Green);
	this->backcolor = gcnew SolidBrush(Color::White);
	this->pen_object = gcnew Pen(main_brush, 2);
	this->font_text = gcnew Font("Arial", 12);
}
void DiagramObject::OnDeserializedMethod(StreamingContext context)
{
	this->p = gcnew Property();
}
//************************************
//ШАБЛОНЫ ОБЪЕКТОВ РИСОВАНИЯ
//************************************
//Шаблон объекта рисования
DiagramObject::DiagramObject(String^ text)
{
	this->text = text;
	p =gcnew Property();
}
// Фигура
Point Figure::Relocation(Point location_center)
{
	return location_center;
}

Figure::Figure(Point loc, System::Drawing::Size size, String^ text) :DiagramObject(text)
{
	this->Size = size;
	this->Location = loc;
	this->text = text;
}
void Figure::DrawText(Rectangle r)
{
	//Рисование текста
	StringFormat^ format = gcnew StringFormat(StringFormatFlags::NoClip);
	format->Alignment = StringAlignment::Center;
	format->LineAlignment = StringAlignment::Center;
	Area::g->DrawString(text, p->font_text, p->main_brush, r, format);
}
//Правило соединения фигур
PairRule::PairRule(Type^ A, Type^ B)
{
	this->A = A;
	this->B = B;
}
bool PairRule::Check(Figure^ a, Figure^ b)
{
	if (a->GetType() == A && b->GetType() == B)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//************************************
//ОБЪЕКТ, РЕАЛИЗУЮЩИЙ СОЕДИНЕНИЕ ФИГУР
//************************************
float Line::Function(Point p1, Point p2, Point search_point, float offset)
{
	float x = (float)(search_point.X - p1.X + offset) * (float)(p2.Y - p1.Y);
	float y = (float)(search_point.Y - p1.Y + offset) * (float)(p2.X - p1.X);
	return x - y;
}

Line::Line(Figure^ f1, Point flow_point, String^ text) : DiagramObject(text)
{
	this->f1 = f1;
	this->FlowPoint = flow_point;
}

void Line::ConnectFigure(Figure^ f2)
{
	this->f2 = f2;
}

void Line::DrawText()
{
	Point middle;
	if (f2 == nullptr)
	{
		middle.X = (FlowPoint.X + f1->Location.X - 30) / 2;
		middle.Y = (FlowPoint.Y + f1->Location.Y - 30) / 2;
	}
	else
	{
		middle.X = (f2->Location.X + f1->Location.X - 30) / 2;
		middle.Y = (f2->Location.Y + f1->Location.Y - 30) / 2;
	}
	Area::g->DrawString(text, p->font_text, p->bright_brush, middle);
}

bool Line::Exist(Point point)
{
	float t1 = Function(f1->Location, f2->Location, point, OFFSET);
	float t2 = Function(f1->Location, f2->Location, point, -OFFSET);
	float x_min = Math::Min(f1->Location.X, f2->Location.X) - OFFSET / 2;
	float x_max = Math::Max(f1->Location.X, f2->Location.X) + OFFSET / 2;
	float y_min = Math::Min(f1->Location.Y, f2->Location.Y) - OFFSET / 2;
	float y_max = Math::Max(f1->Location.Y, f2->Location.Y) + OFFSET / 2;
	if (((t1 < 0 && t2 > 0) || (t2 < 0 && t1 > 0)) &&
		point.X > x_min && point.X < x_max &&
		point.Y > y_min && point.Y < y_max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Line::Paint()
{
	if (f2 == nullptr)
	{
		Area::g->DrawLine(p->pen_object, f1->Location, FlowPoint);
	}
	else
	{
		Area::g->DrawLine(p->pen_object, f1->Location, f2->Location);
	}
	DrawText();
}
//************************************
//ПОЛЕ РИСОВАНИЯ
//************************************
//Класс поля рисования
int Area::CountLine(Figure^ f)
{
	int count = 0;
	for each (Line^ line in lines)
	{
		if (line->f1 == f || line->f2 == f)
		{
			count++;
		}
	}
	return count;
}
bool Area::CheckMaxLine(Figure^ f)
{
	bool result = false;
	Type^ t = f->GetType();
	if (t == RhombObject::typeid)
	{
		if (CountLine(f) > 2)
		{
			result = true;
		}
	}
	else if (t == EllipseObject::typeid)
	{
		if (CountLine(f) > 1)
		{
			result = true;
		}
	}
	return result;
}
void Area::RemoveLines(Figure^ f)
{
	for (int i = 0; i < lines->Count; i++)
	{
		if (lines[i]->f1 == f || lines[i]->f2 == f)
		{
			lines->Remove(lines[i]);
			i--;
		}
	}
}

bool Area::CheckRules(Figure^ a, Figure^ b)
{
	bool result = false;
	for each (PairRule ^ pair in pairs)
	{
		if (pair->Check(a,b))
		{
			result = true;
		}
	}
	return result;
}

void Area::UpdateLines()
{
	List<Figure^>^ f = GetFigures(RhombObject::typeid);
	for each (Figure ^figure in f)
	{
		RhombObject^ r = (RhombObject^)figure;
		List<Line^>^ l = GetLines(r);
		if (l->Count==1)
		{
			l[0]->text = RhombObject::GetRCode(r->r1);
		}
		else if (l->Count == 2)
		{
			l[0]->text = RhombObject::GetRCode(r->r1);
			l[1]->text = RhombObject::GetRCode(r->r2);
		}
	}
}

Area::Area(System::Drawing::Size Size)
{
	objects = gcnew List<Figure^>();
	lines = gcnew List<Line^>();
	//Создание холста рисования (Bitmap)
	this->image = gcnew Bitmap(Size.Width, Size.Height);
	//Инициализация инструмента рисования
	g = Graphics::FromImage(image);
	//Сглаживание линий
	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	SetDefaultSettings();
}

Image^ Area::Resize(System::Drawing::Size new_Size)
{
	if (!new_Size.IsEmpty)
	{
		this->image = gcnew Bitmap(new_Size.Width, new_Size.Height);
		g = Graphics::FromImage(image);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		return image;
	}
	else 
	{
		return nullptr;
	}
}

int Area::Count()
{
	return objects->Count;
}

void Area::AddFigure(Point location, ObjectType type)
{
	Figure^obj;
	switch (type)
	{
	case ObjectType::_Rectangle:
	{
		obj = gcnew RectangleObject(location,Size(150,80),"Сущность");
		break;
	}
	case ObjectType::Rhomb:
	{
		obj = gcnew RhombObject(location, Size(120, 80), "Связь");
		break;
	}
	case ObjectType::Ellipse:
		obj = gcnew EllipseObject(location, Size(120, 80), "Атрибут");
		break;
	}
	objects->Add(obj);
}

bool Area::AddLine(Line ^line)
{
	bool result = false;
	if (line->f1 != nullptr)
	{
		if (line->f2==nullptr)
		{
			lines->Add(line);
			result = true;
		}
		else 
		{
			if (!CheckRules(line->f1, line->f2) || CheckMaxLine(line->f1) || CheckMaxLine(line->f2))
			{
				lines->Remove(line);
			}
		}
	}
	return result;
}

void Area::RemoveObject(Point point)
{
	//Выбор фигуры для удаления
	Figure^ f = GetFigure(point);
	//Удаление связанных с ним связей
	if(f!=nullptr)
	{
		RemoveLines(f);
	}
	//Выбор линии для удаления
	Line^ l=GetLine(point);
	//Удаление фигуры
	objects->Remove(f);
	//Удаление линии
	lines->Remove(l);
}

void Area::RemoveLine(Line^ line)
{
	lines->Remove(line);
}

Figure^ Area::GetFigure(Point point)
{
	for (int i = objects->Count-1; i >= 0; i--)
	{
		if (objects[i]->Exist(point))
		{
			return objects[i];
		}
	}
	return nullptr;
}

Line^ Area::GetLine(Point point)
{
	for (int i = lines->Count-1; i >= 0; i--)
	{
		if (lines[i]->Exist(point))
		{
			return lines[i];
		}
	}
	return nullptr;
}

List<Figure^>^ Area::GetFigures(Type ^type)
{
	List<Figure^>^ f = gcnew List<Figure^>();
	for each (Figure ^figure in objects)
	{
		if (figure->GetType() == type)
		{
			f->Add(figure);
		}
	}
	return f;
}

List<Line^>^ Area::GetLines(Figure^ r)
{
	List<Line^>^ l = gcnew List<Line^>();
	for each (Line ^line in lines)
	{
		if (r == line->f1 || r == line->f2)
		{
			l->Add(line);
		}
	}
	return l;
}

void Area::Clear()
{
	objects->Clear();
	lines->Clear();
	Paint();
}

void Area::Paint()
{
	g->Clear(SystemColors::Control);
	UpdateLines();
	for each (Line ^ obj in lines)
	{
		obj->Paint();
	}
	for each (Figure ^obj in objects)
	{
		obj->Paint();
	}
}

void Area::OnDeserializedMethod(StreamingContext context)
{
	SetDefaultSettings();
}

void Area::SetDefaultSettings()
{
	//Инициализация и определение правил соединения фигур
	pairs = gcnew List<PairRule^>();
	pairs->Add(gcnew PairRule(RectangleObject::typeid, RhombObject::typeid));
	pairs->Add(gcnew PairRule(RhombObject::typeid, RectangleObject::typeid));
	pairs->Add(gcnew PairRule(RectangleObject::typeid, EllipseObject::typeid));
	pairs->Add(gcnew PairRule(EllipseObject::typeid, RectangleObject::typeid));
}

//************************************
//ОБЪЕКТЫ РИСОВАНИЯ
//************************************
//Класс, рисующий прямоугольник
RectangleObject::RectangleObject(Point loc, System::Drawing::Size size, String^ text) :
	Figure(loc, size, text) {}

void RectangleObject::Paint()
{
	//Рисование прямоугольника
	Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
	System::Drawing::Rectangle rectangle = System::Drawing::Rectangle(LeftTop, Size);
	Area::g->DrawRectangle(p->pen_object, rectangle);
	Area::g->FillRectangle(p->backcolor, rectangle);
	//Рисование текста
	DrawText(rectangle);
}

bool RectangleObject::Exist(Point point)
{
	Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
	if (point.X > LeftTop.X && point.X<LeftTop.X + Size.Width &&
		point.Y>LeftTop.Y && point.Y < LeftTop.Y + Size.Height)
	{
		return true;
	}
	else { return false; }
}

//Класс, рисующий ромб

Point RhombObject::Relocation(Point location_center)
{
	//Определение точек ромба
	points = gcnew array<Point>(4)
	{
		Point(location_center.X - Size.Width / 2, location_center.Y),
			Point(location_center.X, location_center.Y - Size.Height / 2),
			Point(location_center.X + Size.Width / 2, location_center.Y),
			Point(location_center.X, location_center.Y + Size.Height / 2),
	};
	return location_center;
}

	String^ RhombObject::GetRCode(Relation r)
	{
		String^ result = "";
		switch (r)
		{
		case Relation::One:
			result= "1";
			break;
		case Relation::Many:
			result= "M";
			break;
		}
		return result;
	}

	RhombObject::RhombObject(Point loc, System::Drawing::Size size, String^ text) :
	Figure(loc, size, text) 
{
	r1 = Relation::One;
	r2 = Relation::One;
}

void RhombObject::SetRelation(Relation r1, Relation r2)
{
	this->r1 = r1;
	this->r2 = r2;
}

bool RhombObject::Exist(Point point)
{
	float a = (float)(Size.Width / 2);//Половина длины диагонали ромба
	float b = (float)(Size.Height / 2);//Половина длины диагонали ромба
	float Ux = (points[2].X - points[0].X) / (2 * a);//Расчет вектора в направлении оси X
	float Vy = (points[3].Y - points[1].Y) / (2 * b);//Расчет вектора в направлении оси Y
	int Wx = point.X - Location.X;
	int Wy = point.Y - Location.Y;
	//
	float x = Math::Abs(Ux * Wx);
	float y = Math::Abs(Vy * Wy);
	//
	if ((x / a + y / b) <= 1)
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}

void RhombObject::Paint()
{
	//Рисование прямоугольника
	Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
	System::Drawing::Rectangle rectangle = System::Drawing::Rectangle(LeftTop, Size);
	Area::g->DrawPolygon(p->pen_object, points);
	Area::g->FillPolygon(p->backcolor, points);
	//Рисование текста
	DrawText(rectangle);
}
//Класс, рисующий овал
EllipseObject::EllipseObject(Point loc, System::Drawing::Size size, String^ text) :
	Figure(loc, size, text) {}

bool EllipseObject::Exist(Point point)
{
	float a = (float)(Size.Width / 2);
	float b = (float)(Size.Height / 2);
	int Wx = point.X - Location.X;
	int Wy = point.Y - Location.Y;
	float X = (Wx* Wx) / (a*a);
	float Y = (Wy* Wy) / (b*b);
	if (X + Y <= 1)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void EllipseObject::Paint()
{
	//Рисование прямоугольника
	Point LeftTop = Point(Location.X - Size.Width / 2, Location.Y - Size.Height / 2);
	System::Drawing::Rectangle rectangle = System::Drawing::Rectangle(LeftTop, Size);
	Area::g->DrawEllipse(p->pen_object, rectangle);
	Area::g->FillEllipse(p->backcolor, rectangle);
	//Рисование текста
	DrawText(rectangle);
}


