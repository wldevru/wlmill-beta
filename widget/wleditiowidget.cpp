#include "wleditiowidget.h"
#include "ui_wleditiowidget.h"

#include <QMenu>
#include <QContextMenuEvent>

#include "wlaxiswidget.h"

WLEditIOWidget::WLEditIOWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLEditIOWidget)
{
    m_Module=nullptr;
    m_enLatchInput=false;

    ui->setupUi(this);

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),SLOT(update()));
    timer->start(50);

    ui->checkBox->setVisible(false);

    connect(ui->checkBox,&QCheckBox::toggled,ui->spinBox,&QSpinBox::setEnabled);
    connect(ui->checkBox,&QCheckBox::toggled,ui->label,&QLabel::setEnabled);
    connect(ui->checkBox,&QCheckBox::toggled,this,&WLEditIOWidget::toggle);
    connect(ui->label,&QPushButton::clicked,this,&WLEditIOWidget::onPBClicked);

    ui->checkBox->setChecked(true);
}

WLEditIOWidget::~WLEditIOWidget()
{
delete ui;
}

void WLEditIOWidget::setModule(WLModule *_Module,bool _input)
{
if(!_Module)
 {
// Q_ASSERT(m_Module);
 setVisible(false);
 return;
 }

m_Module=_Module;
m_input=_input;

switch(m_Module->getTypeModule())
{
 case WLModule::typeMAxis:{
                  WLModuleAxis *ModuleAxis = static_cast<WLModuleAxis*>(m_Module);

                  m_input=false;

                  ui->spinBox->setRange(0, ModuleAxis->getSizeAxis()-1);

                  ui->spinBox->setVisible(true);
                  ui->label->setVisible(true);

                  setLabel("axis");
                  break;
                  }

 case WLModule::typeMIOPut: {
                  WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);

                  ui->spinBox->setRange(0,(m_input? ModuleIOPut->getSizeInputs():ModuleIOPut->getSizeOutputs())-1);

                  ui->spinBox->setVisible(true);
                  ui->label->setVisible(true);

                  connect(ModuleIOPut,&WLModuleIOPut::changedInput,this,&WLEditIOWidget::setLatchInput);

                  setLabel(m_input ? ("input"):("output"));
                  break;
                  }

case WLModule::typeMPWM:    {
                  WLModulePWM *ModulePWM = static_cast<WLModulePWM*>(m_Module);

                  ui->spinBox->setRange(0,(ModulePWM->getSizeOutPWM()-1));

                  ui->spinBox->setVisible(true);
                  ui->label->setVisible(true);

                  setLabel(m_input ? ("in PWM"):("out PWM"));

                 break;
                 }

case WLModule::typeMAIOPut: {
                  WLModuleAIOPut *ModuleAIOPut = static_cast<WLModuleAIOPut*>(m_Module);

                  ui->spinBox->setRange(0,(m_input? ModuleAIOPut->getSizeInputs():ModuleAIOPut->getSizeOutputs())-1);

                  ui->spinBox->setVisible(true);
                    ui->label->setVisible(true);

                  setLabel(m_input ? ("ainput"):("aoutput"));
                  break;
                  }

case WLModule::typeMEncoder:{
                  WLModuleEncoder *ModuleEncoder = static_cast<WLModuleEncoder*>(m_Module);

                  ui->spinBox->setRange(-1,ModuleEncoder->getSizeEncoder()-1);

                  ui->spinBox->setVisible(true);
                    ui->label->setVisible(true);

                  setLabel(("encoder"));
                  break;
                  }
default:

break;
}


}

void WLEditIOWidget::setLabel(QString label)
{
ui->label->setText(label);
}

void WLEditIOWidget::setValue(int val)
{
ui->spinBox->setValue(val > ui->spinBox->maximum() ? -1 : val);
}

int WLEditIOWidget::value()
{
return ui->spinBox->value();
}

WLIOPut *WLEditIOWidget::getIOPut()
{
if(m_Module->getTypeModule()==WLModule::typeMIOPut)
    {
        WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);
        return  m_input ? ModuleIOPut->getInput(value()): ModuleIOPut->getOutput(value());
    }
    else
        return nullptr;
}

WLEncoder *WLEditIOWidget::getEncoder()
{
    if(m_Module->getTypeModule()==WLModule::typeMEncoder)
    {
        WLModuleEncoder *ModuleEncoder = static_cast<WLModuleEncoder*>(m_Module);
        return  m_input ? ModuleEncoder->getEncoder(value()): nullptr;
    }
    else
        return nullptr;
}


WLPWM *WLEditIOWidget::getPWM()
{
    if(m_Module->getTypeModule()==WLModule::typeMPWM)
    {
        WLModulePWM *ModulePWM = static_cast<WLModulePWM*>(m_Module);
        return  m_input ? nullptr : ModulePWM->getOutPWM(value());
    }
    else
        return nullptr;
}

