#pragma once 

#include "Header.h"

//税表项
struct TaxItem
{
	int	  Lev;		//级别	
	float Min;		//下限
	float Max;		//上限
	float Rate;		//税率
	float Det;		//速算扣除值
};

//税表
struct Tax
{
	int	  Ver;		//版本
	float Line;		//起征线
	std::vector<TaxItem*> Items;		//集合
};

//税表管理器
class TaxManager
{
public:
	static TaxManager* Instance();
	bool Init(const std::string& file);
	void Destroy();
	Tax* getTax(int ver);
private:
	std::map<int, Tax*> m_mapTaxs;
};