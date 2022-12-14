#ifndef WLGAXISLABEL_H
#define WLGAXISLABEL_H

#include <QWidget>
#include <QPainter>
#include <QSizePolicy>
#include "wlgcode.h"
#include "wlgdrive.h"

class WLGAxisLabel : public QWidget
{
    Q_OBJECT

public:
    typedef enum {typeName,typeOfst,typePos}type;

public:
    explicit WLGAxisLabel(QWidget *parent = nullptr);

    void setDrive(WLGDrive *_drive);
    void setGCode(WLGCode *_gcode);

    bool isChecked() {return m_checked;}
private:
   WLGDrive *m_drive=nullptr;
   WLGCode     *m_gcode=nullptr;

   QString strValue="000.000";
   QString strF="000.000";

   double m_GPos=0;

   QRect rName;
   QRect rPos;
   QRect rF;
   QRect rOfst;

   bool m_checked=false;

signals:
   void changedPress(QString name,int type);

public slots:

   void setChecked(bool ch) {m_checked=ch; update();}
   void setGPos(double gpos) {m_GPos=gpos;}

       // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
 //   void resizeEvent(QResizeEvent *event);
};

#endif // WLGAXISLABEL_H
