#pragma once
#include <Windows.h>
#include "Calculating_functions.h"

namespace WinForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;
	using namespace ZedGraph;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: double *gamma;    //Параметры γⱼ
	public: double gamma1;    //Левая граница γ₁
	public: double gamma2;    //Правая граница γ₂
	public: bool AvgMaxMinAlreadyExists;
	public: vector<int*> *Clusters_vec;
	public: vector<double**> *Omega_vec;
	public: vector<double> *VO;
	public: vector<double> *VE;
	public: vector<double> *VT;
	public: cli::array<Color> ^Colors;
	public: String ^Str;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//									
			AvgMaxMinAlreadyExists = false;
			Clusters_vec = new vector<int*>;
			Omega_vec = new vector<double**>;
			VO = new vector<double>;
			VE = new vector<double>;
			VT = new vector<double>;
			Str = "";

			Colors = gcnew cli::array<Color>(50);
			random_device gen;
			mt19937 me(gen());
			uniform_int_distribution<> distr(0, 255);
			int rC, bC, gC;

			for (int i = 0; i < 50; i++)
			{
				rC = distr(me);
				bC = distr(me);
				gC = distr(me);
				Colors[i] = Color::FromArgb(rC, gC, bC);
			}

			zedGraphControl2->GraphPane->Title->Text = L"График средних частот Ωᵢ";
			zedGraphControl2->GraphPane->XAxis->Title->Text = L"j";
			zedGraphControl2->GraphPane->YAxis->Title->Text = L"Ωⱼ";
			zedGraphControl2->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl2->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl3->GraphPane->Title->Text = "График числа спайков";
			zedGraphControl3->GraphPane->XAxis->Title->Text = "t";
			zedGraphControl3->GraphPane->YAxis->Title->Text = "";
			zedGraphControl3->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl3->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl4->GraphPane->Title->Text = L"График внешнего поля E(t)";
			zedGraphControl4->GraphPane->XAxis->Title->Text = L"t";
			zedGraphControl4->GraphPane->YAxis->Title->Text = L"E(t)";
			zedGraphControl4->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl4->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl6->GraphPane->Title->Text = L"График зависимости средних частот Ωⱼ от параметра β";
			zedGraphControl6->GraphPane->XAxis->Title->Text = L"β";
			zedGraphControl6->GraphPane->YAxis->Title->Text = L"Ωⱼ";
			zedGraphControl6->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl6->GraphPane->XAxis->MajorGrid->IsVisible = true;
			zedGraphControl6->GraphPane->YAxis->Type = AxisType::Log;

			zedGraphControl1->GraphPane->Title->Text = L"График зависимости числа кластеров от параметра β";
			zedGraphControl1->GraphPane->XAxis->Title->Text = L"β";
			zedGraphControl1->GraphPane->YAxis->Title->Text = L"Кол-во кластеров";
			zedGraphControl1->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl1->GraphPane->XAxis->MajorGrid->IsVisible = true;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			delete Omega_vec;
			delete Clusters_vec;
			delete gamma;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar3;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::ProgressBar^  progressBar2;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TabPage^  tabPage6;
	private: ZedGraph::ZedGraphControl^  zedGraphControl1;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  GShag_Text;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  g2_Text;
	private: System::Windows::Forms::TextBox^  g1_Text;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label22;
	private: ZedGraph::ZedGraphControl^  zedGraphControl6;
	private: ZedGraph::ZedGraphControl^  zedGraphControl2;
	private: System::Windows::Forms::TabControl^  tabControl1;	
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


	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::TextBox^  Omega1_Text;
	private: System::Windows::Forms::Label^  Omega2;
	private: System::Windows::Forms::Label^  Omega1;
	private: System::Windows::Forms::TextBox^  Omega2_Text;
	private: System::Windows::Forms::Button^  Change_scale_Omega;
	private: System::Windows::Forms::Label^  label10;

	private: System::Windows::Forms::Label^  Gamma1;

	private: System::Windows::Forms::Label^  label9;



	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::DataGridView^  dataGridView4;


	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label30;
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->Gamma1 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
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
			this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
			this->Omega1_Text = (gcnew System::Windows::Forms::TextBox());
			this->Omega2 = (gcnew System::Windows::Forms::Label());
			this->Omega1 = (gcnew System::Windows::Forms::Label());
			this->Omega2_Text = (gcnew System::Windows::Forms::TextBox());
			this->Change_scale_Omega = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->zedGraphControl4 = (gcnew ZedGraph::ZedGraphControl());
			this->zedGraphControl3 = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->progressBar3 = (gcnew System::Windows::Forms::ProgressBar());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->g1_Text = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->g2_Text = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->GShag_Text = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->zedGraphControl6 = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker3 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->tabPage6->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Location = System::Drawing::Point(3, 3);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1570, 929);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->comboBox2);
			this->tabPage1->Controls->Add(this->comboBox1);
			this->tabPage1->Controls->Add(this->label18);
			this->tabPage1->Controls->Add(this->label17);
			this->tabPage1->Controls->Add(this->button6);
			this->tabPage1->Controls->Add(this->progressBar2);
			this->tabPage1->Controls->Add(this->label13);
			this->tabPage1->Controls->Add(this->textBox7);
			this->tabPage1->Controls->Add(this->label30);
			this->tabPage1->Controls->Add(this->label29);
			this->tabPage1->Controls->Add(this->label28);
			this->tabPage1->Controls->Add(this->label27);
			this->tabPage1->Controls->Add(this->label26);
			this->tabPage1->Controls->Add(this->label25);
			this->tabPage1->Controls->Add(this->dataGridView4);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->Gamma1);
			this->tabPage1->Controls->Add(this->label9);
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
			this->tabPage1->Size = System::Drawing::Size(1562, 903);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Ввод данных";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1,1", L"2,1", L"3,1", L"4,1", L"5,1", L"1,03" });
			this->comboBox2->Location = System::Drawing::Point(1100, 70);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(100, 32);
			this->comboBox2->TabIndex = 166;
			this->comboBox2->Text = L"1,1";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1", L"2", L"3", L"4", L"5", L"1,03" });
			this->comboBox1->Location = System::Drawing::Point(890, 70);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(100, 32);
			this->comboBox1->TabIndex = 165;
			this->comboBox1->Text = L"1";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(857, 321);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(212, 24);
			this->label18->TabIndex = 162;
			this->label18->Text = L"Идут вычисления... 0%";
			this->label18->Visible = false;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(831, 324);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(281, 24);
			this->label17->TabIndex = 164;
			this->label17->Text = L"Останавливаем вычисления...";
			this->label17->Visible = false;
			// 
			// button6
			// 
			this->button6->Enabled = false;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button6->Location = System::Drawing::Point(956, 201);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(184, 66);
			this->button6->TabIndex = 163;
			this->button6->Text = L"ОТМЕНА";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(668, 280);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(598, 31);
			this->progressBar2->TabIndex = 161;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(480, 530);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(58, 29);
			this->label13->TabIndex = 152;
			this->label13->Text = L" β = ";
			// 
			// textBox7
			// 
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox7->Location = System::Drawing::Point(544, 531);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 29);
			this->textBox7->TabIndex = 151;
			this->textBox7->Text = L"0,005";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(476, 607);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(775, 24);
			this->label30->TabIndex = 150;
			this->label30->Text = L"T₂ - начиная с этого момента времени будут отрисовываться графики E(t) и спайков";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(476, 567);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(704, 24);
			this->label29->TabIndex = 149;
			this->label29->Text = L"T₁ - φⱼ(T₁), j = 0,...,n - 1 будут использованы для вычисления средних частот Ω";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(15, 443);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(383, 24);
			this->label28->TabIndex = 148;
			this->label28->Text = L"T - максимальное время интегрирования";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(15, 410);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(224, 24);
			this->label27->TabIndex = 147;
			this->label27->Text = L"h - шаг интегрирования";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label26->Location = System::Drawing::Point(43, 243);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(266, 24);
			this->label26->TabIndex = 146;
			this->label26->Text = L"Параметры интегрирования";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(419, 243);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(195, 24);
			this->label25->TabIndex = 145;
			this->label25->Text = L"Параметры системы";
			// 
			// dataGridView4
			// 
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView4->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Column3,
					this->Column4
			});
			this->dataGridView4->Location = System::Drawing::Point(1302, 10);
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->Size = System::Drawing::Size(244, 711);
			this->dataGridView4->TabIndex = 144;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"j";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"γⱼ";
			this->Column4->Name = L"Column4";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(1085, 119);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(165, 55);
			this->button1->TabIndex = 141;
			this->button1->Text = L"Сгенерировать набор";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(1030, 69);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(64, 29);
			this->label10->TabIndex = 137;
			this->label10->Text = L" γ₂ = ";
			// 
			// Gamma1
			// 
			this->Gamma1->AutoSize = true;
			this->Gamma1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma1->Location = System::Drawing::Point(820, 69);
			this->Gamma1->Name = L"Gamma1";
			this->Gamma1->Size = System::Drawing::Size(64, 29);
			this->Gamma1->TabIndex = 135;
			this->Gamma1->Text = L" γ₁ = ";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(820, 10);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(447, 25);
			this->label9->TabIndex = 133;
			this->label9->Text = L"Задайте диапазон изменения параметра γⱼ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(469, 426);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(69, 29);
			this->label8->TabIndex = 119;
			this->label8->Text = L" T₂ = ";
			// 
			// T02_text
			// 
			this->T02_text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T02_text->Location = System::Drawing::Point(544, 426);
			this->T02_text->Name = L"T02_text";
			this->T02_text->Size = System::Drawing::Size(100, 29);
			this->T02_text->TabIndex = 118;
			this->T02_text->Text = L"999";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(469, 390);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(69, 29);
			this->label5->TabIndex = 117;
			this->label5->Text = L" T₁ = ";
			// 
			// T01_text
			// 
			this->T01_text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T01_text->Location = System::Drawing::Point(544, 391);
			this->T01_text->Name = L"T01_text";
			this->T01_text->Size = System::Drawing::Size(100, 29);
			this->T01_text->TabIndex = 116;
			this->T01_text->Text = L"500";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(475, 355);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(63, 29);
			this->label7->TabIndex = 115;
			this->label7->Text = L"Ė₀ = ";
			// 
			// E0Star_Text
			// 
			this->E0Star_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0Star_Text->Location = System::Drawing::Point(544, 356);
			this->E0Star_Text->Name = L"E0Star_Text";
			this->E0Star_Text->Size = System::Drawing::Size(100, 29);
			this->E0Star_Text->TabIndex = 114;
			this->E0Star_Text->Text = L"0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(469, 323);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 29);
			this->label6->TabIndex = 113;
			this->label6->Text = L" E₀ = ";
			// 
			// E0_Text
			// 
			this->E0_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0_Text->Location = System::Drawing::Point(544, 321);
			this->E0_Text->Name = L"E0_Text";
			this->E0_Text->Size = System::Drawing::Size(100, 29);
			this->E0_Text->TabIndex = 112;
			this->E0_Text->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(478, 495);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 29);
			this->label3->TabIndex = 108;
			this->label3->Text = L" α = ";
			// 
			// Alpha_Text
			// 
			this->Alpha_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Alpha_Text->Location = System::Drawing::Point(544, 496);
			this->Alpha_Text->Name = L"Alpha_Text";
			this->Alpha_Text->Size = System::Drawing::Size(100, 29);
			this->Alpha_Text->TabIndex = 107;
			this->Alpha_Text->Text = L"1,5";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(479, 460);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 29);
			this->label2->TabIndex = 106;
			this->label2->Text = L" g = ";
			// 
			// g_Text
			// 
			this->g_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g_Text->Location = System::Drawing::Point(544, 461);
			this->g_Text->Name = L"g_Text";
			this->g_Text->Size = System::Drawing::Size(100, 29);
			this->g_Text->TabIndex = 105;
			this->g_Text->Text = L"1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(6, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(722, 241);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 104;
			this->pictureBox1->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(735, 348);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(434, 172);
			this->textBox2->TabIndex = 93;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(47, 287);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 24);
			this->label1->TabIndex = 92;
			this->label1->Text = L" Число шагов";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(185, 287);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 29);
			this->textBox1->TabIndex = 91;
			this->textBox1->Text = L"10000000";
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->Location = System::Drawing::Point(766, 203);
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
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(120, 323);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(55, 29);
			this->label24->TabIndex = 89;
			this->label24->Text = L" T =";
			// 
			// b_Text3
			// 
			this->b_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->b_Text3->Location = System::Drawing::Point(185, 323);
			this->b_Text3->Name = L"b_Text3";
			this->b_Text3->Size = System::Drawing::Size(100, 29);
			this->b_Text3->TabIndex = 88;
			this->b_Text3->Text = L"1000";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(129, 355);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(46, 29);
			this->label23->TabIndex = 87;
			this->label23->Text = L"h =";
			// 
			// h_Text3
			// 
			this->h_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->h_Text3->Location = System::Drawing::Point(185, 358);
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
			this->label21->Location = System::Drawing::Point(365, 289);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(169, 24);
			this->label21->TabIndex = 85;
			this->label21->Text = L" Число уравнений";
			// 
			// n_Text3
			// 
			this->n_Text3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->n_Text3->Location = System::Drawing::Point(544, 284);
			this->n_Text3->Name = L"n_Text3";
			this->n_Text3->Size = System::Drawing::Size(100, 29);
			this->n_Text3->TabIndex = 84;
			this->n_Text3->Text = L"100";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->zedGraphControl2);
			this->tabPage2->Controls->Add(this->Omega1_Text);
			this->tabPage2->Controls->Add(this->Omega2);
			this->tabPage2->Controls->Add(this->Omega1);
			this->tabPage2->Controls->Add(this->Omega2_Text);
			this->tabPage2->Controls->Add(this->Change_scale_Omega);
			this->tabPage2->Controls->Add(this->dataGridView1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1562, 903);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Средние частоты";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// zedGraphControl2
			// 
			this->zedGraphControl2->ImeMode = System::Windows::Forms::ImeMode::On;
			this->zedGraphControl2->IsShowPointValues = true;
			this->zedGraphControl2->Location = System::Drawing::Point(0, 3);
			this->zedGraphControl2->Name = L"zedGraphControl2";
			this->zedGraphControl2->PointValueFormat = L"g";
			this->zedGraphControl2->ScrollGrace = 0;
			this->zedGraphControl2->ScrollMaxX = 0;
			this->zedGraphControl2->ScrollMaxY = 0;
			this->zedGraphControl2->ScrollMaxY2 = 0;
			this->zedGraphControl2->ScrollMinX = 0;
			this->zedGraphControl2->ScrollMinY = 0;
			this->zedGraphControl2->ScrollMinY2 = 0;
			this->zedGraphControl2->Size = System::Drawing::Size(1103, 718);
			this->zedGraphControl2->TabIndex = 114;
			// 
			// Omega1_Text
			// 
			this->Omega1_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega1_Text->Location = System::Drawing::Point(1195, 4);
			this->Omega1_Text->Name = L"Omega1_Text";
			this->Omega1_Text->Size = System::Drawing::Size(99, 29);
			this->Omega1_Text->TabIndex = 145;
			// 
			// Omega2
			// 
			this->Omega2->AutoSize = true;
			this->Omega2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega2->Location = System::Drawing::Point(1124, 41);
			this->Omega2->Name = L"Omega2";
			this->Omega2->Size = System::Drawing::Size(65, 25);
			this->Omega2->TabIndex = 144;
			this->Omega2->Text = L" Ω₂ = ";
			// 
			// Omega1
			// 
			this->Omega1->AutoSize = true;
			this->Omega1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega1->Location = System::Drawing::Point(1124, 6);
			this->Omega1->Name = L"Omega1";
			this->Omega1->Size = System::Drawing::Size(65, 25);
			this->Omega1->TabIndex = 143;
			this->Omega1->Text = L" Ω₁ = ";
			// 
			// Omega2_Text
			// 
			this->Omega2_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega2_Text->Location = System::Drawing::Point(1196, 39);
			this->Omega2_Text->Name = L"Omega2_Text";
			this->Omega2_Text->Size = System::Drawing::Size(98, 29);
			this->Omega2_Text->TabIndex = 142;
			// 
			// Change_scale_Omega
			// 
			this->Change_scale_Omega->Enabled = false;
			this->Change_scale_Omega->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Change_scale_Omega->Location = System::Drawing::Point(1300, 4);
			this->Change_scale_Omega->Name = L"Change_scale_Omega";
			this->Change_scale_Omega->Size = System::Drawing::Size(184, 60);
			this->Change_scale_Omega->TabIndex = 141;
			this->Change_scale_Omega->Text = L"Изменить масштаб от Ω₁ до Ω₂";
			this->Change_scale_Omega->UseVisualStyleBackColor = true;
			this->Change_scale_Omega->Click += gcnew System::EventHandler(this, &MyForm::Change_scale_Omega_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->dataGridView1->Location = System::Drawing::Point(1109, 74);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(445, 647);
			this->dataGridView1->TabIndex = 115;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"j";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Width = 200;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Ωⱼ";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->Width = 200;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->dataGridView2);
			this->tabPage3->Controls->Add(this->zedGraphControl4);
			this->tabPage3->Controls->Add(this->zedGraphControl3);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1562, 903);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Внешнее поле и спайки";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn3,
					this->dataGridViewTextBoxColumn4
			});
			this->dataGridView2->Location = System::Drawing::Point(1109, 0);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(445, 721);
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
			this->zedGraphControl4->IsShowPointValues = true;
			this->zedGraphControl4->Location = System::Drawing::Point(6, 3);
			this->zedGraphControl4->Name = L"zedGraphControl4";
			this->zedGraphControl4->ScrollGrace = 0;
			this->zedGraphControl4->ScrollMaxX = 0;
			this->zedGraphControl4->ScrollMaxY = 0;
			this->zedGraphControl4->ScrollMaxY2 = 0;
			this->zedGraphControl4->ScrollMinX = 0;
			this->zedGraphControl4->ScrollMinY = 0;
			this->zedGraphControl4->ScrollMinY2 = 0;
			this->zedGraphControl4->Size = System::Drawing::Size(1097, 342);
			this->zedGraphControl4->TabIndex = 1;
			// 
			// zedGraphControl3
			// 
			this->zedGraphControl3->IsShowPointValues = true;
			this->zedGraphControl3->Location = System::Drawing::Point(6, 351);
			this->zedGraphControl3->Name = L"zedGraphControl3";
			this->zedGraphControl3->ScrollGrace = 0;
			this->zedGraphControl3->ScrollMaxX = 0;
			this->zedGraphControl3->ScrollMaxY = 0;
			this->zedGraphControl3->ScrollMaxY2 = 0;
			this->zedGraphControl3->ScrollMinX = 0;
			this->zedGraphControl3->ScrollMinY = 0;
			this->zedGraphControl3->ScrollMinY2 = 0;
			this->zedGraphControl3->Size = System::Drawing::Size(1097, 370);
			this->zedGraphControl3->TabIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->textBox5);
			this->tabPage4->Controls->Add(this->panel1);
			this->tabPage4->Controls->Add(this->textBox3);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1562, 903);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Серия экспериментов";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox5->Location = System::Drawing::Point(5, 364);
			this->textBox5->Multiline = true;
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox5->Size = System::Drawing::Size(465, 355);
			this->textBox5->TabIndex = 157;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->comboBox3);
			this->panel1->Controls->Add(this->comboBox4);
			this->panel1->Controls->Add(this->label14);
			this->panel1->Controls->Add(this->label19);
			this->panel1->Controls->Add(this->progressBar3);
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->textBox6);
			this->panel1->Controls->Add(this->button5);
			this->panel1->Controls->Add(this->label15);
			this->panel1->Controls->Add(this->label22);
			this->panel1->Controls->Add(this->progressBar1);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->g1_Text);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->g2_Text);
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->GShag_Text);
			this->panel1->Controls->Add(this->label12);
			this->panel1->Controls->Add(this->label16);
			this->panel1->Location = System::Drawing::Point(597, 115);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(633, 532);
			this->panel1->TabIndex = 156;
			// 
			// comboBox3
			// 
			this->comboBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1,1", L"2,1", L"3,1", L"4,1", L"5,1", L"1,03" });
			this->comboBox3->Location = System::Drawing::Point(404, 14);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(100, 32);
			this->comboBox3->TabIndex = 170;
			this->comboBox3->Text = L"1,1";
			// 
			// comboBox4
			// 
			this->comboBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1", L"2", L"3", L"4", L"5", L"1,03" });
			this->comboBox4->Location = System::Drawing::Point(194, 14);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(100, 32);
			this->comboBox4->TabIndex = 169;
			this->comboBox4->Text = L"1";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(334, 13);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(64, 29);
			this->label14->TabIndex = 168;
			this->label14->Text = L" γ₂ = ";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(124, 13);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(64, 29);
			this->label19->TabIndex = 167;
			this->label19->Text = L" γ₁ = ";
			// 
			// progressBar3
			// 
			this->progressBar3->Location = System::Drawing::Point(129, 292);
			this->progressBar3->Name = L"progressBar3";
			this->progressBar3->Size = System::Drawing::Size(390, 31);
			this->progressBar3->TabIndex = 161;
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(489, 82);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(132, 66);
			this->button3->TabIndex = 159;
			this->button3->Text = L"Отмена\r\n\r\n";
			this->button3->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox6->Location = System::Drawing::Point(117, 451);
			this->textBox6->Multiline = true;
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(410, 58);
			this->textBox6->TabIndex = 158;
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(211, 82);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(140, 67);
			this->button5->TabIndex = 153;
			this->button5->Text = L"Вычислить min, max и avg";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(226, 400);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(212, 24);
			this->label15->TabIndex = 155;
			this->label15->Text = L"Идут вычисления... 0%";
			this->label15->Visible = false;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(125, 246);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(267, 24);
			this->label22->TabIndex = 149;
			this->label22->Text = L"Число различных наборов γᵢ:";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(129, 355);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(390, 31);
			this->progressBar1->TabIndex = 154;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(73, 82);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 66);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Начать вычисления";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// g1_Text
			// 
			this->g1_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g1_Text->Location = System::Drawing::Point(232, 165);
			this->g1_Text->Name = L"g1_Text";
			this->g1_Text->Size = System::Drawing::Size(57, 29);
			this->g1_Text->TabIndex = 2;
			this->g1_Text->Text = L"0,001";
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(398, 243);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(29, 29);
			this->textBox4->TabIndex = 152;
			this->textBox4->Text = L"50";
			// 
			// g2_Text
			// 
			this->g2_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g2_Text->Location = System::Drawing::Point(398, 162);
			this->g2_Text->Name = L"g2_Text";
			this->g2_Text->Size = System::Drawing::Size(57, 29);
			this->g2_Text->TabIndex = 3;
			this->g2_Text->Text = L"0,005";
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(357, 83);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(126, 66);
			this->button4->TabIndex = 151;
			this->button4->Text = L"Очистить графики";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(188, 168);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 24);
			this->label4->TabIndex = 4;
			this->label4->Text = L"β₁=";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(354, 165);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(38, 24);
			this->label11->TabIndex = 5;
			this->label11->Text = L"β₂=";
			// 
			// GShag_Text
			// 
			this->GShag_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->GShag_Text->Location = System::Drawing::Point(297, 203);
			this->GShag_Text->Name = L"GShag_Text";
			this->GShag_Text->Size = System::Drawing::Size(79, 29);
			this->GShag_Text->TabIndex = 7;
			this->GShag_Text->Text = L"0,0002";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(206, 206);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(86, 24);
			this->label12->TabIndex = 6;
			this->label12->Text = L"Шаг по β";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(188, 400);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(281, 24);
			this->label16->TabIndex = 160;
			this->label16->Text = L"Останавливаем вычисления...";
			this->label16->Visible = false;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(6, 6);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox3->Size = System::Drawing::Size(464, 352);
			this->textBox3->TabIndex = 148;
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->checkBox1);
			this->tabPage5->Controls->Add(this->zedGraphControl6);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1562, 903);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Средние частоты для серии";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Enabled = false;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(1318, 690);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(236, 29);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"Показывать легенду";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// zedGraphControl6
			// 
			this->zedGraphControl6->IsShowPointValues = true;
			this->zedGraphControl6->Location = System::Drawing::Point(0, 6);
			this->zedGraphControl6->Name = L"zedGraphControl6";
			this->zedGraphControl6->ScrollGrace = 0;
			this->zedGraphControl6->ScrollMaxX = 0;
			this->zedGraphControl6->ScrollMaxY = 0;
			this->zedGraphControl6->ScrollMaxY2 = 0;
			this->zedGraphControl6->ScrollMinX = 0;
			this->zedGraphControl6->ScrollMinY = 0;
			this->zedGraphControl6->ScrollMinY2 = 0;
			this->zedGraphControl6->Size = System::Drawing::Size(1563, 737);
			this->zedGraphControl6->TabIndex = 1;
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->checkBox4);
			this->tabPage6->Controls->Add(this->zedGraphControl1);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(1562, 903);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Число кластеров для серии";
			this->tabPage6->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Enabled = false;
			this->checkBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox4->Location = System::Drawing::Point(1318, 690);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(236, 29);
			this->checkBox4->TabIndex = 149;
			this->checkBox4->Text = L"Показывать легенду";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox4_CheckedChanged);
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->IsShowPointValues = true;
			this->zedGraphControl1->Location = System::Drawing::Point(0, 6);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(1563, 737);
			this->zedGraphControl1->TabIndex = 148;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->WorkerReportsProgress = true;
			this->backgroundWorker2->WorkerSupportsCancellation = true;
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker2_DoWork);
			this->backgroundWorker2->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker2_ProgressChanged);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker2_RunWorkerCompleted);
			// 
			// backgroundWorker3
			// 
			this->backgroundWorker3->WorkerReportsProgress = true;
			this->backgroundWorker3->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker3_ProgressChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1573, 756);
			this->Controls->Add(this->tabControl1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Исследование коллективной динамики активных ротаторов";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			this->tabPage6->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	GraphPane ^panel = zedGraphControl6->GraphPane;
	GraphPane ^panel2 = zedGraphControl1->GraphPane;

	const int n = Convert::ToInt32(n_Text3->Text);                   //Число уравнений в системе
	const int p = Convert::ToInt32(textBox1->Text);                  //Число итераций, второй критерий остановки
	const int NumOfSets = Convert::ToInt32(textBox4->Text);          //Число наборов
	const double gamma1Copy = Convert::ToDouble(comboBox4->Text);
	const double gamma2Copy = Convert::ToDouble(comboBox3->Text);
	const double beta1 = Convert::ToDouble(g1_Text->Text);           //Начальное значение β
	const double beta2 = Convert::ToDouble(g2_Text->Text);           //Конечное значение β
	const double betaStep = Convert::ToDouble(GShag_Text->Text);     //Шаг по β
	const double h = Convert::ToDouble(h_Text3->Text);               //Шаг интегрирования
	const double T01 = Convert::ToDouble(T01_text->Text);            //Начальное время, от которого будет считаться частота	
	const double T = Convert::ToDouble(b_Text3->Text);               //Максимальное время, до которого будет подсчет, первый критерий остановки
	const double alpha = Convert::ToDouble(Alpha_Text->Text);        //Число α
	const double g = Convert::ToDouble(g_Text->Text);                //Коэффициент связи
	int non = 0;                                                     //Число точек на графике, в которых считаются средние частоты 
	double E0;                                                       //Начальное условие для E    
	double E0Star;                                                   //Начальное условие для Ė
	double t;                                                        //Время			
	int *NumOfClusters;                                              //Массив для хранения числа кластеров
	int *k;                                                          //Число спайков для каждого ротатора
	double **Omega;                                                  //Средние частоты
	double *om;                                                      //Технический массив для вычислений 
	double *Fi;                                                      //Фазы φⱼ(t) j = 0,...,n - 1
	double *Fiplus1;                                                 //Фазы φⱼ(t) j = 0,...,n - 1
	double *cur_gamma;                                               //Набор γⱼ
	double *Fi0;                                                     //Фазы при t = T₁

	const double D2PI = 2 * M_PI;

	if (T01 > T)
	{
		MessageBox::Show(L"T₁ должен быть меньше или равен T", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	//Технические переменные, используемые для расчетов
	int index;
	int counter = 0;
	double oldE0;
	double ts;

	panel->XAxis->Scale->Min = beta1 - 0.0001;
	panel->XAxis->Scale->Max = beta2 + 0.0001;
	panel->XAxis->Scale->MajorStep = betaStep;
	panel->XAxis->Scale->MinorStep = betaStep / 5;
	panel2->XAxis->Scale->Min = beta1 - 0.0001;
	panel2->XAxis->Scale->Max = beta2 + 0.0001;
	panel2->YAxis->Scale->MajorStep = 2;
	panel2->YAxis->Scale->MinorStep = 1;
	panel2->XAxis->Scale->MajorStep = betaStep;
	panel2->XAxis->Scale->MinorStep = betaStep / 5;

	//Вычисляем количество вершин в графе
	for (double beta = beta1; beta <= beta2; beta += betaStep)
	{
		beta = round(beta * 100000) / 100000;
		non++;
	}
	
	PointPairList ^Cl_list;
	cli::array<PointPairList^> ^Omega_List;
	
#pragma omp parallel private(om, Fi, Fiplus1, k, Fi0)
	{
		int threadid = omp_get_thread_num();
			k = new int[n];
			om = new double[n];
			Fi = new double[n];
			Fiplus1 = new double[n];
			Fi0 = new double[n];

#pragma omp for private(Cl_list, Omega_List, E0, E0Star, index, ts, t, cur_gamma, Omega, NumOfClusters, oldE0)
		for (int GlobalInd = 0; GlobalInd < NumOfSets; GlobalInd++)
		{
			if (backgroundWorker1->CancellationPending)
			{
				e->Cancel = true;
				break;
			}
			E0 = Convert::ToDouble(E0_Text->Text);
			E0Star = Convert::ToDouble(E0Star_Text->Text);
			index = 0;
			ts = 0.0;
			t = 0.0;

			cur_gamma = Set_Gamma(n, gamma1Copy, gamma2Copy);
			NumOfClusters = new int[non];
			Omega = new double*[n];
			Cl_list = gcnew PointPairList();
			Omega_List = gcnew cli::array<PointPairList^>(n);

			if (gamma1Copy != gamma2Copy)
			{
				for (int i = 0; i < n; i++)
				{

					Omega[i] = new double[non];
					Omega_List[i] = gcnew PointPairList();

					//Начальное значение φⱼ(0) и число спайков равно 0
					Fi[i] = Fiplus1[i] = Fi0[i] = 0.0;
					k[i] = 0;
				}
			}
			else
			{
				random_device gen;
				mt19937 me(gen());
				uniform_real_distribution<> distr(0, M_PI);
				for (int i = 0; i < n; i++)
				{
					Omega[i] = new double[non];
					Omega_List[i] = gcnew PointPairList();

					Fi[i] = Fi0[i] = distr(me);
					Fiplus1[i] = 0.0;
					k[i] = 0;                          //Изначальное число спайков равно нулю
				}
			}

			//Вычисляем φⱼ(t) методом Рунге-Кутта 4-го порядка
			for (double beta = beta1; beta <= beta2; beta += betaStep)
			{
				beta = round(beta * 100000) / 100000;
				if (threadid == 0)
				{
					backgroundWorker3->ReportProgress((int)((beta - beta1) / (beta2 - beta1) * 100));
				}
				//t от 0 до T01 - h
				for (t; t < T01 - h; t += h)
				{					
					t = round(t * 1000) / 1000;
					for (int j = 0; j < n; j++)
					{
						//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
						Fiplus1[j] = RK4(t, ts, Fi[j], h, cur_gamma[j], g, E0, E0Star, alpha);
						Fi[j] = Fiplus1[j];

						if (Fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
						{
							oldE0 = E0;
							E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
							E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
							E0Star += beta;                                //Добавление β к начальному значению производной
							ts = t + h;                                    //Изменение времени последнего спайка
							Fi[j] = 0.0;			                       //Обнуление значения ф												
						}
					}
				}
				//---------------------------------------------------
				//t от T01 - h до T01
				t = round(t * 1000) / 1000;
				for (int j = 0; j < n; j++)
				{
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					Fiplus1[j] = RK4(t, ts, Fi[j], h, cur_gamma[j], g, E0, E0Star, alpha);
					Fi[j] = Fiplus1[j];

					if (Fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
					{
						oldE0 = E0;
						E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
						E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
						E0Star += beta;                                //Добавление β к начальному значению производной
						ts = t + h;                                    //Изменение времени последнего спайка
						Fi[j] = 0.0;			                       //Обнуление значения ф					
						k[j]++;                                        //Увеличение числа спайков на 1
					}
				}

				t += h;

				for (int l = 0; l < n; l++)
				{
					Fi0[l] = Fi[l];                                    //Запоминание значений фаз при t = T₁
				}
				//---------------------------------------------------
				//t от T01 до T
				for (t; t < T; t += h)
				{
					t = round(t * 1000) / 1000;
					for (int j = 0; j < n; j++)
					{
						//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
						Fiplus1[j] = RK4(t, ts, Fi[j], h, cur_gamma[j], g, E0, E0Star, alpha);
						Fi[j] = Fiplus1[j];

						if (Fi[j] >= D2PI)                                   //В моемент импульса j-го ротатора
						{												     
							oldE0 = E0;									     
							E0 = E(t + h, ts, E0, E0Star, alpha);            //Пересчет начальных условий
							E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);  
							E0Star += beta;                                  //Добавление β к начальному значению производной
							ts = t + h;                                      //Изменение времени последнего спайка
							Fi[j] = 0.0;			                         //Обнуление значения ф
							k[j]++;
						}
					}
				}
				//---------------------------------------------------		
				//Вычисление средних частот Ω		
				for (int i = 0; i < n; i++)
				{
					if (k[i] != 0)
					{
						Omega[i][index] = ((k[i] - 1) * D2PI + Fi[i] - Fi0[i]) / (t - T01);
					}
					else
					{
						Omega[i][index] = (Fi[i] - Fi0[i]) / (t - T01);
					}
					om[i] = Omega[i][index];
				}

				//Вычисление числа кластеров
				NumOfClusters[index] = GetNumberOfClusters(om, n);

				index++;

				//Обнуление переменных для повторного счета при другом значении силы связи g
				t = 0.0;
				ts = 0.0;
				E0 = Convert::ToDouble(E0_Text->Text);
				E0Star = Convert::ToDouble(E0Star_Text->Text);

				for (int i = 0; i < n; i++)
				{
					Fi[i] = Fiplus1[i] = 0.0;
					k[i] = 0;
				}
			}

#pragma omp critical (pushing)
			{
				Omega_vec->push_back(Omega);
				Clusters_vec->push_back(NumOfClusters);
			}

			double _beta = beta1;

			//Рисование графиков
			for (int i = 0; i < n; i++)
			{
				_beta = beta1;
				for (int j = 0; j < non; j++)
				{
					Omega_List[i]->Add(_beta, Omega[i][j]);
					if (_beta <= beta2)
					{
						_beta += betaStep;
						_beta = round(_beta * 100000) / 100000;
					}
				}
				LineItem ^Curve;
#pragma omp critical (DrawOmegaGraph)
				Curve = panel->AddCurve(Convert::ToString(GlobalInd), Omega_List[i], Colors[GlobalInd], SymbolType::Circle);
				Curve->Symbol->Fill->Color = Colors[GlobalInd];
				Curve->Symbol->Size = 8.0f;
				Curve->Symbol->Fill->Type = FillType::Solid;
				if (i > 0)
				{
					Curve->Label->Text = String::Empty;
				}
			}

			zedGraphControl6->AxisChange();
			zedGraphControl6->Invalidate();

			_beta = beta1;

			for (int i = 0; i < non; i++)
			{
				Cl_list->Add(_beta, NumOfClusters[i]);
				_beta += betaStep;
				_beta = round(_beta * 100000) / 100000;
			}
			LineItem ^Curve2;
#pragma omp critical (DrawClusGraph)
			Curve2 = panel2->AddCurve(Convert::ToString(GlobalInd), Cl_list, Colors[GlobalInd], SymbolType::Circle);
			Curve2->Symbol->Fill->Color = Colors[GlobalInd];
			Curve2->Symbol->Fill->Type = FillType::Solid;
			Curve2->Line->IsVisible = false;

			zedGraphControl1->AxisChange();
			zedGraphControl1->Invalidate();

#pragma omp atomic
			counter++;
#pragma omp critical (report)
			backgroundWorker1->ReportProgress((int)((float)counter / NumOfSets * 100));
		}		
		//Освобождение памяти
		delete[]om;
		delete[]Fi;
		delete[]Fiplus1;
		delete[]k;
		delete[]Fi0;
	}
	//Конец параллельной секции------------------------------------------------------------------
	delete[]cur_gamma;
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
{

	Int32 NumOfSets = Convert::ToInt32(textBox4->Text);

	if (NumOfSets > 50)
	{
		MessageBox::Show("Максимальное число наборов: 50", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (NumOfSets == 0)
	{
		MessageBox::Show("Число наборов должно быть больше 0", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	g1_Text->ReadOnly = true;
	g2_Text->ReadOnly = true;
	GShag_Text->ReadOnly = true;
	textBox4->ReadOnly = true;
	label15->Text = "Идут вычисления... 0%";
	label15->Visible = true;
	button2->Enabled = false;
	comboBox3->Enabled = false;
	comboBox4->Enabled = false;
	button3->Enabled = true;

	backgroundWorker1->RunWorkerAsync();
}

private: System::Void Change_scale_Omega_Click(System::Object^  sender, System::EventArgs^  e)
{
	GraphPane ^panel = zedGraphControl2->GraphPane;
	double Om1 = Convert::ToDouble(Omega1_Text->Text);
	double Om2 = Convert::ToDouble(Omega2_Text->Text);

	panel->YAxis->Scale->Min = Om1;
	panel->YAxis->Scale->Max = Om2;

	panel->YAxis->Scale->MajorStepAuto = false;
	panel->YAxis->Scale->MinorStepAuto = false;
	panel->YAxis->Scale->MajorStep = (Om2 - Om1)*0.1;
	panel->YAxis->Scale->MinorStep = (Om2 - Om1)*0.02;
	zedGraphControl2->AxisChange();
	zedGraphControl2->Invalidate();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	dataGridView4->Rows->Clear();

	const int n = Convert::ToInt32(n_Text3->Text);
	gamma1 = Convert::ToDouble(comboBox1->Text);
	gamma2 = Convert::ToDouble(comboBox2->Text);
	gamma = new double[n];
	gamma = Set_Gamma(n, gamma1, gamma2);
	//qsort((void *)gamma, (size_t)n, sizeof(double), compare);

	dataGridView4->Rows->Add(n);

	for (int i = 0; i < n; i++)
	{
		dataGridView4->Rows[i]->Cells[0]->Value = i;
		dataGridView4->Rows[i]->Cells[1]->Value = gamma[i];
	}

	n_Text3->ReadOnly = true;
	button7->Enabled = true;
	MessageBox::Show("Набор сгенерирован", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	zedGraphControl6->GraphPane->CurveList->Clear();
	zedGraphControl1->GraphPane->CurveList->Clear();
	g1_Text->ReadOnly = false;
	g2_Text->ReadOnly = false;
	GShag_Text->ReadOnly = false;
	textBox4->ReadOnly = false;
	AvgMaxMinAlreadyExists = false;
	comboBox3->Enabled = true;
	comboBox4->Enabled = true;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
	zedGraphControl6->AxisChange();
	zedGraphControl6->Invalidate();

	Omega_vec->clear();
	Clusters_vec->clear();
	textBox3->Text = String::Empty;
	textBox5->Text = String::Empty;
	textBox6->Text = String::Empty;
	checkBox1->Checked = true;
	checkBox4->Checked = true;
	checkBox1->Enabled = false;
	checkBox4->Enabled = false;
	button2->Enabled = true;
	button5->Enabled = false;
	button4->Enabled = false;

	MessageBox::Show("Графики очищены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
}
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	progressBar1->Value = e->ProgressPercentage;
	label15->Text = "Идут вычисления... " + Convert::ToString(progressBar1->Value) + "%";
}
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	if (e->Cancelled)
	{
		label16->Visible = false;
		MessageBox::Show("Вычисления приостановлены пользователем", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	else
	{
		MessageBox::Show("Вычисления закончены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	progressBar1->Value = 0;
	progressBar3->Value = 0;
	label15->Visible = false;
	checkBox1->Enabled = true;
	checkBox4->Enabled = true;
	button5->Enabled = true;
	button4->Enabled = true;
	button3->Enabled = false;
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
{	
	const int n = Convert::ToInt32(n_Text3->Text);
	const int NumOfSets = Convert::ToInt32(textBox4->Text);
	const double beta1 = Convert::ToDouble(g1_Text->Text);         
	const double beta2 = Convert::ToDouble(g2_Text->Text);         
	const double betaStep = Convert::ToDouble(GShag_Text->Text);      
	const double gamma1Copy = Convert::ToDouble(comboBox4->Text);
	const double gamma2Copy = Convert::ToDouble(comboBox3->Text);
	int* curClusters;
	double** curOmega;
	double* om;
	String ^str = L"Ω:\r\n";
	String ^str1 = "Кластеры:\r\n";
	String ^str2 = "";
	GraphPane ^panel = zedGraphControl6->GraphPane;
	GraphPane ^panel2 = zedGraphControl1->GraphPane;

	PointPairList ^AvgOmList = gcnew PointPairList();
	PointPairList ^AvgClusList = gcnew PointPairList();
	PointPairList ^MinMaxOmList = gcnew PointPairList();
	PointPairList ^MinMaxClusList = gcnew PointPairList();

	int non = 0;
	int index;
	int k = 0;
	int m = 0;

	for (double beta = beta1; beta <= beta2; beta += betaStep)
	{
		beta = round(beta * 100000) / 100000;
		non++;
	}

	double **MinMaxOm = new double*[non];
	int **MinMaxClus = new int*[non];

	for (int i = 0; i < non; i++)
	{
		MinMaxOm[i] = new double[2 * NumOfSets];
		MinMaxClus[i] = new int[NumOfSets];
	}

	if (AvgMaxMinAlreadyExists)
	{		
			panel->CurveList->RemoveAt(0);
			panel->CurveList->RemoveAt(0);
			panel2->CurveList->RemoveAt(0);
			panel2->CurveList->RemoveAt(0);
	}

	for(int j = 0; j < (int)Omega_vec->size(); j++)
	{
		curOmega = Omega_vec->at(j);
		om = new double[n];
		curClusters = Clusters_vec->at(j);

		for (index = 0; index < non; index++)
		{
			for (int i = 0; i < n; i++)
			{
				om[i] = curOmega[i][index];
			}
			FindMinMax(n, om, &MinMaxOm[index][k], &MinMaxOm[index][k + 1]);
			MinMaxClus[index][m] = curClusters[index];
		}
		m++;
		k += 2;		
	}

	double beta = beta1;
	for (int i = 0; i < non; i++)
	{
		double MaxOmega, MinOmega;
		int MaxClus, MinClus;

		FindMinMax(2 * NumOfSets, MinMaxOm[i], &MinOmega, &MaxOmega);
		FindMinMax(NumOfSets, MinMaxClus[i], &MinClus, &MaxClus);

		MinMaxOmList->Add(beta, MinOmega, MaxOmega);
		AvgOmList->Add(beta, (MinOmega + MaxOmega)*0.5);
		MinMaxClusList->Add(beta, MinClus, MaxClus);
		AvgClusList->Add(beta, (int)((MinClus + MaxClus)*0.5));

		str += String::Format(L"β = {0}; Min = {1:G5}, Max = {2:G5}, Avg = {3:G5}\r\n", beta, MinOmega, MaxOmega, (MinOmega + MaxOmega)*0.5);

		str1 += String::Format(L"β = {0}; Min = {1}, Max = {2}, Avg = {3}\r\n", beta, MinClus, MaxClus, (int)((MinClus + MaxClus)*0.5));

		beta += betaStep;
	}

	str2 += String::Format(L"γⱼ были взяты из интервала [{0}; {1}]", gamma1Copy, gamma2Copy);

	textBox3->Text = str;
	textBox5->Text = str1;
	textBox6->Text = str2;

	LineItem ^Curve = panel->AddCurve("Среднее значение", AvgOmList, Color::DarkOrange, SymbolType::Diamond);
	LineItem ^Curve2 = panel2->AddCurve("Среднее значение", AvgClusList, Color::DarkOrange, SymbolType::Diamond);
	ErrorBarItem ^ErrorBar = panel->AddErrorBar("Min и Max", MinMaxOmList, Color::DarkOrange);
	ErrorBarItem ^ErrorBar2 = panel2->AddErrorBar("Min и Max", MinMaxClusList, Color::DarkOrange);

	Curve->Symbol->Fill->Color = Color::DarkOrange;
	Curve->Line->IsVisible = false;
	Curve->Symbol->Size = 8.0f;
	Curve->Symbol->Fill->Type = FillType::Solid;

	Curve2->Symbol->Fill->Color = Color::DarkOrange;
	Curve2->Line->IsVisible = false;
	Curve2->Symbol->Fill->Type = FillType::Solid;

	panel->CurveList->Move(panel->CurveList->Count - 1, -9999);
	panel->CurveList->Move(panel->CurveList->Count - 1, -10000);
	panel2->CurveList->Move(panel2->CurveList->Count - 1, -9999);
	panel2->CurveList->Move(panel2->CurveList->Count - 1, -10000);
		
	zedGraphControl1->Invalidate();
	zedGraphControl6->Invalidate();

	AvgMaxMinAlreadyExists = true;

	for (int i = 0; i < non; i++)
	{
		delete[]MinMaxOm[i];
		delete[]MinMaxClus[i];
	}
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	GraphPane ^panel = zedGraphControl6->GraphPane;

	if (checkBox1->Checked)
	{
		panel->Legend->IsVisible = true;
	}
	else
	{
		panel->Legend->IsVisible = false;
	}

	zedGraphControl6->Invalidate();
}
private: System::Void checkBox4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	GraphPane ^panel = zedGraphControl1->GraphPane;

	if (checkBox4->Checked)
	{
		panel->Legend->IsVisible = true;
	}
	else
	{
		panel->Legend->IsVisible = false;
	}

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
{
	label15->Visible = false;
	label16->Visible = true;
	backgroundWorker1->CancelAsync();
}
private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	GraphPane^ panel2 = zedGraphControl2->GraphPane;
	GraphPane^ panel3 = zedGraphControl3->GraphPane;
	GraphPane^ panel4 = zedGraphControl4->GraphPane;

	panel2->CurveList->Clear();
	panel3->CurveList->Clear();
	panel4->CurveList->Clear();

	panel2->YAxis->Scale->MajorStepAuto = true;
	panel2->YAxis->Scale->MinorStepAuto = true;

	PointPairList^ g_list = gcnew PointPairList();              //Список точек для графика средних частот Ω
	PointPairList^ E_list = gcnew PointPairList();	            //Список точек для графика поля E(t)		

	const int n = Convert::ToInt32(n_Text3->Text);              //Число уравнений в системе
	const int p = Convert::ToInt32(textBox1->Text);             //Число итераций, второй критерий остановки
	const double h = Convert::ToDouble(h_Text3->Text);          //Шаг
	const double T = Convert::ToDouble(b_Text3->Text);          //Максимальное время, до которого будет подсчет, первый критерий остановки
	const double T01 = Convert::ToDouble(T01_text->Text);       //Начальное время, от которого будет считаться частота
	const double T02 = Convert::ToDouble(T02_text->Text);       //Начальное время, от которого будут рисоваться график E(t) и график числа спайков
	const double g = Convert::ToDouble(g_Text->Text);           //Коэффициент связи
	const double alpha = Convert::ToDouble(Alpha_Text->Text);   //Число α
	const double beta = Convert::ToDouble(textBox7->Text);      //Число β
	int it = 0;                                                 //Индекс строк в таблице
	int NumOfClusters;                                          //Число кластеров при t = T
	double E0 = Convert::ToDouble(E0_Text->Text);               //Начальное условие для E
	double E0Star = Convert::ToDouble(E0Star_Text->Text);       //Начальное условие для Ė
	double t = 0.0;                                             //Текущее время       
	double Et;                                                  //Поле E(t)
	double MaxOmega = -100000.0, MinOmega = 100000.0;           //Максимальная и минимальная средние частоты 	
	double ts = 0.0;                                            //Время последнего спайка
	int *k;                                                     //Число спайков для каждого ротатора  
	double *Fi0;		                                        //Фазы при t = T₁
	double *Fi, *Fiplus1;	                                    //Фазы φⱼ(t) j = 0,...,n - 1
	double *Omega;                                              //Средние частоты Ω

	Str = "";

	const double D2PI = 2 * M_PI;

	if (T01 > T || T02 > T)
	{
		MessageBox::Show(L"T₁ и T₂ должны быть меньше или равны T", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	//Технические переменные, используемые для расчетов 
	int ind = 0;
	int i;
	double oldE0;
	bool spike_flag = false;

	Fi = new double[n];
	Fiplus1 = new double[n];
	Omega = new double[n];
	Fi0 = new double[n];
	k = new int[n];

	double tmin_limit = t - 0.05;

	if (gamma1 != gamma2)
	{
		for (i = 0; i < n; i++)                //Начальные условия для каждого из φⱼ(t) равны нулю
		{
			Fi[i] = Fiplus1[i] = Fi0[i] = 0.0;
			k[i] = 0;                          //Изначальное число спайков равно нулю
		}
	}
	else
	{
		random_device gen;
		mt19937 me(gen());
		uniform_real_distribution<> distr(0, M_PI);
		for (i = 0; i < n; i++)                
		{
			Fi[i] = Fi0[i] = distr(me);
			Fiplus1[i] = 0.0;
			k[i] = 0;                          //Изначальное число спайков равно нулю
		}
	}

	//Основной цикл: Вычисление φⱼ(t) методом Рунге-Кутта 4-го порядка
	if (T01 <= T02)
	{
		//t от 0 до T01 - h
		for (t; t < T01 - h; t += h)
		{
			if (backgroundWorker2->CancellationPending)
			{
				e->Cancel = true;
				return;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                //Добавление β к начальному значению производной
					ts = t + h;                                    //Изменение времени последнего спайка
					Fi[j] = 0.0;			                       //Обнуление значения ф												
				}
			}
			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------
		//t от T01 - h до T01
		if (backgroundWorker2->CancellationPending)
		{
			e->Cancel = true;
			return;
		}
		t = round(t * 1000) / 1000;
		for (int j = 0; j < n; j++)
		{
			//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
			Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
			Fi[j] = Fiplus1[j];

			if (Fi[j] >= D2PI)                              //В моемент импульса j-го ротатора
			{
				oldE0 = E0;
				E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
				E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
				E0Star += beta;                                //Добавление β к начальному значению производной
				ts = t + h;                                    //Изменение времени последнего спайка
				Fi[j] = 0.0;			                       //Обнуление значения ф					
				k[j]++;                                        //Увеличение числа спайков на 1
			}
		}

		for (int l = 0; l < n; l++)
		{
			Fi0[l] = Fi[l];                                    //Запоминание значений фаз при t = T₁
		}

		backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		t += h;
		//---------------------------------------------------
		//t от T01 до T02 - h
		for (t; t < T02 - h; t += h)
		{
			if (backgroundWorker2->CancellationPending)
			{
				e->Cancel = true;
				return;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);           //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                 //Добавление β к начальному значению производной
					ts = t + h;                                     //Изменение времени последнего спайка
					Fi[j] = 0.0;			                        //Обнуление значения ф						
					k[j]++;                                         //Увеличение числа спайков на 1						
				}
			}

			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------			
		//t от T02 - h до T
		for (t; t < T; t += h)
		{
			if (backgroundWorker2->CancellationPending)
			{
				e->Cancel = true;
				return;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);           //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                 //Добавление β к начальному значению производной
					ts = t + h;                                     //Изменение времени последнего спайка
					Fi[j] = 0.0;			                        //Обнуление значения ф						
					k[j]++;                                         //Увеличение числа спайков на 1	
					if (!spike_flag)                                //Отбражение нового спайка на графике
					{
						PointPairList^ Spaik_list = gcnew PointPairList();
						Spaik_list->Add(ts, 0.0);
						Spaik_list->Add(ts, 1.0);

						LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

						zedGraphControl3->AxisChange();
						zedGraphControl3->Invalidate();
						spike_flag = true;
					}
				}
			}
			spike_flag = false;

			Et = E(t + h, ts, E0, E0Star, alpha);
			E_list->Add(t + h, Et);
			VE->push_back(Et);
			VT->push_back(t + h);

			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------
	}
	else
	{
		//t от 0 до T02 - h
		for (t; t < T02 - h; t += h)
		{
			if (backgroundWorker2->CancellationPending)
			{
				e->Cancel = true;
				return;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                //Добавление β к начальному значению производной
					ts = t + h;                                    //Изменение времени последнего спайка
					Fi[j] = 0.0;			                       //Обнуление значения ф												
				}
			}
			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------
		//t от T02 - h до T01 - h
		for (t; t < T01 - h; t += h)
		{
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);           //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                 //Добавление β к начальному значению производной
					ts = t + h;                                     //Изменение времени последнего спайка
					Fi[j] = 0.0;			                        //Обнуление значения ф						
					if (!spike_flag)                                //Отбражение нового спайка на графике
					{
						PointPairList^ Spaik_list = gcnew PointPairList();
						Spaik_list->Add(ts, 0.0);
						Spaik_list->Add(ts, 1.0);

						LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

						zedGraphControl3->AxisChange();
						zedGraphControl3->Invalidate();
						spike_flag = true;
					}
				}
			}
			spike_flag = false;

			Et = E(t + h, ts, E0, E0Star, alpha);
			E_list->Add(t + h, Et);
			VE->push_back(Et);
			VT->push_back(t + h);

			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------
		//t от T01 - h до T01
		if (backgroundWorker2->CancellationPending)
		{
			e->Cancel = true;
			return;
		}
		t = round(t * 1000) / 1000;
		for (int j = 0; j < n; j++)
		{
			//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
			Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
			Fi[j] = Fiplus1[j];

			if (Fi[j] >= D2PI)                              //В моемент импульса j-го ротатора
			{
				oldE0 = E0;
				E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
				E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
				E0Star += beta;                                //Добавление β к начальному значению производной
				ts = t + h;                                    //Изменение времени последнего спайка
				Fi[j] = 0.0;			                       //Обнуление значения ф					
				k[j]++;                                        //Увеличение числа спайков на 1
				if (!spike_flag)                               //Отбражение нового спайка на графике
				{
					PointPairList^ Spaik_list = gcnew PointPairList();
					Spaik_list->Add(ts, 0.0);
					Spaik_list->Add(ts, 1.0);

					LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

					zedGraphControl3->AxisChange();
					zedGraphControl3->Invalidate();
					spike_flag = true;
				}
			}
		}
		spike_flag = false;

		Et = E(t + h, ts, E0, E0Star, alpha);
		E_list->Add(t + h, Et);
		VE->push_back(Et);
		VT->push_back(t + h);

		for (int l = 0; l < n; l++)
		{
			Fi0[l] = Fi[l];                                     //Запоминание значений фаз при t = T₁
		}

		t += h;
		backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		//---------------------------------------------------
		//t от T01 до T
		for (t; t < T; t += h)
		{
			if (backgroundWorker2->CancellationPending)
			{
				e->Cancel = true;
				return;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				Fiplus1[j] = RK4(t, ts, Fi[j], h, gamma[j], g, E0, E0Star, alpha);
				Fi[j] = Fiplus1[j];

				if (Fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);           //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += beta;                                 //Добавление β к начальному значению производной
					ts = t + h;                                     //Изменение времени последнего спайка
					Fi[j] = 0.0;			                        //Обнуление значения ф						
					k[j]++;                                         //Увеличение числа спайков на 1	
					if (!spike_flag)                                //Отбражение нового спайка на графике
					{
						PointPairList^ Spaik_list = gcnew PointPairList();
						Spaik_list->Add(ts, 0.0);
						Spaik_list->Add(ts, 1.0);

						LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

						zedGraphControl3->AxisChange();
						zedGraphControl3->Invalidate();
						spike_flag = true;
					}
				}
			}
			spike_flag = false;

			Et = E(t + h, ts, E0, E0Star, alpha);
			E_list->Add(t + h, Et);
			VE->push_back(Et);
			VT->push_back(t + h);

			backgroundWorker2->ReportProgress((int)(t / (T - h) * 100));
		}
		//---------------------------------------------------			
	}

	//Вычисление средних частот
	for (i = 0; i < n; i++)         
	{
		//Вычисление значения частоты
		if (k[i] != 0)
		{
			Omega[i] = ((k[i] - 1) * D2PI + Fi[i] - Fi0[i]) / (t - T01); 
		}
		else
		{
			Omega[i] = (Fi[i] - Fi0[i]) / (t - T01);       
		}
		g_list->Add(i, Omega[i]);

		//Вычисление максимальной средней частоты
		if (Omega[i] > MaxOmega)  
		{
			MaxOmega = Omega[i];
		}
		//Вычисление минимальной средней частоты
		if (Omega[i] < MinOmega)  
		{
			MinOmega = Omega[i];
		}

		VO->push_back(Omega[i]);
	}

	NumOfClusters = GetNumberOfClusters(Omega, n);	 //Вычисление числа кластеров при t = T		

													 //Заполнение справки
	Str += "Для вычислений был использован метод Рунге-Кутта 4-го порядка.\r\n";
	Str += "\r\n";
	Str += String::Format(L"γⱼ были взяты из интервала [{0}; {1}]\r\n\r\nЧисло кластеров при t = T:{2}", gamma1, gamma2, NumOfClusters);

	double tmax_limit = t + 0.05;

	//Рисование графиков
	LineItem ^Curve6 = panel2->AddCurve(L"Ωⱼ", g_list, Color::Red, SymbolType::Circle);
	LineItem ^Curve7 = panel4->AddCurve("E(t)", E_list, Color::Red, SymbolType::None);

	Curve6->Line->IsVisible = false;
	Curve6->Symbol->Fill->Color = Color::Red;
	Curve6->Symbol->Fill->Type = FillType::Solid;
	Curve6->Symbol->Size = 6;

	panel2->XAxis->Scale->Min = -1;
	panel2->XAxis->Scale->Max = n;
	panel2->YAxis->Scale->Min = MinOmega - (MaxOmega - MinOmega) / 2;
	panel2->YAxis->Scale->Max = MaxOmega + (MaxOmega - MinOmega) / 2;
	panel2->YAxis->Scale->Min = MinOmega - 0.1;
	panel2->YAxis->Scale->Max = MaxOmega + 0.1;

	panel3->XAxis->Scale->Max = t + 0.05;
	panel3->XAxis->Scale->Min = T02 - 0.05;

	panel4->XAxis->Scale->Max = t + 0.05;
	panel4->XAxis->Scale->Min = T02 - 0.05;

	zedGraphControl2->AxisChange();
	zedGraphControl2->Invalidate();
	zedGraphControl4->AxisChange();
	zedGraphControl4->Invalidate();

	delete[]Fi;
	delete[]Fiplus1;
	delete[]Omega;
	delete[]Fi0;
	delete[]k;

}
private: System::Void backgroundWorker2_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	progressBar2->Value = e->ProgressPercentage;
	label18->Text = "Идут вычисления... " + Convert::ToString(progressBar2->Value) + "%";
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e)
{
	label18->Text = "Идут вычисления... 0%";
	dataGridView1->Rows->Clear();
	dataGridView2->Rows->Clear();
	label18->Visible = true;
	b_Text3->ReadOnly = true;
	h_Text3->ReadOnly = true;
	E0_Text->ReadOnly = true;
	E0Star_Text->ReadOnly = true;
	n_Text3->ReadOnly = true;
	T01_text->ReadOnly = true;
	T02_text->ReadOnly = true;
	g_Text->ReadOnly = true;
	Alpha_Text->ReadOnly = true;
	textBox7->ReadOnly = true;
	button7->Enabled = false;
	button1->Enabled = false;
	comboBox1->Enabled = false;
	comboBox2->Enabled = false;
	backgroundWorker2->RunWorkerAsync();
	button6->Enabled = true;
}
private: System::Void backgroundWorker2_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	for (int i = 0; i < (int)VE->size(); i++)
	{
		dataGridView2->Rows->Add();
		dataGridView2->Rows[i]->Cells[0]->Value = VT->at(i);
		dataGridView2->Rows[i]->Cells[1]->Value = VE->at(i);
	}

	for (int i = 0; i < (int)VO->size(); i++)
	{
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = i;
		dataGridView1->Rows[i]->Cells[1]->Value = VO->at(i);
	}

	VT->clear();
	VE->clear();
	VO->clear();

	textBox2->Text = Str;

	if (e->Cancelled)
	{
		label17->Visible = false;
		MessageBox::Show("Вычисления приостановлены пользователем", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	else
	{
		MessageBox::Show("Вычисления закончены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}

	progressBar2->Value = 0;
	label18->Visible = false;
	n_Text3->ReadOnly = false;
	b_Text3->ReadOnly = false;
	h_Text3->ReadOnly = false;
	E0_Text->ReadOnly = false;
	E0Star_Text->ReadOnly = false;
	T01_text->ReadOnly = false;
	T02_text->ReadOnly = false;
	g_Text->ReadOnly = false;
	Alpha_Text->ReadOnly = false;
	textBox7->ReadOnly = false;
	button7->Enabled = true;
	button1->Enabled = true;
	comboBox1->Enabled = true;
	comboBox2->Enabled = true;
	button6->Enabled = false;
	Change_scale_Omega->Enabled = true;
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
{
	label18->Visible = false;
	label17->Visible = true;
	backgroundWorker2->CancelAsync();
}
private: System::Void backgroundWorker3_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	progressBar3->Value = e->ProgressPercentage;
}
};
}