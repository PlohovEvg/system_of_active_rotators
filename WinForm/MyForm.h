#pragma once
#include "Functions.h"
#include <stdlib.h>
#include <ctime>
#include <string>

Ur* Set_Gamma(int _n)
{
	Ur *g = new Ur[_n];

	srand(time(NULL));

	double m = (double)((rand() % 91 + 1010) / 1000.0);
	for (int i = 0; i < _n; i++)                   //Задаем γ для каждого уравнения системы
	{
		g[i].gamma = m;

		m = (double)((rand() % 91 + 1010) / 1000.0);

	}
	return g;
}


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
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int n;
		Ur *f;	
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//			
			n = Convert::ToInt32(n_Text3->Text);
			f = new Ur[n];			
			f = Set_Gamma(n);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  Alpha_Text;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  g_Text;
	private: System::Windows::Forms::PictureBox^  pictureBox1;










	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::TextBox^  b_Text3;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  h_Text3;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  n_Text3;
	private: System::Windows::Forms::TabPage^  tabPage2;	

	private: ZedGraph::ZedGraphControl^  zedGraphControl2;
		

	private:























	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  E0Star_Text;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  E0_Text;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  T01_text;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  T02_text;


	private: System::Windows::Forms::TabPage^  tabPage3;
	private: ZedGraph::ZedGraphControl^  zedGraphControl4;
	private: ZedGraph::ZedGraphControl^  zedGraphControl3;
	private: System::Windows::Forms::DataGridView^  dataGridView1;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: ZedGraph::ZedGraphControl^  zedGraphControl1;
	private: System::Windows::Forms::TextBox^  Y1_Text2;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  Y2_Text2;
	private: System::Windows::Forms::TextBox^  X2_Text2;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  X1_Text2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::DataGridView^  dataGridView2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
