#include "scanbutton.h"
#include "qdebug.h"

ScanButton::ScanButton()
{
    QIcon icon;
    doMeasure = false;
    timer = new QTimer();
    timer->start(200);
    icon.addFile(QStringLiteral(":/test/scan"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon(icon);
    setIconSize(QSize(30, 30));
    connect(timer, SIGNAL(timeout()), SLOT(doTimer()));
    connect(this, SIGNAL(clicked()), SLOT(doScanSlot()));
}

void ScanButton::doTimer()
{
    QIcon icon;
    if(doMeasure)
    {
        icon.addFile(QString(":/test/scan%1").arg((numPic&3)+1), QSize(), QIcon::Normal, QIcon::Off);
        numPic++;
    }
    else
    {
        icon.addFile(QStringLiteral(":/test/scan"), QSize(), QIcon::Normal, QIcon::Off);
        numPic = 0;
    }
    setIcon(icon);
    setIconSize(QSize(30, 30));
}

void ScanButton::doScanSlot()
{
    emit doScan(&doMeasure);
}
