#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sys/shm.h>
#include <QDebug>

#include "DataStructure.h"

#define TEST_DATA_KEY       3988
#define SERVER_SHM_SIM_KEY       5000
#define CLIENT_SHM_SIM_KEY       2000

using namespace std;

PLOWERBODYSIMALGO_DATA _pSIMData;

void* GetSharedPointer(int nKey, int nDataSize) {

    if(nKey == 0 || nDataSize == 0)
        return NULL;

    int nSharedID = shmget(nKey, nDataSize, IPC_CREAT);
    if(nSharedID == -1) {
        return NULL;
    }

    void* pSharedPointer = shmat(nSharedID, (void*)0, 0);
    if(pSharedPointer == (void*)-1) {
        return NULL;
    }

    //TEST
    //qDebug() << "[shared memory] Shared ID : " << nSharedID << " Shared Pointer : " << pSharedPointer << endl;
    return pSharedPointer;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(this->Initialize() == false) {
        qDebug() << "Failed Initialize.";
        return;
    }

    qDebug() << "Success Initialize Plot.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::Initialize() {

    if(this->InitializeSharedMemory() == false) {
        qDebug() << "Failed Initialize Shared memory.";
        return false;
    }else{
        qDebug() << "Success Init Shared memory! SHM KEY : "<< SERVER_SHM_SIM_KEY << " size of SHM : " << sizeof(LOWERBODYSIMALGO_DATA);
    }

    if(this->InitializeObject() == false) {
        qDebug() << "Failed Initialize Object.";
        return false;
    }

    return true;
}

bool MainWindow::InitializeSharedMemory() {

    _pSIMData = (PLOWERBODYSIMALGO_DATA)GetSharedPointer(SERVER_SHM_SIM_KEY, sizeof(LOWERBODYSIMALGO_DATA));

    return (_pSIMData != NULL) ? true : false;
}

bool MainWindow::InitializeObject() {

    if(this->InitializePlot() == false) {
        qDebug() << "Failed Initialize Plot.";
        return false;
    }

    if(this->InitializePlot1() == false){
        qDebug() << "failed Initialize Plot";
        return false;
    }
    //↓↓↓↓↓↓↓↓↓↓Kookmin.univ

    if(this->InitializePlotForce() == false){
        qDebug() << "failed Initialize PlotFT";
        return false;
    }

    if(this->InitializePlotTorque() == false){
        qDebug() << "failed Initialize PlotFT";
        return false;
    }

    if(this->InitializeTimerFT() == false) {
        qDebug() << "Failed Initialize Valuables.";
        return false;
    }
    //↑↑↑↑↑↑↑↑↑↑↑↑Kookmin.univ
    if(this->InitializeTimer() == false) {
        qDebug() << "Failed Initialize Valuables.";
        return false;
    }

    return true;
}

bool MainWindow::InitializePlot() {

    m_pPlot = new KCustomPlot();
    if(m_pPlot == NULL) {
        return false;
    }

    return m_pPlot->SetObject((void*)ui->Widget_Plot_1);
}

bool MainWindow::InitializePlot1(){

    m_pPlot2 = new KCustomPlot();
    if(m_pPlot2 == NULL){
        return false;
    }

    return m_pPlot2->SetObject((void*)ui->Widget_Plot_4);
}
//↓↓↓↓↓↓↓↓↓↓Kookmin.univ
bool MainWindow::InitializePlotForce(){

    m_pPlotForce = new KCustomPlot();
    if(m_pPlotForce == NULL){
        return false;
    }

    return m_pPlotForce->SetObject((void*)ui->Widget_Plot_Footforce);
}
bool MainWindow::InitializePlotTorque(){

    m_pPlotMoment = new KCustomPlot();
    if(m_pPlotMoment == NULL){
        return false;
    }

    return m_pPlotMoment->SetObject((void*)ui->Widget_Plot_Footmoment);
}
//↑↑↑↑↑↑↑↑↑↑↑↑Kookmin.univ
bool MainWindow::InitializeTimer()
{
    m_nTimerCount = 0;

    m_pUpdatePlotTimer = new QTimer();
    connect(m_pUpdatePlotTimer, SIGNAL(timeout()), this, SLOT(UpdatePlot()));
}
bool MainWindow::InitializeTimerFT()
{
    m_nTimerCountFT = 0;

    m_pUpdatePlotTimerFT = new QTimer();
    connect(m_pUpdatePlotTimerFT, SIGNAL(timeout()), this, SLOT(UpdatePlotFT()));
    return true;
}

