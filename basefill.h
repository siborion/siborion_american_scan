#ifndef BASEFILL_H
#define BASEFILL_H

#include <QObject>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QSqlTableModel>
#include "scanbase.h"

class basefill : public QObject
{
    Q_OBJECT
public:
    explicit basefill(const QObjectList &list, QMap<QString,QString> *table);
    void saveData(void);
    void fillData(void);

private:
    int findRecord(QSqlTableModel *tableModel, quint32 id);
    const QObjectList *olParent;
    quint32 uiId;
    QString qsTableName;
    QMap<QString,QString> * qmTable;
    
signals:
    
public slots:
};

#endif // BASEFILL_H