private: System::Windows::Forms::CheckBox^  checkBox1;




	protected:




































	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Y1_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->Y2_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->X2_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->X1_Text2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->T02_text = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->T01_text = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->E0Star_Text = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->E0_Text = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Alpha_Text = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->g_Text = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->b_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->h_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->n_Text3 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->zedGraphControl4 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl3 = (gcnew ZedGraph::ZedGraphControl());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(3, 3);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1456, 599);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->checkBox1);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->Y1_Text2);
			this->tabPage1->Controls->Add(this->label9);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->Y2_Text2);
			this->tabPage1->Controls->Add(this->X2_Text2);
			this->tabPage1->Controls->Add(this->label14);
			this->tabPage1->Controls->Add(this->label15);
			this->tabPage1->Controls->Add(this->X1_Text2);
			this->tabPage1->Controls->Add(this->button4);
			this->tabPage1->Controls->Add(this->button5);
			this->tabPage1->Controls->Add(this->zedGraphControl1);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->T02_text);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->T01_text);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->E0Star_Text);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->E0_Text);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->Alpha_Text);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->g_Text);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Controls->Add(this->textBox2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->button7);
			this->tabPage1->Controls->Add(this->label24);
			this->tabPage1->Controls->Add(this->b_Text3);
			this->tabPage1->Controls->Add(this->label23);
			this->tabPage1->Controls->Add(this->h_Text3);
			this->tabPage1->Controls->Add(this->label21);
			this->tabPage1->Controls->Add(this->n_Text3);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1448, 573);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Ввод данных";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(588, 282);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(186, 28);
			this->checkBox1->TabIndex = 132;
			this->checkBox1->Text = L"Изменять gamma";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(599, 184);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(184, 60);
			this->button1->TabIndex = 131;
			this->button1->Text = L"Вернуть масштаб по умолчанию";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// Y1_Text2
			// 
			this->Y1_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Y1_Text2->Location = System::Drawing::Point(588, 105);
			this->Y1_Text2->Name = L"Y1_Text2";
			this->Y1_Text2->Size = System::Drawing::Size(99, 29);
			this->Y1_Text2->TabIndex = 130;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(525, 143);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(62, 24);
			this->label9->TabIndex = 129;
			this->label9->Text = L" Ф2 = ";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(524, 108);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(62, 24);
			this->label10->TabIndex = 128;
			this->label10->Text = L" Ф1 = ";
			// 
			// Y2_Text2
			// 
			this->Y2_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Y2_Text2->Location = System::Drawing::Point(589, 140);
			this->Y2_Text2->Name = L"Y2_Text2";
			this->Y2_Text2->Size = System::Drawing::Size(98, 29);
			this->Y2_Text2->TabIndex = 127;
			// 
			// X2_Text2
			// 
			this->X2_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->X2_Text2->Location = System::Drawing::Point(588, 70);
			this->X2_Text2->Name = L"X2_Text2";
			this->X2_Text2->Size = System::Drawing::Size(99, 29);
			this->X2_Text2->TabIndex = 126;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(522, 73);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(58, 24);
			this->label14->TabIndex = 125;
			this->label14->Text = L" Т2 = ";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label15->Location = System::Drawing::Point(522, 38);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(58, 24);
			this->label15->TabIndex = 124;
			this->label15->Text = L" Т1 = ";
			// 
			// X1_Text2
			// 
			this->X1_Text2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->X1_Text2->Location = System::Drawing::Point(589, 35);
			this->X1_Text2->Name = L"X1_Text2";
			this->X1_Text2->Size = System::Drawing::Size(99, 29);
			this->X1_Text2->TabIndex = 123;
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(693, 105);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(184, 60);
			this->button4->TabIndex = 122;
			this->button4->Text = L"Изменить масштаб от Ф1 до Ф2";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(693, 39);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(184, 60);
			this->button5->TabIndex = 121;
			this->button5->Text = L"Изменить масштаб от T1 до T2";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->IsShowPointValues = false;
			this->zedGraphControl1->Location = System::Drawing::Point(883, 3);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->PointValueFormat = L"G";
			this->zedGraphControl1->Size = System::Drawing::Size(565, 567);
			this->zedGraphControl1->TabIndex = 120;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(108, 408);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(68, 24);
			this->label8->TabIndex = 119;
			this->label8->Text = L" T02 = ";
			// 
			// T02_text
			// 
			this->T02_text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T02_text->Location = System::Drawing::Point(181, 405);
			this->T02_text->Name = L"T02_text";
			this->T02_text->Size = System::Drawing::Size(100, 29);
			this->T02_text->TabIndex = 118;
			this->T02_text->Text = L"900";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(108, 373);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 24);
			this->label5->TabIndex = 117;
			this->label5->Text = L" T01 = ";
			// 
			// T01_text
			// 
			this->T01_text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T01_text->Location = System::Drawing::Point(181, 370);
			this->T01_text->Name = L"T01_text";
			this->T01_text->Size = System::Drawing::Size(100, 29);
			this->T01_text->TabIndex = 116;
			this->T01_text->Text = L"500";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(311, 300);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(69, 24);
			this->label7->TabIndex = 115;
			this->label7->Text = L"E ̃_0 = ";
			// 
			// E0Star_Text
			// 
			this->E0Star_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0Star_Text->Location = System::Drawing::Point(383, 298);
			this->E0Star_Text->Name = L"E0Star_Text";
			this->E0Star_Text->Size = System::Drawing::Size(100, 29);
			this->E0Star_Text->TabIndex = 114;
			this->E0Star_Text->Text = L"0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(318, 266);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(59, 24);
			this->label6->TabIndex = 113;
			this->label6->Text = L" E0 = ";
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
			// 
			// E0_Text
			// 
			this->E0_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0_Text->Location = System::Drawing::Point(383, 263);
			this->E0_Text->Name = L"E0_Text";
			this->E0_Text->Size = System::Drawing::Size(100, 29);
			this->E0_Text->TabIndex = 112;
			this->E0_Text->Text = L"0";
			this->E0_Text->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged_1);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(128, 514);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(47, 24);
			this->label3->TabIndex = 108;
			this->label3->Text = L" α = ";
			// 
			// Alpha_Text
			// 
			this->Alpha_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Alpha_Text->Location = System::Drawing::Point(181, 511);
			this->Alpha_Text->Name = L"Alpha_Text";
			this->Alpha_Text->Size = System::Drawing::Size(100, 29);
			this->Alpha_Text->TabIndex = 107;
			this->Alpha_Text->Text = L"3";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(128, 479);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 24);
			this->label2->TabIndex = 106;
			this->label2->Text = L" g = ";
			// 
			// g_Text
			// 
			this->g_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g_Text->Location = System::Drawing::Point(181, 476);
			this->g_Text->Name = L"g_Text";
			this->g_Text->Size = System::Drawing::Size(100, 29);
			this->g_Text->TabIndex = 105;
			this->g_Text->Text = L"1,2";
			this->g_Text->TextChanged += gcnew System::EventHandler(this, &MyForm::g_Text_TextChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(10, 6);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(507, 222);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 104;
			this->pictureBox1->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(521, 338);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(356, 226);
			this->textBox2->TabIndex = 93;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(47, 444);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 24);
			this->label1->TabIndex = 92;
			this->label1->Text = L" Число шагов";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(181, 441);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 29);
			this->textBox1->TabIndex = 91;
			this->textBox1->Text = L"200000";
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->Location = System::Drawing::Point(315, 370);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(184, 64);
			this->button7->TabIndex = 90;
			this->button7->Text = L"СТАРТ";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(128, 338);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(48, 24);
			this->label24->TabIndex = 89;
			this->label24->Text = L" T = ";
			// 
			// b_Text3
			// 
			this->b_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->b_Text3->Location = System::Drawing::Point(181, 335);
			this->b_Text3->Name = L"b_Text3";
			this->b_Text3->Size = System::Drawing::Size(100, 29);
			this->b_Text3->TabIndex = 88;
			this->b_Text3->Text = L"10000";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(128, 303);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(47, 24);
			this->label23->TabIndex = 87;
			this->label23->Text = L" h = ";
			// 
			// h_Text3
			// 
			this->h_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->h_Text3->Location = System::Drawing::Point(181, 300);
			this->h_Text3->Name = L"h_Text3";
			this->h_Text3->Size = System::Drawing::Size(100, 29);
			this->h_Text3->TabIndex = 86;
			this->h_Text3->Text = L"0,005";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(6, 268);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(169, 24);
			this->label21->TabIndex = 85;
			this->label21->Text = L" Число уравнений";
			// 
			// n_Text3
			// 
			this->n_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->n_Text3->Location = System::Drawing::Point(181, 265);
			this->n_Text3->Name = L"n_Text3";
			this->n_Text3->Size = System::Drawing::Size(100, 29);
			this->n_Text3->TabIndex = 84;
			this->n_Text3->Text = L"100";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->dataGridView1);
			this->tabPage2->Controls->Add(this->zedGraphControl2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1448, 573);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Графики 1";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->dataGridView1->Location = System::Drawing::Point(997, 6);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(445, 561);
			this->dataGridView1->TabIndex = 115;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"I";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Width = 200;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Omega(i)";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->Width = 200;
			// 
			// zedGraphControl2
			// 
			this->zedGraphControl2->ImeMode = System::Windows::Forms::ImeMode::On;
			this->zedGraphControl2->IsShowPointValues = false;
			this->zedGraphControl2->Location = System::Drawing::Point(6, 6);
			this->zedGraphControl2->Name = L"zedGraphControl2";
			this->zedGraphControl2->PointValueFormat = L"G";
			this->zedGraphControl2->Size = System::Drawing::Size(985, 564);
			this->zedGraphControl2->TabIndex = 114;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->dataGridView2);
			this->tabPage3->Controls->Add(this->zedGraphControl4);
			this->tabPage3->Controls->Add(this->zedGraphControl3);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1448, 573);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Графики 2";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn3,
					this->dataGridViewTextBoxColumn4
			});
			this->dataGridView2->Location = System::Drawing::Point(997, 0);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(445, 561);
			this->dataGridView2->TabIndex = 116;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"t";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->Width = 200;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"E(t)";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->Width = 200;
			// 
			// zedGraphControl4
			// 
			this->zedGraphControl4->IsShowPointValues = false;
			this->zedGraphControl4->Location = System::Drawing::Point(6, 3);
			this->zedGraphControl4->Name = L"zedGraphControl4";
			this->zedGraphControl4->PointValueFormat = L"G";
			this->zedGraphControl4->Size = System::Drawing::Size(986, 285);
			this->zedGraphControl4->TabIndex = 1;
			// 
			// zedGraphControl3
			// 
			this->zedGraphControl3->IsShowPointValues = false;
			this->zedGraphControl3->Location = System::Drawing::Point(6, 277);
			this->zedGraphControl3->Name = L"zedGraphControl3";
			this->zedGraphControl3->PointValueFormat = L"G";
			this->zedGraphControl3->Size = System::Drawing::Size(988, 300);
			this->zedGraphControl3->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1461, 601);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion									
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		GraphPane^ panel1 = zedGraphControl1->GraphPane;
		GraphPane^ panel2 = zedGraphControl2->GraphPane;
		GraphPane^ panel3 = zedGraphControl3->GraphPane;
		GraphPane^ panel4 = zedGraphControl4->GraphPane;

		panel1->CurveList->Clear();
		panel2->CurveList->Clear();
		panel3->CurveList->Clear();
		panel4->CurveList->Clear();

		panel1->Title = "Графики Ф(t) для первых пяти ротаторов";
		panel1->XAxis->Title = "t";
		panel1->YAxis->Title = "Ф";

		panel2->Title = "График Omega(i)";
		panel2->XAxis->Title = "I";
		panel2->YAxis->Title = "Omega";

		panel3->Title = "График числа спайков";
		panel3->XAxis->Title = "t";
		panel3->YAxis->Title = "";

		panel4->Title = "График E(t)";
		panel4->XAxis->Title = "t";
		panel4->YAxis->Title = "E(t)";

		PointPairList^ f1_list = gcnew PointPairList();
		PointPairList^ f2_list = gcnew PointPairList();
		PointPairList^ f3_list = gcnew PointPairList();
		PointPairList^ f4_list = gcnew PointPairList();
		PointPairList^ f5_list = gcnew PointPairList();
		PointPairList^ g_list = gcnew PointPairList();
		PointPairList^ E_list = gcnew PointPairList();		
		PointPairList^ Spaik_list = gcnew PointPairList();
		
		double h = Convert::ToDouble(h_Text3->Text);          //Шаг
		int p = Convert::ToInt32(textBox1->Text);             //Число итераций
		double b = Convert::ToDouble(b_Text3->Text);          //Максимальное время, до которого будет подсчет
		double T01 = Convert::ToDouble(T01_text->Text);         //Начальное время, от которого будет считаться частота
		double T02 = Convert::ToDouble(T02_text->Text);         //Начальное время, от которого будут рисоваться график E(t) и график спайков
		double g = Convert::ToDouble(g_Text->Text);           //Коэффициент связи
		double alpha = Convert::ToDouble(Alpha_Text->Text);   //Число α
		double E0 = Convert::ToDouble(E0_Text->Text);         //Начальное условие для E
		double E0Star = Convert::ToDouble(E0Star_Text->Text); //Начальное условие для E'
		int *k;             //Число спайков каждого отдельного ротатора  
		int it = 0;            //Индекс строк в таблице
		double t = 0.0;        //Текущее время
		double ts = 0.0;       //Время последнего спайка
		double Et;
		int ind = 0;
		double oldE0;
		double *Fi0;				
		int i;
		double *v, *vplus1;		
		double *Omega;						
		string str = "";
		char buffer[100];
		bool flag1;
		
		v = new double[n];
		vplus1 = new double[n];		
		Omega = new double[n];
		Fi0 = new double[n];
		k = new int[n];

		if (checkBox1->Checked == true)
		{
			f = Set_Gamma(n);
		}		

		double tmin_limit = t - 0.05;

		for (i = 0; i < n; i++)                //Начальные условия для каждого из φ равны нулю
		{
			v[i] = vplus1[i] = 0.0;			                      
			k[i] = 0;                          //Изначальное число спайков равно нулю
		}
		

		f1_list->Add(t, v[0]);
		f2_list->Add(t, v[1]);
		f3_list->Add(t, v[2]);
		f4_list->Add(t, v[3]);
		f5_list->Add(t, v[4]);

		dataGridView1->Rows->Clear();

		for (i = 1; ((i < p) && (t <= b)); i++)         //Основной цикл: Вычисление ф методом Рунге-Кутта 4-го порядка
		{
			for (int j = 0; j < n; j++)
			{
				vplus1[j] = RK4(t, ts, v[j], h, f[j], g, E0, E0Star, alpha);
				v[j] = vplus1[j];

				if (v[j] >= 2 * M_PI)       //В моемент импульса j-го ротатора
				{
					k[j]++;                 //Увеличение числа спайков на 1
				    oldE0 = E0;
					E0 = E(t, ts, E0, E0Star, alpha);   //Пересчет начальных условий
					E0Star = dEdt(t, ts, oldE0, E0Star, alpha);  
					E0Star += (alpha*alpha) / n; 
					ts = t;  //Изменение времени последнего спайка
					v[j] = 0.0;			 //Обнуление значения ф
					if (ts >= T02)    //Отбражение нового спайка на графике
					{
						Spaik_list->Clear();
						Spaik_list->Add(ts, 0.0);
						Spaik_list->Add(ts, 1.0);

						LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

						zedGraphControl3->AxisChange();
						zedGraphControl3->Invalidate();
					}
				}
			}
			t = xInc(t, h);
			f1_list->Add(t, v[0]);
			f2_list->Add(t, v[1]);
			f3_list->Add(t, v[2]);
			f4_list->Add(t, v[3]);
			f5_list->Add(t, v[4]);

			if (t >= T02) //Заполнение таблицы точек для вывода графика E(t) 
			{
				Et = E(t, ts, E0, E0Star, alpha);
				E_list->Add(t, Et);

				dataGridView2->Rows->Add();
				dataGridView2->Rows[ind]->Cells[0]->Value = t;  //Заполнение таблицы E(t)
				dataGridView2->Rows[ind]->Cells[1]->Value = Et;
				ind++;
			}

			if ((t == T01)||(abs(t - T01) < h*0.5)||(T01 == 0.0))  //Запоминание начальных значений ф для частоты Omega
			{
				flag1 = true;

			for (int l = 0; l < n; l++)
				{
					Fi0[l] = v[l];   
				}
			}
		}
		
		if (flag1 == true)
		{
			for (i = 0; i < n; i++)         //Вычисление частоты для всех ротаторов, заполнение таблицы
			{
				Omega[i] = (k[i] * 2 * M_PI + v[i] - Fi0[i]) / (t - T01);
				g_list->Add(i, Omega[i]);

				dataGridView1->Rows->Add();
				dataGridView1->Rows[i]->Cells[0]->Value = i;
				dataGridView1->Rows[i]->Cells[1]->Value = Omega[i];
			}
		}

		str += "Gamma1 =";                          //Вывод значений γ для первых пяти ротатороы на экран
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

		double tmax_limit = t + 0.05;

		LineItem ^Curve1 = panel1->AddCurve("Ф1(t)", f1_list, Color::Red, SymbolType::None);
		LineItem ^Curve2 = panel1->AddCurve("Ф2(t)", f2_list, Color::Blue, SymbolType::None);
		LineItem ^Curve3 = panel1->AddCurve("Ф3(t)", f3_list, Color::Green, SymbolType::None);
		LineItem ^Curve4 = panel1->AddCurve("Ф4(t)", f4_list, Color::Brown, SymbolType::None);
		LineItem ^Curve5 = panel1->AddCurve("Ф5(t)", f5_list, Color::Black, SymbolType::None);

		LineItem ^Curve6 = panel2->AddCurve("Omega(i)", g_list, Color::Red, SymbolType::Circle);

		LineItem ^Curve7 = panel4->AddCurve("E(t)", E_list, Color::Red, SymbolType::None);		

		Curve6->Line->IsVisible = false;
		Curve6->Symbol->Fill->Color = Color::Red;
		Curve6->Symbol->Fill->Type = FillType::Solid;
		Curve6->Symbol->Size = 6;
				
		panel1->XAxis->Min = tmin_limit;
		panel1->XAxis->Max = tmax_limit;

		panel2->XAxis->Min = -0.05;
		panel2->XAxis->Max = n + 0.05;

		panel3->XAxis->Max = t + 0.2;
		panel3->XAxis->Min = T02 - 0.2;

		panel4->XAxis->Max = t + 0.2;
		panel4->XAxis->Min = T02 - 0.2;	

		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();
		zedGraphControl2->AxisChange();
		zedGraphControl2->Invalidate();
		zedGraphControl4->AxisChange();
		zedGraphControl4->Invalidate();
		
		delete[]v;
		delete[]vplus1;		
		delete[]Omega;
		delete[]Fi0;
		delete[]k;
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
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void g_Text_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox3_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	GraphPane^ panel = zedGraphControl1->GraphPane;

	panel->XAxis->MinAuto = true;
	panel->XAxis->MaxAuto = true;
	panel->YAxis->MinAuto = true;
	panel->YAxis->MaxAuto = true;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
}
};
}
