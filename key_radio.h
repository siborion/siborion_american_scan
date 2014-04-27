#ifndef key_radio_H
#define key_radio_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>

class key_radio : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
//signals:
    void changeEye(quint8);
//    void keyAuto();
//    void keySave();


public:
    explicit key_radio(QWidget *parent = 0);
    
    
private slots:
    void key_radioOd(bool );
    void key_radioOs(bool );
//    void key_radioAutoClicked();

};

#endif // key_radio_H
