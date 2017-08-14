#include "Tax.h"
#include "tinyxml.h"

TaxManager* TaxManager::Instance()
{
	static TaxManager* manager = nullptr;
	if(!manager)
	{
		manager = new TaxManager();
	}
	return manager;
}

bool TaxManager::Init(const std::string& file)
{
	TiXmlDocument* doc = new TiXmlDocument();
	if (!doc->LoadFile(file.c_str()))
	{
		return false;
	}
	TiXmlElement* root = doc->RootElement();
	if (!root)
	{
		return false;
	}
	TiXmlElement* element = root->FirstChildElement();
	while (element)
	{
		Tax* tax = new Tax();
		char* temp = const_cast<char*>(element->Attribute("version"));
		tax->Ver = atoi(temp);
		temp = const_cast<char*>(element->Attribute("line"));
		tax->Line = (float)atof(temp);
		TiXmlElement* sub = element->FirstChildElement();
		while (sub)
		{
			TaxItem* item = new TaxItem();
			temp = const_cast<char*>(sub->Attribute("level"));
			item->Lev = atoi(temp);
			temp = const_cast<char*>(sub->Attribute("min"));
			item->Min = (float)atof(temp);
			temp = const_cast<char*>(sub->Attribute("max"));
			item->Max = (float)atof(temp);
			temp = const_cast<char*>(sub->Attribute("rate"));
			item->Rate = (float)atof(temp);
			temp = const_cast<char*>(sub->Attribute("deduct"));
			item->Det = (float)atof(temp);
			tax->Items.push_back(item);
			sub = sub->NextSiblingElement();
		}
		m_mapTaxs[tax->Ver] = tax;
		element = element->NextSiblingElement();
	}
	return true;
}

void TaxManager::Destroy()
{
	for (auto item : m_mapTaxs)
	{
		for (auto im : item.second->Items)
		{
			delete im;
			im = nullptr;
		}
		item.second->Items.clear();
		delete item.second;
		item.second = nullptr;
	}
	m_mapTaxs.clear();
}

Tax* TaxManager::getTax(int ver)
{
	auto iter = m_mapTaxs.find(ver);
	return iter != m_mapTaxs.end() ? iter->second : nullptr;
}