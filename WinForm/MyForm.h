#pragma once
#include <Windows.h>
#include "Input_structure.h"
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
	public: bool gamma_generated;
	public: bool AvgMaxMinAlreadyExists;
	public: bool GraphsDrawn;
	public: vector<int*> *Clusters_vec;
	public: vector<double**> *Omega_vec;
	public: cli::array<Color> ^Colors;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//									
			gamma_generated = false;
			AvgMaxMinAlreadyExists = false;
			GraphsDrawn = false;
			Clusters_vec = new vector<int*>;
			Omega_vec = new vector<double**>;

			Colors = gcnew cli::array<Color>(5);

			Colors[0] = Color::Red;
			Colors[1] = Color::Green;
			Colors[2] = Color::Blue;
			Colors[3] = Color::Black;
			Colors[4] = Color::Brown;

			zedGraphControl2->GraphPane->Title->Text = L"График средних частот Ωᵢ";
			zedGraphControl2->GraphPane->XAxis->Title->Text = L"i";
			zedGraphControl2->GraphPane->YAxis->Title->Text = L"Ωᵢ";
			zedGraphControl2->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl2->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl3->GraphPane->Title->Text = "График числа спайков";
			zedGraphControl3->GraphPane->XAxis->Title->Text = "t";
			zedGraphControl3->GraphPane->YAxis->Title->Text = "Спайки";
			zedGraphControl3->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl3->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl4->GraphPane->Title->Text = L"График внешнего поля E(t)";
			zedGraphControl4->GraphPane->XAxis->Title->Text = L"t";
			zedGraphControl4->GraphPane->YAxis->Title->Text = L"E(t)";
			zedGraphControl4->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl4->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl6->GraphPane->Title->Text = L"График зависимости средних частот Ωᵢ от различных значений силы связи g";
			zedGraphControl6->GraphPane->XAxis->Title->Text = L"g";
			zedGraphControl6->GraphPane->YAxis->Title->Text = L"Ωᵢ";
			zedGraphControl6->GraphPane->YAxis->MajorGrid->IsVisible = true;
			zedGraphControl6->GraphPane->XAxis->MajorGrid->IsVisible = true;

			zedGraphControl1->GraphPane->Title->Text = L"График зависимости числа кластеров от различных значений силы связи g";
			zedGraphControl1->GraphPane->XAxis->Title->Text = L"g";
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
			if (components)
			{
				delete components;
			}
		}
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
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::TextBox^  Omega1_Text;
	private: System::Windows::Forms::Label^  Omega2;
	private: System::Windows::Forms::Label^  Omega1;
	private: System::Windows::Forms::TextBox^  Omega2_Text;
	private: System::Windows::Forms::Button^  Change_scale_Omega;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  Gamma2_Text;
	private: System::Windows::Forms::Label^  Gamma1;
	private: System::Windows::Forms::TextBox^  Gamma1_Text;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Label^  label14;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::DataGridView^  dataGridView4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
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
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->Gamma2_Text = (gcnew System::Windows::Forms::TextBox());
			this->Gamma1 = (gcnew System::Windows::Forms::Label());
			this->Gamma1_Text = (gcnew System::Windows::Forms::TextBox());
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
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->GShag_Text = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->g2_Text = (gcnew System::Windows::Forms::TextBox());
			this->g1_Text = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->zedGraphControl6 = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->tabPage4->SuspendLayout();
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
			this->tabPage1->Controls->Add(this->label30);
			this->tabPage1->Controls->Add(this->label29);
			this->tabPage1->Controls->Add(this->label28);
			this->tabPage1->Controls->Add(this->label27);
			this->tabPage1->Controls->Add(this->label26);
			this->tabPage1->Controls->Add(this->label25);
			this->tabPage1->Controls->Add(this->dataGridView4);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->checkBox3);
			this->tabPage1->Controls->Add(this->checkBox2);
			this->tabPage1->Controls->Add(this->label14);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->Gamma2_Text);
			this->tabPage1->Controls->Add(this->Gamma1);
			this->tabPage1->Controls->Add(this->Gamma1_Text);
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
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(476, 580);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(781, 24);
			this->label30->TabIndex = 150;
			this->label30->Text = L"T₀₂ - начиная с этого момента времени будут отрисовываться графики E(t) и спайков"
				L"";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(476, 540);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(716, 24);
			this->label29->TabIndex = 149;
			this->label29->Text = L"T₀₁ - φⱼ(T₀₁), j = 0,...,n - 1 будут использованы для вычисления средних частот Ω"
				L"";
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
			this->dataGridView4->Location = System::Drawing::Point(1302, 119);
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->Size = System::Drawing::Size(244, 602);
			this->dataGridView4->TabIndex = 144;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"i";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"γᵢ";
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
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox3->Location = System::Drawing::Point(1324, 84);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(165, 29);
			this->checkBox3->TabIndex = 140;
			this->checkBox3->Text = L"γᵢ ∈ [5,01; 5,1]";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox2->Location = System::Drawing::Point(1324, 49);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(165, 29);
			this->checkBox2->TabIndex = 139;
			this->checkBox2->Text = L"γᵢ ∈ [1,01; 1,1]";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(1284, 10);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(262, 25);
			this->label14->TabIndex = 138;
			this->label14->Text = L"Стандартные диапазоны";
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
			// Gamma2_Text
			// 
			this->Gamma2_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma2_Text->Location = System::Drawing::Point(1100, 70);
			this->Gamma2_Text->Name = L"Gamma2_Text";
			this->Gamma2_Text->ReadOnly = true;
			this->Gamma2_Text->Size = System::Drawing::Size(100, 29);
			this->Gamma2_Text->TabIndex = 136;
			this->Gamma2_Text->Text = L"1,1";
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
			// Gamma1_Text
			// 
			this->Gamma1_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma1_Text->Location = System::Drawing::Point(890, 70);
			this->Gamma1_Text->Name = L"Gamma1_Text";
			this->Gamma1_Text->ReadOnly = true;
			this->Gamma1_Text->Size = System::Drawing::Size(100, 29);
			this->Gamma1_Text->TabIndex = 134;
			this->Gamma1_Text->Text = L"1,01";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(820, 10);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(446, 25);
			this->label9->TabIndex = 133;
			this->label9->Text = L"Задайте диапазон изменения параметра γᵢ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(461, 426);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(77, 29);
			this->label8->TabIndex = 119;
			this->label8->Text = L" T₀₂ = ";
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
			this->label5->Location = System::Drawing::Point(461, 391);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(77, 29);
			this->label5->TabIndex = 117;
			this->label5->Text = L" T₀₁ = ";
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
			this->label7->Text = L"Ẽ₀ = ";
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
			this->label3->Location = System::Drawing::Point(474, 496);
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
			this->Alpha_Text->Text = L"0,6";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(475, 461);
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
			this->g_Text->Text = L"6";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(81, 6);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(507, 222);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 104;
			this->pictureBox1->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(685, 323);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(384, 172);
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
			this->textBox1->Size = System::Drawing::Size(100, 29);
			this->textBox1->TabIndex = 91;
			this->textBox1->Text = L"400000";
			// 
			// button7
			// 
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
			this->dataGridViewTextBoxColumn1->HeaderText = L"i";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->Width = 200;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Ωᵢ";
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
			this->zedGraphControl3->Location = System::Drawing::Point(0, 351);
			this->zedGraphControl3->Name = L"zedGraphControl3";
			this->zedGraphControl3->ScrollGrace = 0;
			this->zedGraphControl3->ScrollMaxX = 0;
			this->zedGraphControl3->ScrollMaxY = 0;
			this->zedGraphControl3->ScrollMaxY2 = 0;
			this->zedGraphControl3->ScrollMinX = 0;
			this->zedGraphControl3->ScrollMinY = 0;
			this->zedGraphControl3->ScrollMinY2 = 0;
			this->zedGraphControl3->Size = System::Drawing::Size(1103, 370);
			this->zedGraphControl3->TabIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->label15);
			this->tabPage4->Controls->Add(this->progressBar1);
			this->tabPage4->Controls->Add(this->button5);
			this->tabPage4->Controls->Add(this->textBox4);
			this->tabPage4->Controls->Add(this->button4);
			this->tabPage4->Controls->Add(this->textBox3);
			this->tabPage4->Controls->Add(this->GShag_Text);
			this->tabPage4->Controls->Add(this->label12);
			this->tabPage4->Controls->Add(this->label11);
			this->tabPage4->Controls->Add(this->label4);
			this->tabPage4->Controls->Add(this->g2_Text);
			this->tabPage4->Controls->Add(this->g1_Text);
			this->tabPage4->Controls->Add(this->button2);
			this->tabPage4->Controls->Add(this->label22);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1562, 903);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Серия экспериментов";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(944, 426);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(212, 24);
			this->label15->TabIndex = 155;
			this->label15->Text = L"Идут вычисления... 0%";
			this->label15->Visible = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(847, 381);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(390, 31);
			this->progressBar1->TabIndex = 154;
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(971, 173);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(140, 67);
			this->button5->TabIndex = 153;
			this->button5->Text = L"Вычислить min, max и avg";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(1114, 337);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(29, 29);
			this->textBox4->TabIndex = 152;
			this->textBox4->Text = L"0";
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(1117, 174);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(126, 66);
			this->button4->TabIndex = 151;
			this->button4->Text = L"Очистить графики";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
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
			this->textBox3->Size = System::Drawing::Size(655, 713);
			this->textBox3->TabIndex = 148;
			// 
			// GShag_Text
			// 
			this->GShag_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->GShag_Text->Location = System::Drawing::Point(1013, 297);
			this->GShag_Text->Name = L"GShag_Text";
			this->GShag_Text->Size = System::Drawing::Size(57, 29);
			this->GShag_Text->TabIndex = 7;
			this->GShag_Text->Text = L"0,5";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(922, 300);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(86, 24);
			this->label12->TabIndex = 6;
			this->label12->Text = L"Шаг по g";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(1070, 259);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(38, 24);
			this->label11->TabIndex = 5;
			this->label11->Text = L"g₂=";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(904, 262);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 24);
			this->label4->TabIndex = 4;
			this->label4->Text = L"g₁=";
			// 
			// g2_Text
			// 
			this->g2_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g2_Text->Location = System::Drawing::Point(1114, 256);
			this->g2_Text->Name = L"g2_Text";
			this->g2_Text->Size = System::Drawing::Size(57, 29);
			this->g2_Text->TabIndex = 3;
			this->g2_Text->Text = L"6";
			// 
			// g1_Text
			// 
			this->g1_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->g1_Text->Location = System::Drawing::Point(948, 259);
			this->g1_Text->Name = L"g1_Text";
			this->g1_Text->Size = System::Drawing::Size(57, 29);
			this->g1_Text->TabIndex = 2;
			this->g1_Text->Text = L"0";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(833, 173);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 66);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Добавить набор ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(858, 337);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(250, 24);
			this->label22->TabIndex = 149;
			this->label22->Text = L"Число различных наборов:";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->zedGraphControl6);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1562, 903);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Средние частоты для серии";
			this->tabPage5->UseVisualStyleBackColor = true;
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
			this->tabPage6->Controls->Add(this->zedGraphControl1);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(1562, 903);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Число кластеров для серии";
			this->tabPage6->UseVisualStyleBackColor = true;
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
			this->zedGraphControl1->Size = System::Drawing::Size(1564, 740);
			this->zedGraphControl1->TabIndex = 148;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
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
			this->tabPage5->ResumeLayout(false);
			this->tabPage6->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		public:static void Calculate(Int64 i)
		{
			//Здесь итерации цикла
		}

	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
	{				
		if (!gamma_generated)
		{
			MessageBox::Show(L"Набор γ еще не сгенерирован", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		GraphPane^ panel2 = zedGraphControl2->GraphPane;		
		GraphPane^ panel4 = zedGraphControl4->GraphPane;
		GraphPane^ panel3 = zedGraphControl3->GraphPane;
		
		panel2->CurveList->Clear();
		panel3->CurveList->Clear();
		panel4->CurveList->Clear();		

		panel2->YAxis->Scale->MajorStepAuto = true;
		panel2->YAxis->Scale->MinorStepAuto = true;		
	
		PointPairList^ g_list = gcnew PointPairList();        //Список точек для графика средних частот Ω
		PointPairList^ E_list = gcnew PointPairList();	      //Список точек для графика поля E(t)
		PointPairList^ Spaik_list = gcnew PointPairList();
		
		int n = Convert::ToInt32(n_Text3->Text);              //Число уравнений в системе
		double h = Convert::ToDouble(h_Text3->Text);          //Шаг
		int p = Convert::ToInt32(textBox1->Text);             //Число итераций, второй критерий остановки
		double T = Convert::ToDouble(b_Text3->Text);          //Максимальное время, до которого будет подсчет, первый критерий остановки
		double T01 = Convert::ToDouble(T01_text->Text);       //Начальное время, от которого будет считаться частота
		double T02 = Convert::ToDouble(T02_text->Text);       //Начальное время, от которого будут рисоваться график E(t) и график числа спайков
		double g = Convert::ToDouble(g_Text->Text);           //Коэффициент связи
		double alpha = Convert::ToDouble(Alpha_Text->Text);   //Число α
		double E0 = Convert::ToDouble(E0_Text->Text);         //Начальное условие для E
		double E0Star = Convert::ToDouble(E0Star_Text->Text); //Начальное условие для Ė
		int *k;                                               //Число спайков для каждого ротатора  
		int it = 0;                                           //Индекс строк в таблице
		int NumOfClusters;                                    //Число кластеров при t = T
		double t = 0.0;                                       //Текущее время       
		double Et;                                            //Поле E(t)
		double *Fi0;		                                  //Фазы при t = T₀₁
		double *v, *vplus1;	                                  //Фазы φⱼ(t) j = 0,...,n - 1
		double *Omega;                                        //Средние частоты Ω
		double MaxOmega = -100000.0, MinOmega = 100000.0;     //Максимальная и минимальная средние частоты 		
		String ^str = "";                                     //Строка для вывода справочных сведений

		//Технические переменные, используемые для расчетов 
		int ind = 0;
		int i;
		double oldE0;		
		bool flag1 = false;
		bool spike_flag = false;
		
		v = new double[n];           
		vplus1 = new double[n];		 
		Omega = new double[n];       
		Fi0 = new double[n];
		k = new int[n];

		double ts = 0.0; //Время последнего спайка				

		double tmin_limit = t - 0.05;

		for (i = 0; i < n; i++)                //Начальные условия для каждого из φⱼ(t) равны нулю
		{
			v[i] = vplus1[i] = 0.0;			                      
			k[i] = 0;                          //Изначальное число спайков равно нулю
		}			

		dataGridView1->Rows->Clear();
		dataGridView2->Rows->Clear();

		//Основной цикл: Вычисление φⱼ(t) методом Рунге-Кутта 4-го порядка
		for (i = 1; ((i < p) && (t < T)); i++)         
		{					
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				vplus1[j] = RK4(t, ts, v[j], h, gamma[j], g, E0, E0Star, alpha); 
				v[j] = vplus1[j];

				if (v[j] >= 2 * M_PI)                           //В моемент импульса j-го ротатора
				{				                 
				    oldE0 = E0;
					E0 = E(xInc(t, h), ts, E0, E0Star, alpha);           //Пересчет начальных условий
					E0Star = dEdt(xInc(t, h), ts, oldE0, E0Star, alpha);
					E0Star += (alpha*alpha) / n;                //Добавление α²/n к начальному значению производной
					ts = xInc(t, h);                            //Изменение времени последнего спайка
					v[j] = 0.0;			                        //Обнуление значения ф
					if (xInc(t, h) >= T01)
					{
						k[j]++;                                 //Увеличение числа спайков на 1
					}
					if ((ts >= T02)&&(!spike_flag))             //Отбражение нового спайка на графике
					{						
						Spaik_list->Clear();
						Spaik_list->Add(ts, 0.0);
						Spaik_list->Add(ts, 1.0);

						LineItem ^Curve7 = panel3->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

						zedGraphControl3->AxisChange();
						zedGraphControl3->Invalidate();
						spike_flag = true;
					}
				}
			}
			t = xInc(t, h);                    //Увеличение времени на h
			spike_flag = false;			

			if (t >= T02)                      //Заполнение таблицы точек для вывода графика E(t) 
			{
				Et = E(t, ts, E0, E0Star, alpha);
				E_list->Add(t, Et);

				//Заполнение таблицы E(t)
				dataGridView2->Rows->Add();    
				dataGridView2->Rows[ind]->Cells[0]->Value = t; 
				dataGridView2->Rows[ind]->Cells[1]->Value = Et;
				ind++;
			}
		
			if ((t == T01)||((t > T01)&&(t - T01 < h*0.5))||(T01 == 0.0))  //Запоминание начальных значений ф для частоты Ω
			{
				flag1 = true;			

			for (int l = 0; l < n; l++)
				{
					Fi0[l] = v[l];   //Запоминание значений фаз при t = T₀₁
				}
			}
		}		
		
		if (flag1 == true)
		{
			for (i = 0; i < n; i++)         //Вычисление частоты для всех ротаторов, заполнение таблицы
			{
				Omega[i] = ((k[i] - 1) * 2 * M_PI + v[i] - Fi0[i]) / (t - T01); //Вычисление значения частоты
				g_list->Add(i, Omega[i]);			

				if (Omega[i] > MaxOmega)  //Вычисление максимальной средней частоты
				{
					MaxOmega = Omega[i];
				}
				if (Omega[i] < MinOmega)  //Вычисление минимальной средней частоты
				{
					MinOmega = Omega[i];
				}
				
				//Добавление значения частоты в таблицу
				dataGridView1->Rows->Add();     
				dataGridView1->Rows[i]->Cells[0]->Value = i;
				dataGridView1->Rows[i]->Cells[1]->Value = Omega[i];
			}
		}

		NumOfClusters = GetNumberOfClusters(Omega, n);	 //Вычисление числа кластеров при t = T		

//Заполнение справки
str += "Для вычислений был использован метод Рунге-Кутта 4-го порядка.\r\n";
str += "\r\n";
str += L"γᵢ были взяты из интервала [";
str += Convert::ToString(gamma1);
str += "; ";
str += Convert::ToString(gamma2);
str += "]\r\n";
str += "\r\n";
str += "Число кластеров при t = T:";
str += Convert::ToString(NumOfClusters);

textBox2->Text = str;

double tmax_limit = t + 0.05;

//Рисование графиков
LineItem ^Curve6 = panel2->AddCurve(L"Ωᵢ", g_list, Color::Red, SymbolType::Circle);
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

delete[]v;
delete[]vplus1;
delete[]Omega;
delete[]Fi0;
delete[]k;

n_Text3->ReadOnly = false;
	}

private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	GraphPane ^panel = zedGraphControl6->GraphPane;
	GraphPane ^panel2 = zedGraphControl1->GraphPane;

	panel->YAxis->Type = AxisType::Log;

	PointPairList ^Cl_list = gcnew PointPairList();

	gamma1 = Convert::ToDouble(Gamma1_Text->Text);
	gamma2 = Convert::ToDouble(Gamma2_Text->Text);
	int n = Convert::ToInt32(n_Text3->Text);
	double g1 = Convert::ToDouble(g1_Text->Text);         //Начальное значение g
	double g2 = Convert::ToDouble(g2_Text->Text);         //Конечное значение g
	double gh = Convert::ToDouble(GShag_Text->Text);      //Шаг по g
	double **Omega = new double*[n];                      //Двумерный массив для хранения средних частот
	int *NumOfClusters;                                   //Массив для хранения числа кластеров
	double *om = new double[n];                           //Технический массив для вычислений 
	double *v = new double[n];                            //Фазы φⱼ(t) j = 0,...,n - 1
	double *vplus1 = new double[n];                       //Фазы φⱼ(t) j = 0,...,n - 1
	double h = Convert::ToDouble(h_Text3->Text);          //Шаг интегрирования
	int *k = new int[n];                                  //Число спайков для каждого ротатора
	double t = 0.0;                                       //Время
	double T01 = Convert::ToDouble(T01_text->Text);       //Начальное время, от которого будет считаться частота
	double *Fi0 = new double[n];                          //Фазы при t = T₀₁
	double T = Convert::ToDouble(b_Text3->Text);          //Максимальное время, до которого будет подсчет, первый критерий остановки
	double E0 = Convert::ToDouble(E0_Text->Text);         //Начальное условие для E    
	double E0Star = Convert::ToDouble(E0Star_Text->Text); //Начальное условие для Ė
	int p = Convert::ToInt32(textBox1->Text);             //Число итераций, второй критерий остановки
	int non = 0;                                          //Число точек на графике, в которых считаются средние частоты 
	double alpha = Convert::ToDouble(Alpha_Text->Text);   //Число α
	int NumOfSets = Convert::ToInt32(textBox4->Text);
	double *cur_gamma = Set_Gamma(n, gamma1, gamma2);     //Задаем новый набор γⱼ

	//Технические переменные, используемые для расчетов
	int index = 0;
	double oldE0;
	bool flag1 = false;

	cli::array<PointPairList^> ^Omega_List = gcnew cli::array<PointPairList^>(n);

	for (int i = 0; i < n; i++)
	{
		Omega_List[i] = gcnew PointPairList();
	}

	double ts = 0.0;

	panel->XAxis->Scale->Min = g1 - 0.1;
	panel->XAxis->Scale->Max = g2 + 0.1;
	panel->XAxis->Scale->MajorStep = gh;
	panel->XAxis->Scale->MinorStep = gh / 5;
	panel2->XAxis->Scale->Min = g1 - 0.1;
	panel2->XAxis->Scale->Max = g2 + 0.1;
	panel2->YAxis->Scale->MajorStep = 2;
	panel2->YAxis->Scale->MinorStep = 1;
	panel2->XAxis->Scale->MajorStep = gh;
	panel2->XAxis->Scale->MinorStep = gh / 5;

	//Вычисляем количество вершин в графе
	for (double g = g1; g <= g2; g = g + gh)
	{
		g = round(g * 1000) / 1000;
		non++;
	}

	NumOfClusters = new int[non];
	for (int i = 0; i < n; i++)
	{
		Omega[i] = new double[non];
	}

	//Начальное значение φⱼ(0) и число спайков равно 0
	for (int i = 0; i < n; i++)
	{
		v[i] = vplus1[i] = 0.0;
		k[i] = 0;
	}
	//Вычисляем φⱼ(t) методом Рунге-Кутта 4-го порядка
	for (double g = g1; g <= g2; g = g + gh)
	{
		g = round(g * 1000) / 1000;		
		for (int i = 1; ((i < p) && ((t < T))); i++)
		{
			t = round(t * 1000) / 1000;
			for (int j = 0; j < n; j++)
			{
				vplus1[j] = RK4(t, ts, v[j], h, cur_gamma[j], g, E0, E0Star, alpha);
				v[j] = vplus1[j];

				if (v[j] >= 2 * M_PI)
				{
					oldE0 = E0;
					E0 = E(xInc(t, h), ts, E0, E0Star, alpha);
					E0Star = dEdt(xInc(t, h), ts, oldE0, E0Star, alpha);
					E0Star += (alpha*alpha) / n;
					ts = xInc(t, h);
					v[j] = 0.0;
					if (xInc(t, h) >= T01)
					{
						k[j]++;
					}
				}
			}
			t = xInc(t, h);

			//Запоминаем начальные значения φⱼ(T₀₁)
			if ((t == T01) || ((t > T01) && (t - T01 < h*0.5)) || (T01 == 0.0))
			{
				flag1 = true;

				for (int l = 0; l < n; l++)
				{
					Fi0[l] = v[l];
				}
			}
		}

		//Вычисление средних частот Ω
		if (flag1 == true)
		{
			for (int i = 0; i < n; i++)
			{
				Omega[i][index] = ((k[i] - 1) * 2 * M_PI + v[i] - Fi0[i]) / (t - T01);
				om[i] = Omega[i][index];
			}
		}

		//Вычисление числа кластеров
		NumOfClusters[index] = GetNumberOfClusters(om, n);

		index++;

		//Обнуление переменных для повторного счета при другом значении силы связи g
		t = 0.0;
		ts = 0.0;
		flag1 = false;
		E0 = Convert::ToDouble(E0_Text->Text);
		E0Star = Convert::ToDouble(E0Star_Text->Text);

		for (int i = 0; i < n; i++)
		{
			v[i] = vplus1[i] = 0.0;
			k[i] = 0;
		}
		backgroundWorker1->ReportProgress((int)((float)(g - g1) / (g2 - g1) * 100));
	}

	Omega_vec->push_back(Omega);
	Clusters_vec->push_back(NumOfClusters);

	double _g = g1;

	//Рисование графиков
	for (int i = 0; i < n; i++)
	{
		_g = g1;
		for (int j = 0; j < non; j++)
		{
			Omega_List[i]->Add(_g, Omega[i][j]);
			if (_g <= g2)
			{
				_g += gh;
				_g = round(_g * 1000) / 1000;
			}
		}
		LineItem ^Curve;
		Curve = panel->AddCurve(Convert::ToString(NumOfSets), Omega_List[i], Colors[NumOfSets - 1], SymbolType::Circle);
		Curve->Symbol->Fill->Color = Colors[NumOfSets - 1];
		Curve->Symbol->Size = 8.0f;
		Curve->Symbol->Fill->Type = FillType::Solid;
		if (i > 0)
		{
			Curve->Label->Text = String::Empty;
		}
	}

	zedGraphControl6->AxisChange();
	zedGraphControl6->Invalidate();

	_g = g1;

	for (int i = 0; i < non; i++)
	{
		Cl_list->Add(_g, NumOfClusters[i]);
		_g += gh;
		_g = round(_g * 1000) / 1000;
	}
	LineItem ^Curve2;
	Curve2 = panel2->AddCurve(Convert::ToString(NumOfSets), Cl_list, Colors[NumOfSets - 1], SymbolType::Circle);
	Curve2->Symbol->Fill->Color = Colors[NumOfSets - 1];
	Curve2->Symbol->Fill->Type = FillType::Solid;
	Curve2->Line->IsVisible = false;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();

	//Освобождение памяти
	delete[]cur_gamma;
	delete[]om;
	delete[]v;
	delete[]vplus1;
	delete[]k;
	delete[]Fi0;
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
{

	Int32 NumOfSets = Convert::ToInt32(textBox4->Text);

	if (NumOfSets == 5)
	{
		MessageBox::Show("Достигнуто максимальное число наборов", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	NumOfSets++;
	textBox4->Text = Convert::ToString(NumOfSets);
	g1_Text->ReadOnly = true;
	g2_Text->ReadOnly = true;
	GShag_Text->ReadOnly = true;
	label15->Visible = true;

	backgroundWorker1->RunWorkerAsync();

	GraphsDrawn = true;
	
	n_Text3->ReadOnly = false;
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
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (checkBox2->Checked)
	{
		Gamma1_Text->ReadOnly = true;
		Gamma2_Text->ReadOnly = true;
		Gamma1_Text->Text = "1,01";
		Gamma2_Text->Text = "1,1";
	}
	else
	{
		Gamma1_Text->ReadOnly = false;
		Gamma2_Text->ReadOnly = false;
	}
}
private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (checkBox3->Checked)
	{
		Gamma1_Text->ReadOnly = true;
		Gamma2_Text->ReadOnly = true;
		Gamma1_Text->Text = "5,01";
		Gamma2_Text->Text = "5,1";
	}
	else
	{
		Gamma1_Text->ReadOnly = false;
		Gamma2_Text->ReadOnly = false;
	}
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	dataGridView4->Rows->Clear();

	int n = Convert::ToInt32(n_Text3->Text);
	gamma1 = Convert::ToDouble(Gamma1_Text->Text);
	gamma2 = Convert::ToDouble(Gamma2_Text->Text);
	gamma = new double[n];
	gamma = Set_Gamma(n, gamma1, gamma2);
	//qsort((void *)gamma, (size_t)n, sizeof(double), compare);

	dataGridView4->Rows->Add(n);

	for (int i = 0; i < n; i++)
	{
		dataGridView4->Rows[i]->Cells[0]->Value = i;
		dataGridView4->Rows[i]->Cells[1]->Value = gamma[i];
	}

	gamma_generated = true;
	n_Text3->ReadOnly = true;
	MessageBox::Show("Набор сгенерирован", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (!GraphsDrawn)
	{
		MessageBox::Show("Графики еще не построены", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	zedGraphControl6->GraphPane->CurveList->Clear();
	zedGraphControl1->GraphPane->CurveList->Clear();
	textBox4->Text = "0";
	g1_Text->ReadOnly = false;
	g2_Text->ReadOnly = false;
	GShag_Text->ReadOnly = false;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
	zedGraphControl6->AxisChange();
	zedGraphControl6->Invalidate();

	Omega_vec->clear();
	Clusters_vec->clear();
	textBox3->Text = String::Empty;

	MessageBox::Show("Графики очищены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
}
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	progressBar1->Value = e->ProgressPercentage;
	label15->Text = "Идут вычисления... " + Convert::ToString(progressBar1->Value) + "%";
}
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
	MessageBox::Show("Вычисления закончены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	progressBar1->Value = 0;
	label15->Visible = false;
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (!GraphsDrawn)
	{
		MessageBox::Show("Графики еще не построены", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	int n = Convert::ToInt32(n_Text3->Text);
	int NumOfSets = Convert::ToInt32(textBox4->Text);
	GraphPane ^panel = zedGraphControl6->GraphPane;
	GraphPane ^panel2 = zedGraphControl1->GraphPane;
	double g1 = Convert::ToDouble(g1_Text->Text);         //Начальное значение g
	double g2 = Convert::ToDouble(g2_Text->Text);         //Конечное значение g
	double gh = Convert::ToDouble(GShag_Text->Text);      //Шаг по g
	String ^str = L"Ω:\r\n";
	double** curOmega;
	double* om;
	int* curClusters;

	PointPairList ^AvgOmList = gcnew PointPairList();
	PointPairList ^AvgClusList = gcnew PointPairList();
	PointPairList ^MinMaxOmList = gcnew PointPairList();
	PointPairList ^MinMaxClusList = gcnew PointPairList();

	int non = 0;
	int index;
	int k = 0;
	int m = 0;

	for (double g = g1; g <= g2; g = g + gh)
	{
		g = round(g * 1000) / 1000;
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
		textBox3->Text = String::Empty;

		for (int i = 0; i < 2; i++)
		{
			panel->CurveList->RemoveAt(i);
			panel2->CurveList->RemoveAt(i);
		}
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

	double g = g1;
	for (int i = 0; i < non; i++)
	{
		double MaxOmega, MinOmega;		

		FindMinMax(2 * NumOfSets, MinMaxOm[i], &MinOmega, &MaxOmega);

		MinMaxOmList->Add(g, MinOmega, MaxOmega);
		AvgOmList->Add(g, (MinOmega + MaxOmega)*0.5);

		str += "g = ";
		str += Convert::ToString(g);
		str += "; Min = ";
		str += Convert::ToString(round(MinOmega * 10000) / 10000);
		str += ", Max = ";
		str += Convert::ToString(round(MaxOmega * 10000) / 10000);
		str += ", Avg = ";
		str += Convert::ToString(round((MinOmega + MaxOmega)*0.5 * 10000) / 10000);		
		str += "\r\n";

		g += gh;
	}

	str += "\r\nКластеры:\r\n";

	g = g1;

	for (int i = 0; i < non; i++)
	{
		int MaxClus, MinClus;

		FindMinMax(NumOfSets, MinMaxClus[i], &MinClus, &MaxClus);

		MinMaxClusList->Add(g, MinClus, MaxClus);
		AvgClusList->Add(g, (int)((MinClus + MaxClus)*0.5));

		str += "g = ";
		str += Convert::ToString(g);
		str += ";  Min = ";
		str += Convert::ToString(round(MinClus * 10000) / 10000);
		str += ", Max = ";
		str += Convert::ToString(round(MaxClus * 10000) / 10000);
		str += ", Avg = ";
		str += Convert::ToString((int)(round((MinClus + MaxClus)*0.5 * 10000) / 10000));
		str += "\r\n";

		g += gh;
	}

	str += "\r\n";
	str += L"γᵢ были взяты из интервала [";
	str += Convert::ToString(gamma1);
	str += "; ";
	str += Convert::ToString(gamma2);
	str += "]\r\n";

	textBox3->Text = str;

	LineItem ^Curve = panel->AddCurve("Среднее значение", AvgOmList, Color::DarkOrange, SymbolType::Diamond);
	LineItem ^Curve2 = panel2->AddCurve("Среднее значение", AvgClusList, Color::DarkOrange, SymbolType::Diamond);
	ErrorBarItem ^ErrorBar = panel->AddErrorBar("Min и Max", MinMaxOmList, Color::DarkOrange);
	ErrorBarItem ^ErrorBar2 = panel2->AddErrorBar("Min и Max", MinMaxClusList, Color::DarkOrange);

	Curve->Symbol->Fill->Color = Color::DarkOrange;
	Curve->Line->IsVisible = false;
	Curve->Symbol->Size = 16.0f;
	Curve->Symbol->Fill->Type = FillType::Solid;

	Curve2->Symbol->Fill->Color = Color::DarkOrange;
	Curve2->Line->IsVisible = false;
	Curve2->Symbol->Size = 10.0f;
	Curve2->Symbol->Fill->Type = FillType::Solid;

	panel->CurveList->Move(panel->CurveList->Count - 1, -9999);
	panel->CurveList->Move(panel->CurveList->Count - 1, -10000);
	panel2->CurveList->Move(panel2->CurveList->Count - 1, -9999);
	panel2->CurveList->Move(panel2->CurveList->Count - 1, -10000);
		
	zedGraphControl1->Invalidate();
	zedGraphControl6->Invalidate();

	for (int i = 0; i < non; i++)
	{
		delete[]MinMaxOm[i];
		delete[]MinMaxClus[i];
	}
}
};
}