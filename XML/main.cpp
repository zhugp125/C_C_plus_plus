#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include "tinyxml2/tinyxml2.h"
#include "tinyxml/tinyxml.h"
#include <boost/timer.hpp>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

using namespace std;
using namespace tinyxml2;
using namespace boost;

const char* testFileName = "utf8test.xml";

void readXml_tinyxml2()
{
    XMLDocument doc;
    doc.LoadFile(testFileName);
    if (doc.Error())
    {
        cout << "open xml file failed, error id : " << doc.ErrorID() << " error name: " << doc.ErrorName() << endl;
        return ;
    }

    XMLElement* docElement = doc.FirstChildElement("document");
    XMLElement* englishElement = docElement->FirstChildElement("English");
    cout << "english \nattribute: \nname: " << englishElement->Attribute("name")
         << " \nvalue: " << englishElement->Attribute("value")
         << " \ntext: " << englishElement->GetText() << "\n";

    XMLElement* simplifiedElement = docElement->FirstChildElement("SimplifiedChinese");
    cout << "simplifiedChinese \nattribute: \nname: " << simplifiedElement->Attribute("name")
         << " \nvalue: " << simplifiedElement->Attribute("value")
         << " \ntext: " << simplifiedElement->GetText() << "\n";

    XMLElement* chineseElement = docElement->FirstChildElement("汉语");
    cout << "汉语 \nattribute: \n名字: " << chineseElement->Attribute("名字")
         << " \n价值: " << chineseElement->Attribute("价值")
         << " \ntext: " << chineseElement->GetText() << "\n";
}

struct XmlNode
{
    XmlNode(string name = "", string text = "", int value = -1)
        : m_name(name)
        , m_value(value)
        , m_text(text)
    {}

    string m_name;
    int m_value;
    string m_text;
};
map<string, XmlNode> g_data;

void initData()
{
    g_data.insert(make_pair("first", XmlNode("1", "first text", 1)));
    g_data.insert(make_pair("second", XmlNode("2", "second text", 2)));
    g_data.insert(make_pair("three", XmlNode("3", "three text", 3)));
    g_data.insert(make_pair("four", XmlNode("4", "four text", 4)));
}

void writeXml_tinyxml2()
{
    if (g_data.empty())
    {
        cout << "data is empty" << endl;
        return;
    }

    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");

    XMLElement* root = doc.NewElement("document");
    doc.InsertEndChild(root);

    for (auto it = g_data.cbegin(); it != g_data.cend(); ++it)
    {
        const string& key = it->first;
        const XmlNode& node = it->second;

        if (key.empty())
        {
            continue;
        }

        XMLElement* element = doc.NewElement(key.c_str());
        if (!node.m_name.empty())
        {
            element->SetAttribute("name", node.m_name.c_str());
        }
        if (-1 != node.m_value)
        {
            element->SetAttribute("value", node.m_value);
        }
        if (!node.m_text.empty())
        {
            element->SetText(node.m_text.c_str());
        }
        root->InsertEndChild(element);
    }
    doc.SaveFile("writeXml.xml");
}

