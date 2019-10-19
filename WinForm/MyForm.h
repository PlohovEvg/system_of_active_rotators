#pragma once
#include "Functions.h"
#include <stdlib.h>
#include <ctime>
#include <string>

namespace WinForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;
	using namespace std;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ZedGraph::ZedGraphControl^  zedGraphControl1;
	protected:


	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  n_Text3;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  h_Text3;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  b_Text3;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  Y2_Text2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  Y1_Text2;
	private: System::Windows::Forms::TextBox^  X2_Text2;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  X1_Text2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->n_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->h_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->b_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->Y2_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->Y1_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->X2_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->X1_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->IsShowPointValues = false;
			this->zedGraphControl1->Location = System::Drawing::Point(632, 12);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->PointValueFormat = L"G";
			this->zedGraphControl1->Size = System::Drawing::Size(817, 577);
			this->zedGraphControl1->TabIndex = 0;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(12, 282);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(169, 24);
			this->label21->TabIndex = 50;
			this->label21->Text = L" ����� ���������";
			// 
			// n_Text3
			// 
			this->n_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->n_Text3->Location = System::Drawing::Point(187, 279);
			this->n_Text3->Name = L"n_Text3";
			this->n_Text3->Size = System::Drawing::Size(100, 29);
			this->n_Text3->TabIndex = 49;
			this->n_Text3->Text = L"100";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(134, 317);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(47, 24);
			this->label23->TabIndex = 56;
			this->label23->Text = L" h = ";
			// 
			// h_Text3
			// 
			this->h_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->h_Text3->Location = System::Drawing::Point(187, 314);
			this->h_Text3->Name = L"h_Text3";
			this->h_Text3->Size = System::Drawing::Size(100, 29);
			this->h_Text3->TabIndex = 55;
			this->h_Text3->Text = L"0,0001";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(134, 352);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(47, 24);
			this->label24->TabIndex = 58;
			this->label24->Text = L" b = ";
			// 
			// b_Text3
			// 
			this->b_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->b_Text3->Location = System::Drawing::Point(187, 349);
			this->b_Text3->Name = L"b_Text3";
			this->b_Text3->Size = System::Drawing::Size(100, 29);
			this->b_Text3->TabIndex = 57;
			this->b_Text3->Text = L"1";
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->Location = System::Drawing::Point(352, 279);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(184, 64);
			this->button7->TabIndex = 64;
			this->button7->Text = L"�����";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(53, 387);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 24);
			this->label1->TabIndex = 66;
			this->label1->Text = L" ����� �����";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(187, 384);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 29);
			this->textBox1->TabIndex = 65;
			this->textBox1->Text = L"10000";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(12, 12);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(614, 254);
			this->textBox2->TabIndex = 67;
			// 
			// Y2_Text2
			// 
			this->Y2_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Y2_Text2->Location = System::Drawing::Point(187, 489);
			this->Y2_Text2->Name = L"Y2_Text2";
			this->Y2_Text2->Size = System::Drawing::Size(99, 29);
			this->Y2_Text2->TabIndex = 77;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(124, 527);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(58, 24);
			this->label4->TabIndex = 76;
			this->label4->Text = L" Y2 = ";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(123, 492);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(58, 24);
			this->label11->TabIndex = 75;
			this->label11->Text = L" Y1 = ";
			// 
			// Y1_Text2
			// 
			this->Y1_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Y1_Text2->Location = System::Drawing::Point(188, 524);
			this->Y1_Text2->Name = L"Y1_Text2";
			this->Y1_Text2->Size = System::Drawing::Size(98, 29);
			this->Y1_Text2->TabIndex = 74;
			// 
			// X2_Text2
			// 
			this->X2_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->X2_Text2->Location = System::Drawing::Point(187, 454);
			this->X2_Text2->Name = L"X2_Text2";
			this->X2_Text2->Size = System::Drawing::Size(99, 29);
			this->X2_Text2->TabIndex = 73;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(121, 457);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(60, 24);
			this->label12->TabIndex = 72;
			this->label12->Text = L" X2 = ";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label13->Location = System::Drawing::Point(121, 422);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(60, 24);
			this->label13->TabIndex = 71;
			this->label13->Text = L" X1 = ";
			// 
			// X1_Text2
			// 
			this->X1_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->X1_Text2->Location = System::Drawing::Point(188, 419);
			this->X1_Text2->Name = L"X1_Text2";
			this->X1_Text2->Size = System::Drawing::Size(99, 29);
			this->X1_Text2->TabIndex = 70;
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(352, 415);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(184, 60);
			this->button4->TabIndex = 69;
			this->button4->Text = L"�������� ������� �� Y1 �� Y2";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(352, 349);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(184, 60);
			this->button5->TabIndex = 68;
			this->button5->Text = L"�������� ������� �� X1 �� X2";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1461, 601);
			this->Controls->Add(this->Y2_Text2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->Y1_Text2);
			this->Controls->Add(this->X2_Text2);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->X1_Text2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->b_Text3);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->h_Text3);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->n_Text3);
			this->Controls->Add(this->zedGraphControl1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		GraphPane^ panel = zedGraphControl1->GraphPane;

		panel->CurveList->Clear();

		panel->Title = "������� �(�) ��� ������ ���� ���������";
		panel->XAxis->Title = "X";
		panel->YAxis->Title = "�";

		PointPairList^ f1_list = gcnew PointPairList();
		PointPairList^ f2_list = gcnew PointPairList();
		PointPairList^ f3_list = gcnew PointPairList();
		PointPairList^ f4_list = gcnew PointPairList();
		PointPairList^ f5_list = gcnew PointPairList();

		int n = Convert::ToInt32(n_Text3->Text);
		double h = Convert::ToDouble(h_Text3->Text);
		int k = Convert::ToInt32(textBox1->Text);
		double b = Convert::ToDouble(b_Text3->Text);
		double x = 0.0;
		Ur *f = new Ur[n];
		int i;
		double *v, *vplus1;		
		double m = (double)(rand() % 7 + 1);
		double p = (double)(rand() % 10 + 2);
		int zn = rand() % 2;
		string str = "";
		char buffer[10];

		if (zn == 1)
		{
			m = m*-1.0;
		}

		srand(time(NULL));

		v = new double[n];
		vplus1 = new double[n];

		for (i = 0; i < n; i++)
		{
			f[i].gamma = m/p;

			m = (double)(rand() % 7 + 1);
			p = (double)(rand() % 10 + 2);
			zn = rand() % 2;

			if (zn == 1)
			{
				m = m*-1.0;
			}
		}

		str += "Gamma1 =";
		sprintf_s(buffer, "%lf", f[0].gamma);
		str += buffer;
		str += "\r\n";
		str += "Gamma2 =";
		sprintf_s(buffer, "%lf", f[1].gamma);
		str += buffer;
		str += "\r\n";
		str += "Gamma3 =";
		sprintf_s(buffer, "%lf", f[2].gamma);
		str += buffer;
		str += "\r\n";
		str += "Gamma4 =";
		sprintf_s(buffer, "%lf", f[3].gamma);
		str += buffer;
		str += "\r\n";
		str += "Gamma5 =";
		sprintf_s(buffer, "%lf", f[4].gamma);
		str += buffer;
		str += "\r\n";
		textBox2->Text = gcnew String(str.c_str());

		double xmin_limit = x - 0.05;

		for (i = 0; i < n; i++)
		{
			v[i] = vplus1[i] = 0.0;
		}

		f1_list->Add(x, v[0]);
		f2_list->Add(x, v[1]);
		f3_list->Add(x, v[2]);
		f4_list->Add(x, v[3]);
		f5_list->Add(x, v[4]);

		for (i = 1; ((i < k) && (x <= b)); i++)
		{
			for (int j = 0; j < n; j++)
			{
				vplus1[j] = RK4(v[j], h, f[j]);
			}
			x = xInc(x, h);
			f1_list->Add(x, vplus1[0]);
			f2_list->Add(x, vplus1[1]);
			f3_list->Add(x, vplus1[2]);
			f4_list->Add(x, vplus1[3]);
			f5_list->Add(x, vplus1[4]);
		}

		double xmax_limit = x + 0.05;

		LineItem Curve1 = panel->AddCurve("�1(�)", f1_list, Color::Red, SymbolType::None);
		LineItem Curve2 = panel->AddCurve("�2(�)", f2_list, Color::Blue, SymbolType::None);
		LineItem Curve3 = panel->AddCurve("�3(�)", f3_list, Color::Green, SymbolType::None);
		LineItem Curve4 = panel->AddCurve("�4(�)", f4_list, Color::Brown, SymbolType::None);
		LineItem Curve5 = panel->AddCurve("�5(�)", f5_list, Color::Black, SymbolType::None);

		panel->XAxis->Min = xmin_limit;
		panel->XAxis->Max = xmax_limit;

		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();
	}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
{
	GraphPane^ panel = zedGraphControl1->GraphPane;
	double X1 = Convert::ToDouble(X1_Text2->Text);
	double X2 = Convert::ToDouble(X2_Text2->Text);

	panel->XAxis->Min = X1;
	panel->XAxis->Max = X2;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	GraphPane^ panel = zedGraphControl1->GraphPane;
	double Y1 = Convert::ToDouble(Y1_Text2->Text);
	double Y2 = Convert::ToDouble(Y2_Text2->Text);

	panel->YAxis->Min = Y1;
	panel->YAxis->Max = Y2;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
}
};
}