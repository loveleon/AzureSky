#pragma once 

#include "Header.h"

//˰����
struct TaxItem
{
	int	  Lev;		//����	
	float Min;		//����
	float Max;		//����
	float Rate;		//˰��
	float Det;		//����۳�ֵ
};

//˰��
struct Tax
{
	int	  Ver;		//�汾
	float Line;		//������
	std::vector<TaxItem*> Items;		//����
};

//˰�������
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