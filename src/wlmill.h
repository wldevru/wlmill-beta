#ifndef WLMILL_H
#define WLMILL_H

#include <QMainWindow>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTime>
#include <QPicture>
#include <QToolBar>
#include <QMenuBar>
#include <QDial>
#include <QUdpSocket>
#include <QComboBox>
#include <QColorDialog>
#include <QActionGroup>
#include <QSplashScreen>
#include <QShortcut>

#include "wlpamlistwidget.h"
#include "wlvisualwidget.h"
#include "wlpositionwidget.h"
#include "wlgprogram.h"
#include "wllabel.h"
#include "wlgmachine.h"
#include "wliowidget.h"
#include "wlframe.h"
#include "wlevscript.h"
#include "wlmessmanager.h"
#include "wldialogscript.h"
#include "wlgprogramwidget.h"
#include "wledittext.h"
#include "wlmcodesh.h"
#include "wllog.h"
#include "wldatawidget.h"
#include "wlmpgwidget.h"
#include "wleditmpgwidget.h"
#include "wltbuttonscript.h"
#include "wlfilescript.h"
#include "wltimerscript.h"
#include "wlheightmapwidget.h"

#ifdef DEF_PLOT
#include "wloscpwidget.h"
#endif

#ifdef DEF_CAMERA
#include "wlcamera.h"
#endif

#ifdef DEF_QML
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlContext>
#include "wlfile.h"
#endif

#define FileState       QCoreApplication::applicationDirPath()+"//state.dat"
#define configWLMill    QCoreApplication::applicationDirPath()+"//wlmillconfig//config.xml"
#define iniconfigWLMill QCoreApplication::applicationDirPath()+"//wlmillconfig//config.ini"

#define VERSION_Y0 (__DATE__[ 7] - '0')
#define VERSION_Y1 (__DATE__[ 8] - '0')
#define VERSION_Y2 (__DATE__[ 9] - '0')
#define VERSION_Y3 (__DATE__[10] - '0')

#define VERSION_M_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define VERSION_M_FEB (__DATE__[0] == 'F')
#define VERSION_M_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define VERSION_M_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define VERSION_M_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define VERSION_M_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define VERSION_M_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define VERSION_M_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define VERSION_M_SEP (__DATE__[0] == 'S')
#define VERSION_M_OCT (__DATE__[0] == 'O')
#define VERSION_M_NOV (__DATE__[0] == 'N')
#define VERSION_M_DEC (__DATE__[0] == 'D')

#define VERSION_M0 ((VERSION_M_OCT || VERSION_M_NOV || VERSION_M_DEC) ? 1 : 0)
#define VERSION_M1 \
    ( \
        (VERSION_M_JAN) ? 1 : \
        (VERSION_M_FEB) ? 2 : \
        (VERSION_M_MAR) ? 3 : \
        (VERSION_M_APR) ? 4 : \
        (VERSION_M_MAY) ? 5 : \
        (VERSION_M_JUN) ? 6 : \
        (VERSION_M_JUL) ? 7 : \
        (VERSION_M_AUG) ? 8 : \
        (VERSION_M_SEP) ? 9 : \
        (VERSION_M_OCT) ? 0 : \
        (VERSION_M_NOV) ? 1 : \
        (VERSION_M_DEC) ? 2 : \
                          0   \
    )

#define VERSION_D0 ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') : 0)
#define VERSION_D1 (__DATE__[ 5] - '0')

#define VERSION_HOUR0 (__TIME__[0] - '0')
#define VERSION_HOUR1 (__TIME__[1] - '0')

#define VERSION_MIN0 (__TIME__[3] - '0')
#define VERSION_MIN1 (__TIME__[4] - '0')

#define VERSION_SEC0 (__TIME__[6] - '0')
#define VERSION_SEC1 (__TIME__[7] - '0')

#define VERSION_DAY       (10U * VERSION_D0 + VERSION_D1)
#define VERSION_MONTH     (10U * VERSION_M0 + VERSION_M1)
#define VERSION_YEAR      (10U * VERSION_Y2 + VERSION_Y3)

#define VERSION_HOUR      (10U * VERSION_HOUR0 + VERSION_HOUR1)
#define VERSION_MIN       (10U * VERSION_MIN0 + VERSION_MIN1)
#define VERSION_SEC       (10U * VERSION_SEC0 + VERSION_SEC1)

#define VERSION_BCD_DAY   (16U * VERSION_D0 + VERSION_D1)
#define VERSION_BCD_MONTH (16U * VERSION_M0 + VERSION_M1)
#define VERSION_BCD_YEAR  (16U * VERSION_Y2 + VERSION_Y3)

#define VERSION_BCD_HOUR  (16U * VERSION_HOUR0 + VERSION_HOUR1)
#define VERSION_BCD_MIN   (16U * VERSION_MIN0 + VERSION_MIN1)
#define VERSION_BCD_SEC   (16U * VERSION_SEC0 + VERSION_SEC1)

