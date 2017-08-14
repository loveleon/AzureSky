#pragma once

#include "Header.h"

//����������
enum WelfareItemType
{
	WIT_MEDICAL,		//ҽ��
	WIT_RETIRE,			//����
	WIT_FIRE,			//ʧҵ
	WIT_HURT,			//����
	WIT_BIRTH,			//����
	WIT_FUND			//������
};

//������������
enum WelfareCityName
{
	WCN_BEIJING,		//����
	WCN_TIANJIN,		//���
	WCN_SHANGHAI,		//�Ϻ�
	WCN_GUANGZHOU,		//����
	WCN_SHENZHEN,		//����
	WCN_OTHER			//����
};

//������
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
	bool  Allow;		//����
	int   Type;			//����
	float Company;		//��˾
	float Personal;		//����
};

//����
struct Welfare
{
	int   City;			//����
	float SIMin;		//�籣����
	float SIMax;		//�籣����
	float AFMin;		//����������
	float AFMax;		//����������
	std::vector<WelfareItem*> Items;		//����
};

//����������
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