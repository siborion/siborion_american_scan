#include "scanbutton.h"

ScanButton::ScanButton()
{
    timer = new QTimer();
    timer->start(200);
    connect(timer, SIGNAL(timeout()), SLOT(doTimer()));
}

void ScanButton::doTimer()
{
    QIcon icon;

    if(this->isChecked())
    {
        icon.addFile(QString(":/test/scan%1").arg((numPic&3)+1), QSize(), QIcon::Normal, QIcon::Off);
        numPic++;
    }
    else
        icon.addFile(QStringLiteral(":/test/scan"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon(icon);
    setIconSize(QSize(50, 50));
}

