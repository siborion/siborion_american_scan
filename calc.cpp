#include "calc.h"
#include <math.h>
#include <QDebug>

calc::calc()
{
}

#include "calc.h"


double CalculatedACD(double AL, double AConst, double KD)
{
 double m, g, kk,ACD;
 double ACD1,ACD2,ACD3;
  if (AL <= 23.0){
     m = 1.0;
     g = 28.0;
  }
  else{
     m = -1.0;
     g = 23.5;
  }


  //ACD = 0.5663 * AConst - 63.896;
  //ACD = 0.62467 * AConst - 68.747;
  ACD =(AConst*0.5663-65.6+3.595)/0.9704;



  if (ACD > 6.5)
      ACD = 6.5;
  else if (ACD < 3.0)
     ACD = 3.0;

  kk = KD / 57.2957;
  ACD1 =     0.3 * (AL - 23.5);
  ACD2 = tan(kk) * tan(kk);
  ACD3 = 0.1 * m * (23.5- AL) * (23.5 - AL) * tan((0.1 * (g - AL) * (g - AL)) / 57.2957);

  //printf("\r\nACD1=%5.2f ACD2=%5.2f ACD3=%5.2f",ACD1,ACD2,ACD3);

  return (ACD + ACD1 + ACD2 + ACD3 - 0.9917);





 //gnum=(0.1*m*((23.5-alf[defeye])*(23.5-alf[defeye])))*(tan((0.1*((g-alf[defeye])*(g-alf[defeye])))/rtd))-0.9917;
 //   acd=acdf[w]+0.3*(alf[defeye]-23.5)+(tan(tem)*tan(tem))+gnum;
 //       alf[defeye]=altemp;

  //return ACD;
}



double Diff(double DIE)
{
  if ((DIE >= -0.25) & (DIE < 0))
     return 0.0;
  else if ((DIE >= -0.5) & (DIE < -0.25))
     return -0.5;
  else if ((DIE >= -0.75) & (DIE < -0.5))
     return -0.5;
  else if ((DIE >= -1.0) & (DIE < -0.75))
     return -1.0;
  else if ((DIE <= 0.25) & (DIE > 0.0))
    return 0.0;
  else if ((DIE > 0.25) & (DIE <= 0.5))
    return 0.5;
  else if ((DIE > 0.5) & (DIE <= 0.75))
    return 0.5;
  else if ((DIE > 0.75) & (DIE <= 1.0))
    return 1.0;
  else
    return 0.0;
}



void BinkhorstCalc(double AL,double AConst, double K,double Rx,iol_formula* BinhorstValues )
{
 double AL_dash;
 double N1;
 double N2;
 double N3;
 double B;
 double T;
 double RD;
 double R;
 double AD;
 double LP;
 double DR;
 double VD;

 //print("\r\nBinkhorst");
 N1 = 1.333;
 N2 = 1.336;
 N3 = 1.49;
 B = 0.25;
 T = 0.5;
 RD = 6;
 R = 337.5/K;



}

