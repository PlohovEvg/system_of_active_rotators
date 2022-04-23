#pragma once
#include <Windows.h>
#include "Calculating_functions.h"

namespace WinForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Threading::Tasks;
	using namespace System::IO;
	using namespace ZedGraph;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: double* gamma;    //Параметры γⱼ

	public: double gamma1;    //Левая граница γ₁

	public: double gamma2;    //Правая граница γ₂

	public: bool AvgMaxMinAlreadyExists;

	public: vector<int*>* Clusters_vec;

	public: vector<double**>* Omega_vec;

	public: cli::array<Color>^ Colors;

	public: String^ Str;

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//									
			AvgMaxMinAlreadyExists = false;
			Clusters_vec = new vector<int*>;
			Omega_vec = new vector<double**>;

			Str = "";
			gamma = NULL;

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

			OmegaGraph->GraphPane->Title->Text = L"График средних частот Ωⱼ";
			OmegaGraph->GraphPane->XAxis->Title->Text = L"j";
			OmegaGraph->GraphPane->YAxis->Title->Text = L"Ωⱼ";
			OmegaGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			OmegaGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;
			OmegaGraph->GraphPane->YAxis->Scale->MaxAuto = false;
			OmegaGraph->GraphPane->YAxis->Scale->MinAuto = false;
			OmegaGraph->GraphPane->YAxis->Scale->MinorStepAuto = false;
			OmegaGraph->GraphPane->YAxis->Scale->MajorStepAuto = false;
			OmegaGraph->GraphPane->YAxis->Scale->Max = (double)MaxOmegaNUD->Value + (double)MaxOmegaNUD->Value * 0.01;
			OmegaGraph->GraphPane->YAxis->Scale->MajorStep = OmegaGraph->GraphPane->YAxis->Scale->Max * 0.01;
			OmegaGraph->GraphPane->YAxis->Type = AxisType::Log;

			PhasesGraph->GraphPane->Title->Text = L"График фаз φⱼ(T) в конечный момент времени";
			PhasesGraph->GraphPane->XAxis->Title->Text = L"j";
			PhasesGraph->GraphPane->YAxis->Title->Text = L"φⱼ(T)";
			PhasesGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			PhasesGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			SpikesGraph->GraphPane->Title->Text = "График числа возникновения спайков в разные моменты времени";
			SpikesGraph->GraphPane->XAxis->Title->Text = "t";
			SpikesGraph->GraphPane->YAxis->Title->Text = "";
			SpikesGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			SpikesGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			E_fieldGraph->GraphPane->Title->Text = "График внешнего поля E(t)";
			E_fieldGraph->GraphPane->XAxis->Title->Text = L"t";
			E_fieldGraph->GraphPane->YAxis->Title->Text = L"E(t)";
			E_fieldGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			E_fieldGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			PhSyncParamGraph->GraphPane->Title->Text = L"График изменения модуля параметра фазовой синхронизации |μ| со временем";
			PhSyncParamGraph->GraphPane->XAxis->Title->Text = "t";
			PhSyncParamGraph->GraphPane->YAxis->Title->Text = L"|μ|";
			PhSyncParamGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			PhSyncParamGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			OmegaBetaGraph->GraphPane->Title->Text = L"График зависимости средних частот Ωⱼ от параметра β";
			OmegaBetaGraph->GraphPane->XAxis->Title->Text = L"β";
			OmegaBetaGraph->GraphPane->YAxis->Title->Text = L"Ωⱼ";
			OmegaBetaGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			OmegaBetaGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;
			OmegaBetaGraph->GraphPane->YAxis->Type = AxisType::Log;
			OmegaBetaGraph->GraphPane->YAxis->Scale->Min = 0.0;
			OmegaBetaGraph->GraphPane->YAxis->Scale->Max = Convert::ToDouble(MaxOmegaNUD->Text->Replace(".", ","));

			BetaCrNGraph->GraphPane->Title->Text = L"График изменения параметра β⃰ от числа элементов N";
			BetaCrNGraph->GraphPane->XAxis->Title->Text = "N";
			BetaCrNGraph->GraphPane->YAxis->Title->Text = L"β⃰";
			BetaCrNGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			BetaCrNGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			MaxMuBetaGraph->GraphPane->Title->Text = L"График зависимости max|μ(t)| от параметра β";
			MaxMuBetaGraph->GraphPane->XAxis->Title->Text = L"β";
			MaxMuBetaGraph->GraphPane->YAxis->Title->Text = L"max|μ(t)|";
			MaxMuBetaGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			MaxMuBetaGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			ClustersCountBetaGraph->GraphPane->Title->Text = L"График зависимости числа кластеров от параметра β";
			ClustersCountBetaGraph->GraphPane->XAxis->Title->Text = L"β";
			ClustersCountBetaGraph->GraphPane->YAxis->Title->Text = L"Кол-во кластеров";
			ClustersCountBetaGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			ClustersCountBetaGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;

			FreqSyncGraph->GraphPane->Title->Text = FreqSyncGraphTitle;
			FreqSyncGraph->GraphPane->XAxis->Title->Text = L"β";
			FreqSyncGraph->GraphPane->YAxis->Title->Text = L"χ";
			FreqSyncGraph->GraphPane->YAxis->MajorGrid->IsVisible = true;
			FreqSyncGraph->GraphPane->XAxis->MajorGrid->IsVisible = true;
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
	private: static String^ FreqSyncGraphTitle = L"График зависимости параметра частотной синхронизации χ от параметра β";
	private: System::Windows::Forms::Button^ LoadSetFromFileBtn;
	private: System::Windows::Forms::Button^ SaveSetToFileBtn;
	private: System::Windows::Forms::Panel^ OmegaPan;
	private: System::Windows::Forms::Button^ ClearOmegaGraphBtn;
	private: System::Windows::Forms::CheckBox^ ShowMaxMinCB;
	private: System::Windows::Forms::TextBox^ Omega1TB;
	private: System::Windows::Forms::Label^ Omega2;
	private: System::Windows::Forms::Label^ Omega1;
	private: System::Windows::Forms::TextBox^ Omega2TB;
	private: System::Windows::Forms::Button^ Change_scale_Omega;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::RadioButton^ radioButton4;
	private: System::Windows::Forms::TextBox^ OffsetTB;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::NumericUpDown^ MaxOmegaNUD;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TabPage^ tabPage8;
	private: System::Windows::Forms::Panel^ FreqSyncPanel;
	private: System::Windows::Forms::Button^ FreqSyncClearGraphBtn;
	private: System::Windows::Forms::Button^ FreqSyncStartBtn;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Button^ FreqSyncCancelBtn;
	private: System::Windows::Forms::TextBox^ FreqSyncBetaStepTB;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::Label^ label45;
	private: System::Windows::Forms::TextBox^ FreqSyncBeta1TB;
	private: System::Windows::Forms::TextBox^ FreqSyncBeta2TB;
	private: ZedGraph::ZedGraphControl^ FreqSyncGraph;
	private: System::Windows::Forms::ProgressBar^ FreqSyncProgBar;
	private: System::Windows::Forms::Label^ FreqSyncProgressLabel;
	private: System::ComponentModel::BackgroundWorker^ FreqSyncBW;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::GroupBox^ IntegrParams;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ IterationsTB;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::TextBox^ T_TB;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::TextBox^ hTB;
	private: System::Windows::Forms::GroupBox^ SystemParams;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ T02_text;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ T1_TB;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ E0Star_Text;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ E0_Text;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ AlphaTB;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ gTB;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::TextBox^ nTB;

	private: System::Windows::Forms::DataGridView^ TPhaseTable;
	private: System::Windows::Forms::DataGridView^ TimeOfSpikesTable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Time;
	private: System::Windows::Forms::TabPage^  tabPage9;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::ProgressBar^  progressBar4;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker4;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label35;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker5;
	private: System::Windows::Forms::Label^  label36;


	private: ZedGraph::ZedGraphControl^  PhasesGraph;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::ProgressBar^  progressBar5;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::Label^  label40;
	private: System::Windows::Forms::Label^  label41;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker6;
	private: ZedGraph::ZedGraphControl^  MaxMuBetaGraph;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TabPage^  tabPage7;
	private: System::Windows::Forms::Label^  label9;
	private: ZedGraph::ZedGraphControl^  BetaCrNGraph;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: ZedGraph::ZedGraphControl^  PhSyncParamGraph;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::ProgressBar^  progressBar3;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker3;
	private: System::Windows::Forms::ComboBox^ DeltaCmbB;
	private: System::Windows::Forms::ComboBox^ Gamma0CmbB;
	private: System::Windows::Forms::ComboBox^  Gamma2MaxTB;
	private: System::Windows::Forms::ComboBox^  Gamma1MinTB;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  StopCalculationsLbl;
	private: System::Windows::Forms::Button^ StopBtn;
	private: System::Windows::Forms::Label^  SingleCalculationProgressLbl;
	private: System::Windows::Forms::ProgressBar^  progressBar2;
	private: System::ComponentModel::BackgroundWorker^  SingleCalculationBW;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TabPage^  tabPage6;
	private: ZedGraph::ZedGraphControl^  ClustersCountBetaGraph;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  GammaSetsCountTB;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  BetaStepTB;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  Beta2TB;
	private: System::Windows::Forms::TextBox^  Beta1TB;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label22;
	private: ZedGraph::ZedGraphControl^  OmegaBetaGraph;
	private: ZedGraph::ZedGraphControl^  OmegaGraph;
	private: System::Windows::Forms::TabControl^  tabControl1;	
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^ ResultsTB;
	private: System::Windows::Forms::Button^ StartBtn;
	private: System::Windows::Forms::TabPage^  tabPage2;	
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: ZedGraph::ZedGraphControl^  E_fieldGraph;
	private: ZedGraph::ZedGraphControl^  SpikesGraph;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridView^  dataGridView2;





	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  Gamma1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Button^ GenerateGammaBtn;
	private: System::Windows::Forms::DataGridView^  GammaTable;
	private: System::Windows::Forms::Label^  label29;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->LoadSetFromFileBtn = (gcnew System::Windows::Forms::Button());
			this->SaveSetToFileBtn = (gcnew System::Windows::Forms::Button());
			this->IntegrParams = (gcnew System::Windows::Forms::GroupBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->IterationsTB = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->T_TB = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->hTB = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->DeltaCmbB = (gcnew System::Windows::Forms::ComboBox());
			this->Gamma0CmbB = (gcnew System::Windows::Forms::ComboBox());
			this->SingleCalculationProgressLbl = (gcnew System::Windows::Forms::Label());
			this->StopCalculationsLbl = (gcnew System::Windows::Forms::Label());
			this->StopBtn = (gcnew System::Windows::Forms::Button());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->GammaTable = (gcnew System::Windows::Forms::DataGridView());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GenerateGammaBtn = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->Gamma1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->ResultsTB = (gcnew System::Windows::Forms::TextBox());
			this->StartBtn = (gcnew System::Windows::Forms::Button());
			this->SystemParams = (gcnew System::Windows::Forms::GroupBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->T02_text = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->T1_TB = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->E0Star_Text = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->E0_Text = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->AlphaTB = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->gTB = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->nTB = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->OmegaPan = (gcnew System::Windows::Forms::Panel());
			this->OffsetTB = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->MaxOmegaNUD = (gcnew System::Windows::Forms::NumericUpDown());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->ClearOmegaGraphBtn = (gcnew System::Windows::Forms::Button());
			this->ShowMaxMinCB = (gcnew System::Windows::Forms::CheckBox());
			this->Omega1TB = (gcnew System::Windows::Forms::TextBox());
			this->Omega2 = (gcnew System::Windows::Forms::Label());
			this->Omega1 = (gcnew System::Windows::Forms::Label());
			this->Omega2TB = (gcnew System::Windows::Forms::TextBox());
			this->Change_scale_Omega = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->OmegaGraph = (gcnew ZedGraph::ZedGraphControl());
			this->PhasesGraph = (gcnew ZedGraph::ZedGraphControl());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TPhaseTable = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->TimeOfSpikesTable = (gcnew System::Windows::Forms::DataGridView());
			this->Time = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->E_fieldGraph = (gcnew ZedGraph::ZedGraphControl());
			this->SpikesGraph = (gcnew ZedGraph::ZedGraphControl());
			this->PhSyncParamGraph = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->progressBar4 = (gcnew System::Windows::Forms::ProgressBar());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->BetaCrNGraph = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
			this->FreqSyncPanel = (gcnew System::Windows::Forms::Panel());
			this->FreqSyncClearGraphBtn = (gcnew System::Windows::Forms::Button());
			this->FreqSyncStartBtn = (gcnew System::Windows::Forms::Button());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->FreqSyncCancelBtn = (gcnew System::Windows::Forms::Button());
			this->FreqSyncBetaStepTB = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->FreqSyncBeta1TB = (gcnew System::Windows::Forms::TextBox());
			this->FreqSyncBeta2TB = (gcnew System::Windows::Forms::TextBox());
			this->FreqSyncGraph = (gcnew ZedGraph::ZedGraphControl());
			this->FreqSyncProgBar = (gcnew System::Windows::Forms::ProgressBar());
			this->FreqSyncProgressLabel = (gcnew System::Windows::Forms::Label());
			this->tabPage9 = (gcnew System::Windows::Forms::TabPage());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->progressBar5 = (gcnew System::Windows::Forms::ProgressBar());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->MaxMuBetaGraph = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Gamma2MaxTB = (gcnew System::Windows::Forms::ComboBox());
			this->Gamma1MinTB = (gcnew System::Windows::Forms::ComboBox());
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
			this->Beta1TB = (gcnew System::Windows::Forms::TextBox());
			this->GammaSetsCountTB = (gcnew System::Windows::Forms::TextBox());
			this->Beta2TB = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->BetaStepTB = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->OmegaBetaGraph = (gcnew ZedGraph::ZedGraphControl());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->ClustersCountBetaGraph = (gcnew ZedGraph::ZedGraphControl());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SingleCalculationBW = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker3 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker4 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker5 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker6 = (gcnew System::ComponentModel::BackgroundWorker());
			this->FreqSyncBW = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->IntegrParams->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GammaTable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SystemParams->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->OmegaPan->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MaxOmegaNUD))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TPhaseTable))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeOfSpikesTable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->tabPage7->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabPage8->SuspendLayout();
			this->FreqSyncPanel->SuspendLayout();
			this->tabPage9->SuspendLayout();
			this->panel3->SuspendLayout();
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
			this->tabControl1->Controls->Add(this->tabPage7);
			this->tabControl1->Controls->Add(this->tabPage8);
			this->tabControl1->Controls->Add(this->tabPage9);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1573, 756);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->LoadSetFromFileBtn);
			this->tabPage1->Controls->Add(this->SaveSetToFileBtn);
			this->tabPage1->Controls->Add(this->IntegrParams);
			this->tabPage1->Controls->Add(this->pictureBox2);
			this->tabPage1->Controls->Add(this->DeltaCmbB);
			this->tabPage1->Controls->Add(this->Gamma0CmbB);
			this->tabPage1->Controls->Add(this->SingleCalculationProgressLbl);
			this->tabPage1->Controls->Add(this->StopCalculationsLbl);
			this->tabPage1->Controls->Add(this->StopBtn);
			this->tabPage1->Controls->Add(this->progressBar2);
			this->tabPage1->Controls->Add(this->label30);
			this->tabPage1->Controls->Add(this->label29);
			this->tabPage1->Controls->Add(this->GammaTable);
			this->tabPage1->Controls->Add(this->GenerateGammaBtn);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->Gamma1);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Controls->Add(this->ResultsTB);
			this->tabPage1->Controls->Add(this->StartBtn);
			this->tabPage1->Controls->Add(this->SystemParams);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1565, 730);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Ввод данных";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// LoadSetFromFileBtn
			// 
			this->LoadSetFromFileBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->LoadSetFromFileBtn->Location = System::Drawing::Point(1151, 149);
			this->LoadSetFromFileBtn->Name = L"LoadSetFromFileBtn";
			this->LoadSetFromFileBtn->Size = System::Drawing::Size(156, 55);
			this->LoadSetFromFileBtn->TabIndex = 171;
			this->LoadSetFromFileBtn->Text = L"Загрузить набор из файла";
			this->LoadSetFromFileBtn->UseVisualStyleBackColor = true;
			this->LoadSetFromFileBtn->Click += gcnew System::EventHandler(this, &MyForm::LoadSetFromFileBtn_Click);
			// 
			// SaveSetToFileBtn
			// 
			this->SaveSetToFileBtn->Enabled = false;
			this->SaveSetToFileBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SaveSetToFileBtn->Location = System::Drawing::Point(1151, 88);
			this->SaveSetToFileBtn->Name = L"SaveSetToFileBtn";
			this->SaveSetToFileBtn->Size = System::Drawing::Size(156, 55);
			this->SaveSetToFileBtn->TabIndex = 170;
			this->SaveSetToFileBtn->Text = L"Сохранить набор в файл";
			this->SaveSetToFileBtn->UseVisualStyleBackColor = true;
			this->SaveSetToFileBtn->Click += gcnew System::EventHandler(this, &MyForm::SaveSetToFileBtn_Click);
			// 
			// IntegrParams
			// 
			this->IntegrParams->Controls->Add(this->label25);
			this->IntegrParams->Controls->Add(this->label28);
			this->IntegrParams->Controls->Add(this->label27);
			this->IntegrParams->Controls->Add(this->label1);
			this->IntegrParams->Controls->Add(this->IterationsTB);
			this->IntegrParams->Controls->Add(this->label24);
			this->IntegrParams->Controls->Add(this->T_TB);
			this->IntegrParams->Controls->Add(this->label23);
			this->IntegrParams->Controls->Add(this->hTB);
			this->IntegrParams->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IntegrParams->Location = System::Drawing::Point(41, 248);
			this->IntegrParams->Name = L"IntegrParams";
			this->IntegrParams->Size = System::Drawing::Size(289, 316);
			this->IntegrParams->TabIndex = 169;
			this->IntegrParams->TabStop = false;
			this->IntegrParams->Text = L"Параметры интегрирования";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(36, 238);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(159, 24);
			this->label25->TabIndex = 157;
			this->label25->Text = L"интегрирования";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(6, 214);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(229, 24);
			this->label28->TabIndex = 156;
			this->label28->Text = L"T - максимальное время";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(6, 190);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(224, 24);
			this->label27->TabIndex = 155;
			this->label27->Text = L"h - шаг интегрирования";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(6, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 24);
			this->label1->TabIndex = 154;
			this->label1->Text = L" Число шагов";
			// 
			// IterationsTB
			// 
			this->IterationsTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IterationsTB->Location = System::Drawing::Point(144, 32);
			this->IterationsTB->Name = L"IterationsTB";
			this->IterationsTB->ReadOnly = true;
			this->IterationsTB->Size = System::Drawing::Size(100, 29);
			this->IterationsTB->TabIndex = 153;
			this->IterationsTB->Text = L"10000000";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(79, 68);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(55, 29);
			this->label24->TabIndex = 152;
			this->label24->Text = L" T =";
			// 
			// T_TB
			// 
			this->T_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T_TB->Location = System::Drawing::Point(144, 68);
			this->T_TB->Name = L"T_TB";
			this->T_TB->Size = System::Drawing::Size(100, 29);
			this->T_TB->TabIndex = 151;
			this->T_TB->Text = L"11000";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(88, 100);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(46, 29);
			this->label23->TabIndex = 150;
			this->label23->Text = L"h =";
			// 
			// hTB
			// 
			this->hTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->hTB->Location = System::Drawing::Point(144, 103);
			this->hTB->Name = L"hTB";
			this->hTB->Size = System::Drawing::Size(100, 29);
			this->hTB->TabIndex = 149;
			this->hTB->Text = L"0,005";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(791, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(292, 114);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 167;
			this->pictureBox2->TabStop = false;
			// 
			// DeltaCmbB
			// 
			this->DeltaCmbB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DeltaCmbB->FormattingEnabled = true;
			this->DeltaCmbB->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"0", L"0,01", L"0,02", L"0,03", L"0,04", L"0,05",
					L"0,06", L"0,07", L"0,08", L"0,09", L"0,1"
			});
			this->DeltaCmbB->Location = System::Drawing::Point(1007, 138);
			this->DeltaCmbB->Name = L"DeltaCmbB";
			this->DeltaCmbB->Size = System::Drawing::Size(88, 32);
			this->DeltaCmbB->TabIndex = 166;
			this->DeltaCmbB->Text = L"0";
			// 
			// Gamma0CmbB
			// 
			this->Gamma0CmbB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma0CmbB->FormattingEnabled = true;
			this->Gamma0CmbB->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1", L"1,03", L"2", L"3", L"4", L"5" });
			this->Gamma0CmbB->Location = System::Drawing::Point(816, 138);
			this->Gamma0CmbB->Name = L"Gamma0CmbB";
			this->Gamma0CmbB->Size = System::Drawing::Size(88, 32);
			this->Gamma0CmbB->TabIndex = 165;
			this->Gamma0CmbB->Text = L"1,03";
			// 
			// SingleCalculationProgressLbl
			// 
			this->SingleCalculationProgressLbl->AutoSize = true;
			this->SingleCalculationProgressLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->SingleCalculationProgressLbl->Location = System::Drawing::Point(857, 321);
			this->SingleCalculationProgressLbl->Name = L"SingleCalculationProgressLbl";
			this->SingleCalculationProgressLbl->Size = System::Drawing::Size(212, 24);
			this->SingleCalculationProgressLbl->TabIndex = 162;
			this->SingleCalculationProgressLbl->Text = L"Идут вычисления... 0%";
			this->SingleCalculationProgressLbl->Visible = false;
			// 
			// StopCalculationsLbl
			// 
			this->StopCalculationsLbl->AutoSize = true;
			this->StopCalculationsLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->StopCalculationsLbl->Location = System::Drawing::Point(831, 324);
			this->StopCalculationsLbl->Name = L"StopCalculationsLbl";
			this->StopCalculationsLbl->Size = System::Drawing::Size(281, 24);
			this->StopCalculationsLbl->TabIndex = 164;
			this->StopCalculationsLbl->Text = L"Останавливаем вычисления...";
			this->StopCalculationsLbl->Visible = false;
			// 
			// StopBtn
			// 
			this->StopBtn->Enabled = false;
			this->StopBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StopBtn->Location = System::Drawing::Point(941, 202);
			this->StopBtn->Name = L"StopBtn";
			this->StopBtn->Size = System::Drawing::Size(184, 66);
			this->StopBtn->TabIndex = 153;
			this->StopBtn->Text = L"ОТМЕНА";
			this->StopBtn->UseVisualStyleBackColor = true;
			this->StopBtn->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(668, 280);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(598, 31);
			this->progressBar2->Step = 1;
			this->progressBar2->TabIndex = 161;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(366, 631);
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
			this->label29->Location = System::Drawing::Point(366, 591);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(704, 24);
			this->label29->TabIndex = 149;
			this->label29->Text = L"T₁ - φⱼ(T₁), j = 0,...,n - 1 будут использованы для вычисления средних частот Ω";
			// 
			// GammaTable
			// 
			this->GammaTable->AllowUserToAddRows = false;
			this->GammaTable->AllowUserToDeleteRows = false;
			this->GammaTable->AllowUserToResizeRows = false;
			this->GammaTable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->GammaTable->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->GammaTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->GammaTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Column3, this->Column4 });
			this->GammaTable->Location = System::Drawing::Point(1313, 11);
			this->GammaTable->Name = L"GammaTable";
			this->GammaTable->ReadOnly = true;
			this->GammaTable->RowHeadersVisible = false;
			this->GammaTable->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->GammaTable->Size = System::Drawing::Size(246, 711);
			this->GammaTable->TabIndex = 144;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"j";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Width = 30;
			// 
			// Column4
			// 
			this->Column4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column4->HeaderText = L"γⱼ";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// GenerateGammaBtn
			// 
			this->GenerateGammaBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->GenerateGammaBtn->Location = System::Drawing::Point(1151, 27);
			this->GenerateGammaBtn->Name = L"GenerateGammaBtn";
			this->GenerateGammaBtn->Size = System::Drawing::Size(156, 55);
			this->GenerateGammaBtn->TabIndex = 141;
			this->GenerateGammaBtn->Text = L"Сгенерировать набор γⱼ";
			this->GenerateGammaBtn->UseVisualStyleBackColor = true;
			this->GenerateGammaBtn->Click += gcnew System::EventHandler(this, &MyForm::CreateGammaBtn_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(941, 137);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(60, 29);
			this->label10->TabIndex = 137;
			this->label10->Text = L"Δ  = ";
			// 
			// Gamma1
			// 
			this->Gamma1->AutoSize = true;
			this->Gamma1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma1->Location = System::Drawing::Point(746, 137);
			this->Gamma1->Name = L"Gamma1";
			this->Gamma1->Size = System::Drawing::Size(64, 29);
			this->Gamma1->TabIndex = 135;
			this->Gamma1->Text = L" γ₀ = ";
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
			// ResultsTB
			// 
			this->ResultsTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ResultsTB->Location = System::Drawing::Point(735, 348);
			this->ResultsTB->Multiline = true;
			this->ResultsTB->Name = L"ResultsTB";
			this->ResultsTB->ReadOnly = true;
			this->ResultsTB->Size = System::Drawing::Size(434, 172);
			this->ResultsTB->TabIndex = 93;
			this->ResultsTB->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// StartBtn
			// 
			this->StartBtn->Enabled = false;
			this->StartBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StartBtn->Location = System::Drawing::Point(751, 203);
			this->StartBtn->Name = L"StartBtn";
			this->StartBtn->Size = System::Drawing::Size(184, 64);
			this->StartBtn->TabIndex = 90;
			this->StartBtn->Text = L"СТАРТ";
			this->StartBtn->UseVisualStyleBackColor = true;
			this->StartBtn->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// SystemParams
			// 
			this->SystemParams->Controls->Add(this->label13);
			this->SystemParams->Controls->Add(this->textBox7);
			this->SystemParams->Controls->Add(this->label8);
			this->SystemParams->Controls->Add(this->T02_text);
			this->SystemParams->Controls->Add(this->label5);
			this->SystemParams->Controls->Add(this->T1_TB);
			this->SystemParams->Controls->Add(this->label7);
			this->SystemParams->Controls->Add(this->E0Star_Text);
			this->SystemParams->Controls->Add(this->label6);
			this->SystemParams->Controls->Add(this->E0_Text);
			this->SystemParams->Controls->Add(this->label3);
			this->SystemParams->Controls->Add(this->AlphaTB);
			this->SystemParams->Controls->Add(this->label2);
			this->SystemParams->Controls->Add(this->gTB);
			this->SystemParams->Controls->Add(this->label21);
			this->SystemParams->Controls->Add(this->nTB);
			this->SystemParams->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SystemParams->Location = System::Drawing::Point(370, 247);
			this->SystemParams->Name = L"SystemParams";
			this->SystemParams->Size = System::Drawing::Size(292, 317);
			this->SystemParams->TabIndex = 168;
			this->SystemParams->TabStop = false;
			this->SystemParams->Text = L"Параметры системы";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(117, 276);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(58, 29);
			this->label13->TabIndex = 168;
			this->label13->Text = L" β = ";
			// 
			// textBox7
			// 
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox7->Location = System::Drawing::Point(181, 277);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 29);
			this->textBox7->TabIndex = 167;
			this->textBox7->Text = L"0,07";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(106, 172);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(69, 29);
			this->label8->TabIndex = 166;
			this->label8->Text = L" T₂ = ";
			// 
			// T02_text
			// 
			this->T02_text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T02_text->Location = System::Drawing::Point(181, 172);
			this->T02_text->Name = L"T02_text";
			this->T02_text->Size = System::Drawing::Size(100, 29);
			this->T02_text->TabIndex = 165;
			this->T02_text->Text = L"10900";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(106, 136);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(69, 29);
			this->label5->TabIndex = 164;
			this->label5->Text = L" T₁ = ";
			// 
			// T1_TB
			// 
			this->T1_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->T1_TB->Location = System::Drawing::Point(181, 137);
			this->T1_TB->Name = L"T1_TB";
			this->T1_TB->Size = System::Drawing::Size(100, 29);
			this->T1_TB->TabIndex = 163;
			this->T1_TB->Text = L"5000";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(112, 101);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(63, 29);
			this->label7->TabIndex = 162;
			this->label7->Text = L"Ė₀ = ";
			// 
			// E0Star_Text
			// 
			this->E0Star_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0Star_Text->Location = System::Drawing::Point(181, 102);
			this->E0Star_Text->Name = L"E0Star_Text";
			this->E0Star_Text->Size = System::Drawing::Size(100, 29);
			this->E0Star_Text->TabIndex = 161;
			this->E0Star_Text->Text = L"0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(106, 69);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 29);
			this->label6->TabIndex = 160;
			this->label6->Text = L" E₀ = ";
			// 
			// E0_Text
			// 
			this->E0_Text->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->E0_Text->Location = System::Drawing::Point(181, 67);
			this->E0_Text->Name = L"E0_Text";
			this->E0_Text->Size = System::Drawing::Size(100, 29);
			this->E0_Text->TabIndex = 159;
			this->E0_Text->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(115, 241);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 29);
			this->label3->TabIndex = 158;
			this->label3->Text = L" α = ";
			// 
			// AlphaTB
			// 
			this->AlphaTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->AlphaTB->Location = System::Drawing::Point(181, 242);
			this->AlphaTB->Name = L"AlphaTB";
			this->AlphaTB->Size = System::Drawing::Size(100, 29);
			this->AlphaTB->TabIndex = 157;
			this->AlphaTB->Text = L"1,5";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(116, 206);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 29);
			this->label2->TabIndex = 156;
			this->label2->Text = L" g = ";
			// 
			// gTB
			// 
			this->gTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gTB->Location = System::Drawing::Point(181, 207);
			this->gTB->Name = L"gTB";
			this->gTB->Size = System::Drawing::Size(100, 29);
			this->gTB->TabIndex = 155;
			this->gTB->Text = L"1";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(6, 33);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(169, 24);
			this->label21->TabIndex = 154;
			this->label21->Text = L" Число уравнений";
			// 
			// nTB
			// 
			this->nTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->nTB->Location = System::Drawing::Point(181, 30);
			this->nTB->Name = L"nTB";
			this->nTB->Size = System::Drawing::Size(100, 29);
			this->nTB->TabIndex = 153;
			this->nTB->Text = L"100";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->OmegaPan);
			this->tabPage2->Controls->Add(this->groupBox1);
			this->tabPage2->Controls->Add(this->OmegaGraph);
			this->tabPage2->Controls->Add(this->PhasesGraph);
			this->tabPage2->Controls->Add(this->dataGridView1);
			this->tabPage2->Controls->Add(this->TPhaseTable);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1565, 730);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Средние частоты";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// OmegaPan
			// 
			this->OmegaPan->Controls->Add(this->OffsetTB);
			this->OmegaPan->Controls->Add(this->label18);
			this->OmegaPan->Controls->Add(this->MaxOmegaNUD);
			this->OmegaPan->Controls->Add(this->label17);
			this->OmegaPan->Controls->Add(this->ClearOmegaGraphBtn);
			this->OmegaPan->Controls->Add(this->ShowMaxMinCB);
			this->OmegaPan->Controls->Add(this->Omega1TB);
			this->OmegaPan->Controls->Add(this->Omega2);
			this->OmegaPan->Controls->Add(this->Omega1);
			this->OmegaPan->Controls->Add(this->Omega2TB);
			this->OmegaPan->Controls->Add(this->Change_scale_Omega);
			this->OmegaPan->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OmegaPan->Location = System::Drawing::Point(1109, 103);
			this->OmegaPan->Name = L"OmegaPan";
			this->OmegaPan->Size = System::Drawing::Size(453, 223);
			this->OmegaPan->TabIndex = 152;
			// 
			// OffsetTB
			// 
			this->OffsetTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OffsetTB->Location = System::Drawing::Point(289, 181);
			this->OffsetTB->Name = L"OffsetTB";
			this->OffsetTB->Size = System::Drawing::Size(125, 29);
			this->OffsetTB->TabIndex = 161;
			this->OffsetTB->Text = L"0,015";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(203, 184);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(80, 24);
			this->label18->TabIndex = 160;
			this->label18->Text = L"Отступ:";
			// 
			// MaxOmegaNUD
			// 
			this->MaxOmegaNUD->DecimalPlaces = 3;
			this->MaxOmegaNUD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MaxOmegaNUD->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 131072 });
			this->MaxOmegaNUD->Location = System::Drawing::Point(77, 182);
			this->MaxOmegaNUD->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->MaxOmegaNUD->Name = L"MaxOmegaNUD";
			this->MaxOmegaNUD->Size = System::Drawing::Size(97, 29);
			this->MaxOmegaNUD->TabIndex = 159;
			this->MaxOmegaNUD->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->MaxOmegaNUD->ValueChanged += gcnew System::EventHandler(this, &MyForm::MaxOmegaNUD_ValueChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(5, 184);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(66, 24);
			this->label17->TabIndex = 158;
			this->label17->Text = L"Ωmax:";
			// 
			// ClearOmegaGraphBtn
			// 
			this->ClearOmegaGraphBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ClearOmegaGraphBtn->Location = System::Drawing::Point(9, 110);
			this->ClearOmegaGraphBtn->Name = L"ClearOmegaGraphBtn";
			this->ClearOmegaGraphBtn->Size = System::Drawing::Size(138, 60);
			this->ClearOmegaGraphBtn->TabIndex = 156;
			this->ClearOmegaGraphBtn->Text = L"Очистить графики";
			this->ClearOmegaGraphBtn->UseVisualStyleBackColor = true;
			this->ClearOmegaGraphBtn->Click += gcnew System::EventHandler(this, &MyForm::ClearOmegaGraphBtn_Click);
			// 
			// ShowMaxMinCB
			// 
			this->ShowMaxMinCB->AutoSize = true;
			this->ShowMaxMinCB->Enabled = false;
			this->ShowMaxMinCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ShowMaxMinCB->Location = System::Drawing::Point(9, 76);
			this->ShowMaxMinCB->Name = L"ShowMaxMinCB";
			this->ShowMaxMinCB->Size = System::Drawing::Size(349, 28);
			this->ShowMaxMinCB->TabIndex = 155;
			this->ShowMaxMinCB->Text = L"Показывать подписи для Max и Min";
			this->ShowMaxMinCB->UseVisualStyleBackColor = true;
			this->ShowMaxMinCB->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// Omega1TB
			// 
			this->Omega1TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega1TB->Location = System::Drawing::Point(75, 11);
			this->Omega1TB->Name = L"Omega1TB";
			this->Omega1TB->Size = System::Drawing::Size(99, 29);
			this->Omega1TB->TabIndex = 154;
			// 
			// Omega2
			// 
			this->Omega2->AutoSize = true;
			this->Omega2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega2->Location = System::Drawing::Point(4, 48);
			this->Omega2->Name = L"Omega2";
			this->Omega2->Size = System::Drawing::Size(65, 25);
			this->Omega2->TabIndex = 153;
			this->Omega2->Text = L" Ω₂ = ";
			// 
			// Omega1
			// 
			this->Omega1->AutoSize = true;
			this->Omega1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega1->Location = System::Drawing::Point(4, 13);
			this->Omega1->Name = L"Omega1";
			this->Omega1->Size = System::Drawing::Size(65, 25);
			this->Omega1->TabIndex = 152;
			this->Omega1->Text = L" Ω₁ = ";
			// 
			// Omega2TB
			// 
			this->Omega2TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Omega2TB->Location = System::Drawing::Point(76, 46);
			this->Omega2TB->Name = L"Omega2TB";
			this->Omega2TB->Size = System::Drawing::Size(98, 29);
			this->Omega2TB->TabIndex = 151;
			// 
			// Change_scale_Omega
			// 
			this->Change_scale_Omega->Enabled = false;
			this->Change_scale_Omega->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Change_scale_Omega->Location = System::Drawing::Point(180, 11);
			this->Change_scale_Omega->Name = L"Change_scale_Omega";
			this->Change_scale_Omega->Size = System::Drawing::Size(184, 64);
			this->Change_scale_Omega->TabIndex = 150;
			this->Change_scale_Omega->Text = L"Изменить масштаб от Ω₁ до Ω₂";
			this->Change_scale_Omega->UseVisualStyleBackColor = true;
			this->Change_scale_Omega->Click += gcnew System::EventHandler(this, &MyForm::Change_scale_Omega_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton4);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(1109, 6);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(453, 91);
			this->groupBox1->TabIndex = 151;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Отображение графика";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Checked = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton3->Location = System::Drawing::Point(9, 20);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(210, 28);
			this->radioButton3->TabIndex = 149;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Средние частоты Ωⱼ";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton3_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton4->Location = System::Drawing::Point(9, 54);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(387, 28);
			this->radioButton4->TabIndex = 148;
			this->radioButton4->Text = L"Фазы в конечный момент времени φⱼ(T)";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton4_CheckedChanged);
			// 
			// OmegaGraph
			// 
			this->OmegaGraph->ImeMode = System::Windows::Forms::ImeMode::On;
			this->OmegaGraph->IsShowPointValues = true;
			this->OmegaGraph->Location = System::Drawing::Point(0, 3);
			this->OmegaGraph->Name = L"OmegaGraph";
			this->OmegaGraph->PointValueFormat = L"g";
			this->OmegaGraph->ScrollGrace = 0;
			this->OmegaGraph->ScrollMaxX = 0;
			this->OmegaGraph->ScrollMaxY = 0;
			this->OmegaGraph->ScrollMaxY2 = 0;
			this->OmegaGraph->ScrollMinX = 0;
			this->OmegaGraph->ScrollMinY = 0;
			this->OmegaGraph->ScrollMinY2 = 0;
			this->OmegaGraph->Size = System::Drawing::Size(1103, 718);
			this->OmegaGraph->TabIndex = 114;
			// 
			// PhasesGraph
			// 
			this->PhasesGraph->ImeMode = System::Windows::Forms::ImeMode::On;
			this->PhasesGraph->IsShowPointValues = true;
			this->PhasesGraph->Location = System::Drawing::Point(0, 3);
			this->PhasesGraph->Name = L"PhasesGraph";
			this->PhasesGraph->PointValueFormat = L"g";
			this->PhasesGraph->ScrollGrace = 0;
			this->PhasesGraph->ScrollMaxX = 0;
			this->PhasesGraph->ScrollMaxY = 0;
			this->PhasesGraph->ScrollMaxY2 = 0;
			this->PhasesGraph->ScrollMinX = 0;
			this->PhasesGraph->ScrollMinY = 0;
			this->PhasesGraph->ScrollMinY2 = 0;
			this->PhasesGraph->Size = System::Drawing::Size(1103, 718);
			this->PhasesGraph->TabIndex = 148;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->dataGridView1->Location = System::Drawing::Point(1109, 332);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(445, 389);
			this->dataGridView1->TabIndex = 115;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->dataGridViewTextBoxColumn1->HeaderText = L"j";
			this->dataGridViewTextBoxColumn1->MinimumWidth = 30;
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->Width = 34;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn2->HeaderText = L"Ωⱼ";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			// 
			// TPhaseTable
			// 
			this->TPhaseTable->AllowUserToAddRows = false;
			this->TPhaseTable->AllowUserToDeleteRows = false;
			this->TPhaseTable->AllowUserToResizeRows = false;
			this->TPhaseTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TPhaseTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn5,
					this->dataGridViewTextBoxColumn6
			});
			this->TPhaseTable->Location = System::Drawing::Point(1109, 332);
			this->TPhaseTable->Name = L"TPhaseTable";
			this->TPhaseTable->RowHeadersVisible = false;
			this->TPhaseTable->Size = System::Drawing::Size(445, 389);
			this->TPhaseTable->TabIndex = 150;
			this->TPhaseTable->Visible = false;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->dataGridViewTextBoxColumn5->HeaderText = L"j";
			this->dataGridViewTextBoxColumn5->MinimumWidth = 30;
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->Width = 34;
			// 
			// dataGridViewTextBoxColumn6
			// 
			this->dataGridViewTextBoxColumn6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn6->HeaderText = L"φⱼ(T)";
			this->dataGridViewTextBoxColumn6->Name = L"dataGridViewTextBoxColumn6";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->TimeOfSpikesTable);
			this->tabPage3->Controls->Add(this->radioButton2);
			this->tabPage3->Controls->Add(this->radioButton1);
			this->tabPage3->Controls->Add(this->dataGridView2);
			this->tabPage3->Controls->Add(this->E_fieldGraph);
			this->tabPage3->Controls->Add(this->SpikesGraph);
			this->tabPage3->Controls->Add(this->PhSyncParamGraph);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1565, 730);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Внешнее поле и спайки";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// TimeOfSpikesTable
			// 
			this->TimeOfSpikesTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->TimeOfSpikesTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TimeOfSpikesTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->Time });
			this->TimeOfSpikesTable->Location = System::Drawing::Point(1109, 429);
			this->TimeOfSpikesTable->Name = L"TimeOfSpikesTable";
			this->TimeOfSpikesTable->RowHeadersVisible = false;
			this->TimeOfSpikesTable->Size = System::Drawing::Size(445, 292);
			this->TimeOfSpikesTable->TabIndex = 120;
			this->TimeOfSpikesTable->Visible = false;
			// 
			// Time
			// 
			this->Time->HeaderText = L"t";
			this->Time->Name = L"Time";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton2->Location = System::Drawing::Point(1131, 361);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(423, 28);
			this->radioButton2->TabIndex = 118;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"График параметра фазовой синхронизации";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton1->Location = System::Drawing::Point(1131, 395);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(172, 28);
			this->radioButton1->TabIndex = 117;
			this->radioButton1->Text = L"График спайков";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn3,
					this->dataGridViewTextBoxColumn4
			});
			this->dataGridView2->Location = System::Drawing::Point(1109, 0);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->Size = System::Drawing::Size(445, 345);
			this->dataGridView2->TabIndex = 116;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->dataGridViewTextBoxColumn3->HeaderText = L"t";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->Width = 35;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn4->HeaderText = L"E(t)";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			// 
			// E_fieldGraph
			// 
			this->E_fieldGraph->IsShowPointValues = true;
			this->E_fieldGraph->Location = System::Drawing::Point(6, 3);
			this->E_fieldGraph->Name = L"E_fieldGraph";
			this->E_fieldGraph->ScrollGrace = 0;
			this->E_fieldGraph->ScrollMaxX = 0;
			this->E_fieldGraph->ScrollMaxY = 0;
			this->E_fieldGraph->ScrollMaxY2 = 0;
			this->E_fieldGraph->ScrollMinX = 0;
			this->E_fieldGraph->ScrollMinY = 0;
			this->E_fieldGraph->ScrollMinY2 = 0;
			this->E_fieldGraph->Size = System::Drawing::Size(1097, 342);
			this->E_fieldGraph->TabIndex = 1;
			// 
			// SpikesGraph
			// 
			this->SpikesGraph->IsShowPointValues = true;
			this->SpikesGraph->Location = System::Drawing::Point(6, 351);
			this->SpikesGraph->Name = L"SpikesGraph";
			this->SpikesGraph->ScrollGrace = 0;
			this->SpikesGraph->ScrollMaxX = 0;
			this->SpikesGraph->ScrollMaxY = 0;
			this->SpikesGraph->ScrollMaxY2 = 0;
			this->SpikesGraph->ScrollMinX = 0;
			this->SpikesGraph->ScrollMinY = 0;
			this->SpikesGraph->ScrollMinY2 = 0;
			this->SpikesGraph->Size = System::Drawing::Size(1097, 370);
			this->SpikesGraph->TabIndex = 0;
			this->SpikesGraph->Visible = false;
			// 
			// PhSyncParamGraph
			// 
			this->PhSyncParamGraph->IsShowPointValues = true;
			this->PhSyncParamGraph->Location = System::Drawing::Point(6, 351);
			this->PhSyncParamGraph->Name = L"PhSyncParamGraph";
			this->PhSyncParamGraph->ScrollGrace = 0;
			this->PhSyncParamGraph->ScrollMaxX = 0;
			this->PhSyncParamGraph->ScrollMaxY = 0;
			this->PhSyncParamGraph->ScrollMaxY2 = 0;
			this->PhSyncParamGraph->ScrollMinX = 0;
			this->PhSyncParamGraph->ScrollMinY = 0;
			this->PhSyncParamGraph->ScrollMinY2 = 0;
			this->PhSyncParamGraph->Size = System::Drawing::Size(1097, 370);
			this->PhSyncParamGraph->TabIndex = 119;
			// 
			// tabPage7
			// 
			this->tabPage7->Controls->Add(this->panel2);
			this->tabPage7->Controls->Add(this->label36);
			this->tabPage7->Controls->Add(this->button12);
			this->tabPage7->Controls->Add(this->textBox13);
			this->tabPage7->Controls->Add(this->label35);
			this->tabPage7->Controls->Add(this->textBox8);
			this->tabPage7->Controls->Add(this->label9);
			this->tabPage7->Controls->Add(this->BetaCrNGraph);
			this->tabPage7->Location = System::Drawing::Point(4, 22);
			this->tabPage7->Name = L"tabPage7";
			this->tabPage7->Padding = System::Windows::Forms::Padding(3);
			this->tabPage7->Size = System::Drawing::Size(1565, 730);
			this->tabPage7->TabIndex = 6;
			this->tabPage7->Text = L"Фазовая синхронизация";
			this->tabPage7->UseVisualStyleBackColor = true;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button11);
			this->panel2->Controls->Add(this->button8);
			this->panel2->Controls->Add(this->button9);
			this->panel2->Controls->Add(this->progressBar4);
			this->panel2->Controls->Add(this->label20);
			this->panel2->Controls->Add(this->label33);
			this->panel2->Controls->Add(this->button10);
			this->panel2->Controls->Add(this->textBox11);
			this->panel2->Controls->Add(this->textBox12);
			this->panel2->Controls->Add(this->label32);
			this->panel2->Controls->Add(this->label34);
			this->panel2->Controls->Add(this->label31);
			this->panel2->Controls->Add(this->textBox9);
			this->panel2->Controls->Add(this->textBox10);
			this->panel2->Location = System::Drawing::Point(1204, 6);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(360, 369);
			this->panel2->TabIndex = 179;
			// 
			// button11
			// 
			this->button11->Enabled = false;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button11->Location = System::Drawing::Point(3, 216);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(168, 71);
			this->button11->TabIndex = 174;
			this->button11->Text = L"Добавить одно измерение";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// button8
			// 
			this->button8->Enabled = false;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button8->Location = System::Drawing::Point(180, 216);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(168, 71);
			this->button8->TabIndex = 2;
			this->button8->Text = L"Построить аппроксимацию";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button9->Location = System::Drawing::Point(3, 139);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(168, 71);
			this->button9->TabIndex = 4;
			this->button9->Text = L"Начать построение";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// progressBar4
			// 
			this->progressBar4->Location = System::Drawing::Point(2, 293);
			this->progressBar4->Name = L"progressBar4";
			this->progressBar4->Size = System::Drawing::Size(352, 31);
			this->progressBar4->TabIndex = 163;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(74, 327);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(214, 24);
			this->label20->TabIndex = 164;
			this->label20->Text = L"Идёт построение... 0%";
			this->label20->Visible = false;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(50, 99);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(168, 24);
			this->label33->TabIndex = 169;
			this->label33->Text = L"Число измерений";
			// 
			// button10
			// 
			this->button10->Enabled = false;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button10->Location = System::Drawing::Point(180, 139);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(168, 71);
			this->button10->TabIndex = 173;
			this->button10->Text = L"Очистить графики";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// textBox11
			// 
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox11->Location = System::Drawing::Point(222, 96);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(57, 29);
			this->textBox11->TabIndex = 170;
			this->textBox11->Text = L"9";
			// 
			// textBox12
			// 
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox12->Location = System::Drawing::Point(161, 7);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(57, 29);
			this->textBox12->TabIndex = 171;
			this->textBox12->Text = L"1,03";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(187, 50);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(51, 24);
			this->label32->TabIndex = 168;
			this->label32->Text = L"N₂ = ";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label34->Location = System::Drawing::Point(117, 10);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(40, 24);
			this->label34->TabIndex = 172;
			this->label34->Text = L"γ = ";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label31->Location = System::Drawing::Point(21, 53);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(51, 24);
			this->label31->TabIndex = 167;
			this->label31->Text = L"N₁ = ";
			// 
			// textBox9
			// 
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox9->Location = System::Drawing::Point(78, 50);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(57, 29);
			this->textBox9->TabIndex = 165;
			this->textBox9->Text = L"10";
			// 
			// textBox10
			// 
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox10->Location = System::Drawing::Point(244, 47);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(57, 29);
			this->textBox10->TabIndex = 166;
			this->textBox10->Text = L"100";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(1293, 644);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(182, 24);
			this->label36->TabIndex = 178;
			this->label36->Text = L"Идут вычисления...";
			this->label36->Visible = false;
			// 
			// button12
			// 
			this->button12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button12->Location = System::Drawing::Point(1297, 570);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(168, 71);
			this->button12->TabIndex = 177;
			this->button12->Text = L"Старт";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Visible = false;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click);
			// 
			// textBox13
			// 
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox13->Location = System::Drawing::Point(1367, 535);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(57, 29);
			this->textBox13->TabIndex = 175;
			this->textBox13->Text = L"10";
			this->textBox13->Visible = false;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label35->Location = System::Drawing::Point(1318, 538);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(45, 24);
			this->label35->TabIndex = 176;
			this->label35->Text = L"N = ";
			this->label35->Visible = false;
			// 
			// textBox8
			// 
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox8->Location = System::Drawing::Point(1208, 378);
			this->textBox8->Multiline = true;
			this->textBox8->Name = L"textBox8";
			this->textBox8->ReadOnly = true;
			this->textBox8->Size = System::Drawing::Size(352, 119);
			this->textBox8->TabIndex = 3;
			this->textBox8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox8->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(436, 698);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(791, 24);
			this->label9->TabIndex = 1;
			this->label9->Text = L"β ⃰ - значение параметра β, при котором наступает фазовая синхронизация ротаторов"
				L"";
			// 
			// BetaCrNGraph
			// 
			this->BetaCrNGraph->IsShowPointValues = true;
			this->BetaCrNGraph->Location = System::Drawing::Point(3, 3);
			this->BetaCrNGraph->Name = L"BetaCrNGraph";
			this->BetaCrNGraph->ScrollGrace = 0;
			this->BetaCrNGraph->ScrollMaxX = 0;
			this->BetaCrNGraph->ScrollMaxY = 0;
			this->BetaCrNGraph->ScrollMaxY2 = 0;
			this->BetaCrNGraph->ScrollMinX = 0;
			this->BetaCrNGraph->ScrollMinY = 0;
			this->BetaCrNGraph->ScrollMinY2 = 0;
			this->BetaCrNGraph->Size = System::Drawing::Size(1200, 692);
			this->BetaCrNGraph->TabIndex = 0;
			// 
			// tabPage8
			// 
			this->tabPage8->Controls->Add(this->FreqSyncPanel);
			this->tabPage8->Controls->Add(this->FreqSyncGraph);
			this->tabPage8->Controls->Add(this->FreqSyncProgBar);
			this->tabPage8->Controls->Add(this->FreqSyncCancelBtn);
			this->tabPage8->Controls->Add(this->FreqSyncProgressLabel);
			this->tabPage8->Location = System::Drawing::Point(4, 22);
			this->tabPage8->Name = L"tabPage8";
			this->tabPage8->Size = System::Drawing::Size(1565, 730);
			this->tabPage8->TabIndex = 9;
			this->tabPage8->Text = L"Частотная синхронизация";
			this->tabPage8->UseVisualStyleBackColor = true;
			// 
			// FreqSyncPanel
			// 
			this->FreqSyncPanel->Controls->Add(this->FreqSyncClearGraphBtn);
			this->FreqSyncPanel->Controls->Add(this->FreqSyncStartBtn);
			this->FreqSyncPanel->Controls->Add(this->label42);
			this->FreqSyncPanel->Controls->Add(this->FreqSyncBetaStepTB);
			this->FreqSyncPanel->Controls->Add(this->label43);
			this->FreqSyncPanel->Controls->Add(this->label45);
			this->FreqSyncPanel->Controls->Add(this->FreqSyncBeta1TB);
			this->FreqSyncPanel->Controls->Add(this->FreqSyncBeta2TB);
			this->FreqSyncPanel->Location = System::Drawing::Point(1203, 5);
			this->FreqSyncPanel->Name = L"FreqSyncPanel";
			this->FreqSyncPanel->Size = System::Drawing::Size(360, 184);
			this->FreqSyncPanel->TabIndex = 182;
			// 
			// FreqSyncClearGraphBtn
			// 
			this->FreqSyncClearGraphBtn->Enabled = false;
			this->FreqSyncClearGraphBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncClearGraphBtn->Location = System::Drawing::Point(178, 104);
			this->FreqSyncClearGraphBtn->Name = L"FreqSyncClearGraphBtn";
			this->FreqSyncClearGraphBtn->Size = System::Drawing::Size(173, 71);
			this->FreqSyncClearGraphBtn->TabIndex = 174;
			this->FreqSyncClearGraphBtn->Text = L"Очистить график";
			this->FreqSyncClearGraphBtn->UseVisualStyleBackColor = true;
			this->FreqSyncClearGraphBtn->Click += gcnew System::EventHandler(this, &MyForm::FreqSyncClearGraphBtn_Click);
			// 
			// FreqSyncStartBtn
			// 
			this->FreqSyncStartBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncStartBtn->Location = System::Drawing::Point(4, 104);
			this->FreqSyncStartBtn->Name = L"FreqSyncStartBtn";
			this->FreqSyncStartBtn->Size = System::Drawing::Size(168, 71);
			this->FreqSyncStartBtn->TabIndex = 4;
			this->FreqSyncStartBtn->Text = L"Начать построение";
			this->FreqSyncStartBtn->UseVisualStyleBackColor = true;
			this->FreqSyncStartBtn->Click += gcnew System::EventHandler(this, &MyForm::FreqSyncStartBtn_Click);
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label42->Location = System::Drawing::Point(51, 64);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(91, 24);
			this->label42->TabIndex = 169;
			this->label42->Text = L"Шаг по β:";
			// 
			// FreqSyncCancelBtn
			// 
			this->FreqSyncCancelBtn->Enabled = false;
			this->FreqSyncCancelBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncCancelBtn->Location = System::Drawing::Point(1304, 283);
			this->FreqSyncCancelBtn->Name = L"FreqSyncCancelBtn";
			this->FreqSyncCancelBtn->Size = System::Drawing::Size(173, 71);
			this->FreqSyncCancelBtn->TabIndex = 173;
			this->FreqSyncCancelBtn->Text = L"Отмена";
			this->FreqSyncCancelBtn->UseVisualStyleBackColor = true;
			this->FreqSyncCancelBtn->Click += gcnew System::EventHandler(this, &MyForm::FreqSyncCancelBtn_Click);
			// 
			// FreqSyncBetaStepTB
			// 
			this->FreqSyncBetaStepTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncBetaStepTB->Location = System::Drawing::Point(148, 61);
			this->FreqSyncBetaStepTB->Name = L"FreqSyncBetaStepTB";
			this->FreqSyncBetaStepTB->Size = System::Drawing::Size(110, 29);
			this->FreqSyncBetaStepTB->TabIndex = 170;
			this->FreqSyncBetaStepTB->Text = L"0,005";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label43->Location = System::Drawing::Point(188, 15);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(48, 24);
			this->label43->TabIndex = 168;
			this->label43->Text = L"β₂ = ";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label45->Location = System::Drawing::Point(22, 18);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(48, 24);
			this->label45->TabIndex = 167;
			this->label45->Text = L"β₁ = ";
			// 
			// FreqSyncBeta1TB
			// 
			this->FreqSyncBeta1TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncBeta1TB->Location = System::Drawing::Point(79, 15);
			this->FreqSyncBeta1TB->Name = L"FreqSyncBeta1TB";
			this->FreqSyncBeta1TB->Size = System::Drawing::Size(57, 29);
			this->FreqSyncBeta1TB->TabIndex = 165;
			this->FreqSyncBeta1TB->Text = L"0,01";
			// 
			// FreqSyncBeta2TB
			// 
			this->FreqSyncBeta2TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncBeta2TB->Location = System::Drawing::Point(245, 12);
			this->FreqSyncBeta2TB->Name = L"FreqSyncBeta2TB";
			this->FreqSyncBeta2TB->Size = System::Drawing::Size(57, 29);
			this->FreqSyncBeta2TB->TabIndex = 166;
			this->FreqSyncBeta2TB->Text = L"0,1";
			// 
			// FreqSyncGraph
			// 
			this->FreqSyncGraph->IsShowPointValues = true;
			this->FreqSyncGraph->Location = System::Drawing::Point(2, 5);
			this->FreqSyncGraph->Name = L"FreqSyncGraph";
			this->FreqSyncGraph->ScrollGrace = 0;
			this->FreqSyncGraph->ScrollMaxX = 0;
			this->FreqSyncGraph->ScrollMaxY = 0;
			this->FreqSyncGraph->ScrollMaxY2 = 0;
			this->FreqSyncGraph->ScrollMinX = 0;
			this->FreqSyncGraph->ScrollMinY = 0;
			this->FreqSyncGraph->ScrollMinY2 = 0;
			this->FreqSyncGraph->Size = System::Drawing::Size(1200, 720);
			this->FreqSyncGraph->TabIndex = 181;
			// 
			// FreqSyncProgBar
			// 
			this->FreqSyncProgBar->Location = System::Drawing::Point(1207, 209);
			this->FreqSyncProgBar->Name = L"FreqSyncProgBar";
			this->FreqSyncProgBar->Size = System::Drawing::Size(350, 31);
			this->FreqSyncProgBar->TabIndex = 163;
			// 
			// FreqSyncProgressLabel
			// 
			this->FreqSyncProgressLabel->AutoSize = true;
			this->FreqSyncProgressLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FreqSyncProgressLabel->Location = System::Drawing::Point(1277, 243);
			this->FreqSyncProgressLabel->Name = L"FreqSyncProgressLabel";
			this->FreqSyncProgressLabel->Size = System::Drawing::Size(214, 24);
			this->FreqSyncProgressLabel->TabIndex = 164;
			this->FreqSyncProgressLabel->Text = L"Идёт построение... 0%";
			this->FreqSyncProgressLabel->Visible = false;
			// 
			// tabPage9
			// 
			this->tabPage9->Controls->Add(this->panel3);
			this->tabPage9->Controls->Add(this->MaxMuBetaGraph);
			this->tabPage9->Location = System::Drawing::Point(4, 22);
			this->tabPage9->Name = L"tabPage9";
			this->tabPage9->Size = System::Drawing::Size(1565, 730);
			this->tabPage9->TabIndex = 8;
			this->tabPage9->Text = L"График мю от бета";
			this->tabPage9->UseVisualStyleBackColor = true;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->button15);
			this->panel3->Controls->Add(this->progressBar5);
			this->panel3->Controls->Add(this->label37);
			this->panel3->Controls->Add(this->label38);
			this->panel3->Controls->Add(this->button16);
			this->panel3->Controls->Add(this->textBox14);
			this->panel3->Controls->Add(this->textBox15);
			this->panel3->Controls->Add(this->label39);
			this->panel3->Controls->Add(this->label40);
			this->panel3->Controls->Add(this->label41);
			this->panel3->Controls->Add(this->textBox16);
			this->panel3->Controls->Add(this->textBox17);
			this->panel3->Location = System::Drawing::Point(1204, 181);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(360, 288);
			this->panel3->TabIndex = 180;
			// 
			// button15
			// 
			this->button15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button15->Location = System::Drawing::Point(3, 139);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(168, 71);
			this->button15->TabIndex = 4;
			this->button15->Text = L"Начать построение";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &MyForm::button15_Click);
			// 
			// progressBar5
			// 
			this->progressBar5->Location = System::Drawing::Point(3, 216);
			this->progressBar5->Name = L"progressBar5";
			this->progressBar5->Size = System::Drawing::Size(352, 31);
			this->progressBar5->TabIndex = 163;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label37->Location = System::Drawing::Point(75, 250);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(214, 24);
			this->label37->TabIndex = 164;
			this->label37->Text = L"Идёт построение... 0%";
			this->label37->Visible = false;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label38->Location = System::Drawing::Point(50, 99);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(168, 24);
			this->label38->TabIndex = 169;
			this->label38->Text = L"Число измерений";
			// 
			// button16
			// 
			this->button16->Enabled = false;
			this->button16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button16->Location = System::Drawing::Point(180, 139);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(168, 71);
			this->button16->TabIndex = 173;
			this->button16->Text = L"Удалить график";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MyForm::button16_Click);
			// 
			// textBox14
			// 
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox14->Location = System::Drawing::Point(222, 96);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(57, 29);
			this->textBox14->TabIndex = 170;
			this->textBox14->Text = L"30";
			// 
			// textBox15
			// 
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox15->Location = System::Drawing::Point(161, 7);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(57, 29);
			this->textBox15->TabIndex = 171;
			this->textBox15->Text = L"1,03";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label39->Location = System::Drawing::Point(187, 50);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(48, 24);
			this->label39->TabIndex = 168;
			this->label39->Text = L"β₂ = ";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label40->Location = System::Drawing::Point(117, 10);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(40, 24);
			this->label40->TabIndex = 172;
			this->label40->Text = L"γ = ";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label41->Location = System::Drawing::Point(21, 53);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(48, 24);
			this->label41->TabIndex = 167;
			this->label41->Text = L"β₁ = ";
			// 
			// textBox16
			// 
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox16->Location = System::Drawing::Point(78, 50);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(57, 29);
			this->textBox16->TabIndex = 165;
			this->textBox16->Text = L"0,005";
			// 
			// textBox17
			// 
			this->textBox17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox17->Location = System::Drawing::Point(244, 47);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(57, 29);
			this->textBox17->TabIndex = 166;
			this->textBox17->Text = L"0,13";
			// 
			// MaxMuBetaGraph
			// 
			this->MaxMuBetaGraph->IsShowPointValues = true;
			this->MaxMuBetaGraph->Location = System::Drawing::Point(3, 4);
			this->MaxMuBetaGraph->Name = L"MaxMuBetaGraph";
			this->MaxMuBetaGraph->ScrollGrace = 0;
			this->MaxMuBetaGraph->ScrollMaxX = 0;
			this->MaxMuBetaGraph->ScrollMaxY = 0;
			this->MaxMuBetaGraph->ScrollMaxY2 = 0;
			this->MaxMuBetaGraph->ScrollMinX = 0;
			this->MaxMuBetaGraph->ScrollMinY = 0;
			this->MaxMuBetaGraph->ScrollMinY2 = 0;
			this->MaxMuBetaGraph->Size = System::Drawing::Size(1200, 720);
			this->MaxMuBetaGraph->TabIndex = 5;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->textBox5);
			this->tabPage4->Controls->Add(this->panel1);
			this->tabPage4->Controls->Add(this->textBox3);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1565, 730);
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
			this->panel1->Controls->Add(this->Gamma2MaxTB);
			this->panel1->Controls->Add(this->Gamma1MinTB);
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
			this->panel1->Controls->Add(this->Beta1TB);
			this->panel1->Controls->Add(this->GammaSetsCountTB);
			this->panel1->Controls->Add(this->Beta2TB);
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->BetaStepTB);
			this->panel1->Controls->Add(this->label12);
			this->panel1->Controls->Add(this->label16);
			this->panel1->Location = System::Drawing::Point(597, 115);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(633, 532);
			this->panel1->TabIndex = 156;
			// 
			// Gamma2MaxTB
			// 
			this->Gamma2MaxTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma2MaxTB->FormattingEnabled = true;
			this->Gamma2MaxTB->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1,1", L"2,1", L"3,1", L"4,1", L"5,1", L"1,03" });
			this->Gamma2MaxTB->Location = System::Drawing::Point(404, 14);
			this->Gamma2MaxTB->Name = L"Gamma2MaxTB";
			this->Gamma2MaxTB->Size = System::Drawing::Size(100, 32);
			this->Gamma2MaxTB->TabIndex = 170;
			this->Gamma2MaxTB->Text = L"1,1";
			// 
			// Gamma1MinTB
			// 
			this->Gamma1MinTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Gamma1MinTB->FormattingEnabled = true;
			this->Gamma1MinTB->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1", L"2", L"3", L"4", L"5", L"1,03" });
			this->Gamma1MinTB->Location = System::Drawing::Point(194, 14);
			this->Gamma1MinTB->Name = L"Gamma1MinTB";
			this->Gamma1MinTB->Size = System::Drawing::Size(100, 32);
			this->Gamma1MinTB->TabIndex = 169;
			this->Gamma1MinTB->Text = L"1";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(334, 13);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(70, 29);
			this->label14->TabIndex = 168;
			this->label14->Text = L"  γ₂ = ";
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
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(489, 82);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(132, 66);
			this->button3->TabIndex = 169;
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
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(73, 82);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 66);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Начать вычисления";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// Beta1TB
			// 
			this->Beta1TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Beta1TB->Location = System::Drawing::Point(232, 165);
			this->Beta1TB->Name = L"Beta1TB";
			this->Beta1TB->Size = System::Drawing::Size(57, 29);
			this->Beta1TB->TabIndex = 2;
			this->Beta1TB->Text = L"0,001";
			// 
			// GammaSetsCountTB
			// 
			this->GammaSetsCountTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->GammaSetsCountTB->Location = System::Drawing::Point(398, 243);
			this->GammaSetsCountTB->Name = L"GammaSetsCountTB";
			this->GammaSetsCountTB->Size = System::Drawing::Size(29, 29);
			this->GammaSetsCountTB->TabIndex = 152;
			this->GammaSetsCountTB->Text = L"50";
			// 
			// Beta2TB
			// 
			this->Beta2TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Beta2TB->Location = System::Drawing::Point(398, 162);
			this->Beta2TB->Name = L"Beta2TB";
			this->Beta2TB->Size = System::Drawing::Size(57, 29);
			this->Beta2TB->TabIndex = 3;
			this->Beta2TB->Text = L"0,005";
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
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
			// BetaStepTB
			// 
			this->BetaStepTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->BetaStepTB->Location = System::Drawing::Point(297, 203);
			this->BetaStepTB->Name = L"BetaStepTB";
			this->BetaStepTB->Size = System::Drawing::Size(79, 29);
			this->BetaStepTB->TabIndex = 7;
			this->BetaStepTB->Text = L"0,0002";
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
			this->tabPage5->Controls->Add(this->OmegaBetaGraph);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1565, 730);
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
			// OmegaBetaGraph
			// 
			this->OmegaBetaGraph->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OmegaBetaGraph->IsShowPointValues = true;
			this->OmegaBetaGraph->Location = System::Drawing::Point(3, 3);
			this->OmegaBetaGraph->Name = L"OmegaBetaGraph";
			this->OmegaBetaGraph->ScrollGrace = 0;
			this->OmegaBetaGraph->ScrollMaxX = 0;
			this->OmegaBetaGraph->ScrollMaxY = 0;
			this->OmegaBetaGraph->ScrollMaxY2 = 0;
			this->OmegaBetaGraph->ScrollMinX = 0;
			this->OmegaBetaGraph->ScrollMinY = 0;
			this->OmegaBetaGraph->ScrollMinY2 = 0;
			this->OmegaBetaGraph->Size = System::Drawing::Size(1559, 724);
			this->OmegaBetaGraph->TabIndex = 1;
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->checkBox4);
			this->tabPage6->Controls->Add(this->ClustersCountBetaGraph);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(1565, 730);
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
			// ClustersCountBetaGraph
			// 
			this->ClustersCountBetaGraph->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ClustersCountBetaGraph->IsShowPointValues = true;
			this->ClustersCountBetaGraph->Location = System::Drawing::Point(3, 3);
			this->ClustersCountBetaGraph->Name = L"ClustersCountBetaGraph";
			this->ClustersCountBetaGraph->ScrollGrace = 0;
			this->ClustersCountBetaGraph->ScrollMaxX = 0;
			this->ClustersCountBetaGraph->ScrollMaxY = 0;
			this->ClustersCountBetaGraph->ScrollMaxY2 = 0;
			this->ClustersCountBetaGraph->ScrollMinX = 0;
			this->ClustersCountBetaGraph->ScrollMinY = 0;
			this->ClustersCountBetaGraph->ScrollMinY2 = 0;
			this->ClustersCountBetaGraph->Size = System::Drawing::Size(1559, 724);
			this->ClustersCountBetaGraph->TabIndex = 148;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// SingleCalculationBW
			// 
			this->SingleCalculationBW->WorkerReportsProgress = true;
			this->SingleCalculationBW->WorkerSupportsCancellation = true;
			this->SingleCalculationBW->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::SingleCalculationBW_DoWork);
			this->SingleCalculationBW->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::SingleCalculationBW_ProgressChanged);
			this->SingleCalculationBW->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::SingleCalculationBW_RunWorkerCompleted);
			// 
			// backgroundWorker3
			// 
			this->backgroundWorker3->WorkerReportsProgress = true;
			this->backgroundWorker3->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker3_ProgressChanged);
			// 
			// backgroundWorker4
			// 
			this->backgroundWorker4->WorkerReportsProgress = true;
			this->backgroundWorker4->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker4_DoWork);
			this->backgroundWorker4->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker4_ProgressChanged);
			this->backgroundWorker4->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker4_RunWorkerCompleted);
			// 
			// backgroundWorker5
			// 
			this->backgroundWorker5->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker5_DoWork);
			this->backgroundWorker5->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker5_RunWorkerCompleted);
			// 
			// backgroundWorker6
			// 
			this->backgroundWorker6->WorkerReportsProgress = true;
			this->backgroundWorker6->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker6_DoWork);
			this->backgroundWorker6->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::backgroundWorker6_ProgressChanged);
			this->backgroundWorker6->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker6_RunWorkerCompleted);
			// 
			// FreqSyncBW
			// 
			this->FreqSyncBW->WorkerReportsProgress = true;
			this->FreqSyncBW->WorkerSupportsCancellation = true;
			this->FreqSyncBW->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::FreqSyncBW_DoWork);
			this->FreqSyncBW->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::FreqSyncBW_ProgressChanged);
			this->FreqSyncBW->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::FreqSyncBW_RunWorkerCompleted);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1573, 756);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Исследование коллективной динамики активных ротаторов";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->IntegrParams->ResumeLayout(false);
			this->IntegrParams->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GammaTable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->SystemParams->ResumeLayout(false);
			this->SystemParams->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->OmegaPan->ResumeLayout(false);
			this->OmegaPan->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MaxOmegaNUD))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TPhaseTable))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TimeOfSpikesTable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->tabPage7->ResumeLayout(false);
			this->tabPage7->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->tabPage8->ResumeLayout(false);
			this->tabPage8->PerformLayout();
			this->FreqSyncPanel->ResumeLayout(false);
			this->FreqSyncPanel->PerformLayout();
			this->tabPage9->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
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

		//Для вычислений без сбора дополнительной информации и с возможностью остановки backgroundWorker
		private: int PerformCalculations(int NumOfEquations, double endTime, double Beta, double& _E0, double& _E0Star, double& _ts, double* fi, double* fipl1, BackgroundWorker^ bw)
		{
			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double g = Convert::ToDouble(gTB->Text);              //Коэффициент связи
			const double alpha = Convert::ToDouble(AlphaTB->Text);      //Число α
			double t = 0.0;                                             //Текущее время       

			const double D2PI = 2 * M_PI;
			double oldE0;

			//Основной цикл: Вычисление φⱼ(t) методом Рунге-Кутта 4-го порядка
			//Без подсчетов какой-либо дополнительной информации
			for (t; t < endTime; t += h)
			{
				if (bw->CancellationPending)
				{
					return -1;
				}
				t = round(t * 1000) / 1000;
				for (int j = 0; j < NumOfEquations; j++)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
					{
						oldE0 = _E0;
						_E0 = E(t + h, _ts, _E0, _E0Star, alpha);          //Пересчет начальных условий
						_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
						_E0Star += Beta;                                //Добавление β к начальному значению производной
						_ts = t + h;                                    //Изменение времени последнего спайка
						fi[j] = 0.0;                                   //Обнуление значения ф
					}
				}
				bw->ReportProgress((int)(t / (T - h) * 100));
			}

			return 0;
		}

		//Для вычислений со сбором информации о средних частотах и с возможностью остановки backgroundWorker
		private: int PerformCalculations(int NumOfEquations, double startTime, double endTime, double Beta, double& _E0, double& _E0Star, double& _ts, int* clustersArr, double* fi,
			double* fipl1, double* fi0, BackgroundWorker^ bw)
		{
			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double g = Convert::ToDouble(gTB->Text);              //Коэффициент связи
			const double alpha = Convert::ToDouble(AlphaTB->Text);      //Число α
			double t = startTime;                                       //Текущее время

			const double D2PI = 2 * M_PI;
			double oldE0;
			// Первая итерация отдельно-------------------------------------------------------------------------------------------------------------------------------------------
			if (bw->CancellationPending)
			{
				return -1;
			}
			t = round(t * 1000) / 1000;
			for (int j = 0; j < NumOfEquations; j++)
			{
				if (bw->CancellationPending)
				{
					return -1;
				}
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
				fi[j] = fipl1[j];

				if (fi[j] >= D2PI)                              //В моемент импульса j-го ротатора
				{
					oldE0 = _E0;
					_E0 = E(t + h, _ts, _E0, _E0Star, alpha);          //Пересчет начальных условий
					_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
					_E0Star += Beta;                                //Добавление β к начальному значению производной
					_ts = t + h;                                    //Изменение времени последнего спайка
					fi[j] = 0.0;                                   //Обнуление значения ф
					clustersArr[j]++;                              //Увеличение числа спайков на 1
				}
			}

			for (int l = 0; l < NumOfEquations; l++)
			{
				fi0[l] = fi[l];                                    //Запоминание значений фаз при t = T₁
			}

			bw->ReportProgress((int)(t / (T - h) * 100));
			t += h;
			//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

			for (t; t < endTime; t += h)
			{
				if (bw->CancellationPending)
				{
					return -1;
				}
				t = round(t * 1000) / 1000;
				for (int j = 0; j < NumOfEquations; j++)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
					{
						oldE0 = _E0;
						_E0 = E(t + h, _ts, _E0, _E0Star, alpha);           //Пересчет начальных условий
						_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
						_E0Star += Beta;                                 //Добавление β к начальному значению производной
						_ts = t + h;                                     //Изменение времени последнего спайка
						fi[j] = 0.0;                                    //Обнуление значения ф
						clustersArr[j]++;                               //Увеличение числа спайков на 1
					}
				}

				bw->ReportProgress((int)(t / (T - h) * 100));
			}

			return 0;
		}

		//Для вычислений со сбором информации о спайках, среднем поле и параметре фазовой синхронизации и с возможностью остановки backgroundWorker
		private: int PerformCalculations(int NumOfEquations, double startTime, double endTime, double Beta, double& _E0, double& _E0Star, double& _ts, double* fi, double* fipl1,
			PointPairList^ E_PPL, PointPairList^ Mu_PPL, BackgroundWorker^ bw)
		{
			GraphPane^ panel = SpikesGraph->GraphPane;
			panel->CurveList->Clear();

			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double g = Convert::ToDouble(gTB->Text);              //Коэффициент связи
			const double alpha = Convert::ToDouble(AlphaTB->Text);      //Число α
			double Et;                                                  //Поле E(t)
			double t = startTime;                                       //Текущее время
			complex<double> Mu;                                         //Параметр фазовой синхронизации μ

			const double D2PI = 2 * M_PI;
			bool spike_flag = false;
			double oldE0;
			complex<double> CompFi;
			const complex<double> CompN((double)NumOfEquations, 0.0);

			for (t; t < endTime; t += h)
			{
				if (bw->CancellationPending)
				{
					return -1;
				}
				t = round(t * 1000) / 1000;
				Mu = complex<double>(0.0, 0.0);
				for (int j = 0; j < NumOfEquations; j++)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                      //В моемент импульса j-го ротатора
					{
						oldE0 = _E0;
						_E0 = E(t + h, _ts, _E0, _E0Star, alpha);           //Пересчет начальных условий
						_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
						_E0Star += Beta;                                    //Добавление β к начальному значению производной
						_ts = t + h;                                        //Изменение времени последнего спайка
						fi[j] = 0.0;                                        //Обнуление значения ф
						if (!spike_flag)                                    //Отбражение нового спайка на графике
						{
							PointPairList^ Spaik_list = gcnew PointPairList();
							Spaik_list->Add(_ts, 0.0);
							Spaik_list->Add(_ts, 1.0);

							LineItem^ Curve7 = panel->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

							SpikesGraph->AxisChange();
							SpikesGraph->Invalidate();
							spike_flag = true;
						}
					}
					CompFi = polar<double>(1.0, fi[j]);
					Mu += CompFi;
				}
				spike_flag = false;

				Et = E(t + h, _ts, _E0, _E0Star, alpha);
				E_PPL->Add(t + h, Et);
				Mu = Mu / CompN;
				Mu_PPL->Add(t + h, abs(Mu));

				bw->ReportProgress((int)(t / (T - h) * 100));
			}

			return 0;
		}

		//Для вычислений со сбором информации о частотах, спайках, среднем поле и параметре фазовой синхронизации и с возможностью остановки backgroundWorker
		private: int PerformCalculations(bool T1LessThanT2, int NumOfEquations, double startTime, double Beta, double& _E0, double& _E0Star, double& _ts, int* clustersArr, double* fi,
			double* fipl1, double* fi0, PointPairList^ E_PPL, PointPairList^ Mu_PPL, BackgroundWorker^ bw)
		{
			GraphPane^ panel = SpikesGraph->GraphPane;
			panel->CurveList->Clear();

			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double g = Convert::ToDouble(gTB->Text);              //Коэффициент связи
			const double alpha = Convert::ToDouble(AlphaTB->Text);      //Число α
			double Et;                                                  //Поле E(t)
			double t = startTime;                                       //Текущее время
			complex<double> Mu;                                         //Параметр фазовой синхронизации μ
			const double D2PI = 2 * M_PI;
			bool spike_flag = false;
			double oldE0;
			complex<double> CompFi;
			const complex<double> CompN((double)NumOfEquations, 0.0);

			if (T1LessThanT2)
			{
				for (t; t < T; t += h)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					t = round(t * 1000) / 1000;
					Mu = complex<double>(0.0, 0.0);
					for (int j = 0; j < NumOfEquations; j++)
					{
						if (bw->CancellationPending)
						{
							return -1;
						}
						//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
						fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
						fi[j] = fipl1[j];

						if (fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
						{
							oldE0 = _E0;
							_E0 = E(t + h, _ts, _E0, _E0Star, alpha);           //Пересчет начальных условий
							_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
							_E0Star += Beta;                                 //Добавление β к начальному значению производной
							_ts = t + h;                                     //Изменение времени последнего спайка
							fi[j] = 0.0;                                    //Обнуление значения ф
							clustersArr[j]++;                               //Увеличение числа спайков на 1
							if (!spike_flag)                                //Отбражение нового спайка на графике
							{
								PointPairList^ Spaik_list = gcnew PointPairList();
								Spaik_list->Add(_ts, 0.0);
								Spaik_list->Add(_ts, 1.0);

								LineItem^ Curve7 = panel->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

								SpikesGraph->AxisChange();
								SpikesGraph->Invalidate();
								spike_flag = true;
							}
						}
						CompFi = polar<double>(1.0, fi[j]);
						Mu += CompFi;
					}
					spike_flag = false;

					Et = E(t + h, _ts, _E0, _E0Star, alpha);
					E_PPL->Add(t + h, Et);
					Mu = Mu / CompN;
					Mu_PPL->Add(t + h, abs(Mu));

					bw->ReportProgress((int)(t / (T - h) * 100));
				}
			}
			else
			{
				// Первая итерация отдельно-------------------------------------------------------------------------------------------------------------------------------------------
				if (bw->CancellationPending)
				{
					return -1;
				}
				t = round(t * 1000) / 1000;
				Mu = complex<double>(0.0, 0.0);
				for (int j = 0; j < NumOfEquations; j++)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                              //В моемент импульса j-го ротатора
					{
						oldE0 = _E0;
						_E0 = E(t + h, _ts, _E0, _E0Star, alpha);          //Пересчет начальных условий
						_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
						_E0Star += Beta;                                //Добавление β к начальному значению производной
						_ts = t + h;                                    //Изменение времени последнего спайка
						fi[j] = 0.0;                                   //Обнуление значения ф
						clustersArr[j]++;                              //Увеличение числа спайков на 1
						if (!spike_flag)                               //Отбражение нового спайка на графике
						{
							PointPairList^ Spaik_list = gcnew PointPairList();
							Spaik_list->Add(_ts, 0.0);
							Spaik_list->Add(_ts, 1.0);

							LineItem^ Curve7 = panel->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

							SpikesGraph->AxisChange();
							SpikesGraph->Invalidate();
							spike_flag = true;
						}
					}
					CompFi = polar<double>(1.0, fi[j]);
					Mu += CompFi;
				}
				spike_flag = false;

				Et = E(t + h, _ts, _E0, _E0Star, alpha);
				E_PPL->Add(t + h, Et);
				Mu = Mu / CompN;
				Mu_PPL->Add(t + h, abs(Mu));

				for (int l = 0; l < NumOfEquations; l++)
				{
					fi0[l] = fi[l];                                     //Запоминание значений фаз при t = T₁
				}

				t += h;

				bw->ReportProgress((int)(t / (T - h) * 100));
				//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

				for (t; t < T; t += h)
				{
					if (bw->CancellationPending)
					{
						return -1;
					}
					t = round(t * 1000) / 1000;
					Mu = complex<double>(0.0, 0.0);
					for (int j = 0; j < NumOfEquations; j++)
					{
						if (bw->CancellationPending)
						{
							return -1;
						}
						//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
						fipl1[j] = RK4(t, _ts, fi[j], h, gamma[j], g, _E0, _E0Star, alpha);
						fi[j] = fipl1[j];

						if (fi[j] >= D2PI)                                  //В моемент импульса j-го ротатора
						{
							oldE0 = _E0;
							_E0 = E(t + h, _ts, _E0, _E0Star, alpha);           //Пересчет начальных условий
							_E0Star = dEdt(t + h, _ts, oldE0, _E0Star, alpha);
							_E0Star += Beta;                                 //Добавление β к начальному значению производной
							_ts = t + h;                                     //Изменение времени последнего спайка
							fi[j] = 0.0;                                    //Обнуление значения ф
							clustersArr[j]++;                                         //Увеличение числа спайков на 1	
							if (!spike_flag)                                //Отбражение нового спайка на графике
							{
								PointPairList^ Spaik_list = gcnew PointPairList();
								Spaik_list->Add(_ts, 0.0);
								Spaik_list->Add(_ts, 1.0);

								LineItem^ Curve7 = panel->AddCurve("", Spaik_list, Color::Red, SymbolType::None);

								SpikesGraph->AxisChange();
								SpikesGraph->Invalidate();
								spike_flag = true;
							}
						}
						CompFi = polar<double>(1.0, fi[j]);
						Mu += CompFi;
					}
					spike_flag = false;

					Et = E(t + h, _ts, _E0, _E0Star, alpha);
					E_PPL->Add(t + h, Et);
					Mu = Mu / CompN;
					Mu_PPL->Add(t + h, abs(Mu));

					bw->ReportProgress((int)(t / (T - h) * 100));
				}
			}

			return 0;
		}

		//Для вычислений с подсчётом параметра фазовой синхронизации и своим набором гамма
		private: int PerformCalculations(int NumOfEquations, double _beta, complex<double> &mu, double* fi, double* fipl1, double* gamma)
		{
			const double h = Convert::ToDouble(hTB->Text);                   //Шаг интегрирования
			const double T = Convert::ToDouble(T_TB->Text);                  //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double alpha = Convert::ToDouble(AlphaTB->Text);           //Число α
			const double g = Convert::ToDouble(gTB->Text);                   //Коэффициент связи
			double E0 = Convert::ToDouble(E0_Text->Text);                    //Начальное условие для E
			double E0Star = Convert::ToDouble(E0Star_Text->Text);            //Начальное условие для Ė
			double t = 0.0;                                                  //Время
			double ts = 0.0;
			double oldE0;
			const double D2PI = 2 * M_PI;
			const complex<double> CompN((double)NumOfEquations, 0.0);
			complex<double> CompFi;

			//t от 0 до T - h---------------------------------------------------------------------------------------------------------------------------------
			for (t; t < T - h; t += h)
			{
				t = round(t * 1000) / 1000;
				for (int j = 0; j < NumOfEquations; j++)
				{
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, ts, fi[j], h, gamma[j], g, E0, E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
					{
						oldE0 = E0;
						E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
						E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
						E0Star += _beta;                                //Добавление β к начальному значению производной
						ts = t + h;                                    //Изменение времени последнего спайка
						fi[j] = 0.0;			                       //Обнуление значения ф
					}
				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------------
			//t от T - h до T---------------------------------------------------------------------------------------------------------------------------------
			t = round(t * 1000) / 1000;
			mu = complex<double>(0.0, 0.0);

			for (int j = 0; j < NumOfEquations; j++)
			{
				//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
				fipl1[j] = RK4(t, ts, fi[j], h, gamma[j], g, E0, E0Star, alpha);
				fi[j] = fipl1[j];

				if (fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
				{
					oldE0 = E0;
					E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
					E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
					E0Star += _beta;                                //Добавление β к начальному значению производной
					ts = t + h;                                    //Изменение времени последнего спайка
					fi[j] = 0.0;			                       //Обнуление значения ф
				}
				CompFi = polar<double>(1.0, fi[j]);
				mu += CompFi;
			}
			mu = mu / CompN;
			t += h;
			//------------------------------------------------------------------------------------------------------------------------------------------------
			return 0;
		}
		//Для вычислений с подсчётом максимума параметра фазовой синхронизации и своим набором гамма
		private: int PerformCalculations(int NumOfEquations, double _beta, double &maxAbsmu, double* fi, double* fipl1, double* gamma) 
		{
			const double h = Convert::ToDouble(hTB->Text);                   //Шаг интегрирования
			const double T = Convert::ToDouble(T_TB->Text);                  //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double alpha = Convert::ToDouble(AlphaTB->Text);           //Число α
			const double g = Convert::ToDouble(gTB->Text);                   //Коэффициент связи
			double E0 = Convert::ToDouble(E0_Text->Text);                    //Начальное условие для E
			double E0Star = Convert::ToDouble(E0Star_Text->Text);            //Начальное условие для Ė
			double t = 0.0;                                                  //Время
			const double T2 = Convert::ToDouble(T02_text->Text);
			double oldE0;
			double ts = 0.0;

			const double D2PI = 2 * M_PI;

			complex<double> Mu;
			complex<double> CompFi;
			const complex<double> CompN((double)NumOfEquations, 0.0);

			//t от 0 до T02 - h-------------------------------------------------------------------------------------------------------------------------------
			for (t; t < T2 - h; t += h)
			{
				t = round(t * 1000) / 1000;
				for (int j = 0; j < NumOfEquations; j++)
				{
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, ts, fi[j], h, gamma[j], g, E0, E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
					{
						oldE0 = E0;
						E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
						E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
						E0Star += _beta;                                //Добавление β к начальному значению производной
						ts = t + h;                                    //Изменение времени последнего спайка
						fi[j] = 0.0;			                       //Обнуление значения ф
					}
				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------------
			//t от T02 до T-----------------------------------------------------------------------------------------------------------------------------------
			for (t; t < T; t += h)
			{
				t = round(t * 1000) / 1000;
				Mu = complex<double>(0.0, 0.0);
				for (int j = 0; j < NumOfEquations; j++)
				{
					//Вычисление нового значения φⱼ(t) методом Рунге-Кутта 4-го порядка
					fipl1[j] = RK4(t, ts, fi[j], h, gamma[j], g, E0, E0Star, alpha);
					fi[j] = fipl1[j];

					if (fi[j] >= D2PI)                                 //В моемент импульса j-го ротатора
					{
						oldE0 = E0;
						E0 = E(t + h, ts, E0, E0Star, alpha);          //Пересчет начальных условий
						E0Star = dEdt(t + h, ts, oldE0, E0Star, alpha);
						E0Star += _beta;                                //Добавление β к начальному значению производной
						ts = t + h;                                    //Изменение времени последнего спайка
						fi[j] = 0.0;			                       //Обнуление значения ф
					}
					CompFi = polar<double>(1.0, fi[j]);
					Mu += CompFi;
				}
				Mu = Mu / CompN;

				if (abs(Mu) > maxAbsmu)
				{
					maxAbsmu = abs(Mu);
				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------------

			return 0;
		}

		private: System::Void SingleCalculationBW_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
		{
			GraphPane^ panel2 = OmegaGraph->GraphPane;
			GraphPane^ panel4 = E_fieldGraph->GraphPane;
			GraphPane^ panel5 = PhSyncParamGraph->GraphPane;
			GraphPane^ panel6 = PhasesGraph->GraphPane;

			panel4->CurveList->Clear();
			panel5->CurveList->Clear();
			panel6->CurveList->Clear();

			panel2->YAxis->Scale->MajorStepAuto = true;
			panel2->YAxis->Scale->MinorStepAuto = true;
			panel2->Title->Text = L"График средних частот Ωⱼ";

			PointPairList^ g_list = gcnew PointPairList();              //Список точек для графика средних частот Ω
			PointPairList^ E_list = gcnew PointPairList();	            //Список точек для графика поля E(t)
			PointPairList^ Mu_list = gcnew PointPairList();             //Список точек для графика |μ| от t
			PointPairList^ FIT_list = gcnew PointPairList();            //Список точек для графика φⱼ(T) в конечный момент времени

			const int n = Convert::ToInt32(nTB->Text);                  //Число уравнений в системе
			const int p = Convert::ToInt32(IterationsTB->Text);         //Максимальное число итераций
			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double T01 = Convert::ToDouble(T1_TB->Text);          //Начальное время, от которого будет считаться частота
			const double T02 = Convert::ToDouble(T02_text->Text);       //Начальное время, от которого будут рисоваться график E(t) и график числа спайков
			const double beta = Convert::ToDouble(textBox7->Text);      //Параметр β
			int NumOfClusters;                                          //Число кластеров при t = T
			int IndexOfMaxOmega, IndexOfMinOmega;                       //Номера элементов с максимальными и минимальными частотами
			double E0 = Convert::ToDouble(E0_Text->Text);               //Начальное условие для E
			double E0Star = Convert::ToDouble(E0Star_Text->Text);       //Начальное условие для Ė
			double MaxOmega = -100000.0, MinOmega = 100000.0;           //Максимальная и минимальная средние частоты
			double ts = 0.0;                                            //Время последнего спайка
			int* k;                                                     //Число спайков для каждого ротатора
			double* Fi0;		                                        //Фазы при t = T₁
			double* Fi, * Fiplus1;	                                    //Фазы φⱼ(t) j = 0,...,n - 1
			double* Omega;                                              //Средние частоты Ω

			Str = "";

			const double D2PI = 2 * M_PI;

			if (T01 > T || T02 > T)
			{
				MessageBox::Show(L"T₁ и T₂ должны быть меньше или равны T", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			Fi = new double[n];
			Fiplus1 = new double[n];
			Omega = new double[n];
			Fi0 = new double[n];
			k = new int[n];

			double tmin_limit = - 0.05;

			if (gamma1 != gamma2)
			{
				for (int i = 0; i < n; i++)                //Начальные условия для каждого из φⱼ(t) равны нулю
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
				for (int i = 0; i < n; i++)
				{
					Fi[i] = Fi0[i] = distr(me);
					Fiplus1[i] = 0.0;
					k[i] = 0;                          //Изначальное число спайков равно нулю
				}
			}

			//Основной цикл: Вычисление φⱼ(t) методом Рунге-Кутта 4-го порядка
			if (T01 <= T02)
			{
				int res = PerformCalculations(n, T01 - h, beta, E0, E0Star, ts, Fi, Fiplus1, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				res = PerformCalculations(n, T01 - h, T02 - h, beta, E0, E0Star, ts, k, Fi, Fiplus1, Fi0, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				res = PerformCalculations(true, n, T02 - h, beta, E0, E0Star, ts, k, Fi, Fiplus1, Fi0, E_list, Mu_list, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}
			}
			else
			{
				int res = PerformCalculations(n, T02 - h, beta, E0, E0Star, ts, Fi, Fiplus1, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				res = PerformCalculations(n, T02 - h, T01 - h, beta, E0, E0Star, ts, Fi, Fiplus1, E_list, Mu_list, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				res = PerformCalculations(false, n, T02 - h, beta, E0, E0Star, ts, k, Fi, Fiplus1, Fi0, E_list, Mu_list, SingleCalculationBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}
			}

			//Вычисление средних частот
			for (int i = 0; i < n; i++)
			{
				//Вычисление значения частоты
				if (k[i] != 0)
				{
					Omega[i] = ((k[i] - 1) * D2PI + Fi[i] - Fi0[i]) / (T - T01);
				}
				else
				{
					Omega[i] = (Fi[i] - Fi0[i]) / (T - T01);
				}
				g_list->Add(i, Omega[i]);
				FIT_list->Add(i, Fi[i]);

				//Вычисление максимальной средней частоты
				if (Omega[i] > MaxOmega)
				{
					MaxOmega = Omega[i];
					IndexOfMaxOmega = i;
				}
				//Вычисление минимальной средней частоты
				if (Omega[i] < MinOmega)
				{
					MinOmega = Omega[i];
					IndexOfMinOmega = i;
				}
			}

			g_list->Remove(gcnew PointPair(IndexOfMaxOmega, MaxOmega));
			g_list->Remove(gcnew PointPair(IndexOfMinOmega, MinOmega));

			NumOfClusters = GetNumberOfClusters(Omega, n);	 //Вычисление числа кластеров при t = T

			//Заполнение справки
			Str += "Для вычислений был использован метод Рунге-Кутта 4-го порядка.\r\n\r\n";
			Str += String::Format(L"γⱼ были взяты из интервала [{0:G3}; {1:G3}]\r\n\r\nЧисло кластеров при t = T:{2}", gamma1, gamma2, NumOfClusters);

			double tmax_limit = T + 0.05;

			PointPairList^ MinMaxOmegaList = gcnew PointPairList();

			//Рисование графиков
			LineItem^ Curve6 = panel2->AddCurve(String::Format(L"β = {0}, кластеров: {1}", Convert::ToDouble(textBox7->Text), NumOfClusters), g_list, Color::Red, SymbolType::Circle);
			LineItem^ Curve7 = panel4->AddCurve("E(t)", E_list, Color::Red, SymbolType::None);
			LineItem^ Curve8 = panel5->AddCurve(L"|μ|(t)", Mu_list, Color::Red, SymbolType::None);
			LineItem^ Curve9 = panel6->AddCurve(L"φⱼ(T)", FIT_list, Color::Blue, SymbolType::Circle);

			MinMaxOmegaList->Add(IndexOfMaxOmega, MaxOmega);
			MinMaxOmegaList->Add(IndexOfMinOmega, MinOmega);

			LineItem^ CurveMinMaxOmega = panel2->AddCurve("", MinMaxOmegaList, Color::Green, SymbolType::Circle);

			//panel2->Title->Text += String::Format("\nКластеров: {0}", NumOfClusters);

			float pointsSize = 6.0f;

			Curve6->Line->IsVisible = false;
			Curve6->Symbol->Fill->Color = Colors[panel2->CurveList->Count - 1 % Colors->Length - 1];
			Curve6->Symbol->Border->Color = Colors[panel2->CurveList->Count - 1 % Colors->Length - 1];
			Curve6->Symbol->Fill->Type = FillType::Solid;
			Curve6->Symbol->Size = pointsSize;

			CurveMinMaxOmega->Line->IsVisible = false;
			CurveMinMaxOmega->Symbol->Fill->Color = Color::Green;
			CurveMinMaxOmega->Symbol->Fill->Type = FillType::Solid;
			CurveMinMaxOmega->Symbol->Size = pointsSize;

			Curve9->Line->IsVisible = false;
			Curve9->Symbol->Fill->Color = Color::Blue;
			Curve9->Symbol->Fill->Type = FillType::Solid;
			Curve9->Symbol->Size = pointsSize;

			panel2->XAxis->Scale->Min = -1;
			panel2->XAxis->Scale->Max = n;
			//double yaxisOffset = Convert::ToDouble(OffsetTB->Text);
			//panel2->YAxis->Scale->Min = MinOmega - yaxisOffset;
			//panel2->YAxis->Scale->Max = MaxOmega + yaxisOffset;
			//Omega1TB->Text = String::Format("{0}", Math::Round(MinOmega - yaxisOffset, 3));
			//Omega2TB->Text = String::Format("{0}", Math::Round(MaxOmega + yaxisOffset, 3));

			OmegaGraph->AxisChange();

			ArrowObj^ Arr1 = gcnew ArrowObj(IndexOfMaxOmega + 1.5, MaxOmega + (MaxOmega - MinOmega) * 0.5, IndexOfMaxOmega, MaxOmega);
			ArrowObj^ Arr2 = gcnew ArrowObj(IndexOfMinOmega + 1.5, MinOmega - (MaxOmega - MinOmega) * 0.5, IndexOfMinOmega, MinOmega);
			LineObj^ Line1 = gcnew LineObj(Arr1->Location->X1, Arr1->Location->Y1, Arr1->Location->X1 + 1.5, Arr1->Location->Y1);
			LineObj^ Line2 = gcnew LineObj(Arr2->Location->X1, Arr2->Location->Y1, Arr2->Location->X1 + 1.5, Arr2->Location->Y1);
			TextObj^ Text1 = gcnew TextObj("Max", (Line1->Location->X1 + Line1->Location->X2) * 0.5, Line1->Location->Y1 + (MaxOmega - MinOmega) * 0.1);
			TextObj^ Text2 = gcnew TextObj("Min", (Line2->Location->X1 + Line2->Location->X2) * 0.5, Line2->Location->Y1 + (MaxOmega - MinOmega) * 0.1);

			Arr1->IsVisible = false;
			Arr2->IsVisible = false;
			Line1->IsVisible = false;
			Line2->IsVisible = false;
			Text1->FontSpec->Border->IsVisible = false;
			Text1->FontSpec->Fill->Color = Color::Transparent;
			Text1->IsVisible = false;
			Text2->FontSpec->Border->IsVisible = false;
			Text2->FontSpec->Fill->Color = Color::Transparent;
			Text2->IsVisible = false;

			panel2->GraphObjList->Add(Arr1);
			panel2->GraphObjList->Add(Arr2);
			panel2->GraphObjList->Add(Line1);
			panel2->GraphObjList->Add(Line2);
			panel2->GraphObjList->Add(Text1);
			panel2->GraphObjList->Add(Text2);

			panel6->XAxis->Scale->Min = -1;
			panel6->XAxis->Scale->Max = n;

			SpikesGraph->GraphPane->XAxis->Scale->Max = T + 0.05;
			SpikesGraph->GraphPane->XAxis->Scale->Min = T02 - 0.05;

			panel4->XAxis->Scale->Max = T + 0.05;
			panel4->XAxis->Scale->Min = T02 - 0.05;

			panel5->XAxis->Scale->Max = T + 0.05;
			panel5->XAxis->Scale->Min = T02 - 0.05;

			OmegaGraph->AxisChange();
			OmegaGraph->Invalidate();
			E_fieldGraph->AxisChange();
			E_fieldGraph->Invalidate();
			PhSyncParamGraph->AxisChange();
			PhSyncParamGraph->Invalidate();
			PhasesGraph->AxisChange();
			PhasesGraph->Invalidate();

			delete[]Fi;
			delete[]Fiplus1;
			delete[]Omega;
			delete[]Fi0;
			delete[]k;
		}

		private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
		{
			GraphPane^ panel = OmegaBetaGraph->GraphPane;
			GraphPane^ panel2 = ClustersCountBetaGraph->GraphPane;

			const int n = Convert::ToInt32(nTB->Text);                       //Число уравнений в системе
			const int p = Convert::ToInt32(IterationsTB->Text);              //Число итераций, второй критерий остановки
			const int NumOfSets = Convert::ToInt32(GammaSetsCountTB->Text);  //Число наборов
			const double gamma1Copy = Convert::ToDouble(Gamma1MinTB->Text);  //Минимальное значение γ₁
			const double gamma2Copy = Convert::ToDouble(Gamma2MaxTB->Text);	 //Максимальное значение γ₂
			const double beta1 = Convert::ToDouble(Beta1TB->Text);           //Начальное значение β
			const double beta2 = Convert::ToDouble(Beta2TB->Text);           //Конечное значение β
			const double betaStep = Convert::ToDouble(BetaStepTB->Text);     //Шаг по β
			const double h = Convert::ToDouble(hTB->Text);                   //Шаг интегрирования
			const double T1 = Convert::ToDouble(T1_TB->Text);                //Начальное время, от которого будет считаться частота	
			const double T = Convert::ToDouble(T_TB->Text);                  //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double alpha = Convert::ToDouble(AlphaTB->Text);           //Число α
			const double g = Convert::ToDouble(gTB->Text);                   //Коэффициент связи
			int non = 0;                                                     //Число точек на графике, в которых считаются средние частоты 
			double E0;                                                       //Начальное условие для E    
			double E0Star;                                                   //Начальное условие для Ė
			double t;                                                        //Время			
			int* NumOfClusters;                                              //Массив для хранения числа кластеров
			int* k;                                                          //Число спайков для каждого ротатора
			double** Omega;                                                  //Средние частоты
			double* om;                                                      //Технический массив для вычислений 
			double* Fi;                                                      //Фазы φⱼ(t) j = 0,...,n - 1
			double* Fiplus1;                                                 //Фазы φⱼ(t) j = 0,...,n - 1
			double* cur_gamma;                                               //Набор случайных параметров γⱼ
			double* Fi0;                                                     //Фазы при t = T₁

			const double D2PI = 2 * M_PI;                                    //Константа 2π

			if (T1 > T)
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

			PointPairList^ Cl_list;
			cli::array<PointPairList^>^ Omega_List;

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

					cur_gamma = Set_Gamma_in_range(n, gamma1Copy, gamma2Copy);
					NumOfClusters = new int[non];
					Omega = new double* [n];
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
						for (t; t < T1 - h; t += h)
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
						//t от T₁ - h до T₁
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
						//t от T₁ до T
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
								Omega[i][index] = ((k[i] - 1) * D2PI + Fi[i] - Fi0[i]) / (t - T1);
							}
							else
							{
								Omega[i][index] = (Fi[i] - Fi0[i]) / (t - T1);
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
						LineItem^ Curve;
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

					OmegaBetaGraph->AxisChange();
					OmegaBetaGraph->Invalidate();

					_beta = beta1;

					for (int i = 0; i < non; i++)
					{
						Cl_list->Add(_beta, NumOfClusters[i]);
						_beta += betaStep;
						_beta = round(_beta * 100000) / 100000;
					}
					LineItem^ Curve2;
#pragma omp critical (DrawClusGraph)
					Curve2 = panel2->AddCurve(Convert::ToString(GlobalInd), Cl_list, Colors[GlobalInd], SymbolType::Circle);
					Curve2->Symbol->Fill->Color = Colors[GlobalInd];
					Curve2->Symbol->Fill->Type = FillType::Solid;
					Curve2->Line->IsVisible = false;

					ClustersCountBetaGraph->AxisChange();
					ClustersCountBetaGraph->Invalidate();

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

		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{

			Int32 NumOfSets = Convert::ToInt32(GammaSetsCountTB->Text);

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

			Beta1TB->ReadOnly = true;
			Beta2TB->ReadOnly = true;
			BetaStepTB->ReadOnly = true;
			GammaSetsCountTB->ReadOnly = true;
			label15->Text = "Идут вычисления... 0%";
			label15->Visible = true;
			button2->Enabled = false;
			Gamma2MaxTB->Enabled = false;
			Gamma1MinTB->Enabled = false;
			button3->Enabled = true;
			button3->Focus();

			backgroundWorker1->RunWorkerAsync();
		}

		private: System::Void Change_scale_Omega_Click(System::Object^ sender, System::EventArgs^ e)
		{
			GraphPane^ panel = OmegaGraph->GraphPane;

			if (Omega1TB->Text != String::Empty)
			{
				double Om1 = Convert::ToDouble(Omega1TB->Text);
				panel->YAxis->Scale->Min = Om1;
			}

			if(Omega2TB->Text != String::Empty)
			{
				double Om2 = Convert::ToDouble(Omega2TB->Text);
				panel->YAxis->Scale->Max = Om2;
			}
			panel->YAxis->Scale->MajorStepAuto = false;
			panel->YAxis->Scale->MinorStepAuto = false;
			panel->YAxis->Scale->MajorStep = (panel->YAxis->Scale->Max - panel->YAxis->Scale->Min) * 0.1;
			panel->YAxis->Scale->MinorStep = (panel->YAxis->Scale->Max - panel->YAxis->Scale->Min) * 0.02;
			OmegaGraph->AxisChange();
			OmegaGraph->Invalidate();
		}

		private: System::Void CreateGammaBtn_Click(System::Object^ sender, System::EventArgs^ e)
		{
			GammaTable->Rows->Clear();

			const int n = Convert::ToInt32(nTB->Text);
			const double gamma0 = Convert::ToDouble(Gamma0CmbB->Text);
			const double delta = Convert::ToDouble(DeltaCmbB->Text);

			gamma = Set_Gamma(n, gamma0, delta);
			gamma1 = gamma2 = gamma[0];
			qsort((void*)gamma, (size_t)n, sizeof(double), compare);

			GammaTable->Rows->Add(n);
			GammaTable->Rows[0]->Cells[0]->Value = 0;
			GammaTable->Rows[0]->Cells[1]->Value = gamma[0];

			for (int i = 1; i < n; i++)
			{
				if (gamma[i] > gamma2)
				{
					gamma2 = gamma[i];
				}
				if (gamma[i] < gamma1)
				{
					gamma1 = gamma[i];
				}

				GammaTable->Rows[i]->Cells[0]->Value = i;
				GammaTable->Rows[i]->Cells[1]->Value = gamma[i];
			}

			StartBtn->Enabled = true;
			SaveSetToFileBtn->Enabled = true;

			MessageBox::Show("Набор сгенерирован", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		}

		private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
		{
			OmegaBetaGraph->GraphPane->CurveList->Clear();
			ClustersCountBetaGraph->GraphPane->CurveList->Clear();
			Beta1TB->ReadOnly = false;
			Beta2TB->ReadOnly = false;
			BetaStepTB->ReadOnly = false;
			GammaSetsCountTB->ReadOnly = false;
			AvgMaxMinAlreadyExists = false;
			Gamma2MaxTB->Enabled = true;
			Gamma1MinTB->Enabled = true;

			ClustersCountBetaGraph->AxisChange();
			ClustersCountBetaGraph->Invalidate();
			OmegaBetaGraph->AxisChange();
			OmegaBetaGraph->Invalidate();

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

		private: System::Void backgroundWorker1_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
		{
			progressBar1->Value = e->ProgressPercentage;
			label15->Text = "Идут вычисления... " + Convert::ToString(progressBar1->Value) + "%";
		}

		private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
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

		private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e)
		{
			const int n = Convert::ToInt32(nTB->Text);
			const int NumOfSets = Convert::ToInt32(GammaSetsCountTB->Text);
			const double beta1 = Convert::ToDouble(Beta1TB->Text);
			const double beta2 = Convert::ToDouble(Beta2TB->Text);
			const double betaStep = Convert::ToDouble(BetaStepTB->Text);
			const double gamma1Copy = Convert::ToDouble(Gamma1MinTB->Text);
			const double gamma2Copy = Convert::ToDouble(Gamma2MaxTB->Text);
			int* curClusters;
			double** curOmega;
			double* om;
			String^ str = L"Ω:\r\n";
			String^ str1 = "Кластеры:\r\n";
			String^ str2 = "";
			GraphPane^ panel = OmegaBetaGraph->GraphPane;
			GraphPane^ panel2 = ClustersCountBetaGraph->GraphPane;

			PointPairList^ AvgOmList = gcnew PointPairList();
			PointPairList^ AvgClusList = gcnew PointPairList();
			PointPairList^ MinMaxOmList = gcnew PointPairList();
			PointPairList^ MinMaxClusList = gcnew PointPairList();

			int non = 0;
			int index;
			int k = 0;
			int m = 0;

			for (double beta = beta1; beta <= beta2; beta += betaStep)
			{
				beta = round(beta * 100000) / 100000;
				non++;
			}

			double** MinMaxOm = new double* [non];
			int** MinMaxClus = new int* [non];

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

			for (int j = 0; j < (int)Omega_vec->size(); j++)
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
				AvgOmList->Add(beta, (MinOmega + MaxOmega) * 0.5);
				MinMaxClusList->Add(beta, MinClus, MaxClus);
				AvgClusList->Add(beta, (int)((MinClus + MaxClus) * 0.5));

				str += String::Format(L"β = {0}; Min = {1:G5}, Max = {2:G5}, Avg = {3:G5}\r\n", beta, MinOmega, MaxOmega, (MinOmega + MaxOmega) * 0.5);

				str1 += String::Format(L"β = {0}; Min = {1}, Max = {2}, Avg = {3}\r\n", beta, MinClus, MaxClus, (int)((MinClus + MaxClus) * 0.5));

				beta += betaStep;
			}

			str2 += String::Format(L"γⱼ были взяты из интервала [{0}; {1}]", gamma1Copy, gamma2Copy);

			textBox3->Text = str;
			textBox5->Text = str1;
			textBox6->Text = str2;

			LineItem^ Curve = panel->AddCurve("Среднее значение", AvgOmList, Color::DarkOrange, SymbolType::Diamond);
			LineItem^ Curve2 = panel2->AddCurve("Среднее значение", AvgClusList, Color::DarkOrange, SymbolType::Diamond);
			ErrorBarItem^ ErrorBar = panel->AddErrorBar("Min и Max", MinMaxOmList, Color::DarkOrange);
			ErrorBarItem^ ErrorBar2 = panel2->AddErrorBar("Min и Max", MinMaxClusList, Color::DarkOrange);

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

			ClustersCountBetaGraph->Invalidate();
			OmegaBetaGraph->Invalidate();

			AvgMaxMinAlreadyExists = true;

			for (int i = 0; i < non; i++)
			{
				delete[]MinMaxOm[i];
				delete[]MinMaxClus[i];
			}
		}

		private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			GraphPane^ panel = OmegaBetaGraph->GraphPane;

			if (checkBox1->Checked)
			{
				panel->Legend->IsVisible = true;
			}
			else
			{
				panel->Legend->IsVisible = false;
			}

			OmegaBetaGraph->Invalidate();
		}

		private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			GraphPane^ panel = ClustersCountBetaGraph->GraphPane;

			if (checkBox4->Checked)
			{
				panel->Legend->IsVisible = true;
			}
			else
			{
				panel->Legend->IsVisible = false;
			}

			ClustersCountBetaGraph->AxisChange();
			ClustersCountBetaGraph->Invalidate();
		}

		private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
		{
			label15->Visible = false;
			label16->Visible = true;
			backgroundWorker1->CancelAsync();
		}

		private: System::Void SingleCalculationBW_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
		{
			progressBar2->Value = e->ProgressPercentage;
			SingleCalculationProgressLbl->Text = "Идут вычисления... " + Convert::ToString(progressBar2->Value) + "%";
		}

		private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e)
		{
			const double delta = Convert::ToDouble(DeltaCmbB->Text);
			SingleCalculationProgressLbl->Text = "Идут вычисления... 0%";
			SingleCalculationProgressLbl->Visible = true;
			dataGridView1->Rows->Clear();
			dataGridView2->Rows->Clear();
			TPhaseTable->Rows->Clear();
			TimeOfSpikesTable->Rows->Clear();
			StartBtn->Enabled = false;
			IntegrParams->Enabled = false;
			SystemParams->Enabled = false;
			StopBtn->Enabled = true;
			StopBtn->Focus();

			SingleCalculationBW->RunWorkerAsync(delta);
		}

		private: System::Void SingleCalculationBW_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
		{
			if (e->Cancelled)
			{
				StopCalculationsLbl->Visible = false;
				MessageBox::Show("Вычисления приостановлены пользователем", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);

				progressBar2->Value = 0;
				SingleCalculationProgressLbl->Visible = false;
				StartBtn->Enabled = true;
				IntegrParams->Enabled = true;
				SystemParams->Enabled = true;
				StopBtn->Enabled = false;
				Change_scale_Omega->Enabled = true;

				return;
			}

			IPointList^ PhiTList = PhasesGraph->GraphPane->CurveList[PhasesGraph->GraphPane->CurveList->Count - 1]->Points;
			IPointList^ EPointList = E_fieldGraph->GraphPane->CurveList[E_fieldGraph->GraphPane->CurveList->Count - 1]->Points;
			IPointList^ OmegaPointList = OmegaGraph->GraphPane->CurveList[0]->Points;
			IPointList^ OmegaPointListMinMax = OmegaGraph->GraphPane->CurveList[OmegaGraph->GraphPane->CurveList->Count - 1]->Points;
			CurveList^ SpikesCurvesList = SpikesGraph->GraphPane->CurveList;

			for (int i = 0; i < PhiTList->Count; i++)
			{
				TPhaseTable->Rows->Add(PhiTList[i]->X, PhiTList[i]->Y);
			}

			for (int i = 0; i < SpikesCurvesList->Count; i++)
			{
				TimeOfSpikesTable->Rows->Add();
				TimeOfSpikesTable->Rows[i]->Cells[0]->Value = SpikesCurvesList[i]->Points[0]->X;
			}

			for (int i = 0; i < EPointList->Count; i++)
			{
				dataGridView2->Rows->Add(EPointList[i]->X, EPointList[i]->Y);
			}

			for (int i = 0; i < OmegaPointList->Count; i++)
			{
				dataGridView1->Rows->Add(OmegaPointList[i]->X, OmegaPointList[i]->Y);
			}

			dataGridView1->Rows->Add(OmegaPointListMinMax[0]->X, OmegaPointListMinMax[0]->Y);
			dataGridView1->Rows->Add(OmegaPointListMinMax[1]->X, OmegaPointListMinMax[1]->Y);

			dataGridView1->Sort(dataGridView1->Columns->GetFirstColumn(DataGridViewElementStates::None), ListSortDirection::Ascending);

			ResultsTB->Text = Str;

			MessageBox::Show("Вычисления закончены", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);

			progressBar2->Value = 0;
			SingleCalculationProgressLbl->Visible = false;
			StartBtn->Enabled = true;
			IntegrParams->Enabled = true;
			SystemParams->Enabled = true;
			StopBtn->Enabled = false;
			Change_scale_Omega->Enabled = true;
			ShowMaxMinCB->Enabled = true;
		}

		private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SingleCalculationProgressLbl->Visible = false;
			StopCalculationsLbl->Visible = true;
			SingleCalculationBW->CancelAsync();
		}

		private: System::Void backgroundWorker3_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
		{
			progressBar3->Value = e->ProgressPercentage;
		}

		private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			TimeOfSpikesTable->Visible = true;
			SpikesGraph->Visible = true;
			PhSyncParamGraph->Visible = false;
		}

		private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			TimeOfSpikesTable->Visible = false;
			PhSyncParamGraph->Visible = true;
			SpikesGraph->Visible = false;
		}

		private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e)
		{
			GraphPane^ panel = BetaCrNGraph->GraphPane;
			PointPairList^ ApprPoints = gcnew PointPairList();
			CurveItem^ curve = panel->CurveList[0];
			double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;
			double a, b;
			double minX, maxX;
			double Q = 0.0;

			minX = maxX = curve->Points[0]->X;

			if (panel->CurveList->Count > 1)
			{
				panel->CurveList->RemoveAt(panel->CurveList->Count - 1);
			}

			for (int i = 0; i < curve->NPts; i++)
			{
				PointPair^ curPoint = curve->Points[i];
				sum1 += 1 / pow(curPoint->X, 2);
				sum2 += curPoint->Y / curPoint->X;
				sum3 += curPoint->Y;
				sum4 += 1 / curPoint->X;

				if (curPoint->X < minX)
				{
					minX = curPoint->X;
				}
				if (curPoint->X > maxX)
				{
					maxX = curPoint->X;
				}
			}
			a = sum2 / sum1;
			b = 1 / curve->NPts * (sum3 - a * sum4);

			for (int i = 0; i < curve->NPts; i++)
			{
				PointPair^ curPoint = curve->Points[i];
				Q += pow(curPoint->Y - (a / curPoint->X + b), 2);
			}

			for (double x = minX - 0.1; x <= maxX + 0.1; x += 0.01)
			{
				ApprPoints->Add(x, a / x + b);
			}

			LineItem^ ApprCurve = panel->AddCurve("Аппроксимация", ApprPoints, Color::Blue, SymbolType::None);
			textBox8->Visible = true;
			textBox8->Text = String::Format("Уравнение аппроксимации:\r\ny = {0}/x + {1}\r\nНевязка:{2:G5}", a, b, Q);

			BetaCrNGraph->AxisChange();
			BetaCrNGraph->Invalidate();
		}

		private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e)
		{
			button9->Enabled = false;
			button8->Enabled = false;
			button10->Enabled = false;
			button11->Enabled = false;
			textBox9->Enabled = false;
			textBox10->Enabled = false;
			textBox11->Enabled = false;
			textBox12->Enabled = false;
			label20->Text = "Идёт построение... 0%";
			label20->Visible = true;

			backgroundWorker4->RunWorkerAsync();
		}

		private: System::Void backgroundWorker4_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
		{
			GraphPane^ pane = BetaCrNGraph->GraphPane;

			PointPairList^ list = gcnew PointPairList();

			const int N1 = Convert::ToInt32(textBox9->Text);                 //Число уравнений N₁
			const int N2 = Convert::ToInt32(textBox10->Text);                //Число уравнений N₂
			const int NOM = Convert::ToInt32(textBox11->Text);               //Число измерений
			int NStep = (N2 - N1) / NOM;                                     //Шаг по N
			double beta;                                                     //Начальное значение β
			double betaStep;                                                 //Начальный шаг по β
			double* Fi0;                                                     //Начальное распределение фаз φⱼ(0)
			double* Fi;                                                      //Фазы φⱼ(t) j = 0,...,n - 1
			double* Fiplus1;                                                 //Фазы φⱼ(t) j = 0,...,n - 1
			double* gamma;                                                   //Набор γⱼ
			const double gamma0 = Convert::ToDouble(textBox12->Text);
			int counter = 0;
			const double D2PI = 2 * M_PI;
			complex<double> Mu;

#pragma omp parallel for private(Fi0, Fi, Fiplus1, gamma, Mu, beta, betaStep) schedule(static, 1)
			for (int i = N1; i <= N2; i += NStep)
			{
				Fi0 = new double[i];
				Fi = new double[i];
				Fiplus1 = new double[i];

				gamma = Set_Gamma(i, gamma0, 0.0);
				beta = 0.0;
				if ((i >= 0) && (i < 70))
					betaStep = 0.0579;
				else
					if ((i >= 70) && (i < 90))
						betaStep = 0.0426;
					else
						betaStep = 0.0324;

				double prevbeta = beta;

				const complex<double> CompN((double)i, 0.0);

				random_device gen;
				mt19937 me(gen());
				uniform_real_distribution<> distr(0, M_PI);
				for (int j = 0; j < i; j++)
				{
					Fi0[j] = distr(me);
				}
				while (betaStep > 1e-03)
				{
					for (int j = 0; j < i; j++)
					{
						Fi[j] = Fi0[j];
						Fiplus1[j] = 0.0;
					}

					PerformCalculations(i, beta, Mu, Fi, Fiplus1, gamma);

					if (1 - abs(Mu) < 1e-03)
					{
						betaStep /= 2;
						if (betaStep > 1e-03)
							beta = prevbeta + betaStep;
					}
					else
					{
						prevbeta = beta;
						beta += betaStep;
					}
				}

#pragma omp critical (pushing)
				list->Add(i, beta);
#pragma omp atomic
				counter++;
#pragma omp critical (report)
				backgroundWorker4->ReportProgress((int)((float)counter / (NOM + 1) * 100));

				delete[] Fi0;
				delete[] Fi;
				delete[] Fiplus1;
				delete[] gamma;
			}
			//Конец параллельной секции------------------------------------------------------------------

			list->Sort();
			LineItem^ curve = pane->AddCurve("", list, Color::Red, SymbolType::Circle);
			curve->Symbol->Fill->Color = Color::Red;
			curve->Symbol->Fill->Type = FillType::Solid;

			BetaCrNGraph->AxisChange();
			BetaCrNGraph->Invalidate();
		}

		private: System::Void backgroundWorker4_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
		{
			progressBar4->Value = e->ProgressPercentage;
			label20->Text = "Идёт построение... " + Convert::ToString(progressBar4->Value) + "%";
		}

		private: System::Void backgroundWorker4_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
		{
			MessageBox::Show(L"Построение графика β⃰ от N завершено", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);

			button8->Enabled = true;
			button10->Enabled = true;
			button11->Enabled = true;
			progressBar4->Value = 0;
			label20->Visible = false;
		}

		private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e)
		{
			GraphPane^ pane = BetaCrNGraph->GraphPane;
			pane->CurveList->Clear();

			button9->Enabled = true;
			button10->Enabled = false;
			button8->Enabled = false;
			button11->Enabled = false;
			textBox8->Visible = false;
			textBox12->ReadOnly = false;
			textBox9->ReadOnly = false;
			textBox10->ReadOnly = false;
			textBox11->ReadOnly = false;

			BetaCrNGraph->AxisChange();
			BetaCrNGraph->Invalidate();
		}

		private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e)
		{
			label35->Visible = true;
			textBox13->Visible = true;
			button12->Visible = true;
		}

		private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e)
		{
			button8->Enabled = false;
			button10->Enabled = false;
			button11->Enabled = false;
			button12->Enabled = false;
			textBox13->Enabled = false;
			label36->Visible = true;

			backgroundWorker5->RunWorkerAsync();
		}

		private: System::Void backgroundWorker5_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
		{
			GraphPane^ pane = BetaCrNGraph->GraphPane;

			const int N = Convert::ToInt32(textBox13->Text);                 //Число уравнений N
			const double gamma0 = Convert::ToDouble(textBox12->Text);        //Значение γ для всех элементов
			double beta = 0.0;                                               //Начальное значение β
			double betaStep;                                                 //Начальный шаг по β
			double* Fi0;                                                     //Начальное распределение фаз φⱼ(0)
			double* Fi;                                                      //Фазы φⱼ(t) j = 0,...,n - 1
			double* Fiplus1;                                                 //Фазы φⱼ(t) j = 0,...,n - 1
			double* gamma;                                                   //Набор γⱼ
			complex<double> Mu;

			Fi0 = new double[N];
			Fi = new double[N];
			Fiplus1 = new double[N];

			gamma = Set_Gamma(N, gamma0, 0.0);
			if ((N >= 0) && (N < 70))
				betaStep = 0.0579;
			else
				if ((N >= 70) && (N < 90))
					betaStep = 0.0426;
				else
					betaStep = 0.0324;

			double prevbeta = beta;

			const complex<double> CompN((double)N, 0.0);

			random_device gen;
			mt19937 me(gen());
			uniform_real_distribution<> distr(0, M_PI);
			for (int j = 0; j < N; j++)
			{
				Fi0[j] = distr(me);
			}

			while (betaStep > 1e-03)
			{				
				for (int j = 0; j < N; j++)
				{
					Fi[j] = Fi0[j];
					Fiplus1[j] = 0.0;
				}
				PerformCalculations(N, beta, Mu, Fi, Fiplus1, gamma);

				if (1 - abs(Mu) < 1e-03)
				{
					betaStep /= 2;
					if (betaStep > 1e-03)
						beta = prevbeta + betaStep;
				}
				else
				{
					prevbeta = beta;
					beta += betaStep;
				}
			}

			PointPairList^ list = (PointPairList^)pane->CurveList[0]->Points;
			list->Add(N, beta);
			if (!list->Sorted)
				list->Sort();
			pane->CurveList[0]->Points = list;

			BetaCrNGraph->AxisChange();
			BetaCrNGraph->Invalidate();
		}

		private: System::Void backgroundWorker5_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
		{
			MessageBox::Show(L"Новое измерение добавлено на график", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);

			button11->Enabled = true;
			button8->Enabled = true;
			button10->Enabled = true;
			button11->Enabled = true;
			button12->Enabled = true;
			textBox13->Enabled = true;
			label35->Visible = false;
			textBox13->Visible = false;
			button12->Visible = false;
			label36->Visible = false;
		}

		private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			dataGridView1->Visible = true;
			OmegaGraph->Visible = true;
			OmegaPan->Visible = true;
		}

		private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			dataGridView1->Visible = false;
			TPhaseTable->Visible = true;
			OmegaGraph->Visible = false;
			OmegaPan->Visible = false;
		}

		private: System::Void backgroundWorker6_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
		{
			GraphPane^ pane = MaxMuBetaGraph->GraphPane;

			PointPairList^ list = gcnew PointPairList();

			const double Beta1 = Convert::ToDouble(textBox16->Text);         //Начальное значение β
			const double Beta2 = Convert::ToDouble(textBox17->Text);         //Конечное значение β
			const int NOM = Convert::ToInt32(textBox14->Text);               //Число измерений
			const int N = Convert::ToInt32(nTB->Text);                       //Число уравнений
			double BetaStep = (Beta2 - Beta1) / NOM;                         //Шаг по β
			double* Fi0;                                                     //Начальное распределение фаз φⱼ(0)
			double* Fi;                                                      //Фазы φⱼ(t) j = 0,...,n - 1
			double* Fiplus1;                                                 //Фазы φⱼ(t) j = 0,...,n - 1
			double* gamma;                                                   //Набор γⱼ
			const double gamma0 = Convert::ToDouble(textBox15->Text);
			int counter = 0;
			double beta;
			double maxAbsMu;

			Fi0 = new double[N];
			gamma = Set_Gamma(N, gamma0, 0.0);

			random_device gen;
			mt19937 me(gen());
			uniform_real_distribution<> distr(0, M_PI);
			for (int j = 0; j < N; j++)
			{
				Fi0[j] = distr(me);
			}

#pragma omp parallel for private( Fi, Fiplus1, maxAbsMu, beta)
			for (int Ind = 0; Ind <= NOM; Ind++)
			{
				Fi = new double[N];
				Fiplus1 = new double[N];
				maxAbsMu = -1.0;
				beta = Beta1 + Ind * BetaStep;

				for (int i = 0; i < N; i++)
				{
					Fi[i] = Fi0[i];
					Fiplus1[i] = 0.0;
				}

				PerformCalculations(N, beta, maxAbsMu, Fi, Fiplus1, gamma);

#pragma omp critical (pushing)
				list->Add(beta, maxAbsMu);
#pragma omp atomic
				counter++;
#pragma omp critical (report)
				backgroundWorker6->ReportProgress((int)((float)counter / (NOM + 1) * 100));
			}
			//Конец параллельной секции------------------------------------------------------------------

			list->Sort();
			LineItem^ curve = pane->AddCurve("", list, Color::Red, SymbolType::Circle);
			curve->Symbol->Fill->Color = Color::Red;
			curve->Symbol->Fill->Type = FillType::Solid;

			MaxMuBetaGraph->AxisChange();
			MaxMuBetaGraph->Invalidate();

			delete[]Fi;
			delete[]Fiplus1;
			delete[]Fi0;
			delete[]gamma;
		}

		private: System::Void backgroundWorker6_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
		{
			progressBar5->Value = e->ProgressPercentage;
			label37->Text = "Идёт построение... " + Convert::ToString(progressBar5->Value) + "%";
		}

		private: System::Void backgroundWorker6_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
		{
			MessageBox::Show(L"Построение графика max|μ(t)| от β завершено", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			label37->Visible = false;
			button16->Enabled = true;
			progressBar5->Value = 0;
		}

		private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e)
		{
			button15->Enabled = false;
			textBox14->Enabled = false;
			textBox15->Enabled = false;
			textBox16->Enabled = false;
			textBox17->Enabled = false;
			label37->Visible = true;
			label37->Text = "Идёт построение... 0 %";

			backgroundWorker6->RunWorkerAsync();
		}

		private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e)
		{
			MaxMuBetaGraph->GraphPane->CurveList->Clear();
			button16->Enabled = false;
			button15->Enabled = true;
			textBox14->Enabled = true;
			textBox15->Enabled = true;
			textBox16->Enabled = true;
			textBox17->Enabled = true;

			MaxMuBetaGraph->AxisChange();
			MaxMuBetaGraph->Invalidate();
		}

		private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (ShowMaxMinCB->Checked)
			{
				for each (GraphObj ^ obj in OmegaGraph->GraphPane->GraphObjList)
				{
					obj->IsVisible = true;
				}
			}
			else
			{
				for each (GraphObj ^ obj in OmegaGraph->GraphPane->GraphObjList)
				{
					obj->IsVisible = false;
				}
			}
			OmegaGraph->Invalidate();
		}

		private: System::Void SaveSetToFileBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			SaveFileDialog^ sfd = gcnew SaveFileDialog();
			sfd->DefaultExt = ".txt";
			sfd->AddExtension = true;
			sfd->FileName = "Набор гамма " + Gamma0CmbB->Text + " " + DeltaCmbB->Text + " " + DateTime::Now.ToString("dd.MM HH.mm");
			sfd->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			sfd->InitialDirectory = "E:\\Пользователь\\Pictures\\Курсовая работа Скриншоты\\Наборы гамма";
			
			if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK) 
			{
				return;
			}

			String ^fileName = sfd->FileName;
			StringBuilder^ sb = gcnew StringBuilder();
			String^ firstline = String::Format("{0}\t{1}", Gamma0CmbB->Text, DeltaCmbB->Text);
			sb->AppendLine(firstline);

			for (int i = 0; i < GammaTable->Rows->Count - 1; i++)
			{
				sb->AppendLine(GammaTable[1, i]->Value->ToString());
			}

			sb->Append(GammaTable[1, GammaTable->Rows->Count - 1]->Value->ToString());

			System::IO::File::WriteAllText(fileName, sb->ToString());
			System::Diagnostics::Process::Start(System::IO::Path::GetDirectoryName(fileName));
		}

		private: System::Void LoadSetFromFileBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			OpenFileDialog^ ofd = gcnew OpenFileDialog();
			ofd->InitialDirectory = "E:\\Пользователь\\Pictures\\Курсовая работа Скриншоты\\Наборы гамма";
			ofd->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			ofd->Multiselect = false;
			
			if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			{
				return;
			}

			GammaTable->Rows->Clear();

			String^ file = ofd->FileName;
			StreamReader^ sr = gcnew StreamReader(file);
			int counter = 0;
			cli::array<String^>^ firstLine = sr->ReadLine()->Split(gcnew cli::array<wchar_t> {'\t'});
			Gamma0CmbB->Text = firstLine[0];
			DeltaCmbB->Text = firstLine[1];
			List<double>^ GammaList = gcnew List<double>();

			while (!sr->EndOfStream)
			{
				String ^Line = sr->ReadLine();
				GammaList->Add(Convert::ToDouble(Line));
				GammaTable->Rows->Add(counter, Line);
				counter++;
			}

			gamma = new double[GammaList->Count];

			for (int i = 0; i < GammaList->Count; i++) 
			{
				gamma[i] = GammaList[i];
			}

			gamma1 = gamma[0];
			gamma2 = gamma[GammaList->Count];

			SaveSetToFileBtn->Enabled = true;
			StartBtn->Enabled = true;
		}
		private: System::Void ClearOmegaGraphBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			Change_scale_Omega->Enabled = false;
			OmegaGraph->GraphPane->CurveList->Clear();
			OmegaGraph->Invalidate();
		}

		private: System::Void MaxOmegaNUD_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			double oldVal = OmegaGraph->GraphPane->YAxis->Scale->Min;
			OmegaGraph->GraphPane->YAxis->Scale->Max = (double)MaxOmegaNUD->Value + (double)MaxOmegaNUD->Value * 0.01;
			OmegaGraph->GraphPane->YAxis->Scale->Min = oldVal;
			OmegaGraph->AxisChange();
			OmegaGraph->Invalidate();
		}

		private: System::Void FreqSyncStartBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (gamma == NULL)
			{
				MessageBox::Show(L"Набор γ не задан", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			FreqSyncPanel->Enabled = false;
			FreqSyncProgressLabel->Visible = true;
			FreqSyncCancelBtn->Enabled = true;
			FreqSyncBW->RunWorkerAsync();
		}

		private: System::Void FreqSyncBW_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
		{
			FreqSyncGraph->GraphPane->Title->Text = FreqSyncGraphTitle + Environment::NewLine + String::Format(L"Δ = {0}", Convert::ToDouble(DeltaCmbB->Text));

			PointPairList^ XiPPL = gcnew PointPairList();

			const int n = Convert::ToInt32(nTB->Text);                  //Число уравнений в системе
			const int p = Convert::ToInt32(IterationsTB->Text);         //Максимальное число итераций
			const double h = Convert::ToDouble(hTB->Text);              //Шаг
			const double T = Convert::ToDouble(T_TB->Text);             //Максимальное время, до которого будет подсчет, первый критерий остановки
			const double T01 = Convert::ToDouble(T1_TB->Text);          //Начальное время, от которого будет считаться частота
			const double Beta1 = Convert::ToDouble(FreqSyncBeta1TB->Text); //Левая граница β₁
			const double Beta2 = Convert::ToDouble(FreqSyncBeta2TB->Text); //Правая граница β₂
			const double BetaStep = Convert::ToDouble(FreqSyncBetaStepTB->Text); //Шаг по β
			const double E0 = Convert::ToDouble(E0_Text->Text);         //Начальное условие для E
			const double E0Star = Convert::ToDouble(E0Star_Text->Text); //Начальное условие для Ė
			const double TS = 0.0;                                      //Время последнего спайка
			int NumOfClusters;                                          //Число кластеров при t = T
			int IndexOfMaxOmega, IndexOfMinOmega;                       //Номера элементов с максимальными и минимальными частотами
			double Xi;                                                  //Параметр частотной синхронизации
			double beta = Beta1;                                        //Параметр β
			int* k;                                                     //Число спайков для каждого ротатора
			double* Fi0;                                                //Фазы при t = T₁
			double* Fi, * Fiplus1;                                      //Фазы φⱼ(t) j = 0,...,n - 1
			double* Omega;                                              //Средние частоты Ω

			bool stopFlag = false;
			const double D2PI = 2 * M_PI;
			double maxXi = -1.0;
			double minXi = 2.0;

			Fi = new double[n];
			Fiplus1 = new double[n];
			Fi0 = new double[n];
			Omega = new double[n];
			k = new int[n];

			double A = (Beta2 - Beta1) / BetaStep;
			double dec = A - (int)A;

			int iterCounter = 1;
			int IterationsCount = A + 1;
			if (dec != 0.0)
			{
				IterationsCount++;
			}

			FreqSyncGraph->Tag = String::Format("({0}/{1})", iterCounter, IterationsCount);

			while (beta <= Beta2)
			{
				FreqSyncBW->ReportProgress(0);

				double e0 = E0;
				double e0s = E0Star;
				double ts = TS;

				for (int i = 0; i < n; i++)                //Начальные условия для каждого из φⱼ(t) равны нулю
				{
					Fi[i] = Fiplus1[i] = Fi0[i] = 0.0;
					k[i] = 0;                          //Изначальное число спайков равно нулю
				}

				int res = PerformCalculations(n, T01 - h, beta, e0, e0s, ts, Fi, Fiplus1, FreqSyncBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				res = PerformCalculations(n, T01 - h, T, beta, e0, e0s, ts, k, Fi, Fiplus1, Fi0, FreqSyncBW);
				if (res == -1)
				{
					e->Cancel = true;
					return;
				}

				//Вычисление средних частот
				for (int i = 0; i < n; i++)
				{
					//Вычисление значения частоты
					if (k[i] != 0)
					{
						Omega[i] = ((k[i] - 1) * D2PI + Fi[i] - Fi0[i]) / (T - T01);
					}
					else
					{
						Omega[i] = (Fi[i] - Fi0[i]) / (T - T01);
					}
				}

				NumOfClusters = GetNumberOfClusters(Omega, n);	 //Вычисление числа кластеров при t = T
				Xi = (double)(NumOfClusters - 1) / (n - 1);

				if (Xi > maxXi)
				{
					maxXi = Xi;
				}

				if (Xi < minXi)
				{
					minXi = Xi;
				}

				XiPPL->Add(beta, Xi, String::Format(L"β = {0} χ = {1}", beta, Xi));

				beta += BetaStep;
				if (beta > Beta2 && !stopFlag)
				{
					beta = Beta2;
					stopFlag = true;
				}

				iterCounter++;
				FreqSyncGraph->Tag = String::Format("({0}/{1})", iterCounter, IterationsCount);
			}

			LineItem^ curve = FreqSyncGraph->GraphPane->AddCurve("", XiPPL, Color::Blue, SymbolType::None);
			FreqSyncGraph->GraphPane->XAxis->Scale->Min = Beta1 - 0.001;
			FreqSyncGraph->GraphPane->XAxis->Scale->Max = Beta2 + 0.001;
			FreqSyncGraph->GraphPane->YAxis->Scale->Min = minXi - 0.01;
			FreqSyncGraph->GraphPane->YAxis->Scale->Max = maxXi + 0.01;
			curve->Line->Width = 2.5;
			//curve->Line->IsSmooth = true;
			//curve->Line->SmoothTension = 1.0;

			FreqSyncGraph->AxisChange();
			FreqSyncGraph->Invalidate();

			delete[] Fi;
			delete[] Fiplus1;
			delete[] Fi0;
			delete[] Omega;
			delete[] k;
		}

		private: System::Void FreqSyncBW_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) 
		{
			FreqSyncProgBar->Value = e->ProgressPercentage;
			FreqSyncProgressLabel->Text = String::Format("Идёт построение... {0}% ", e->ProgressPercentage) + FreqSyncGraph->Tag->ToString();
		}

		private: System::Void FreqSyncBW_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) 
		{
			Activate();

			if(e->Cancelled)
			{
				MessageBox::Show("Построение отменено", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("Построение закончено", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Information);
				FreqSyncClearGraphBtn->Enabled = true;
			}
			FreqSyncProgBar->Value = 0;
			FreqSyncCancelBtn->Enabled = false;
			FreqSyncPanel->Enabled = true;
			FreqSyncProgressLabel->Visible = false;
		}

		private: System::Void FreqSyncClearGraphBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			FreqSyncGraph->GraphPane->CurveList->Clear();
			FreqSyncGraph->Invalidate();
		}

		private: System::Void FreqSyncCancelBtn_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			FreqSyncBW->CancelAsync();
		}
	};
}