#include "bscanbutton.h"

BScanButton::BScanButton()
{

    QIcon iconPatient;
    iconPatient.addFile(QStringLiteral(":/test/bscan_en"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon(iconPatient);
    this->setMaximumHeight(50);
    setIconSize(this->size());
}