void HolladayCalc(double AL, double AConst, double K,double Rx, iol_formula* HolladayValues)
{
int Loop;
double N1;
double N2;
double RT;
double R;
double Rag;
double VD;
double Alm;
double AQ;
double BQ;
double CQ;
double ER;
double LP;
double SF;
double AD;
double AG;
double IOL_1;
double IOL_2;
double DR=0.0;
double P_Emmetropia;
double ERROR_1;
double ERROR_2;
double Rx_ERROR;
double Emmetropia_Rounded;
double Diff_In_Emmetropia;
double Diff_Add;
double Emmetropia_New;


//print("\r\nHolladay");
N1 = 1.333;
N2 = 1.336;
RT = 0.200;
R = 337.5/K;
VD = 12.0;
ER = 0.0;
//SF = AConst * 0.5663 - 65.60;
SF = AConst;

//printf("\r\nSF = %5.2f",SF);
LP=0.0;
Alm = AL + RT;
if (R >= 7)
  Rag = R;
else if (R < 7)
  Rag = 7;

AG = 12.5 * AL/23.45;
if (AG > 13.5)
   AG = 13.5;
AD = 0.56+Rag - sqrt(Rag*Rag-(AG*AG/4));

IOL_1 =1000*N2*(N2*R-(N1-1)*Alm-0.001*DR*(VD*(N2*R-(N1-1)*Alm)+Alm*R));
IOL_2 = (Alm-AD-SF)*(N2*R-(N1-1)*(AD+SF)-0.001*DR*(VD*(N2*R-(N1-1)*(AD+SF))+(AD+SF)*R));

P_Emmetropia = IOL_1/IOL_2;
//printf("\r\n%5.2f %5.2f",AL,P_Emmetropia);
HolladayValues->PEMM = P_Emmetropia;

  DR=Rx;
IOL_1 =1000*N2*(N2*R-(N1-1)*Alm-0.001*DR*(VD*(N2*R-(N1-1)*Alm)+Alm*R));
IOL_2 = (Alm-AD-SF)*(N2*R-(N1-1)*(AD+SF)-0.001*DR*(VD*(N2*R-(N1-1)*(AD+SF))+(AD+SF)*R));

P_Emmetropia = IOL_1/IOL_2;

LP = P_Emmetropia;

  Emmetropia_Rounded = floor(P_Emmetropia);
  Diff_In_Emmetropia = P_Emmetropia - Emmetropia_Rounded;
  Diff_Add = Diff(Diff_In_Emmetropia);
  Emmetropia_New = Emmetropia_Rounded + Diff_Add;
  Loop=0;
  for (LP = Emmetropia_New - 1.5; LP <= Emmetropia_New + 1.5; LP = LP + 0.5)
   {
    HolladayValues->IOLPower[Loop] = LP;
    ERROR_1 = 1000*N2*(N2*R-(N1-1)*Alm)-LP*(Alm-AD-SF)*(N2*R-(N1-1)*(AD+SF));
    ERROR_2 = N2*(VD*(N2*R-(N1-1)*Alm)+Alm*R)-0.001*LP*(Alm-AD-SF)*(VD*(N2*R-(N1-1)*(AD+SF))+(AD+SF)*R);
    Rx_ERROR = ERROR_1/ERROR_2;
    HolladayValues->PORx[Loop] = Rx_ERROR;
//  printf("\r\n%5.2f,%5.2f",HolladayValues->IOLPower[Loop],HolladayValues->PORx[Loop]);
    Loop++;
   }
//   printf("\r\n");



//AQ = (N1-1)-(0.001*ER*((VD*(N1-1))-R));
//BQ = ER*0.001*((Alm*VD*(N1-1)) -(R*(Alm-(VD*N2))))-(((N1-1)*Alm)+(N2*R));
//CQ = (Alm*N2*R)-(0.001*ER*Alm*VD*R*N2)-(1000*N2*((N2*R)-((N1-1)*Alm)-(0.001*ER*((VD*((N2*R)-((N1-1)*Alm)))+(Alm*R)))))/LP;


//SF = (-BQ - sqrt(BQ*BQ-(4*AQ*CQ))/(2*AQ)) - AD;
//printf("\r\n%5.2f",SF);

}

void SRKIICalc(double AL, double AConst, double K, double Rx, iol_formula* SRKIIValues)
{
    double i;
    double Emmetropia, Emmetropia_Rounded,Emmetropia_New,CR,REFR1;
    double Diff_In_Emmetropia, Diff_Add;
    double REFR;
    int Loop;

    if (AL < 20.0)
        AConst = AConst + 3;
    else if ((AL >= 20.0) & (AL < 21.0))
        AConst = AConst + 2;
    else if ((AL >= 21.0) & (AL < 22.0))
        AConst = AConst + 1;
    else if ((AL >= 22) & (AL < 24.5))
        AConst = AConst;
    else if (AL >= 24.5)
        AConst = AConst - 0.5;

    Emmetropia = AConst - (0.9 * K) - (2.5 * AL);

    SRKIIValues->PEMM = Emmetropia;

    Emmetropia_Rounded = floor(Emmetropia);

    Diff_In_Emmetropia = Emmetropia - Emmetropia_Rounded;

    if (Emmetropia < 14.0)
        CR = 1.0;
    else if (Emmetropia >= 14.0)
        CR = 1.25;

//    qDebug()<<"Emmetropia"<<Emmetropia;


    Diff_Add = Diff(Diff_In_Emmetropia);

    Emmetropia_New = Emmetropia_Rounded + Diff_Add;
    Diff_In_Emmetropia = Emmetropia - Emmetropia_New;
    REFR1 = Diff_In_Emmetropia / CR;

    Emmetropia_New -= Rx;

//    Emmetropia_New += Rx*CR;

    REFR1 += Rx;

    Loop=0;
    for (i = Emmetropia_New - 1.5; i <= Emmetropia_New + 1.5; i = i + 0.5)
    {
        REFR = (REFR1 + (Emmetropia_New - i) / CR);
//        REFR = (REFR1 + (i) / CR);
        SRKIIValues->PORx[Loop] = REFR;
        SRKIIValues->IOLPower[Loop] = i;
        Loop++;
    }
}

