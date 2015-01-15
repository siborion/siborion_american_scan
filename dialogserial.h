#ifndef DIALOGSERIAL_H
#define DIALOGSERIAL_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class DialogSerial;
}

class DialogSerial : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSerial(QWidget *parent = 0, QStringList *name = 0);
    ~DialogSerial();
    QComboBox *cbPort;

private:
    Ui::DialogSerial *ui;

};

#endif // DIALOGSERIAL_H
