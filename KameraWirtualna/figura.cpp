#include "figura.h"

#include <cstdlib>
#include <iostream>

figura::figura(double** points, int n)
{
    this->points = points;
    nPoints = n;
    points_transform = static_cast<double**>(malloc(sizeof(double*) * n));
    for(int i = 0 ; i < n ; i++)
    {
        points_transform[i] = static_cast<double*>(malloc(sizeof(double) * 3));
    }
}

figura::figura()
{
}

figura::~figura()
{
    if(this->points!= nullptr)
    {
        for(int i = 0 ; i < this->nPoints;i++)
        {
            free(points[i]);
        }
        free(points);
    }
    if(this->points_transform!= nullptr)
    {
        for(int i = 0 ; i < this->nPoints;i++)
        {
            free(points_transform[i]);
        }
        free(points_transform);
    }
    if(this->lines!= nullptr)
    {
        for(int i = 0 ; i < this->nLines;i++)
        {
            free(lines[i]);
        }
        free(lines);
    }
}

void figura::add_lines(int** lines, int n)
{
    this->lines = lines;
    nLines = n;
}

void figura::transform(int point, double x, double y, double z)
{
    points_transform[point][1] = x;
    points_transform[point][2] = y;
    points_transform[point][3] = z;
}

int figura::numberOfPoints()
{
    return nPoints;
}

int figura::numberOfLines()
{
    return nLines;
}

double* figura::operator[](int i) const
{
    return points_transform[i];
}

int* figura::getLine(int i)
{
    return lines[i];
}

double* figura::getPoints(int i)
{
    return points[i];
}

double* figura::getPointsTransformed(int i)
{
    return points_transform[i];
}


struct positions
{
    double ** points = nullptr;
    int ** lines = nullptr;
    int n_points;
    int n_lines;
};



positions create_prostopadloscian(double x,double y,double z,double h)
{
    positions p;
    p.points = static_cast<double**>(malloc(sizeof(double*) * 8));
    p.lines = static_cast<int**>(malloc(sizeof(int*) * 12));
    p.n_points = 8;
    p.n_lines = 12;
    for(int i = 0 ;i < 8 ; i++)
    {
        p.points[i] = static_cast<double*>(malloc(sizeof(double) * 3));
    }
    for(int i = 0 ;i < 12 ; i++)
    {
        p.lines[i] = static_cast<int*>(malloc(sizeof(int) * 2));
    }
    for(int i = 0 ;i < 4 ; i++)
    {
        p.lines[i][0] = i ;
        p.lines[i][1] = (i+1)%4;
        
        p.lines[i+4][0] = i ;
        p.lines[i+4][1] = i+4;
        
        p.lines[i+8][0] = i + 4 ;
        p.lines[i+8][1] = (i+1)%4+ 4;
    }
    p.points[0][0] = x;
    p.points[0][1] = y;
    p.points[0][2] = z;
    
    p.points[1][0] = x;
    p.points[1][1] = y;
    p.points[1][2] = z+h;
    
    p.points[2][0] = x-h;
    p.points[2][1] = y;
    p.points[2][2] = z+h;
    
    p.points[3][0] = x-h;
    p.points[3][1] = y;
    p.points[3][2] = z;

    p.points[4][0] = x;
    p.points[4][1] = y+2*h;
    p.points[4][2] = z;

    p.points[5][0] = x;
    p.points[5][1] = y+2*h;
    p.points[5][2] = z+h;

    p.points[6][0] = x-h;
    p.points[6][1] = y+2*h;
    p.points[6][2] = z+h;

    p.points[7][0] = x-h;
    p.points[7][1] = y+2*h;
    p.points[7][2] = z;
    return p;
};
positions create_dodecahedron(double x,double y,double z,double h)
{
    positions p;
    p.points = static_cast<double**>(malloc(sizeof(double*) * 20));
    p.lines = static_cast<int**>(malloc(sizeof(int*) * 30));
    p.n_points = 20;
    p.n_lines = 30;
    for(int i = 0 ;i < 20 ; i++)
    {
        p.points[i] = static_cast<double*>(malloc(sizeof(double) * 3));
    }
    for(int i = 0 ;i < 30 ; i++)
    {
        p.lines[i] = static_cast<int*>(malloc(sizeof(int) * 2));
    }
    for(int i = 0 ;i < 5 ; i++)
    {
        p.lines[i][0] = i ;
        p.lines[i][1] = (i+1)%5;
        
        p.lines[i+5][0] = i ;
        p.lines[i+5][1] = i+5;
        
        p.lines[i+10][0] = i + 5 ;
        p.lines[i+10][1] = i + 10;

        p.lines[i+15][0] = i + 10;
        p.lines[i+15][1] = (i+1)%5 + 5;

        p.lines[i+20][0] = i +10;
        p.lines[i+20][1] = i +15;

        p.lines[i+25][0] = i + 15 ;
        p.lines[i+25][1] = (i+1)%5+ 15;
    }

    std::vector<std::vector<double>> original_coordinates = {
        {-1, -1, 1},  {0, -0.6180339887498949, 1.618033988749895},    {0, 0.6180339887498949, 1.618033988749895},
        {-1, 1, 1},{-1.618033988749895, 0, 0.6180339887498949},  {-0.6180339887498949, -1.618033988749895, 0},
        {1, -1, 1},{1, 1, 1}, {-0.6180339887498949, 1.618033988749895, 0},  {-1.618033988749895, 0, -0.6180339887498949},
        {0.6180339887498949, -1.618033988749895, 0},     {1.618033988749895, 0, 0.6180339887498949},  {0.6180339887498949, 1.618033988749895, 0},
        {-1, 1, -1},{-1, -1, -1}, {1, -1, -1},{1.618033988749895, 0, -0.6180339887498949}, {1, 1, -1},
        {0, 0.6180339887498949, -1.618033988749895},  {0, -0.6180339887498949, -1.618033988749895}
    };

    for (int i = 0; i < 20; ++i) {
        p.points[i][0] = x + h*original_coordinates[i][0];
        p.points[i][1] = y + h*original_coordinates[i][1];
        p.points[i][2] = z + h*original_coordinates[i][2];
    }

    return p;
}

std::vector<figura*> get_base()
{
    std::vector<figura*> res(5);
    positions p = create_prostopadloscian(90,0,400,80); 
    res[0] = new figura(p.points,p.n_points);
    res[0]->add_lines(p.lines,p.n_lines);
    p = create_prostopadloscian(-30,0,400,80); 
    res[1] = new figura(p.points,p.n_points);
    res[1]->add_lines(p.lines,p.n_lines);
    p = create_prostopadloscian(90,0,800,80); 
    res[2] = new figura(p.points,p.n_points);
    res[2]->add_lines(p.lines,p.n_lines);
    p = create_prostopadloscian(-30,0,800,80); 
    res[3] = new figura(p.points,p.n_points);
    res[3]->add_lines(p.lines,p.n_lines);
    p =create_dodecahedron(300,0,400,80);
    res[4] = new figura(p.points,p.n_points);
    res[4]->add_lines(p.lines,p.n_lines);
    return res;
}

