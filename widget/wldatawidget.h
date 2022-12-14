#ifndef WLDATAWIDGET_H
#define WLDATAWIDGET_H

#include <QWidget>
#include <QAbstractTableModel>

#include "wlgcode.h"
#include "wldatatablemodel.h"
#include "wltbuttonscript.h"

namespace Ui {
class WLDataWidget;
}

class WLDataWidget;

class WLTBarData: public WLTBarScript
{
Q_OBJECT

public:
    explicit WLTBarData(WLEVScript *_script,QWidget *parent=nullptr):WLTBarScript(_script,"",parent)
    {

    }
    void setDataWidget(WLDataWidget *_DataWidget);

    Q_INVOKABLE     int curIndex();
    Q_INVOKABLE QString curData();

private:
    WLDataWidget *DataWidget=nullptr;
};

class WLDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLDataWidget(QWidget *parent = nullptr);
    ~WLDataWidget();

    void setModel(WLDataTableModel *Model);
    void setHeadersTable(QString strheaders);
    QStringList getHeaderTable();

    void addToolBar(WLTBarData *toolBar);

        int curIndex();
    QString curData();

    void setSupportStr(QString);
private:
    Ui::WLDataWidget *ui;

    WLDataTableModel *m_Model=nullptr;
    QString m_supportColumn;

private slots:
};

#endif // WLDATAWIDGET_H


