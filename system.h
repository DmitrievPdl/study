#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <map>
#include <vector>
#define DIM 500
#define ERR 1.0e-6

class System
{
public:
    System(double size, double phiLeft,double phiRight, double phiDown, double phiTop, int numGrid);

    double size() const;
    double phiLeft() const;
    double phiRight() const;
    double phiDown() const;
    double phiTop() const;
    int numGrid() const;
    double step() const;
    void iterationMethod();
private:
    double size_;
    double phiLeft_;
    double phiRight_;
    double phiDown_;
    double phiTop_;
    const int numGrid_;
    double step_;
public:
    double phi[DIM][DIM];

};
#endif // SYSTEM_H
