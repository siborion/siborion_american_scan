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
//    explicit basefill(quint32 id, const QObjectList &list, QString tableName, QObject *parent);
    explicit basefill(quint32 id, const QObjectList &list, QString tableName);
    void saveData(void);
    void fillData(void);

private:
    scanbase *pBase;
    int findRecord(QSqlTableModel *tableModel, quint32 id);
    const QObjectList *olParent;
    quint32 uiId;
    QString qsTableName;
    
signals:
    
public slots:
};

#endif // BASEFILL_H