#define defDockStateS "\x00\x00\x00\xFF\x00\x00\x00\x00\xFD\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x01X\x00\x00\x03\xAB\xFC\x02\x00\x00\x00\x01\xFB\x00\x00\x00\x18\x00""D\x00M\x00i\x00l\x00l\x00""C\x00o\x00n\x00t\x00r\x00o\x00l\x01\x00\x00\x00O\x00\x00\x03\xAB\x00\x00\x01\x92\x00\x00'%\x00\x00\x00\x01\x00\x00\x01m\x00\x00\x03\xAB\xFC\x02\x00\x00\x00\x01\xFC\x00\x00\x00O\x00\x00\x03\xAB\x00\x00\x01\x83\x00\x01\x86\xB5\xFA\x00\x00\x00\x02\x01\x00\x00\x00\x04\xFB\x00\x00\x00\x12\x00""D\x00P\x00o\x00s\x00i\x00t\x00i\x00o\x00n\x01\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x01&\x00\x00\x03\xE7\xFB\x00\x00\x00\f\x00""D\x00I\x00O\x00P\x00u\x00t\x01\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x7F\x00\xFF\xFF\xFF\xFB\x00\x00\x00\x10\x00""D\x00P\x00r\x00o\x00g\x00r\x00""a\x00m\x01\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x01""1\x00\xFF\xFF\xFF\xFB\x00\x00\x00\x10\x00""D\x00P\x00r\x00o\x00g\x00r\x00""a\x00m\x01\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\xB3\x00\x00\x03\xAB\x00\x00\x00\x04\x00\x00\x00\x04\x00\x00\x00\b\x00\x00\x00\b\xFC\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x02\x00\x00\x00\x0E\x00t\x00""b\x00M\x00""C\x00o\x00""d\x00""e\x01\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x12\x00t\x00""b\x00M\x00""e\x00s\x00s\x00""a\x00g\x00""e\x01\x00\x00\x02i\x00\x00\x05\x17\x00\x00\x00\x00\x00\x00\x00\x00"

#define   configGMPath QCoreApplication::applicationDirPath()+"//wlmillconfig//"
#define   configGMFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mmconfig.xml"
#define   configGKFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mkconfig.xml"
#define        pamFile QCoreApplication::applicationDirPath()+"//wlmillconfig//pam.dat"
#define      toolsFile QCoreApplication::applicationDirPath()+"//wlmillconfig//tools.csv"
#define         scFile QCoreApplication::applicationDirPath()+"//wlmillconfig//cs.csv"
#define        _scFile QCoreApplication::applicationDirPath()+"//wlmillconfig//sc.csv"

#define    iconsGMPath QCoreApplication::applicationDirPath()+"//icons//"
#define   _iconsGMPath QCoreApplication::applicationDirPath()+"//wlmillconfig//icons//"

#define    mScriptFile QCoreApplication::applicationDirPath()+"//wlmillconfig//mscript.js"
#define    lScriptFile QCoreApplication::applicationDirPath()+"//wlmillconfig//lscript.js"

#define   _mScriptFile QCoreApplication::applicationDirPath()+"//wlmillconfig//script//mscript.js"
#define   _lScriptFile QCoreApplication::applicationDirPath()+"//wlmillconfig//script//lscript.js"
#define    _scriptPath QCoreApplication::applicationDirPath()+"//wlmillconfig//script//"
#define       _qmlPath QCoreApplication::applicationDirPath()+"//wlmillconfig//qml//"
#define     _soundPath QCoreApplication::applicationDirPath()+"//wlmillconfig//sound//"

class WLTBarTool: public WLTBarData
{
Q_OBJECT

public:
    explicit WLTBarTool(WLEVScript *_script,QWidget *parent=nullptr):WLTBarData (_script,parent)    {
    }
    Q_INVOKABLE     int selectTool(){return curIndex();}
    Q_INVOKABLE QString selectData(){return curData();}
};

class WLMill : public QMainWindow
{

