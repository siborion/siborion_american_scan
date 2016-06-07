#ifndef ADJVIEW_H
#define ADJVIEW_H

#include <QTableView>
#include <QResizeEvent>
#include <QStandardItemModel>
#include <QHeaderView>

class adjview : public QTableView
{
    Q_OBJECT
private:
    QList<int> columnPercent;
public:
    explicit adjview(QTableView *parent = 0);
    explicit adjview(int row, int col, QList<int> columnPercent, QTableView *parent = 0);
    explicit adjview(int row, QStringList col, QList<int> columnPercent, QTableView *parent = 0);
    explicit adjview(QStringList row, int col, QList<int> columnPercent, QTableView *parent = 0);
    explicit adjview(QList<int> columnPercent, QTableView *parent = 0);
    void setColumnPercent(QList<int>);

signals:

public slots:

protected:
void resizeEvent( QResizeEvent *__e );


};

#endif // ADJVIEW_H
