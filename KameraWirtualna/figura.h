#pragma once
#include <vcruntime.h>
#include <vector>
#include <SFML/Graphics.hpp>

class figura
{
public:
    figura(double ** points,int n);
    figura();
    ~figura();
    void add_lines(int ** lines,int n);
    void add_walls(int ** walls,int n);
    void addColors(sf::Color* colors);
    void transform(int point, double x,double y,double z);
    int numberOfPoints();
    int numberOfLines();
    int numberOfWalls();
    double* operator [] (int i) const;
    int* getLine(int i);
    int* getWall(int i);
    sf::Color getWallCollor(int i);
    double* getPoints(int i);
    double** getAllPoint();
    double* getPointsTransformed(int i);
private:
    double ** points = nullptr;
    int** lines = nullptr;
    int** walls = nullptr;
    sf::Color * colors =nullptr;
    double ** points_transform = nullptr;
    int nPoints;
    int nLines;
    int nWalls;
};

std::vector<figura*> get_base();

struct wieszcholek
{
    double ** pt;
    int* wall;
    sf::Color color;
    wieszcholek* left = nullptr;
    wieszcholek* right = nullptr;
};

/*Point p1 = {parent->pt[parent->wall[0]][0], parent->pt[parent->wall[0]][1], parent->pt[parent->wall[0]][2]};
    Point p2 = {parent->pt[parent->wall[1]][0], parent->pt[parent->wall[1]][1], parent->pt[parent->wall[1]][2]};
    Point p3 = {parent->pt[parent->wall[2]][0], parent->pt[parent->wall[2]][1], parent->pt[parent->wall[2]][2]};
    Point p4 = {parent->pt[parent->wall[3]][0], parent->pt[parent->wall[3]][1], parent->pt[parent->wall[3]][2]};
    Wall ww {p1,p2,p3,p4};
    double a, b, c,c;
    calculateNormal(p1, p2, p3, a, b, c);
    z1max = planeEquation(a, b, c, p4);
    
     p1 = {x.pt[x.wall[0]][0], x.pt[x.wall[0]][1], x.pt[x.wall[0]][2]};
     p2 = {x.pt[x.wall[1]][0], x.pt[x.wall[1]][1], x.pt[x.wall[1]][2]};
     p3 = {x.pt[x.wall[2]][0], x.pt[x.wall[2]][1], x.pt[x.wall[2]][2]};
    p4 = {x.pt[x.wall[3]][0], x.pt[x.wall[3]][1], x.pt[x.wall[3]][2]};
    calculateNormal(p1, p2, p3, a, b, c);
    
    //bool r = isPointBehindWall({,,},{0,0,0},ww); 
    z2max = planeEquation(a, b, c, p4);*/
//if((x.pt[x.wall[0]][0]+x.pt[x.wall[1]][0]+x.pt[x.wall[2]][0]+x.pt[x.wall[3]][0])/4*a+(x.pt[x.wall[0]][1]+x.pt[x.wall[1]][1]+x.pt[x.wall[2]][1]+x.pt[x.wall[3]][1])/4*b+(x.pt[x.wall[0]][2]+x.pt[x.wall[1]][2]+x.pt[x.wall[2]][2]+x.pt[x.wall[3]][2])/4*c+z1max> 0)