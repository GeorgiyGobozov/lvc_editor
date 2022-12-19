#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::Serialization;
using namespace System::Drawing;
using namespace System::IO;


//************************************
// СВОЙСТВА ОБЪЕКТОВ
//************************************
//Тип объекта рисования
public enum class ObjectType
{
	_Rectangle,//Прямоугольник
	Rhomb,//Ромб
	Ellipse//Окружность
};
//Свойства отрисовки объектов
public ref struct  Property
{
	//Общие свойства
	Brush^ main_brush;//Главный цвет
	Brush^ bright_brush;//Яркий цвет
	Brush^ backcolor;//Цвет фона
	//Свойства объекта рисования
	Pen^ pen_object;//Свойства рисования линии
	//Свойства текста
	Font^ font_text;
	Property();
};

//************************************
//ШАБЛОНЫ ОБЪЕКТОВ РИСОВАНИЯ
//************************************
//Шаблон объекта рисования
[DataContract]
public ref class DiagramObject abstract
{
private:
	//Метод, срабатывающий после десериализации, для установления значений по умолчанию
	[OnDeserialized] void OnDeserializedMethod(StreamingContext context);
public:
	Property ^p;//Свойства графики
	[DataMember] String^ text;//Текст объекта
	DiagramObject(String^ text);
	//Метод, определяющий существование своей отрисованной фигуры на поле по точке
	virtual bool Exist(Point point) = 0;
	//Метод отрисовки объекта
	virtual void Paint() = 0;
};
// Фигура
[DataContract]
public ref class Figure abstract:DiagramObject
{
private:
	[DataMember] Point location;//Положение на поле рисования
	[DataMember] System::Drawing::Size size;//Размер
protected:
	//Метод, осуществляющий пересчет положения объекта и теста
	virtual Point Relocation(Point location_center);
public:
	//Размер объекта на поле
	[DataMember(Order=0)] property System::Drawing::Size Size
	{
		System::Drawing::Size get() { return size; }
		void set(System::Drawing::Size size) { this->size = size; }
	}
	//Положение объекта на поле
	[DataMember(Order = 1)] property Point Location
	{
		Point get() { return location; }
		void set(Point loc) { location = Relocation(loc); }
	}
	Figure(Point loc, System::Drawing::Size size, String^ text);
	//Метод, осуществляющий отрисовку текста
	void DrawText(Rectangle r);
};
//Правило соединения фигур
public ref struct PairRule
{
	Type^ A;//Тип 1
	Type^ B;//Тип 2
	PairRule(Type^ A, Type^ B);
	//Метод проверки правила
	bool Check(Figure^ a, Figure^ b);
};
//************************************
//ОБЪЕКТ, РЕАЛИЗУЮЩИЙ СОЕДИНЕНИЕ ФИГУР
//************************************
[DataContract]
public ref class Line :DiagramObject
{
private:
	[DataMember] const float OFFSET = 5;//Погрешность при попадании курсора на линии
	//Метод, определяющий попадание точки на линию с учетом погрешности
	float Function(Point p1,Point p2, Point search_point,float offset);
public:
	[DataMember] Figure^ f1;//Фигура 1
	[DataMember] Figure^ f2;//Фигура 2
	Point FlowPoint;//Временная точка, когда неопределена 2 фигура 
	Line(Figure^ f1, Point flow_point, String^ text);
	//Метод, присоединяющий конец линии к заданной фигуре
	void ConnectFigure(Figure^ f2);
	//Метод, осуществляющий отрисовку текста
	void DrawText();
	bool Exist(Point point) override;
	void Paint() override;
};

//************************************
//ПОЛЕ РИСОВАНИЯ
//************************************
//Класс поля рисования
[DataContract]
public ref class Area
{
private:
	[DataMember(Order = 0)] List<Figure^>^ objects;//Список фигур
	[DataMember(Order = 1)] List<Line^>^ lines;//Список соединений
	List<PairRule^>^ pairs;//Список правил соединения
	//Метод, определяющий количество линий, соединенных с заданной фигурой
	int CountLine(Figure^ f);
	//Метод, определяющий полноту подключения соединений с заданной фигурой
	bool CheckMaxLine(Figure^ f);
	//Метод, удаляющий соединения с заданной фигурой
	void RemoveLines(Figure^ f);
	//Метод проверки правил соединения фигур
	bool CheckRules(Figure^ a, Figure^ b);
	//Обновление данных соединений
	void UpdateLines();
	//Метод, срабатывающий после десериализации, для установления значений по умолчанию
	[OnDeserialized] void OnDeserializedMethod(StreamingContext context);
	void SetDefaultSettings();
public:
	static Graphics^ g;//Инструмент рисования
	Image^ image;//Область рисования
	Area(System::Drawing::Size size);
	//Метод, изменяющий размер поля
	Image^ Resize(System::Drawing::Size new_size);
	//Количество объектов
	int Count();
	//Метод добавления фигуры
	void AddFigure(Point location, ObjectType type);
	//Метод добавления соединения
	bool AddLine(Line^ line);
	//Метод удаления фигуры
	void RemoveObject(Point point);
	//Метод удаления линии
	void RemoveLine(Line^ line);
	//Получение фигуры по позиции
	Figure^ GetFigure(Point point);
	//Получение линии по позиции
	Line^ GetLine(Point point);
	//Получение списка фигур определенного типа
	List<Figure^>^ GetFigures(Type^ type);
	//Получение списка линий, соединенных с заданной фигурой
	List<Line^>^ GetLines(Figure^ r);
	//Удаление всех объектов с поля
	void Clear();
	//Метод рисования объектов на поле
	void Paint();
};

//************************************
//ОБЪЕКТЫ РИСОВАНИЯ
//************************************
//Класс, рисующий прямоугольник
[DataContract]
public ref class RectangleObject : public Figure
{
public:
	RectangleObject(Point loc, System::Drawing::Size size, String^ text);
	bool Exist(Point point) override;
	void Paint() override;
};

//Тип связи
public enum class Relation
{
	One,//Один
	Many//Много
};

//Класс, рисующий ромб
[DataContract]
public ref class RhombObject : public Figure
{
private:
	array<Point>^ points;//Точки построения ромба
protected:
	Point Relocation(Point location_center) override;
public:
	[DataMember] Relation r1;//Тип связи с фигурой 1
	[DataMember] Relation r2;//Тип связи с фигурой 2
	//Метод получения строкового значения типа связи
	static String^ GetRCode(Relation r);
	RhombObject(Point loc, System::Drawing::Size size, String^ text);
	//Метод, устанавливающий значения типа связей
	void SetRelation(Relation r1, Relation r2);
	bool Exist(Point point) override;
	void Paint() override;
};

//Класс, рисующий овал
[DataContract]
public ref class EllipseObject : public Figure
{
public:
	EllipseObject(Point loc, System::Drawing::Size size, String^ text);
	bool Exist(Point point) override;
	void Paint() override;
};

