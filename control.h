#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);

signals:

public slots:
    void ttt();

};

#endif // CONTROL_H
