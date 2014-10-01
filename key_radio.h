#ifndef key_radio_H
#define key_radio_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include "curentparam.h"

class key_radio : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
    void changeCataractSignal(bool cataract);
    void changeContactSignal (bool contact);

private:
    CurentParam *curentParam;
    QRadioButton *rbOd;
    QRadioButton *rbOs;
    QGroupBox    *gbEye;
    QRadioButton *rbContact;
    QRadioButton *rbImmersion;

public:
    explicit key_radio(QWidget *parent = 0);
    
private slots:
    void changeSideSlot();
    void doChangeSide();
    void doChangeCataract();
    void doChangeContact();
};

#endif // key_radio_H
