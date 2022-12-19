#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::Serialization;
using namespace System::Drawing;
using namespace System::IO;


//************************************
// �������� ��������
//************************************
//��� ������� ���������
public enum class ObjectType
{
	_Rectangle,//�������������
	Rhomb,//����
	Ellipse//����������
};
//�������� ��������� ��������
public ref struct  Property
{
	//����� ��������
	Brush^ main_brush;//������� ����
	Brush^ bright_brush;//����� ����
	Brush^ backcolor;//���� ����
	//�������� ������� ���������
	Pen^ pen_object;//�������� ��������� �����
	//�������� ������
	Font^ font_text;
	Property();
};

//************************************
//������� �������� ���������
//************************************
//������ ������� ���������
[DataContract]
public ref class DiagramObject abstract
{
private:
	//�����, ������������� ����� ��������������, ��� ������������ �������� �� ���������
	[OnDeserialized] void OnDeserializedMethod(StreamingContext context);
public:
	Property ^p;//�������� �������
	[DataMember] String^ text;//����� �������
	DiagramObject(String^ text);
	//�����, ������������ ������������� ����� ������������ ������ �� ���� �� �����
	virtual bool Exist(Point point) = 0;
	//����� ��������� �������
	virtual void Paint() = 0;
};
// ������
[DataContract]
public ref class Figure abstract:DiagramObject
{
private:
	[DataMember] Point location;//��������� �� ���� ���������
	[DataMember] System::Drawing::Size size;//������
protected:
	//�����, �������������� �������� ��������� ������� � �����
	virtual Point Relocation(Point location_center);
public:
	//������ ������� �� ����
	[DataMember(Order=0)] property System::Drawing::Size Size
	{
		System::Drawing::Size get() { return size; }
		void set(System::Drawing::Size size) { this->size = size; }
	}
	//��������� ������� �� ����
	[DataMember(Order = 1)] property Point Location
	{
		Point get() { return location; }
		void set(Point loc) { location = Relocation(loc); }
	}
	Figure(Point loc, System::Drawing::Size size, String^ text);
	//�����, �������������� ��������� ������
	void DrawText(Rectangle r);
};
//������� ���������� �����
public ref struct PairRule
{
	Type^ A;//��� 1
	Type^ B;//��� 2
	PairRule(Type^ A, Type^ B);
	//����� �������� �������
	bool Check(Figure^ a, Figure^ b);
};
//************************************
//������, ����������� ���������� �����
//************************************
[DataContract]
public ref class Line :DiagramObject
{
private:
	[DataMember] const float OFFSET = 5;//����������� ��� ��������� ������� �� �����
	//�����, ������������ ��������� ����� �� ����� � ������ �����������
	float Function(Point p1,Point p2, Point search_point,float offset);
public:
	[DataMember] Figure^ f1;//������ 1
	[DataMember] Figure^ f2;//������ 2
	Point FlowPoint;//��������� �����, ����� ������������ 2 ������ 
	Line(Figure^ f1, Point flow_point, String^ text);
	//�����, �������������� ����� ����� � �������� ������
	void ConnectFigure(Figure^ f2);
	//�����, �������������� ��������� ������
	void DrawText();
	bool Exist(Point point) override;
	void Paint() override;
};

//************************************
//���� ���������
//************************************
//����� ���� ���������
[DataContract]
public ref class Area
{
private:
	[DataMember(Order = 0)] List<Figure^>^ objects;//������ �����
	[DataMember(Order = 1)] List<Line^>^ lines;//������ ����������
	List<PairRule^>^ pairs;//������ ������ ����������
	//�����, ������������ ���������� �����, ����������� � �������� �������
	int CountLine(Figure^ f);
	//�����, ������������ ������� ����������� ���������� � �������� �������
	bool CheckMaxLine(Figure^ f);
	//�����, ��������� ���������� � �������� �������
	void RemoveLines(Figure^ f);
	//����� �������� ������ ���������� �����
	bool CheckRules(Figure^ a, Figure^ b);
	//���������� ������ ����������
	void UpdateLines();
	//�����, ������������� ����� ��������������, ��� ������������ �������� �� ���������
	[OnDeserialized] void OnDeserializedMethod(StreamingContext context);
	void SetDefaultSettings();
public:
	static Graphics^ g;//���������� ���������
	Image^ image;//������� ���������
	Area(System::Drawing::Size size);
	//�����, ���������� ������ ����
	Image^ Resize(System::Drawing::Size new_size);
	//���������� ��������
	int Count();
	//����� ���������� ������
	void AddFigure(Point location, ObjectType type);
	//����� ���������� ����������
	bool AddLine(Line^ line);
	//����� �������� ������
	void RemoveObject(Point point);
	//����� �������� �����
	void RemoveLine(Line^ line);
	//��������� ������ �� �������
	Figure^ GetFigure(Point point);
	//��������� ����� �� �������
	Line^ GetLine(Point point);
	//��������� ������ ����� ������������� ����
	List<Figure^>^ GetFigures(Type^ type);
	//��������� ������ �����, ����������� � �������� �������
	List<Line^>^ GetLines(Figure^ r);
	//�������� ���� �������� � ����
	void Clear();
	//����� ��������� �������� �� ����
	void Paint();
};

//************************************
//������� ���������
//************************************
//�����, �������� �������������
[DataContract]
public ref class RectangleObject : public Figure
{
public:
	RectangleObject(Point loc, System::Drawing::Size size, String^ text);
	bool Exist(Point point) override;
	void Paint() override;
};

//��� �����
public enum class Relation
{
	One,//����
	Many//�����
};

//�����, �������� ����
[DataContract]
public ref class RhombObject : public Figure
{
private:
	array<Point>^ points;//����� ���������� �����
protected:
	Point Relocation(Point location_center) override;
public:
	[DataMember] Relation r1;//��� ����� � ������� 1
	[DataMember] Relation r2;//��� ����� � ������� 2
	//����� ��������� ���������� �������� ���� �����
	static String^ GetRCode(Relation r);
	RhombObject(Point loc, System::Drawing::Size size, String^ text);
	//�����, ��������������� �������� ���� ������
	void SetRelation(Relation r1, Relation r2);
	bool Exist(Point point) override;
	void Paint() override;
};

//�����, �������� ����
[DataContract]
public ref class EllipseObject : public Figure
{
public:
	EllipseObject(Point loc, System::Drawing::Size size, String^ text);
	bool Exist(Point point) override;
	void Paint() override;
};

