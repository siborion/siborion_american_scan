#ifndef BASES_H
#define BASES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>


class bases : public QWidget
{
    Q_OBJECT
public:
    explicit bases(QWidget *parent = 0);

signals:

public slots:

private:
    void adjTable();
    QTableWidget *twTable;
    QPushButton *pbAdd;
    QPushButton *pbDel;
    QPushButton *pbEdit;

};

#endif // BASES_H
