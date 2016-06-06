#ifndef COMBOITEM_H
#define COMBOITEM_H

#include <QComboBox>

class ComboItem : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboItem(QWidget *parent = 0);

private:
//    virtual void hidePopup();
    void focusInEvent(QFocusEvent *e);
signals:

public slots:

private slots:
    void slClearFocus();
    void slPopup();

};

#endif // COMBOITEM_H
