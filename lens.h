#ifndef LENS_H
#define LENS_H

#include <QDialog>
#include <QHeaderView>
#include <QFormLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <adjview.h>

class lens : public QDialog
{
    Q_OBJECT
public:
    explicit lens(QWidget *parent = 0);
private:
    adjview *twLens;
    QStandardItemModel *modelLens;

};

#endif // LENS_H
