#ifndef ADJVIEW_H
#define ADJVIEW_H

#include <QTableView>
#include <QResizeEvent>

class adjview : public QTableView
{
    Q_OBJECT
private:
    QList<int> columnPercent;
public:
    explicit adjview(QTableView *parent = 0);
    void setColumnPercent(QList<int>);

signals:

public slots:

protected:
void resizeEvent( QResizeEvent *__e );


};

#endif // ADJVIEW_H
