#ifndef BASES_H
#define BASES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QResizeEvent>

enum {enPatient, enDoctor, enLens};

class bases : public QWidget
{
    Q_OBJECT
public:
    explicit bases(QWidget *parent = 0);

signals:

public slots:

private:
    void adjCol();

    QTableView *twTable;
    QPushButton *pbAdd;
    QPushButton *pbDel;
    QPushButton *pbEdit;
    QPushButton *pbPatientHistory;
    QStandardItemModel *model;
    quint8 TypeBase;

protected:
void resizeEvent( QResizeEvent *__e );

private slots:
    void adjTable(quint8);
    void changeBasePatient();
    void changeBaseDoctor();
    void changeBaseLens();

};

#endif // BASES_H
