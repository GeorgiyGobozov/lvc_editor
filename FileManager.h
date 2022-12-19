#pragma once
#include "Objects.h"

namespace lvceditor {

	using namespace System;
	using namespace System::IO;
	using namespace System::Runtime::Serialization;
	using namespace System::Xml;

	//�����, ����������� �����������/��������� ������
	ref class FileManager
	{
	public:
		String^ message_error;//��������� �� ������
		//��������
		Area^ Load(String^ url);
		//����������
		bool Save(Area ^area, String^ url);
	};
}

