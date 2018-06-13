#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include <QSlider>

#include "kcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    KCustomPlot *m_pPlot;
    KCustomPlot *m_pPlot2;
    KCustomPlot *m_dFrequency;

    KCustomPlot *m_pPlotForce; //FTsensor,Kookmin.univ
    KCustomPlot *m_pPlotMoment; //FTsensor,Kookmin.univ

    KCustomPlot *m_pPlotZMPX; //ZMP,Kookmin.univ
    KCustomPlot *m_pPlotZMPY; //ZMP,Kookmin.univ

    QTimer *m_pUpdatePlotTimer;
    QTimer *m_pUpdatePlotTimerFT;
    QTimer *m_pUpdatePlotTimerZMP;

    long long m_nTimerCount;
    long long m_nTimerCountFT;
    long long m_nTimerCountZMP;


    bool    RAR_on_off;
    bool    LAR_on_off;

private slots:
    void UpdatePlot();

    void on_pushButton_StartTimer_clicked();

    void on_pushButton_DataSetting_clicked();

    void on_pushButton_StopTimer_clicked();

    void on_RHY_Color_highlighted(int index);

    void on_RHY_clicked();

    void on_RHR_Color_highlighted(int index);

    void on_RHR_clicked();

    void on_RHP_Color_highlighted(int index);

    void on_RHP_clicked();

    void on_RK_Color_highlighted(int index);

    void on_RK_clicked();

    void on_RAP_Color_highlighted(int index);

    void on_RAP_clicked();

    void on_RAR_Color_highlighted(int index);

    void on_RAR_clicked();

    void on_LHY_Color_highlighted(int index);

    void on_LHY_clicked();

    void on_LHR_Color_highlighted(int index);

    void on_LHR_clicked();

    void on_LHP_Color_highlighted(int index);

    void on_LHP_clicked();

    void on_LK_Color_highlighted(int index);

    void on_LK_clicked();

    void on_LAP_Color_highlighted(int index);

    void on_LAP_clicked();

    void on_LAR_Color_highlighted(int index);

    void on_LAR_clicked();

    void on_pushButton_StructureReset_clicked();


     //↓↓↓Kookmin.univ

    void UpdatePlotFT(); //FTsensor,Kookmin.univ

    void on_pushButton_DataSetting_FT_clicked(); //FTsensor,Kookmin.univ

    void on_pushButton_StartTimer_FT_clicked(); //FTsensor,Kookmin.univ

    void on_pushButton_StopTimer_FT_clicked(); //FTsensor,Kookmin.univ


    void on_R_Fz_Color_highlighted(int index); //FTsensor,Kookmin.univ

    void on_L_Fz_Color_highlighted(int index); //FTsensor,Kookmin.univ


    void on_R_Fz_clicked(); //FTsensor,Kookmin.univ

    void on_L_Fz_clicked(); //FTsensor,Kookmin.univ


    void on_R_Mx_Color_highlighted(int index); //FTsensor,Kookmin.univ

    void on_R_My_Color_highlighted(int index); //FTsensor,Kookmin.univ

    void on_L_Mx_Color_highlighted(int index); //FTsensor,Kookmin.univ

    void on_L_My_Color_highlighted(int index); //FTsensor,Kookmin.univ


    void on_R_Mx_clicked(); //FTsensor,Kookmin.univ

    void on_R_My_clicked(); //FTsensor,Kookmin.univ

    void on_L_Mx_clicked(); //FTsensor,Kookmin.univ

    void on_L_My_clicked(); //FTsensor,Kookmin.univ

    void on_pushButton_StructureReset_FT_clicked(); //FTsensor,Kookmin.univ

    ///////////////////

    void UpdatePlotZMP(); //ZMP,Kookmin.univ

    void on_pushButton_DataSetting_ZMP_clicked(); //ZMP,Kookmin.univ

    void on_pushButton_StartTimer_ZMP_clicked(); //ZMP,Kookmin.univ

    void on_pushButton_StopTimer_ZMP_clicked(); //ZMP,Kookmin.univ


    void on_ZMPX_Color_highlighted(int index); //ZMP,Kookmin.univ

    void on_ZMPY_Color_highlighted(int index); //ZMP,Kookmin.univ


    void on_ZMPX_clicked(); //ZMP,Kookmin.univ

    void on_ZMPY_clicked(); //ZMP,Kookmin.univ


    void on_pushButton_StructureReset_ZMP_clicked(); //ZMP,Kookmin.univ

    //↑Kookmin.univ


private:
    Ui::MainWindow *ui;

    bool Initialize();
    bool InitializeSharedMemory();
    bool InitializeObject();
    bool InitializeTimer();
    bool InitializeTimerFT();
    bool InitializeTimerZMP();
    bool InitializePlot();
    bool InitializePlot1();
    bool InitializePlotForce();
    bool InitializePlotTorque();
    bool InitializePlotZMPX();
    bool InitializePlotZMPY();

    void SetDummyData();
};

#endif // MAINWINDOW_H
