#ifndef key_radio_H
#define key_radio_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
//#include "curentparam.h"
#include "typedef.h"

class key_radio : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
//    void changeCataractSignal(bool cataract);
    void change();

private:
    void refresh();
//    CurentParam *curentParam;
    QRadioButton *rbOd;
    QRadioButton *rbOs;
    QGroupBox    *gbEye;
    QRadioButton *rbContact;
    QRadioButton *rbImmersion;
    QRadioButton *rbAutoFreeze;
    QRadioButton *rbAuto;
    QRadioButton *rbManual;
    QRadioButton *rbCataract;
    QRadioButton *rbAphakic;

public:
    explicit key_radio(QWidget *parent = 0);
    
private slots:
    void changeSideSlot();
    void doChangeRegim();

};

#endif // key_radio_H
