#pragma once
#include "Objects.h"

namespace lvceditor {

	using namespace System;
	using namespace System::IO;
	using namespace System::Runtime::Serialization;
	using namespace System::Xml;

	//Класс, управляющий сохранением/загрузкой данных
	ref class FileManager
	{
	public:
		String^ message_error;//Сообщение об ошибке
		//Загрузка
		Area^ Load(String^ url);
		//Сохранение
		bool Save(Area ^area, String^ url);
	};
}

