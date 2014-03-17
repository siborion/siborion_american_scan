#ifndef key_radio_H
#define key_radio_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class key_radio : public QWidget
{
    Q_OBJECT
public:
    explicit key_radio(QWidget *parent = 0);
    
signals:
    void key_radioAuto();
    
private slots:
    void key_radioAutoClicked();
    
};

#endif // key_radio_H