void MainWindow::UpdatePlot()
{
    //Test Set Data
//    this->SetDummyData();

    if(m_pPlot != NULL){
        m_pPlot->SetData(AXIS_Y_1, _pSIMData->sensored_data.axis_joint_state[AXIS_RHY].joint_position*180/3.14);
        m_pPlot->SetData(AXIS_Y_2, _pSIMData->sensored_data.axis_joint_state[AXIS_RHR].joint_position*180/3.14);
        m_pPlot->SetData(AXIS_Y_3, _pSIMData->sensored_data.axis_joint_state[AXIS_RHP].joint_position*180/3.14);
        m_pPlot->SetData(AXIS_Y_4, _pSIMData->sensored_data.axis_joint_state[AXIS_RKN].joint_position*180/3.14);
        m_pPlot->SetData(AXIS_Y_5, _pSIMData->sensored_data.axis_joint_state[AXIS_RAP].joint_position*180/3.14);
        if(RAR_on_off==true)
        {
           m_pPlot->SetData(AXIS_Y_6, _pSIMData->sensored_data.axis_joint_state[AXIS_RAR].joint_position*180/3.14);
        }
        m_pPlot->UpdateGraph();
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->SetData(AXIS_Y_1, _pSIMData->sensored_data.axis_joint_state[AXIS_LHY].joint_position*180/3.14);
        m_pPlot2->SetData(AXIS_Y_2, _pSIMData->sensored_data.axis_joint_state[AXIS_LHR].joint_position*180/3.14);
        m_pPlot2->SetData(AXIS_Y_3, _pSIMData->sensored_data.axis_joint_state[AXIS_LHP].joint_position*180/3.14);
        m_pPlot2->SetData(AXIS_Y_4, _pSIMData->sensored_data.axis_joint_state[AXIS_LKN].joint_position*180/3.14);
        m_pPlot2->SetData(AXIS_Y_5, _pSIMData->sensored_data.axis_joint_state[AXIS_LAP].joint_position*180/3.14);
        if(LAR_on_off==true)
        {
           m_pPlot2->SetData(AXIS_Y_6, _pSIMData->sensored_data.axis_joint_state[AXIS_LAR].joint_position*180/3.14);
        }
        m_pPlot2->UpdateGraph();
    }

    m_nTimerCount++;
}

void MainWindow::SetDummyData() {

//    // import data -> shared memory.
//    for(int nIndex = AXIS_Y_1; nIndex < MAX_AXIS_YCOUNT; nIndex++)
//        _pPacket->info[nIndex].value = sin(m_nTimerCount + nIndex);
}

void MainWindow::on_pushButton_DataSetting_clicked()
{
    double value = ui->lineEdit_FrequencyValue->text().toDouble();
    if(m_pPlot != NULL){
        m_pPlot->SetFrequency(value);
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->SetFrequency(value);
    }
}

void MainWindow::on_pushButton_StartTimer_clicked()
{
    if(m_pPlot != NULL){
        m_pPlot->SetTimerEnabled(true);
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->SetTimerEnabled(true);
    }
    m_pUpdatePlotTimer->start(10);
}

void MainWindow::on_pushButton_StopTimer_clicked()
{
    if(m_pPlot != NULL){
        m_pPlot->SetTimerEnabled(false);
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->SetTimerEnabled(false);
    }
    m_pUpdatePlotTimer->stop();
}

void MainWindow::on_RHY_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_1 , color);
    }
}