void SRKTCalc(double AL, double AConst,double K,double Rx,iol_formula* SRKTValues)
{
 double ALCORR,ACCORR,C0,C1,C3,C4,C5,C6,C8,C9,CRWDES,SQRTR1;
 double Emmetropia,Emmetropia_Rounded,Emmetropia_New,Diff_In_Emmetropia,Diff_Add;
 double REFR1,i;
 double IOLPower;
 double REFR;
 double ACD;

 int Loop=0;


 //print("\r\nSRKT");
 ACD = 0.62467 * AConst - 68.747;

 if (AL > 24.2)
   ALCORR = (1.716 - 0.0237 * AL) * AL - 3.446;
 else
   ALCORR = AL;

 C0 = K;
 C1 = 337.5 / C0;
 CRWDES = 0.58412 * ALCORR + 0.098 * C0 - 5.40948;
 SQRTR1 = C1 * C1 - ((CRWDES * CRWDES) / 4.0);
 if (SQRTR1 < 0)
   SQRTR1 = 0.0;

 ACCORR = C1 - sqrt(SQRTR1) + ACD - 3.3357;

 C3 = AL * 0.97971 + 0.65696;

 C4 = C3 - ACCORR;

 C5 = 1.336 * C1 - 0.333 * ACCORR;

 C6 = 1.336 * C1 - 0.333 * C3;

 C8 = 12.0 * C6 + C3 * C1;

 C9 = 12.0 * C5 + ACCORR * C1;

 REFR1 = Rx;
 Emmetropia = (1336.0 * (C6 - 0.001 * REFR1 * C8)) / (C4 * (C5 - 0.001 * REFR1 * C9));
 Emmetropia_Rounded = floor(Emmetropia);
 SRKTValues->PEMM = (1336.0 * (C6 - 0.001 * 0 * C8)) / (C4 * (C5 - 0.001 * REFR1 * C9));
 Diff_In_Emmetropia = Emmetropia - Emmetropia_Rounded;
 Diff_Add = Diff(Diff_In_Emmetropia);
 Emmetropia_New = Emmetropia_Rounded + Diff_Add;
 for (i = Emmetropia_New - 1.5; i <= Emmetropia_New + 1.5; i = i + 0.5)
 {
     SRKTValues->IOLPower[Loop] = i;
     REFR = (1336.0 * C6 - i * C4 * C5) / (1.336 * C8 - 0.001 * i * C4 * C9);
     SRKTValues->PORx[Loop] = REFR;
     SRKTValues->IOLPower[Loop] = i;
     Loop++;
 }
}


int HofferCalc(double A, double ACD, double K,double Rx,iol_formula* HofferValues)
{
  double C,R1,P;
  double P_Emmetropia,P_Emmetropia_New,DIE,REFR;
  int Loop;
 double m, g, kk;
 double ACD1,ACD2,ACD3;

 if (K <= 0)
    return -1;
 if (A <= 0)
    return -1;

  if (A <= 23.0){
     m = 1.0;
     g = 28.0;
  }
  else{
     m = -1.0;
     g = 23.5;
  }


  if (ACD > 6.5)
      ACD = 6.5;
  else if (ACD < 3.0)
     ACD = 3.0;

  kk = K / 57.2957;
  ACD1 =     0.3 * (A - 23.5);
  ACD2 = tan(kk) * tan(kk);
  ACD3 = 0.1 * m * (23.5- A) * (23.5 - A) * tan((0.1 * (g - A) * (g - A)) / 57.2957);


  C = (ACD + ACD1 + ACD2 + ACD3 - 0.9917);

//  C = CalculatedACD(A,AConst, K);
//  C = AConst;

//  printf("\r\nACD=%7.4f",C);
  P_Emmetropia = (1336.0 / (A          - C- 0.05))-(1.336/ ((1.336 / (K + Rx)) - ((C  + 0.05) / 1000.0)));
          //p0 = (1336.0/  (alf[defeye]-acd-0.05))-(1.336/ ((1.336 / (k + 0)) - ((acd+ 0.05) / 1000.0)));

  HofferValues->PEMM = (1336.0 / (A          - C- 0.05))-(1.336/ ((1.336 / (K + 0)) - ((C  + 0.05) / 1000.0)));
  //printf("\r\nP_Emmetropia = %5.2f AConst=%5.2f AL=%5.2f K=%5.2f",P_Emmetropia, AConst,A,K);
  P_Emmetropia_New = floor(P_Emmetropia);
  DIE = P_Emmetropia - P_Emmetropia_New;
  P_Emmetropia_New = P_Emmetropia_New + Diff(DIE);

  Loop = 0;
  for (P = P_Emmetropia_New - 1.5; P<=P_Emmetropia_New + 1.5; P= P + 0.5){
    R1 = (1.336 / (1.336 / (1336 / (A - C - 0.05) - P) + (C + 0.05) / 1000.0)) - K;
    REFR = R1 / (1 + (0.012 * R1));
    HofferValues->PORx[Loop] = REFR;
    HofferValues->IOLPower[Loop] = P;
//	lcdWriteValue(HofferValues.IOLPower[Loop],IOL_TABLE_HPOSITION+ 35 +(Loop * 15),22,FLOAT);
//	lcdWriteValue(HofferValues.PORx[Loop],IOL_TABLE_HPOSITION + 35 +(Loop * 15),32,FLOAT);
//    printf("\r\n%5.2f,%5.2f",HofferValues->IOLPower[Loop],HofferValues->PORx[Loop]);
    Loop++;
  }
//  printf("\r\n");
 return 0;
}

