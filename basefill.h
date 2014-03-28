#ifndef BASEFILL_H
#define BASEFILL_H

#include <QObject>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>
#include <QComboBox>
#include <QSqlTableModel>
#include "scanbase.h"

class basefill : public QObject
{
    Q_OBJECT
public:
    explicit basefill(QObject *parent = 0);

private:
    scanbase *pBase;
    void fillData();
    int findRecord(QSqlTableModel *tableModel, quint32 id);
    void save();
    quint32 Id;
    
signals:
    
public slots:
    
};

#endif // BASEFILL_H