void MainWindow::on_RHY_clicked()
{
    bool bResult = ui->RHY->isChecked();
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_1, bResult);
    }
}
void MainWindow::on_RHR_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_2 , color);
    }
}

void MainWindow::on_RHR_clicked()
{
    bool bResult = ui->RHR->isChecked();
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_2, bResult);
    }
}

void MainWindow::on_RHP_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_3 , color);
    }
}

void MainWindow::on_RHP_clicked()
{
    bool bResult = ui->RHP->isChecked();
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_3, bResult);
    }
}

void MainWindow::on_RK_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_4 , color);
    }
}

void MainWindow::on_RK_clicked()
{
    bool bResult = ui->RK->isChecked();
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_4, bResult);
    }
}

void MainWindow::on_RAP_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_5 , color);
    }
}

void MainWindow::on_RAP_clicked()
{
    bool bResult = ui->RAP->isChecked();
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_5, bResult);
    }
}

void MainWindow::on_RAR_Color_highlighted(int color)
{
    if(m_pPlot != NULL){
    m_pPlot->SetColor(AXIS_Y_6 , color);
    }
}

void MainWindow::on_RAR_clicked()
{
    bool bResult = ui->RAR->isChecked();
    if(bResult == true)
    {
        RAR_on_off = true;
    }
    else
    {
        RAR_on_off = false;
    }
    if(m_pPlot != NULL){
        m_pPlot->SetVisible(AXIS_Y_6, bResult);
    }
}

////////////////////////////////////////////////////////////

void MainWindow::on_LHY_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_1 , color);
    }
}

void MainWindow::on_LHY_clicked()
{
    bool bResult = ui->LHY->isChecked();
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_1, bResult);
    }
}
void MainWindow::on_LHR_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_2 , color);
    }
}

void MainWindow::on_LHR_clicked()
{
    bool bResult = ui->LHR->isChecked();
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_2, bResult);
    }
}

void MainWindow::on_LHP_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_3 , color);
    }
}

void MainWindow::on_LHP_clicked()
{
    bool bResult = ui->LHP->isChecked();
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_3, bResult);
    }
}

void MainWindow::on_LK_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_4 , color);
    }
}

void MainWindow::on_LK_clicked()
{
    bool bResult = ui->LK->isChecked();
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_4, bResult);
    }
}

void MainWindow::on_LAP_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_5 , color);
    }
}

void MainWindow::on_LAP_clicked()
{
    bool bResult = ui->LAP->isChecked();
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_5, bResult);
    }
}

void MainWindow::on_LAR_Color_highlighted(int color)
{
    if(m_pPlot2 != NULL){
    m_pPlot2->SetColor(AXIS_Y_6 , color);
    }
}

void MainWindow::on_LAR_clicked()
{
    bool bResult = ui->LAR->isChecked();
    if(bResult == true)
    {
        LAR_on_off = true;
        qDebug() << "AR_on_off true.";
    }
    else
    {
        LAR_on_off = false;
        qDebug() << "AR_on_off false.";
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->SetVisible(AXIS_Y_6, bResult);
    }
}

void MainWindow::on_pushButton_StructureReset_clicked()
{
    if(m_pPlot != NULL){
        m_pPlot->ClearData();
    }
    if(m_pPlot2 != NULL){
        m_pPlot2->ClearData();
    }
}

//↓↓↓↓↓↓↓↓↓↓Kookmin.univ

void MainWindow::UpdatePlotFT()
{
    //Test Set Data
//    this->SetDummyData();

    if(m_pPlotForce != NULL){

        m_pPlotForce->SetData(R_F_Z, _pSIMData->sensored_data.ft_sensor.ft_data[RIGHT_FOOT].fz);
        m_pPlotForce->SetData(L_F_Z, _pSIMData->sensored_data.ft_sensor.ft_data[LEFT_FOOT].fz);

        m_pPlotForce->UpdateGraph();
    }
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetData(R_M_X, _pSIMData->sensored_data.ft_sensor.ft_data[RIGHT_FOOT].tx);
        m_pPlotMoment->SetData(R_M_Y, _pSIMData->sensored_data.ft_sensor.ft_data[RIGHT_FOOT].ty);

        m_pPlotMoment->SetData(L_M_X, _pSIMData->sensored_data.ft_sensor.ft_data[LEFT_FOOT].tx);
        m_pPlotMoment->SetData(L_M_Y, _pSIMData->sensored_data.ft_sensor.ft_data[LEFT_FOOT].ty);

        m_pPlotMoment->UpdateGraph();
    }

    m_nTimerCountFT++;
}