int HaigisCalc(double a0, double a1, double a2, double AL, double AConst, double ac,double K,double Rx,iol_formula* HaigisValues)
{
    double R=337.5;
//    double a0;
//    double a1=0.4;
//    double a2=0.1;
    double ACDd;
    double u = -0.241;
    double v= 0.139;
    double Dc;
    double nc = 1.3315;
    double z;
    double dx=0.012;
//    double dx=12;
    double Dl;
    double n = 1336;
    double q;
    double Refr;
    double iol;
    double iolLRScor;
    double q1,q2;
    double haigis_PEmm;
    double haigis_PEmm_New;
    double DIE;
    int Loop;
    double P;

//    a0= 0.62467 * AConst -72.434;

    //Optical ACD calculation
    if (ac!= 0.00)
        ACDd=   a0 + a1*ac + a2*AL;
    else
        ACDd = (a0 + u*a1) +(a2+v*a1) * AL;


//    R = 336.0;
//    R /= K;
    if(K>40)
        R = (R/K);
    else
        R = K;


    R /= 1000;

    Dc = ((nc -1))/(R);


/// P_Emmetropia
    z = Dc  +  (Rx/(1-Rx*dx));

    Dl= (((n/(AL-ACDd))-(n/((n/z)-ACDd))));

    haigis_PEmm = Dl;
    haigis_PEmm_New = HaigisValues->PEMM = haigis_PEmm;


    haigis_PEmm_New = floor(haigis_PEmm);
    DIE = haigis_PEmm - haigis_PEmm_New;
    haigis_PEmm_New = haigis_PEmm_New + Diff(DIE);


//    haigis_PEmm = Dl;
//    haigis_PEmm_New = floor(Dl);
//    DIE = haigis_PEmm - haigis_PEmm_New;
//    HaigisValues->PEMM = haigis_PEmm_New = haigis_PEmm_New + Diff(DIE);








 //   printf("\r\nL=%5.2lf,AC=%5.2lf,R=%5.2lf,Rx=%5.3lf",AL,ac,R,Rx);
//    printf("\r\nd=%5.3lf Haigis_PEmm=%5.3lf\n",ACDd,haigis_PEmm);
   // q =  n * (n-Dl*(AL-ACDd))/(n*(AL-ACDd) + ACDd *(n-Dl*(AL-ACDd)));




//    Refr = (q - Dc)/(1+dx*(q-Dc));

   Loop=0;

//   n*=1000;
//   Dc*=1000;

   for (P = haigis_PEmm_New - 1.5; P<=haigis_PEmm_New + 1.5; P= P + 0.5)
   {
       q1= n*(n-((P)*(AL-ACDd)));


       q2=(n*(AL-ACDd)) + ACDd*(n-(P*(AL-ACDd)));

       q=q1/q2;




       Refr=(q-Dc)/(1+0.012*(q-Dc));




       HaigisValues->PORx[Loop] = Refr;
       HaigisValues->IOLPower[Loop] = P;
       Loop++;
   }
}







int Calculator(int FormulaType, double AL, double AConst, double K, double Rx,iol_formula* formula_values)
{
   double i;


   //AL= 23.5;
   //AConst = 118.50;
   //K = 45.0;
//   printf("\r\nSRKII");
//   SRKIICalc(AL,AConst,K);

   switch (FormulaType)
   {
   case SRKII:
            SRKIICalc(AL,AConst,K, Rx,formula_values);
       break;
   case SRKT:
            SRKTCalc(AL,AConst,K, Rx,formula_values);
       break;
   case HOFFERQ:
            HofferCalc(AL,AConst,K, Rx,formula_values);
       break;
   case HOLLADAY:
            HolladayCalc(AL,AConst,K, Rx,formula_values);
       break;
//   case HAIGIS:
//            HaigisCalc(AL, AConst, ACD_measure, K, 0, formula_values);
//       break;
   }
  return 0;
}

