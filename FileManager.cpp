#include "FileManager.h"

namespace lvceditor {
    Area^ FileManager::Load(String^ url)
    {
        try
        {
            NetDataContractSerializer^ formatter = gcnew NetDataContractSerializer();
            XmlReader^ writer = XmlReader::Create(url);
            Area ^area=(Area^)formatter->ReadObject(writer);
            writer->Close();
            return area;
        }
        catch(...)
        {
            message_error= "Ошибка при открытии файла";
            return nullptr;
        }
    }
    bool FileManager::Save(Area^ area, String^ url)
    {
        try
        {
            NetDataContractSerializer^ formatter = gcnew NetDataContractSerializer();
            XmlWriterSettings^ setting = gcnew XmlWriterSettings();
            setting->Indent = true;
            XmlWriter^ writer = XmlWriter::Create(url, setting);
            formatter->WriteObject(writer, area);
            writer->Close();
            return true;
        }
        catch(...)
        {
            message_error = "Ошибка при сохранении файла";
            return false;
        }
    }
}
