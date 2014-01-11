#ifndef LENS_H
#define LENS_H

#include <QDialog>
#include <QHeaderView>
#include <QFormLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <adjview.h>

class lens : public QDialog
{
    Q_OBJECT
public:
    explicit lens(QWidget *parent = 0);
private:
    adjview *twLens;
    QStandardItemModel *modelLens;

    QString baseMap[17][2] = {
        {"Lens Name",  "lensName"},
        {"Lens Mfg", "lensMfg"},
        {"Optic Diameter 1", "opticDiameter1"},
        {"Optic Diameter 2", "opticDiameter2"},
        {"Over Lenght", "overLenght"},
        {"Loop Angle", "loopAngle"},
        {"Mfg A-Const", "mfgAConst"},
        {"Mfg ACD", "mfgACD"},
        {"Mfg SF", "mfgSF"},
        {"Power Range", "powerRange"},
        {"Optic Material", "opticMaterial"},
        {"Loop Material", "loopMaterial"},
        {"PC", "pc"},
        {"Notes", "notes"},
        {"Added", "added"},
        {"Holladay SF", "holladaySF"},
        {"Holladay ACD", "holladayACD"},
        };

};

#endif // LENS_H