void MainWindow::on_pushButton_DataSetting_FT_clicked()
{
    double value = ui->lineEdit_FrequencyValue_FT->text().toDouble();
    if(m_pPlotForce != NULL){
        m_pPlotForce->SetFrequency(value);
    }
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetFrequency(value);
    }
}


void MainWindow::on_pushButton_StartTimer_FT_clicked()
{
    if(m_pPlotForce != NULL){
        m_pPlotForce->SetTimerEnabled(true);
    }
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetTimerEnabled(true);
    }

    m_pUpdatePlotTimerFT->start(10);
}

void MainWindow::on_pushButton_StopTimer_FT_clicked()
{
    if(m_pPlotForce != NULL){
        m_pPlotForce->SetTimerEnabled(false);
    }
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetTimerEnabled(false);
    }
    m_pUpdatePlotTimerFT->stop();
}

void MainWindow::on_R_Fz_Color_highlighted(int color)
{
    if(m_pPlotForce != NULL){
    m_pPlotForce->SetColor(R_F_Z, color);
    }
}

void MainWindow::on_L_Fz_Color_highlighted(int color)
{
    if(m_pPlotForce != NULL){
    m_pPlotForce->SetColor(L_F_Z, color);
    }
}

void MainWindow::on_R_Fz_clicked()
{
    bool bResult = ui->R_Fz->isChecked();
    if(m_pPlotForce != NULL){
        m_pPlotForce->SetVisible(R_F_Z, bResult);
    }
}

void MainWindow::on_L_Fz_clicked()
{
    bool bResult = ui->L_Fz->isChecked();
    if(m_pPlotForce != NULL){
        m_pPlotForce->SetVisible(L_F_Z, bResult);
    }
}

void MainWindow::on_R_Mx_Color_highlighted(int color)
{
    if(m_pPlotMoment != NULL){
    m_pPlotMoment->SetColor(R_M_X, color);
    }
}
void MainWindow::on_R_My_Color_highlighted(int color)
{
    if(m_pPlotMoment != NULL){
    m_pPlotMoment->SetColor(R_M_Y, color);
    }
}

void MainWindow::on_L_Mx_Color_highlighted(int color)
{
    if(m_pPlotMoment != NULL){
    m_pPlotMoment->SetColor(L_M_X, color);
    }
}
void MainWindow::on_L_My_Color_highlighted(int color)
{
    if(m_pPlotMoment != NULL){
    m_pPlotMoment->SetColor(L_M_Y, color);
    }
}

void MainWindow::on_R_Mx_clicked()
{
    bool bResult = ui->R_Mx->isChecked();
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetVisible(R_M_X, bResult);
    }
}

void MainWindow::on_R_My_clicked()
{
    bool bResult = ui->R_My->isChecked();
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetVisible(R_M_Y, bResult);
    }
}

void MainWindow::on_L_Mx_clicked()
{
    bool bResult = ui->L_Mx->isChecked();
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetVisible(L_M_X, bResult);
    }
}

void MainWindow::on_L_My_clicked()
{
    bool bResult = ui->L_My->isChecked();
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->SetVisible(L_M_Y, bResult);
    }
}

void MainWindow::on_pushButton_StructureReset_FT_clicked()
{
    if(m_pPlotForce != NULL){
        m_pPlotForce->ClearData();
    }
    if(m_pPlotMoment != NULL){
        m_pPlotMoment->ClearData();
    }
}
//↑↑↑↑↑↑↑↑↑↑↑↑Kookmin.univ
