#ifndef BIGVIEW_H
#define BIGVIEW_H

#include <QWidget>
#include <QLCDNumber>
#include <QGridLayout>

class bigview : public QWidget
{
    Q_OBJECT
public:
    explicit bigview(QWidget *parent = 0);
    void setDisplay(double);

private:
    QLCDNumber *lcdNumber;
    
signals:
    
public slots:
    
};

#endif // BIGVIEW_H
