#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class key : public QWidget
{
    Q_OBJECT
public:
    explicit key(QWidget *parent = 0);
    
signals:
    void keyAuto();
    
private slots:
    void keyAutoClicked();
    
};

#endif // KEY_H
