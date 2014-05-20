#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include <QFormLayout>
#include <adjview.h>
#include <QComboBox>


class formula : public QWidget
{
    Q_OBJECT
private:
    adjview *twHead;
    adjview *twCalculator;
    adjview *twFormula;
    adjview *twEmm;
    QComboBox *cbFormula;
    QStringList getListFormula();
    QStandardItem *getItem(QString, Qt::AlignmentFlag);

public:
    void setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs);

public:
    explicit formula(QWidget *parent = 0);
    
signals:
    
private slots:
    void refreshFormula(void);
};

#endif // FORMULA_H
