#ifndef PRINTB_H
#define PRINTB_H

#include "typedef.h"
#include "curparam.h"
#include <QWidget>
#include "qtrpt.h"

class Printb : public QWidget
{
    Q_OBJECT
public:
    explicit Printb(QWidget *parent = 0, CurParam *link=0);
    void doPreview();
private:
    CurParam *curParam;
    QtRPT *report    ;

signals:

public slots:

private slots:
    void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
    void setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage);
};

#endif // PRINTB_H
