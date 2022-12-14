#ifndef WLAXISWIDGET_H
#define WLAXISWIDGET_H

#include <QDialog>
#include "wlaxis.h"

namespace Ui {
class WLAxisWidget;
}

class WLAxisWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLAxisWidget(WLAxis *_axis,bool _slave,double _offset,QWidget *parent = nullptr);
    ~WLAxisWidget();

    void setShowButtonDialog(bool en);

public:
    void saveDataAxis();
    double getOffset();

    bool isUniqueInputs();
    bool isUniqueOutputs();

    double geDelaytSCurveMs();

    WLAxis *getAxis() {return m_axis;}

    quint8 getIndexInPEL();
    quint8 getIndexInMEL();
    quint8 getIndexInORG();
    quint8 getIndexInALM();

    quint8 getIndexOutENB();
    quint8 getIndexOutRALM();

    WLIOPut::typeActionInput getActInPEL();
    WLIOPut::typeActionInput getActInMEL();
    WLIOPut::typeActionInput getActInALM();
    WLIOPut::typeActionInput getActInORG();

    void setEditSpindle(bool en);

private:
    Ui::WLAxisWidget *ui;

    WLAxis *m_axis;
    bool m_slave=false;
    bool m_Fminutess=false;
    double m_stepsize=1.0;
    QString m_unit="1;";

public slots:
    void accept();
    void setUnit(QString);

    void setStepSize(double stepsize);
    void setFminutes(bool);

private slots:
    void onEditParSMPlus();
    void onEditPid();
    void onEditErrorPid();
    void updateTypeMotor(int);

};

#endif // WLAXISWIDGET_H
