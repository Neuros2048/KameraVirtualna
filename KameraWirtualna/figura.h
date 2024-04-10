#pragma once
#include <vcruntime.h>
#include <vector>

class figura
{
public:
    figura(double ** points,int n);
    figura();
    ~figura();
    void add_lines(int ** lines,int n);
    void transform(int point, double x,double y,double z);
    int numberOfPoints();
    int numberOfLines();
    double* operator [] (int i) const;
    int* getLine(int i);
    double* getPoints(int i);
    double* getPointsTransformed(int i);
private:
    double ** points = nullptr;
    int** lines = nullptr;
    double ** points_transform = nullptr;
    int nPoints;
    int nLines;
};

std::vector<figura*> get_base();