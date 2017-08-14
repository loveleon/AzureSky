#pragma once

#include "Header.h"

//福利项类型
enum WelfareItemType
{
	WIT_MEDICAL,		//医疗
	WIT_RETIRE,			//养老
	WIT_FIRE,			//失业
	WIT_HURT,			//工伤
	WIT_BIRTH,			//生育
	WIT_FUND			//公积金
};

//福利城市名字
enum WelfareCityName
{
	WCN_BEIJING,		//北京
	WCN_TIANJIN,		//天津
	WCN_SHANGHAI,		//上海
	WCN_GUANGZHOU,		//广州
	WCN_SHENZHEN,		//深圳
	WCN_OTHER			//其他
};

//福利项
struct WelfareItem
{
	WelfareItem(){}
	WelfareItem(int t, bool a, float c, float p)
	{
		Type = t;
		Allow = a;
		Company = c;
		Personal = p;
	}
	bool  Allow;		//参与
	int   Type;			//类型
	float Company;		//公司
	float Personal;		//个人
};

//福利
struct Welfare
{
	int   City;			//城市
	float SIMin;		//社保下限
	float SIMax;		//社保上限
	float AFMin;		//公积金下限
	float AFMax;		//公积金上限
	std::vector<WelfareItem*> Items;		//集合
};

//福利管理器
class WelfareManager
{
public:
	static WelfareManager* Instance();
	bool Init(const std::string& file);
	void Destroy();
	Welfare* getWelfare(int city);
	int getItemID(const std::string& str);
	int getCityID(const std::string& str);
	std::map<std::string, int>& getCityNames(){ return m_mapCityNameID; }
private:
	std::map<int, Welfare*> m_mapWelfares;
	std::map<std::string, int> m_mapItemTypeID;
	std::map<std::string, int> m_mapCityNameID;
};