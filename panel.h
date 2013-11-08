#ifndef _PANEL_H_
#define _PANEL_H_ 1

#include <qtabwidget.h>
#include "scanplot.h"


class QComboBox;
class SpinBox;
class CheckBox;
class Knob;

class Panel: public QTabWidget
{
    Q_OBJECT

public:
    Panel( QWidget * = NULL );

Q_SIGNALS:

private Q_SLOTS:

private:
    QWidget *createOnlineTab( QWidget * );
    QWidget *createBaseTab( QWidget * );
};

#endif
