#include "Welfare.h"
#include "tinyxml.h"

WelfareManager* WelfareManager::Instance()
{
	static WelfareManager* manager = nullptr;
	if(!manager)
	{
		manager = new WelfareManager();
	}
	return manager;
}

bool WelfareManager::Init(const std::string& file)
{
	m_mapItemTypeID["medical"] = WIT_MEDICAL;
	m_mapItemTypeID["retire"] = WIT_RETIRE;
	m_mapItemTypeID["fire"] = WIT_FIRE;
	m_mapItemTypeID["hurt"] = WIT_HURT;
	m_mapItemTypeID["birth"] = WIT_BIRTH;
	m_mapItemTypeID["fund"] = WIT_FUND;

	m_mapCityNameID["北京"] = WCN_BEIJING;
	m_mapCityNameID["天津"] = WCN_TIANJIN;
	m_mapCityNameID["上海"] = WCN_SHANGHAI;
	m_mapCityNameID["广州"] = WCN_GUANGZHOU;
	m_mapCityNameID["深圳"] = WCN_SHENZHEN;
	m_mapCityNameID["其他"] = WCN_OTHER;

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
		Welfare* welfare = new Welfare();
		char* temp = (char*)element->Attribute("name");
		welfare->City = getCityID(temp);
		temp = (char*)element->Attribute("si_min");
		welfare->SIMin = (float)atof(temp);
		temp = (char*)element->Attribute("si_max");
		welfare->SIMax = (float)atof(temp);
		temp = (char*)element->Attribute("af_min");
		welfare->AFMin = (float)atof(temp);
		temp = (char*)element->Attribute("af_max");
		welfare->AFMax = (float)atof(temp);
		TiXmlElement* sub = element->FirstChildElement();
		while (sub)
		{
			WelfareItem* item = new WelfareItem();
			item->Allow = true;
			temp = (char*)sub->Attribute("name");
			item->Type = getItemID(temp);
			temp = (char*)sub->Attribute("company");
			item->Company = (float)atof(temp);
			temp = (char*)sub->Attribute("personal");
			item->Personal = (float)atof(temp);
			welfare->Items.push_back(item);
			sub = sub->NextSiblingElement();	
		}
		m_mapWelfares[welfare->City] = welfare;
		element = element->NextSiblingElement();
	}
	return true;
}

void WelfareManager::Destroy()
{
	for(auto item : m_mapWelfares)
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
	m_mapWelfares.clear();
}

Welfare* WelfareManager::getWelfare(int city)
{
	auto iter = m_mapWelfares.find(city);
	return iter != m_mapWelfares.end() ? iter->second : nullptr;
}

int WelfareManager::getItemID(const std::string& str)
{
	auto iter = m_mapItemTypeID.find(str);
	return iter != m_mapItemTypeID.end() ? iter->second : -1;
}

int WelfareManager::getCityID(const std::string& str)
{
	auto iter = m_mapCityNameID.find(str);
	return iter != m_mapCityNameID.end() ? iter->second : -1;
}