#pragma once

#include "Header.h"

//������
struct Salary
{
	Salary()
	{ 
		Pre = 0.0f; 
		Det = 0.0f;
		Tax = 0.0f;
		Suf = 0.0f;
	}
	float Pre;	//����
	float Det;  //�ۿ�
	float Tax;	//˰��
	float Suf;	//˰��
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
	float Ins;		//�籣����
	float Fund;		//���������
	float Private;	//���˽����ܶ�
	float Company;	//��˾�����ܶ�
	std::vector<WelfareItem> Items;	 //��ǰ����ϸ��
};

class Calculator
{
public:
	//˰ǰ->˰��
	static bool Pre2Suf(Salary& salary, int version = 2011);
	//˰��->˰ǰ
	static bool Suf2Pre(Salary& salary, int version = 2011);
	//˰->˰ǰ˰��
	static bool Tax2Two(Salary& salary, int version = 2011);
	//�۳���
	static bool DoDeduct(Deduct& deduct, const std::vector<WelfareItem>& Items);
};