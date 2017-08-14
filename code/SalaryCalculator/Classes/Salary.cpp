#include "Salary.h"
#include "Tax.h"
#include "Welfare.h"

bool Calculator::Pre2Suf(Salary& salary, int version)
{
	float pre = salary.Pre - salary.Det; 
	if (pre < 0 || pre > ULONG_MAX)
	{
		return false;
	}

	Tax* tax = TaxManager::Instance()->getTax(version);
	if (!tax)
	{
		return false;
	}
	
	float line = tax->Line;
	float rest = pre - line;
	if(rest <= 0)
	{
		salary.Tax = 0;
		salary.Suf = pre;
		return true;
	}

	for(int i = 0; ;i++)
	{
		float min = tax->Items[i]->Min;
		float max = tax->Items[i]->Max;
		if(rest > min && rest <= max) 
		{
			float rate = tax->Items[i]->Rate;
			float deduct = tax->Items[i]->Det;
			salary.Tax = (pre - line) * rate - deduct;
			salary.Suf = pre - salary.Tax;
			return true;
		}
	}
}

bool Calculator::Suf2Pre(Salary& salary, int version)
{
	float suf = salary.Suf;
	if (suf < 0 || suf > ULONG_MAX)
	{
		return false;
	}

	Tax* tax = TaxManager::Instance()->getTax(version);
	if(!tax)
	{
		return false;
	}

	float line = tax->Line;
	float rest = suf - line;
	if(rest <= 0)
	{
		salary.Tax = 0;
		salary.Pre = suf + salary.Det;
		return true;
	}

	float pre = 0;
	for(int i = 0; i < (int)tax->Items.size(); i++)
	{
		float min = tax->Items[i]->Min;
		float max = tax->Items[i]->Max;
		float rate = tax->Items[i]->Rate;
		float deduct = tax->Items[i]->Det;
		float temp = (suf - deduct - rate * line) /(1 - rate);
		if (temp > pre)
		{
			pre = temp;
		}
	}
	salary.Tax = pre - suf;
	salary.Pre = pre + salary.Det;
	return true;
}

bool Calculator::Tax2Two(Salary& salary, int version)
{
	float tax = salary.Tax;
	if (tax < 0 || tax > ULONG_MAX)
	{
		return false;
	}

	Tax* table = TaxManager::Instance()->getTax(version);
	if(!table)
	{
		return false;
	}

	float line = table->Line;
	float pre = (float)ULONG_MAX;
	for(int i = 0; i < (int)table->Items.size(); i++)
	{
		float min = table->Items[i]->Min;
		float max = table->Items[i]->Max;
		float rate = table->Items[i]->Rate;
		float deduct = table->Items[i]->Det;
		float temp = (tax + deduct) / rate + line;
		if (temp < pre)
		{
			pre = temp;
		}
	}
	salary.Suf = pre - tax;
	salary.Pre = pre + salary.Det;
	return true;
}

bool Calculator::DoDeduct(Deduct& deduct, const std::vector<WelfareItem>& Items)
{
	float ins = deduct.Ins;
	float fund = deduct.Fund;
	if (ins < 0 || ins > ULONG_MAX || fund < 0 || fund > ULONG_MAX)
	{
		return false;
	}

	for (int i = 0; i < (int)Items.size(); i++)
	{
		WelfareItem item;
		item.Type = i;
		float temp = i < WIT_FUND ? ins : fund;
		item.Allow = Items[i].Allow;
		item.Personal = int(Items[i].Personal * temp);
		item.Company = int(Items[i].Company * temp);
		deduct.Items.push_back(item);
		if (item.Allow)
		{
			deduct.Private += item.Personal;
			deduct.Company += item.Company;
		}	
	}
	return true;
}