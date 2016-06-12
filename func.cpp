#include <Qfont>


QFont getFont(quint8 size, bool bold)
{
    QFont font;
    font.setBold(bold);
    font.setPointSize(size);
    font.setFamily(QStringLiteral("Arial"));
    return font;
}

