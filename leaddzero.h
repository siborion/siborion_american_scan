#ifndef LEADDZERO_H
#define LEADDZERO_H

#include <QLineEdit>

class leAddZero : public QLineEdit
{
    Q_OBJECT
public:
    explicit leAddZero(QWidget *parent = 0);
    void setTextZero(QString);

private slots:
    void lineEditUpdate();
};

#endif // LEADDZERO_H
