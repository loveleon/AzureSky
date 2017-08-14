#pragma once

#include "Header.h"

//工资项
struct Salary
{
	Salary()
	{ 
		Pre = 0.0f; 
		Det = 0.0f;
		Tax = 0.0f;
		Suf = 0.0f;
	}
	float Pre;	//发放
	float Det;  //扣款
	float Tax;	//税额
	float Suf;	//税后
};

struct WelfareItem;
struct Deduct
{
	Deduct()
	{
		Ins = 0.0f;
		Fund = 0.0f;
		Private = 0.0f;
		Company = 0.0f;
		Items.clear();
	}
	float Ins;		//社保基数
	float Fund;		//公积金基数
	float Private;	//个人缴纳总额
	float Company;	//公司缴纳总额
	std::vector<WelfareItem> Items;	 //当前缴纳细项
};

class Calculator
{
public:
	//税前->税后
	static bool Pre2Suf(Salary& salary, int version = 2011);
	//税后->税前
	static bool Suf2Pre(Salary& salary, int version = 2011);
	//税->税前税后
	static bool Tax2Two(Salary& salary, int version = 2011);
	//扣除款
	static bool DoDeduct(Deduct& deduct, const std::vector<WelfareItem>& Items);
};