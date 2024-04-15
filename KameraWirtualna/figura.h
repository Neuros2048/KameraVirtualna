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
