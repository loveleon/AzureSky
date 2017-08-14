#pragma once

#include "Tax.h"
#include "Welfare.h"
#include "Salary.h"

namespace SalaryCalculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// UI 摘要
	/// </summary>
	public ref class UI : public System::Windows::Forms::Form
	{
	public:
		UI(void)
		{
			InitializeComponent();
			
			if (!TaxManager::Instance()->Init("Config/Tax.xml"))
			{
				assert("Config Tax Fail!");
				return;
			}
			if (!WelfareManager::Instance()->Init("Config/Welfare.xml"))
			{
				assert("Config Welfare Fail!");
				return;
			}

			m_nTaxType = 2011;
			m_pCurWelfare = nullptr;
			
			auto citys = WelfareManager::Instance()->getCityNames();
			std::map<int, std::string> temp;
			for (auto n : citys)
			{
				temp[n.second] = n.first;
			}
			for (auto t : temp)
			{
				this->comboBox1->Items->Add(gcnew System::String(t.second.c_str()));
			}

			this->radioButton1->Checked = true;
			this->radioButton2->Checked = false;

			this->checkBox1->Checked = true;
			this->checkBox2->Checked = true;
			this->checkBox3->Checked = true;
			this->checkBox4->Checked = true;
			this->checkBox5->Checked = true;
			this->checkBox6->Checked = true;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~UI()
		{
			if (components)
			{
				delete components;
			}

			TaxManager::Instance()->Destroy();
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

		int m_nTaxType;
		Welfare* m_pCurWelfare;

		void WelfareItemAllow(int index)
		{
			if (!m_pCurWelfare)
			{
				return;
			}
			bool b = m_pCurWelfare->Items[index]->Allow;
			m_pCurWelfare->Items[index]->Allow = !b;
		}

		void calDeduct(Deduct& d)
		{
			d.Ins = String::IsNullOrEmpty(this->textBox4->Text) ? 0.0f : Convert::ToSingle(this->textBox4->Text);
			d.Fund = String::IsNullOrEmpty(this->textBox5->Text) ? 0.0f : Convert::ToSingle(this->textBox5->Text);
			std::vector<WelfareItem> temp;
			temp.push_back(WelfareItem(WIT_MEDICAL, Convert::ToBoolean(this->checkBox1->Checked), Convert::ToSingle(this->textBox6->Text) / 100, Convert::ToSingle(this->textBox17->Text) / 100));
			temp.push_back(WelfareItem(WIT_RETIRE, Convert::ToBoolean(this->checkBox2->Checked), Convert::ToSingle(this->textBox7->Text) / 100, Convert::ToSingle(this->textBox16->Text) / 100));
			temp.push_back(WelfareItem(WIT_FIRE, Convert::ToBoolean(this->checkBox3->Checked), Convert::ToSingle(this->textBox8->Text) / 100, Convert::ToSingle(this->textBox15->Text) / 100));
			temp.push_back(WelfareItem(WIT_HURT, Convert::ToBoolean(this->checkBox4->Checked), Convert::ToSingle(this->textBox9->Text) / 100, Convert::ToSingle(this->textBox14->Text) / 100));
			temp.push_back(WelfareItem(WIT_BIRTH, Convert::ToBoolean(this->checkBox5->Checked), Convert::ToSingle(this->textBox10->Text) / 100, Convert::ToSingle(this->textBox13->Text) / 100));
			temp.push_back(WelfareItem(WIT_FUND, Convert::ToBoolean(this->checkBox6->Checked), Convert::ToSingle(this->textBox11->Text) / 100, Convert::ToSingle(this->textBox12->Text) / 100));
			Calculator::DoDeduct(d, temp);
		}

		void DeductExt(Deduct& d)
		{
			this->label38->Text = Convert::ToString(d.Company);
			this->label39->Text = Convert::ToString(d.Private);

			this->label24->Text = Convert::ToString(d.Items[WIT_MEDICAL].Company);
			this->label25->Text = Convert::ToString(d.Items[WIT_RETIRE].Company);
			this->label26->Text = Convert::ToString(d.Items[WIT_FIRE].Company);
			this->label27->Text = Convert::ToString(d.Items[WIT_HURT].Company);
			this->label28->Text = Convert::ToString(d.Items[WIT_BIRTH].Company);
			this->label29->Text = Convert::ToString(d.Items[WIT_FUND].Company);

			this->label35->Text = Convert::ToString(d.Items[WIT_MEDICAL].Personal);
			this->label34->Text = Convert::ToString(d.Items[WIT_RETIRE].Personal);
			this->label33->Text = Convert::ToString(d.Items[WIT_FIRE].Personal);
			this->label32->Text = Convert::ToString(d.Items[WIT_HURT].Personal);
			this->label31->Text = Convert::ToString(d.Items[WIT_BIRTH].Personal);
			this->label30->Text = Convert::ToString(d.Items[WIT_FUND].Personal);
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"城市：";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 37);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"税前：";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 64);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 12);
			this->label3->TabIndex = 2;
			this->label3->Text = L"个税：";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(13, 91);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(41, 12);
			this->label4->TabIndex = 3;
			this->label4->Text = L"税后：";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(49, 6);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(136, 20);
			this->comboBox1->TabIndex = 4;
			this->comboBox1->Text = L"请选择所在城市";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &UI::comboBox1_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(49, 33);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(136, 21);
			this->textBox1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(117, 61);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(68, 21);
			this->textBox2->TabIndex = 6;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(49, 89);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(136, 21);
			this->textBox3->TabIndex = 7;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(191, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"计算税后";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UI::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(191, 60);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 9;
			this->button2->Text = L"计算前后";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &UI::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(191, 88);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 10;
			this->button3->Text = L"计算税前";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &UI::button3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(13, 123);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 12);
			this->label5->TabIndex = 11;
			this->label5->Text = L"社保基数：";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(13, 151);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 12);
			this->label6->TabIndex = 12;
			this->label6->Text = L"公积金基数：";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(85, 119);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(121, 21);
			this->textBox4->TabIndex = 13;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(85, 147);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(121, 21);
			this->textBox5->TabIndex = 14;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(216, 124);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 12);
			this->label7->TabIndex = 15;
			this->label7->Text = L"[0,0]";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(216, 150);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 12);
			this->label8->TabIndex = 16;
			this->label8->Text = L"[0,0]";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(14, 181);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(65, 12);
			this->label9->TabIndex = 17;
			this->label9->Text = L"缴纳比例：";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(79, 181);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(53, 12);
			this->label10->TabIndex = 18;
			this->label10->Text = L"单位缴纳";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(187, 181);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(53, 12);
			this->label11->TabIndex = 19;
			this->label11->Text = L"个人缴纳";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(14, 206);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(48, 16);
			this->checkBox1->TabIndex = 20;
			this->checkBox1->Text = L"养老";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(14, 231);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(48, 16);
			this->checkBox2->TabIndex = 21;
			this->checkBox2->Text = L"医疗";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(14, 256);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(48, 16);
			this->checkBox3->TabIndex = 22;
			this->checkBox3->Text = L"失业";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox3_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(14, 281);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(48, 16);
			this->checkBox4->TabIndex = 23;
			this->checkBox4->Text = L"工伤";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox4_CheckedChanged);
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(14, 306);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(48, 16);
			this->checkBox5->TabIndex = 24;
			this->checkBox5->Text = L"生育";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox5_CheckedChanged);
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(14, 331);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(60, 16);
			this->checkBox6->TabIndex = 25;
			this->checkBox6->Text = L"公积金";
			this->checkBox6->UseVisualStyleBackColor = true;
			this->checkBox6->CheckedChanged += gcnew System::EventHandler(this, &UI::checkBox6_CheckedChanged);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(81, 204);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(40, 21);
			this->textBox6->TabIndex = 26;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(81, 228);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(40, 21);
			this->textBox7->TabIndex = 27;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(81, 253);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(40, 21);
			this->textBox8->TabIndex = 28;
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(81, 277);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(40, 21);
			this->textBox9->TabIndex = 29;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(81, 301);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(40, 21);
			this->textBox10->TabIndex = 30;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(81, 327);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(40, 21);
			this->textBox11->TabIndex = 31;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(189, 327);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(40, 21);
			this->textBox12->TabIndex = 37;
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(189, 301);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(40, 21);
			this->textBox13->TabIndex = 36;
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(189, 277);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(40, 21);
			this->textBox14->TabIndex = 35;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(189, 253);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(40, 21);
			this->textBox15->TabIndex = 34;
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(189, 228);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(40, 21);
			this->textBox16->TabIndex = 33;
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(189, 204);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(40, 21);
			this->textBox17->TabIndex = 32;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(128, 209);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(11, 12);
			this->label12->TabIndex = 38;
			this->label12->Text = L"%";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(128, 233);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(11, 12);
			this->label13->TabIndex = 39;
			this->label13->Text = L"%";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(128, 257);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(11, 12);
			this->label14->TabIndex = 40;
			this->label14->Text = L"%";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(128, 281);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(11, 12);
			this->label15->TabIndex = 41;
			this->label15->Text = L"%";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(128, 305);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(11, 12);
			this->label16->TabIndex = 42;
			this->label16->Text = L"%";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(128, 329);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(11, 12);
			this->label17->TabIndex = 43;
			this->label17->Text = L"%";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(240, 330);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(11, 12);
			this->label18->TabIndex = 49;
			this->label18->Text = L"%";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(240, 306);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(11, 12);
			this->label19->TabIndex = 48;
			this->label19->Text = L"%";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(240, 282);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(11, 12);
			this->label20->TabIndex = 47;
			this->label20->Text = L"%";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(240, 258);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(11, 12);
			this->label21->TabIndex = 46;
			this->label21->Text = L"%";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(240, 234);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(11, 12);
			this->label22->TabIndex = 45;
			this->label22->Text = L"%";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(240, 210);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(11, 12);
			this->label23->TabIndex = 44;
			this->label23->Text = L"%";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(145, 209);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(11, 12);
			this->label24->TabIndex = 50;
			this->label24->Text = L"0";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(145, 234);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(11, 12);
			this->label25->TabIndex = 51;
			this->label25->Text = L"0";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(145, 258);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(11, 12);
			this->label26->TabIndex = 52;
			this->label26->Text = L"0";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(145, 281);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(11, 12);
			this->label27->TabIndex = 53;
			this->label27->Text = L"0";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(145, 304);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(11, 12);
			this->label28->TabIndex = 54;
			this->label28->Text = L"0";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(145, 331);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(11, 12);
			this->label29->TabIndex = 55;
			this->label29->Text = L"0";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(257, 332);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(11, 12);
			this->label30->TabIndex = 61;
			this->label30->Text = L"0";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(257, 305);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(11, 12);
			this->label31->TabIndex = 60;
			this->label31->Text = L"0";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(257, 282);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(11, 12);
			this->label32->TabIndex = 59;
			this->label32->Text = L"0";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(257, 259);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(11, 12);
			this->label33->TabIndex = 58;
			this->label33->Text = L"0";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(257, 235);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(11, 12);
			this->label34->TabIndex = 57;
			this->label34->Text = L"0";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(257, 210);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(11, 12);
			this->label35->TabIndex = 56;
			this->label35->Text = L"0";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(12, 361);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(77, 12);
			this->label36->TabIndex = 62;
			this->label36->Text = L"单位共缴纳：";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(148, 361);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(77, 12);
			this->label37->TabIndex = 63;
			this->label37->Text = L"个人共缴纳：";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(85, 361);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(11, 12);
			this->label38->TabIndex = 64;
			this->label38->Text = L"0";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(222, 361);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(11, 12);
			this->label39->TabIndex = 65;
			this->label39->Text = L"0";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(191, 5);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 66;
			this->button4->Text = L"帮助";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &UI::button4_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(49, 63);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(35, 16);
			this->radioButton1->TabIndex = 67;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"新";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &UI::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(82, 63);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(35, 16);
			this->radioButton2->TabIndex = 68;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"旧";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &UI::radioButton2_CheckedChanged);
			// 
			// UI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(293, 384);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label39);
			this->Controls->Add(this->label38);
			this->Controls->Add(this->label37);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label34);
			this->Controls->Add(this->label35);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->textBox12);
			this->Controls->Add(this->textBox13);
			this->Controls->Add(this->textBox14);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->textBox16);
			this->Controls->Add(this->textBox17);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->checkBox6);
			this->Controls->Add(this->checkBox5);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"UI";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"工资计算器 v1.0";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		int selectedIndex = this->comboBox1->SelectedIndex;
		m_pCurWelfare = WelfareManager::Instance()->getWelfare(selectedIndex);
		
		this->label7->Text = String::Format("[{0},{1}]", m_pCurWelfare->SIMin, m_pCurWelfare->SIMax);
		this->label8->Text = String::Format("[{0},{1}]", m_pCurWelfare->AFMin, m_pCurWelfare->AFMax);

		this->textBox6->Text = Convert::ToString(m_pCurWelfare->Items[WIT_MEDICAL]->Company * 100);
		this->textBox7->Text = Convert::ToString(m_pCurWelfare->Items[WIT_RETIRE]->Company * 100);
		this->textBox8->Text = Convert::ToString(m_pCurWelfare->Items[WIT_FIRE]->Company * 100);
		this->textBox9->Text = Convert::ToString(m_pCurWelfare->Items[WIT_HURT]->Company * 100);
		this->textBox10->Text = Convert::ToString(m_pCurWelfare->Items[WIT_BIRTH]->Company * 100);
		this->textBox11->Text = Convert::ToString(m_pCurWelfare->Items[WIT_FUND]->Company * 100);

		this->textBox17->Text = Convert::ToString(m_pCurWelfare->Items[WIT_MEDICAL]->Personal * 100);
		this->textBox16->Text = Convert::ToString(m_pCurWelfare->Items[WIT_RETIRE]->Personal * 100);
		this->textBox15->Text = Convert::ToString(m_pCurWelfare->Items[WIT_FIRE]->Personal * 100);
		this->textBox14->Text = Convert::ToString(m_pCurWelfare->Items[WIT_HURT]->Personal * 100);
		this->textBox13->Text = Convert::ToString(m_pCurWelfare->Items[WIT_BIRTH]->Personal * 100);
		this->textBox12->Text = Convert::ToString(m_pCurWelfare->Items[WIT_FUND]->Personal * 100);
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		float f = Convert::ToSingle(this->textBox1->Text);

		Salary s;
		s.Pre = String::IsNullOrEmpty(this->textBox1->Text) ? 0.0f : Convert::ToSingle(this->textBox1->Text);

		Deduct d;
		if (0 < this->comboBox1->SelectedIndex)
		{
			calDeduct(d);
			s.Det = d.Private;
		}
		
		Calculator::Pre2Suf(s, m_nTaxType);
		this->textBox2->Text = Convert::ToString(s.Tax);
		this->textBox3->Text = Convert::ToString(s.Suf);

		if (0 < this->comboBox1->SelectedIndex)
		{
			DeductExt(d);
		}
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		 Salary s;
		 s.Tax = String::IsNullOrEmpty(this->textBox2->Text) ? 0.0f : Convert::ToSingle(this->textBox2->Text);

		 Deduct d;
		 if (0 < this->comboBox1->SelectedIndex)
		 {
			 calDeduct(d);
			 s.Det = d.Private;
		 }

		 Calculator::Tax2Two(s, m_nTaxType);
		 this->textBox1->Text = s.Pre.ToString();
		 this->textBox3->Text = s.Suf.ToString();

		 if (0 < this->comboBox1->SelectedIndex)
		 {
			 DeductExt(d);
		 }
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		 Salary s;
		 s.Suf = String::IsNullOrEmpty(this->textBox3->Text) ? 0.0f : Convert::ToSingle(this->textBox3->Text);

		 Deduct d;
		 if (0 < this->comboBox1->SelectedIndex)
		 {
			 calDeduct(d);
			 s.Det = d.Private;
		 }

		 Calculator::Suf2Pre(s, m_nTaxType);
		 this->textBox1->Text = s.Pre.ToString();
		 this->textBox2->Text = s.Tax.ToString();

		 if (0 < this->comboBox1->SelectedIndex)
		 {
			 DeductExt(d);
		 }
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		MessageBoxA(0, "1、选择城市\n2、填入社保和公积金基数\n3、修改具体参数\n4、点击计算", "帮助", 0);
	}

	private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		m_nTaxType = 2011;
	}

	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		m_nTaxType = 2007;
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_RETIRE);
	}

	private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_MEDICAL);
	}

	private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_FIRE);
	}

	private: System::Void checkBox4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_HURT);;
	}

	private: System::Void checkBox5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_BIRTH);
	}

	private: System::Void checkBox6_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		WelfareItemAllow(WIT_FUND);
	}
};
}
