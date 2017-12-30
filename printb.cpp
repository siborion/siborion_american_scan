#include "printb.h"
#include <QDateTime>


Printb::Printb(QWidget *parent, CurParam *link) : QWidget(parent)
{
    curParam = link;
}

void Printb::doPreview()
{
    iScan = curParam->scanB->grabFrameBuffer(false);
    qDebug()<<iScan.size();

    QString fileName = ":/test/reportb";
    report = new QtRPT(this);

    qDebug()<<"PrintB";

    report->loadReport(fileName);
    report->recordCount << 7;

    QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));

    QObject::connect(report, SIGNAL(setValueImage(int,QString,QImage&,int)),
                     this, SLOT(setValueImage(int,QString,QImage&,int)));

    report->printExec(true);
}


void Printb::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    if(paramName == "name")
        paramValue =  curParam->patientName;
    if(paramName == "id")
        paramValue =  curParam->patientId;
    if(paramName == "doctor")
        paramValue =  curParam->doctorName;
    if(paramName == "birth")
        paramValue =  curParam->birthDate;
    if (paramName == "date")
    {
        paramValue = QDateTime::currentDateTime().toString("MM.dd.yyyy");

    }
}

void Printb::setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage)
{
    qDebug()<<paramName;
    if (paramName == "image")
        paramValue = iScan;
}

