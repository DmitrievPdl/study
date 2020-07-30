#include "system.h"
#include<iostream>
#include<cmath>

System::System(double size, double phiLeft,double phiRight, double phiDown, double phiTop, int numGrid)
    : size_(size),phiLeft_(phiLeft),phiRight_(phiRight),phiDown_(phiDown), phiTop_(phiTop), numGrid_(numGrid), step_(size / DIM)
{}



double System::size() const
{
    return size_;
}
double System::phiLeft() const
{
    return phiLeft_;
}
double System::phiRight() const
{
    return phiRight_;
}
double System::phiDown() const
{
    return phiDown_;
}
double System::phiTop() const
{
    return phiTop_;
}
int System::numGrid() const
{
    return numGrid_;
}
double System::step() const
{
    return step_;
}



void System::iterationMethod(){
    double phi1[DIM][DIM],maximum,temp;
    maximum = 1; // чтобы войти в цикл
    //граничные условия
    for (int i = 0; i < DIM-1; i++) {
        phi[i][0] = phiDown();
        phi1[i][0] = phiDown();
    }
    for (int i = 0; i < DIM-1; i++) {
        phi[i][DIM-1] = phiTop();
        phi1[i][DIM-1] = phiTop();
    }
    for (int j = 0; j < DIM-1; j++) {
        phi[0][j] = phiLeft();
        phi1[0][j] = phiLeft();
    }
    for (int j = 0; j < DIM-1; j++) {
        phi[DIM-1][j] = phiRight();
        phi1[DIM-1][j] = phiRight();
    }
    //нулевая итерация
    for (int i = 1; i < DIM-1; i++) {
           for (int j = 1; j < DIM-1; j++) {
               phi1[i][j] = 0.1;
               phi[i][j] = 0.1;
           }
       }
    int i =0;
    while (i < 7000){
        for (int i = 1; i < DIM-1; i++) {
               for (int j = 1; j < DIM-1; j++) {
                   phi1[i][j] = phi[i][j];
               }
        }
        for (int i = 1; i < DIM-1; i++) {
               for (int j = 1; j < DIM-1; j++) {
                   phi[i][j] = (phi1[i+1][j] + phi1[i-1][j] + phi1[i][j+1] + phi1[i][j-1]) / 4.0;
               }
        }
        /*for (int i = 0; i < DIM; i++) {
               for (int j = 0; j < DIM; j++) {
                   temp = std::abs(phi[i][j] - phi1[i][j]);
                   if (maximum > temp){
                       maximum = temp;
                   }
               }
        }*/
        i++;
    }

}



