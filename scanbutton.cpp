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
        switch(numPic&3)
        {
        case 0:
            icon.addFile(QStringLiteral(":/test/scan1"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 1:
            icon.addFile(QStringLiteral(":/test/scan2"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 2:
            icon.addFile(QStringLiteral(":/test/scan3"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 3:
            icon.addFile(QStringLiteral(":/test/scan4"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        }
        numPic++;
    }
    else
    {
        icon.addFile(QStringLiteral(":/test/scan"), QSize(), QIcon::Normal, QIcon::Off);
    }
    setIcon(icon);
    setIconSize(QSize(50, 50));
}

