#include "print.h"
#include <QDebug>

print::print(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *layout              = new QVBoxLayout(this);

    QPrinter printer;

//    QPrintDialog printDialog(&printer, this);
    QPrintPreviewDialog printDialog(&printer, this);

    if (printDialog.exec())
    {
        QPainter painter;

                if (! painter.begin(&printer))
                {
                    qWarning("Ошибка открытия принтера!");
                }

        // Сообственно все, откроется диалог где указывать принтер нужно, далее рисуем просто наш отчет
        //Теперь давайка отрисуем отчет на этом принтере
        painter.setFont(QFont("Arial", 14)); //шрифт
        painter.setPen(QPen(2)); // толщина линий таблицы
        int y_pdf = 30;
        int WtabPdf=350;
        int X_oneTab = 20;
        int X_twoTab = 370;
        int H_tab = 25;
        //        painter.drawText(230,y_pdf, "Протокол № " + m_ui->labelNumberZav_znach->text());
        y_pdf +=H_tab;
        QRect rectfont = QRect(X_oneTab,y_pdf,WtabPdf,H_tab);
        painter.drawRect(rectfont);
        painter.drawText(rectfont, Qt::AlignLeft ,"Заводской номер");
        rectfont.setRect(X_twoTab,y_pdf,WtabPdf,H_tab);
        painter.drawRect(rectfont);
        //        painter.drawText(rectfont, Qt::AlignLeft ,m_ui->labelNumberZav_znach->text());
        // и так далее рисуем
        painter.end(); // завершаем рисование

//            layout->addWidget(painter);
    }  // end printDialog.exec()



}

