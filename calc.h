#ifndef CALC_H
#define CALC_H

#define SRKII      1
#define SRKT       2
#define HOFFERQ    3
#define HOLLADAY   4
#define HAIGIS     5





typedef struct _formulae{
    double PEMM;
    double IOLPower[7];
    double PORx[7];
}iol_formula;


int Calculator(int FormulaType, double AL, double AConst, double K,double Rx,iol_formula* formula_values);

void SRKIICalc(double AL, double AConst, double K,double Rx,iol_formula* SRKIIValues);
void SRKTCalc(double AL, double AConst,double K,double Rx,iol_formula* SRKTValues);
int HofferCalc(double A, double AConst, double K,double Rx,iol_formula* HofferValues);
void HolladayCalc(double AL, double AConst, double K,double Rx, iol_formula* HolladayValues);
void BinkhorstCalc(double AL,double AConst, double K,double Rx,iol_formula* BinhorstValues );


class calc
{
public:
    calc();
};

#endif // CALC_H
