//����ͷ�ļ�

#pragma once

#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>

using namespace std;

//�����������Ա������д��
#define CREATE_MEMBER(type,name) \
public: \
	type get##name(){ return m_##name; } \
	void set##name(type n){ m_##name = n; } \
protected: \
	type m_##name;