void readXml_tinyxml()
{
    TiXmlDocument doc(testFileName);
    if (!doc.LoadFile())
    {
        cout << "open xml file failed, error id : " << doc.ErrorId() << " error name: " << doc.ErrorDesc() << endl;
        return ;
    }

    TiXmlElement* root = doc.RootElement();
    cout << "[root name]: " << root->Value() << "\n";

    for (const TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
    {
        cout << element->Value() << " ";

        for (const TiXmlAttribute* attr = element->FirstAttribute(); attr != NULL; attr = attr->Next())
        {
            cout << attr->Name() << ": " << attr->Value() << " ";
        }
        cout << "text: " << element->GetText() << endl;
    }
}

void writeXml_tinyxml()
{
    if (g_data.empty())
    {
        cout << "data is empty" << endl;
        return;
    }

    TiXmlDocument doc;
    TiXmlDeclaration decl("1.0", "UTF-8", "Yes");
    doc.InsertEndChild(decl);

    TiXmlElement *root = new TiXmlElement("document");
    doc.LinkEndChild(root);

    for (auto it = g_data.cbegin(); it != g_data.cend(); ++it)
    {
        const string& key = it->first;
        const XmlNode& node = it->second;

        if (key.empty())
        {
            continue;
        }

        TiXmlElement *element = new TiXmlElement(key.c_str());
        if (!node.m_name.empty())
        {
            element->SetAttribute("name", node.m_name.c_str());
        }
        if (-1 != node.m_value)
        {
            element->SetAttribute("value", node.m_value);
        }
        if (!node.m_text.empty())
        {
            TiXmlText *text = new TiXmlText(node.m_text.c_str());
            element->LinkEndChild(text);
        }
        root->LinkEndChild(element);
    }
    cout << doc.SaveFile("writeXml_tinyxml.xml") << endl;
}

vector<map<string, XmlNode> > g_vec;
void initVec()
{
    map<string, XmlNode> m;
    m.insert(make_pair("first", XmlNode("one", "1", 0)));
    g_vec.push_back(m);

    m.insert(make_pair("second", XmlNode("two", "2", 1)));
    g_vec.push_back(m);

    m.insert(make_pair("third", XmlNode("three", "3")));
    g_vec.push_back(m);

    m.insert(make_pair("four", XmlNode("four", "4", 2)));
    g_vec.push_back(m);

    m.insert(make_pair("five", XmlNode("five", "5", 4)));
    g_vec.push_back(m);

    m.insert(make_pair("six", XmlNode("six", "6", 5)));
    g_vec.push_back(m);

    m.insert(make_pair("seven", XmlNode("seven", "7", 8)));
    g_vec.push_back(m);

    m.insert(make_pair("eight", XmlNode("eight", "8", 7)));
    g_vec.push_back(m);

    m.insert(make_pair("nine", XmlNode("nine", "9", 8)));
    g_vec.push_back(m);

    m.insert(make_pair("ten", XmlNode("ten", "10", 10)));
    g_vec.push_back(m);

    m.insert(make_pair("elevn", XmlNode("seven", "7", 8)));
    g_vec.push_back(m);

    for (int i = 0; i < 200; ++i)
    {
        g_vec.push_back(m);
    }
}

// test
bool write_tinyxml(const char* file)
{
    if (NULL == file || strlen(file) == 0)
    {
        return false;
    }

    TiXmlDocument doc;
    doc.LinkEndChild(new TiXmlDeclaration("1.0", "UTF-8", ""));

    TiXmlElement* root = new TiXmlElement("document");
    doc.LinkEndChild(root);

    for (auto vit = g_vec.cbegin(); vit != g_vec.cend(); ++vit)
    {
        TiXmlElement* data = new TiXmlElement("data");
        const map<string, XmlNode>& m = *vit;
        for (auto mit = m.cbegin(); mit != m.cend(); ++mit)
        {
            const string& key = mit->first;
            const XmlNode& node = mit->second;
            TiXmlElement* element = new TiXmlElement(key.c_str());
            if (!node.m_name.empty())
            {
                TiXmlElement* name = new TiXmlElement("name");
                name->SetAttribute("name", node.m_name.c_str());
                element->LinkEndChild(name);
            }
            if (node.m_value != -1)
            {
                TiXmlElement* value = new TiXmlElement("value");
                value->SetAttribute("value", node.m_value);
                element->LinkEndChild(value);
            }
            if (!node.m_text.empty())
            {
                TiXmlElement* text = new TiXmlElement("text");
                text->LinkEndChild(new TiXmlText(node.m_text.c_str()));
                element->LinkEndChild(text);
            }
            data->LinkEndChild(element);
        }
        root->LinkEndChild(data);
    }
    return doc.SaveFile(file);
}

// test
bool write_tinyxml2(const char* file)
{
    if (file == NULL || strlen(file) == 0)
    {
        return false;
    }

    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    doc.LinkEndChild(decl);

    XMLElement* root = doc.NewElement("document");
    doc.LinkEndChild(root);

    for (auto vit = g_vec.cbegin(); vit != g_vec.cend(); ++vit)
    {
        XMLElement* data = doc.NewElement("data");
        const map<string, XmlNode>& m = *vit;
        for (auto mit = m.cbegin(); mit != m.cend(); ++mit)
        {
            const string& key = mit->first;
            const XmlNode& node = mit->second;
            XMLElement* element = doc.NewElement(key.c_str());
            if (!node.m_name.empty())
            {
                XMLElement* name = doc.NewElement("name");
                name->SetAttribute("name", node.m_name.c_str());
                element->LinkEndChild(name);
            }
            if (node.m_value != -1)
            {
                XMLElement* value = doc.NewElement("value");
                value->SetAttribute("value", node.m_value);
                element->LinkEndChild(value);
            }
            if (!node.m_text.empty())
            {
                XMLElement* text = doc.NewElement("text");
                text->SetText(node.m_text.c_str());
                element->LinkEndChild(text);
            }
            data->LinkEndChild(element);
        }
        root->LinkEndChild(data);
    }
    return doc.SaveFile(file);
}

// test
bool write_qtxml(const char* file)
{
    if (NULL == file || strlen(file) == 0)
    {
        return false;
    }

    QFile f(file);
    if (!f.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QXmlStreamWriter writer(&f);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("document");
    for (auto vit = g_vec.cbegin(); vit != g_vec.cend(); ++vit)
    {
        writer.writeStartElement("data");
        const map<string, XmlNode>& m = *vit;
        for (auto mit = m.cbegin(); mit != m.cend(); ++mit)
        {
            const string& key = mit->first;
            const XmlNode& node = mit->second;

            writer.writeStartElement(key.c_str());
            if (!node.m_name.empty())
            {
                writer.writeStartElement("name");
                writer.writeAttribute("name", node.m_name.c_str());
                writer.writeEndElement();
            }
            if (node.m_value != -1)
            {
                writer.writeStartElement("value");
                writer.writeAttribute("value", QString::number(node.m_value));
                writer.writeEndElement();
            }
            if (!node.m_text.empty())
            {
                writer.writeTextElement("text", node.m_name.c_str());
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();

    return !writer.hasError();
}

// test
bool read_tinyxml(const char* file)
{
    if (NULL == file || strlen(file) == 0)
    {
        return false;
    }

    TiXmlDocument doc(file);
    if (!doc.LoadFile())
    {
        cout << "open xml file failed, error id : " << doc.ErrorId() << " error name: " << doc.ErrorDesc() << endl;
        return false;
    }

    TiXmlElement* root = doc.RootElement();
    root->Value();

    for (TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
    {
        element->Value();
        for (TiXmlElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
        {
            child->Value();
            TiXmlElement* name = child->FirstChildElement("name");
            if (name != NULL)
            {
                name->Attribute("name");
            }
            TiXmlElement* value = child->FirstChildElement("value");
            if (value != NULL)
            {
                value->Attribute("value");
            }
            TiXmlElement* text = child->FirstChildElement("text");
            if (text != NULL)
            {
                text->GetText();
            }
        }
    }

    return true;
}

// test
bool read_tinyxml2(const char* file)
{
    if (NULL == file || strlen(file) == 0)
    {
        return false;
    }

    XMLDocument doc;
    doc.LoadFile(file);
    if (doc.Error())
    {
        cout << "open xml file failed, error id : " << doc.ErrorID() << " error name: " << doc.ErrorName() << endl;
        return false;
    }

    XMLElement* root = doc.RootElement();
    root->Value();

    for (XMLElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
    {
        element->Value();
        for (XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
        {
            child->Value();
            XMLElement* name = child->FirstChildElement("name");
            if (name != NULL)
            {
                name->Attribute("name");
            }
            XMLElement* value = child->FirstChildElement("value");
            if (value != NULL)
            {
                value->Attribute("value");
            }
            XMLElement* text = child->FirstChildElement("text");
            if (text != NULL)
            {
                text->GetText();
            }
        }
    }
    return true;
}

// test
bool read_qtxml(const char* file)
{
    if (NULL == file || strlen(file) == 0)
    {
        return false;
    }

    QFile f(file);
    if (!f.open(QIODevice::ReadOnly))
    {
        cout << "open file failed\n";
        return false;
    }
    QXmlStreamReader reader(&f);

    while (!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            QString name = reader.name().toString();
            if (name == "name")
            {
                reader.attributes().value("name").toString();
            }
            else if (name == "value")
            {
                reader.attributes().value("value").toString();
            }
            else if (name == "text")
            {
                reader.readElementText();
            }
            else
            {
                reader.name().toString();
            }
        }
    }

    bool ok = reader.hasError();
    if (ok)
    {
        cout << "error: " << reader.errorString().toStdString() << "\n";
        cout << reader.lineNumber() << "\n";
    }
    return !ok;
}

int main()
{
    /*
    readXml_tinyxml2();
    initData();
    writeXml_tinyxml2();

    cout << "--------------------------------\n";
    readXml_tinyxml();
    writeXml_tinyxml();
    */

    const char* file = "test.xml";

    initVec();

    /*
    {
        timer t;
        write_tinyxml(file);
        cout << "tinyxml write xml file time: " << t.elapsed() << "s\n";
    }

    {
        timer t;
        write_tinyxml2(file);
        cout << "tinyxml2 write xml file time: " << t.elapsed() << "s\n";
    }

    {
        timer t;
        write_qtxml(file);
        cout << "qt write xml file time: " << t.elapsed() << "s\n";
    }

    {
        timer t;
        read_tinyxml(file);
        cout << "tinyxml read xml file time: " << t.elapsed() << "s\n";
    }

    {
        timer t;
        read_tinyxml2(file);
        cout << "tinyxml2 read xml file time: " << t.elapsed() << "s\n";
    }

    {
        timer t;
        read_qtxml(file);
        cout << "qt xml read xml file time: " << t.elapsed() << "s\n";
    }
    */

    cout << "Hello World!" << endl;
    return 0;
}