WLAxis *WLEditIOWidget::getAxis()
{
    if(m_Module->getTypeModule()==WLModule::typeMAxis)
    {
        WLModuleAxis *ModuleAxis = static_cast<WLModuleAxis*>(m_Module);
        return  ModuleAxis->getAxis(value());
    }
    else
        return nullptr;
}

bool WLEditIOWidget::isChecked()
{
return ui->checkBox->isChecked()&&isEnable();
}

bool WLEditIOWidget::isEnable()
{
return m_Module!=nullptr;
}

QAbstractButton *WLEditIOWidget::getButton()
{
return ui->checkBox;
}

void WLEditIOWidget::update()
{
    if(!m_Module) return;

    if(m_Module->getTypeModule()==WLModule::typeMIOPut)
    {
        if(m_enLatchInput)
            ui->spinBox->setStyleSheet("background-color: rgb(20 ,255,205)");
        else  if (getIOPut()->getNow())
            ui->spinBox->setStyleSheet("background-color: rgb(255,120,120)");
        else
            ui->spinBox->setStyleSheet("background-color: rgb(255,250,250)");
    }
}

void WLEditIOWidget::togInvers()
{
 switch(m_Module->getTypeModule())
 {
 case WLModule::typeMIOPut:   getIOPut()->togInv();  break;
 case WLModule::typeMPWM:     getPWM()->togInv();    break;
 case WLModule::typeMEncoder: getEncoder()->togInv();break;

 default: break;
 }
}

void WLEditIOWidget::onActEditAxis()
{
WLAxisWidget AW(getAxis(),0,0,this);

AW.setShowButtonDialog(true);
AW.setEditSpindle(true);
AW.setModal(true);
AW.show();
AW.exec();
}


void WLEditIOWidget::onActTogInvers()
{
if(QMessageBox::question(this,tr("Question")
                        ,m_input ? tr("invert input"):tr("invert output")
                        ,QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
             togInvers();
             }
}

void WLEditIOWidget::onActLatchInput()
{
m_enLatchInput=!m_enLatchInput;
ui->spinBox->setDisabled(m_enLatchInput);
}

void WLEditIOWidget::onActResetEncoder()
{
getEncoder()->setCount(0);
}

void WLEditIOWidget::onActSetFreq()
{
WLEnterNum EN(this);

EN.setMinMaxNow(1,30000, getPWM()->getFreq());
EN.setLabel(tr("Eneter Frequency:"));
EN.setSuffix(tr("Hz"));

if(EN.exec())
  {
  getPWM()->setFreq(EN.getNow());
  }
}

void WLEditIOWidget::setLatchInput(int index)
{
if(m_enLatchInput)
  {
  m_enLatchInput=false;
  ui->spinBox->setValue(index);
  ui->spinBox->setDisabled(m_enLatchInput);
}
}



void WLEditIOWidget::setCheckable(bool enable)
{
if(m_Module) {
    ui->checkBox->setVisible(enable);
    }

}

void WLEditIOWidget::setChecked(bool check)
{
ui->checkBox->setChecked(check);

emit toggle(check);
}

void WLEditIOWidget::onPBClicked()
{
QMenu menu(this);

if(!m_Module
 ||!isChecked()
 ||(value()<0)) return;

switch(m_Module->getTypeModule())
{
case WLModule::typeMAxis:
                   {
                   QAction *actEdit=menu.addAction(tr("edit"),this,SLOT(onActEditAxis()));
                   }
                  break;

case WLModule::typeMIOPut:
                   {
                   QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));

                    actTog->setCheckable(true);
                    actTog->setChecked(getIOPut()->isInv());

                    if(m_input)
                      {
                      QAction *actLatchIn=menu.addAction(tr("latch input"),this,SLOT(onActLatchInput()));;

                      actLatchIn->setCheckable(true);
                      actLatchIn->setChecked(m_enLatchInput);
                      }
                    }
                  break;

case WLModule::typeMEncoder:
                     if(m_input)
                     {
                     menu.addAction(QString::number(getEncoder()->count()));
                     menu.addAction(">>0",this,SLOT(onActResetEncoder()));

                     QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));
                     actTog->setCheckable(true);
                     actTog->setChecked(getEncoder()->isInv());
                     }
                   break;

case WLModule::typeMPWM:
                  {
                  QAction *actTog=menu.addAction(tr("invers"),this,SLOT(onActTogInvers()));

                  actTog->setCheckable(true);
                  actTog->setChecked(getPWM()->isInv());

                  menu.addAction("F:"+QString::number(getPWM()->getFreq())+"Hz",this,SLOT(onActSetFreq()));
                  }
                  break;

default: return;
}


//menu.exec(event->globalPos());
QPoint pos=ui->label->pos();
pos.setY(pos.y()+ui->label->height());
menu.exec(mapToGlobal(pos));
}