	Q_OBJECT

public:
    WLMill(QWidget *parent = nullptr);
    ~WLMill();

private:

void closeEvent (QCloseEvent * event);
void leaveEvent ( QEvent * event );


void UpdateFileName();

QString getLastProgram();

private:
bool m_bclose;

private:
QByteArray m_state1;
QByteArray m_state2;

private:
//HANDLE mx;

unsigned long m_lifeM;

//Ui::WiteLineClass ui;
QTime TimeNow;
QTime TimeEnd;
int f;

QString        lastFileSC;
WLGProgram    *m_GProgram;
WLGMachine *MillMachine;
WLMessManager *MessManager;

WLEVScript *MScript;
WLEVScript *LScript;

QSplashScreen *splash;

WLLog *Log;

#ifdef DEF_CAMERA
WLCamera *camera;
#endif

#ifdef DEF_PLOT
WLOscpWidget *oscp;
#endif

QTabWidget *tabWidget;

WLGProgramWidget  *ProgramWidget;
QUdpSocket *remoteComSocket;

//DockProgram
QDockWidget *dockProgram;
QDockWidget *dockPosition;
QDockWidget *dockTools;
QDockWidget *dockIOPut;
QDockWidget *dockMPG;
QDockWidget *dockConsoleMScript;
QDockWidget *dockConsoleLScript;
QDockWidget *dockManual;
QDockWidget *dockHeightMap;

//WLSpindleWidget *DockSpindle;

QTextEdit *TextPam;
//TBControls
QToolBar    *TBControls;

QPushButton *ButtonGo;
QPushButton *ButtonConv;
QPushButton *ButtonReset;

QPushButton *PButtonSetTraj;
QPushButton *PButtonGoHome;
QPushButton *PButtonGoBack;
QPushButton *PButtonGoTo;
WLLabel     *SpeedLabel;

WLLabel     *LabelBufSize;

//DockChekers
QDockWidget *DockCheckers;
WLLabel *LabelMade;
WLLabel *LabelOrder;
WLLabel *LabelOrderMade;
//TBVisual
QToolBar *TBView;
QToolBar *TBMessage;
QToolBar *TBScript;
QToolBar *TBWireChild;

WLDataWidget *ToolWidget=nullptr;
WLDataWidget *SCWidget=nullptr;
/*
QToolBar *TBWireCorrect;
QToolBar *TBWireEdit;
QToolBar *TBWireMovie;
*/
//

WLDialogScript     *DialogM;
WLDialogScript     *DialogL;

//MessManager *MessManager=nullptr;

WLPositionWidget *PositionWidget=nullptr;
WLVisualWidget *VisualWidget=nullptr;

WLIOWidget  *IOWidget;
WLMPGWidget *MPGWidget;
WLHeightMapWidget *HMWidget;

QToolButton *TButtonGo;
QToolButton *TButtonStop;

QList <QWidget*> addTabList;
//Menu
QMenuBar *MenuBar;

//QWorkspace *WorkSpace;
QDialog *MW;

public:
        void setLifeM(unsigned int M) {m_lifeM=M;  emit changedLife();}
unsigned int getLifeM() {return m_lifeM;}

private:

#ifdef DEF_QML
QQuickWidget *createQuickWidget(QString file);
#endif

public slots:
void runQML(QString file);
void addTabQML(QString file);

void runQMLFile(QString file);
void addTabQMLFile(QString file);

void removeTab(QString name);

void playSound(QString file)  {playSoundFile(_soundPath+file);}
void playSoundFile(QString file);
void runFile(QString file);

private: 
	
 void autoSaveChekers();

 void createTabTools();
 void createTabSC();

 void createDockPosition();
 void createDockConsoleMScript();
 void createDockConsoleLScript();
 void createDockMPG();
 void createDockProgram();
 void createDockManual();
 void createDockSpindle();
 void createDockIOPut();
 void createDockHeightMap();

 void createTBControls();

 void createTBar1();
 void createTBar2();
 void createTBControl();

 void createMenuBar();

 void updateOrderMade();

 void saveDataState();  
 void loadDataState();

 bool loadConfigINI();
 bool loadConfigXML();
 
 QWidget* getButtomScript(QIcon icon,QString txt,QString toolTip,QString script);


private slots:

  void saveConfigINI();

  void readyMachine();

  void onGoHome();
  void onPBSetG28();
  void onPBGetG28();

  void onPBRotSC();
  void onPBSetP0();
  void onPBSetP1();

  void onPBStart();
  void onPBStartAt();
  void onPBStartContinue();

protected:

signals:

    void changedLife();

	void sendMessage(QString);    
    void changedStateKeyControl(int key,bool state);

private slots:
    void onModbusConsole();

    void restoreState1();
    void restoreState2();

    void saveState1();
    void saveState2();

    void onEditDevice();
    void onEditGModel();
    void onEditMPG();
    void onSetColors();

    void onEditDrive(QString nameDrive);

    void onEditWLMill();

    void setStateButtonGo(bool state);

	void updateEnableMoved(bool);

    void addLifeM() {m_lifeM++;emit changedLife();}

	void showMessage(QString name,QString data,int code);

	void setFocusPause() {/*TButtonPause->setFocus();*/}

	void updateTitle();

	void onSaveAsProgram();
	void onLoadProgram();

	void onSaveSC();
    void onLoadSC();

    void onSaveTools();
    void onLoadTools();

    void onSaveDebugFile();

    void onEditCodeMScript();
    void onEditCodeLScript();

	void UpdateTimes();

	void Error(QString,QString);

    void about();

	void help();

    void placeVisualizer();

    // QWidget interfaceplaceVisualizer()
protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // WLMILL_H
