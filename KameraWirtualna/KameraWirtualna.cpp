#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <cstring>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Matrix.h"
#include "figura.h"

using namespace std;
int width = 1600;
int height = 800;
# define M_PI 3.14159265358979323846

struct Point {
    double x, y, z;
};

// Funkcja obliczająca wektor normalny do płaszczyzny na podstawie trzech punktów
void calculateNormal(const Point& p1, const Point& p2, const Point& p3, double& a, double& b, double& c) {
    // Obliczenie dwóch wektorów tworzących trójkąt
    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v1z = p2.z - p1.z;

    double v2x = p3.x - p1.x;
    double v2y = p3.y - p1.y;
    double v2z = p3.z - p1.z;

    // Obliczenie składowych wektora normalnego jako iloczynu wektorowego
    a = v1y * v2z - v1z * v2y;
    b = v1z * v2x - v1x * v2z;
    c = v1x * v2y - v1y * v2x;

    // Normalizacja wektora normalnego
    double length = sqrt(a * a + b * b + c * c);
    if (length != 0) {
        a /= length;
        b /= length;
        c /= length;
    }
}

// Funkcja wyznaczająca równanie płaszczyzny na podstawie wektora normalnego i punktu na płaszczyźnie
double planeEquation(double a, double b, double c, const Point& point) {
    double d = -(a * point.x + b * point.y + c * point.z); // Obliczenie odległości od początku układu współrzędnych
    return d/ sqrt(a * a + b * b + c * c);
    // Wyświetlenie równania płaszczyzny
    
}



wieszcholek * maketree(wieszcholek * parent, wieszcholek x)
{
    wieszcholek* nowy;
    if(parent == nullptr)
    {
        wieszcholek* nowy = new wieszcholek;
        nowy->pt = x.pt;
        nowy->wall = x.wall;
        nowy->color = x.color;
        return nowy;
    }
    double z1max = 0,z2max = 0;
    Point p1 = {parent->pt[parent->wall[0]][0], parent->pt[parent->wall[0]][1], parent->pt[parent->wall[0]][2]};
    Point p2 = {parent->pt[parent->wall[1]][0], parent->pt[parent->wall[1]][1], parent->pt[parent->wall[1]][2]};
    Point p3 = {parent->pt[parent->wall[2]][0], parent->pt[parent->wall[2]][1], parent->pt[parent->wall[2]][2]};

    // Wyznaczenie wektora normalnego do płaszczyzny
    double a, b, c;
    calculateNormal(p1, p2, p3, a, b, c);
    // Użycie jednego z punktów do wyznaczenia równania płaszczyzny
    z1max = planeEquation(a, b, c, p1);

     p1 = {x.pt[x.wall[0]][0], x.pt[x.wall[0]][1], x.pt[x.wall[0]][2]};
     p2 = {x.pt[x.wall[1]][0], x.pt[x.wall[1]][1], x.pt[x.wall[1]][2]};
     p3 = {x.pt[x.wall[2]][0], x.pt[x.wall[2]][1], x.pt[x.wall[2]][2]};
    calculateNormal(p1, p2, p3, a, b, c);
    z2max = planeEquation(a, b, c, p1);
    if(z2max > z1max)
    {
        parent->left =  maketree(parent->left, x);
    }else
    {
        parent->right =  maketree(parent->right, x);
    }
    return parent;
};


int main()
{
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Kamera Wirtualan");
    sf::CircleShape shape(100.f);
    sf::Vertex line[]{
        sf::Vertex(sf::Vector2f(45,100)),
        sf::Vertex(sf::Vector2f(30,200))
    };
    shape.setFillColor(sf::Color::Green);
    sf::ConvexShape czworoscian(4);
    czworoscian.setPoint(0,sf::Vector2f(30,30));
    czworoscian.setPoint(1,sf::Vector2f(30,80));
    czworoscian.setPoint(3,sf::Vector2f(90,30));
    czworoscian.setPoint(2,sf::Vector2f(70,70));
    czworoscian.setFillColor(sf::Color::Blue);
    //czworoscian.setOutlineColor(sf::Color::White);
    //czworoscian.setOutlineThickness(3);
    vector<figura*> figury = get_base();
    double x1,y1,x2,y2,z1,z2,s1,s2,s3,s4,ct;
    int* p;
    double* p1, *p2,*p3,*p4;
    Matrix opertion(4,4);
    Matrix transform_operation(4,4);
    Matrix vect(4,1);
    Matrix last(4,4);
    Matrix revers_transformation(4,4);
    Matrix transforamtion(4,4);
    Matrix result(4,1);
    opertion.set_matrix_4_to(Jednostkowa,1);
    transforamtion.set_matrix_4_to(Jednostkowa,1);
    revers_transformation.set_matrix_4_to(Jednostkowa,1);
    double scale = min(width,height);
    double angle = 45;
    vector<double**> pointw(figury.size()*6);
    vector<int*> walls(figury.size()*6);
    vector<sf::Color> colors(figury.size()*6);
    wieszcholek* root;
    int j = 0;
    for(auto f : figury)
    {
        for(int i = 0 ;i < 6 ; i++,j++)
        {
            walls[j] = f->getWall(i);
            pointw[j] = f->getAllPoint();
            colors[j] = f->getWallCollor(i);
        }
    }
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            revers_transformation.set_matrix_4_to(Jednostkowa,1);
            scale = min(width,height);
            angle = 45;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotgora,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotdol,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotZprawo,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotZlewo,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotPrawo,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotLewo,0.1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchdol,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchgora,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchprawo,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchlewo,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchtyl,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchprzod,1);
            revers_transformation.multiplication(opertion,last);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
            angle -= 0.1;
            angle = angle>=1? angle: 1; 
            //scale-=1;
            //scale = scale < 10? 10: scale;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            angle += 0.1;
            angle = angle<=89? angle: 89; 
            //scale+= 1;
        }
        for(auto f : figury)
        {
            for(int i =0 ; i < f->numberOfPoints();i++ )
            {
                p1 = f->getPoints(i);
                p2 = f->getPointsTransformed(i);
                vect[0][0] = p1[0];
                vect[1][0] = p1[1];
                vect[2][0] = p1[2];
                vect[3][0] = 1;
             
                result.multiplication(revers_transformation,vect);
                result.normalize();
               
                
                p2[0] = result[0][0];
                p2[1] = result[1][0];
                p2[2] = result[2][0];
            }
        }
        root = nullptr;
        pair< wieszcholek*,bool> curr;
        stack<pair< wieszcholek*,bool>> sw;
        
        for(int i = 0 ; i < walls.size();i++)
        {
            root = maketree(root, {pointw[i],walls[i],colors[i]});
        }
        window.clear();
        sw.push({root,false});
        /*
        for(auto f : figury)
        {
            for(int i =0 ; i < f->numberOfLines();i++ )
            {
                p = f->getLine(i);
                p1 = f->getPointsTransformed(p[0]);
                p2 = f->getPointsTransformed(p[1]);
                if(p1[2] >= 0 || p2[2] >=0)
                {
                    ct = cos(angle*M_PI/180)/sin(angle*M_PI/180) * scale;
                    s1 =  ct / p1[2];
                    s2 =  ct / p2[2];
                    line[0].position.x = s1*p1[0] + width/2;
                    line[0].position.y = -s1*p1[1] + height/2;
                    line[1].position.x = s2*p2[0] + width/2;
                    line[1].position.y = -s2*p2[1] + height/2;
                    if(p1[2]<=0)
                    {
                        z1 = p1[2];
                        z2 = p2[2];
                        
                        x1 = (p2[0]- p1[0])* (z2/(z2-z1));
                        x2 =  p2[0] -x1;
                        y1 = (p2[1]- p1[1])* (z2/(z2-z1));
                        y2 =  p2[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        line[0].position.x = 10.0*ct*x2 + width/2;
                        line[0].position.y = -10.0*ct*y2 + height/2;
                        
                    }if(p2[2]<=0)
                    {
                        z1 = p1[2];
                        z2 = p2[2];
                        x1 = (p1[0]- p2[0])* (z1/(z1-z2));
                        x2 =  p1[0] -x1;
                        y1 = (p1[1]- p2[1])* (z1/(z1-z2));
                        y2 =  p1[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        line[1].position.x = 10.0*ct*x2 + width/2;
                        line[1].position.y = -10.0*ct*y2 + height/2;
                    }
                    window.draw(line, 2, sf::Lines);
                }
            }
        }*/
        
        /*for(auto f : figury)
        {
            for(int i =0 ; i < f->numberOfWalls();i++ )
            {
                p = f->getWall(i);
                p1 = f->getPointsTransformed(p[0]);
                p2 = f->getPointsTransformed(p[1]);
                p3 = f->getPointsTransformed(p[2]);
                p4 = f->getPointsTransformed(p[3]);
                
                if(p1[2] >= 0 || p2[2] >=0 || p3[2] >=0 || p4[2] >=0)
                {
                    ct = cos(angle*M_PI/180)/sin(angle*M_PI/180) * scale;
                    s1 =  ct / p1[2];
                    s2 =  ct / p2[2];
                    s3 =  ct / p3[2];
                    s4 =  ct / p4[2];
                    
                    czworoscian.setPoint(0,sf::Vector2f(s1*p1[0] + width/2,-s1*p1[1] + height/2));
                    czworoscian.setPoint(1,sf::Vector2f(s2*p2[0] + width/2,-s2*p2[1] + height/2));
                    czworoscian.setPoint(2,sf::Vector2f(s3*p3[0] + width/2,-s3*p3[1] + height/2));
                    czworoscian.setPoint(3,sf::Vector2f(s4*p4[0] + width/2,-s4*p4[1] + height/2));
                    czworoscian.setFillColor(f->getWallCollor(i));
                    
                    
                    if(p1[2]<=0)
                    {
                        z1 = p1[2];
                        z2 = p2[2];
                        
                        x1 = (p2[0]- p1[0])* (z2/(z2-z1));
                        x2 =  p2[0] -x1;
                        y1 = (p2[1]- p1[1])* (z2/(z2-z1));
                        y2 =  p2[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        line[0].position.x = 10.0*ct*x2 + width/2;
                        line[0].position.y = -10.0*ct*y2 + height/2;
                        
                    }if(p2[2]<=0)
                    {
                        z1 = p1[2];
                        z2 = p2[2];
                        x1 = (p1[0]- p2[0])* (z1/(z1-z2));
                        x2 =  p1[0] -x1;
                        y1 = (p1[1]- p2[1])* (z1/(z1-z2));
                        y2 =  p1[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        line[1].position.x = 10.0*ct*x2 + width/2;
                        line[1].position.y = -10.0*ct*y2 + height/2;
                    }
                    window.draw(czworoscian);
                    //window.draw(line, 2, sf::Lines);
                }
            }
        }*/
        while(!sw.empty())
        {
            curr = sw.top();
            sw.pop();
            if(!curr.second)
            {
                sw.push({curr.first,true});
                if(curr.first->left!= nullptr) sw.push({curr.first->left,false});
            }else
            {
                if(curr.first->right!= nullptr) sw.push({curr.first->right,false});
                p = curr.first->wall;// f->getWall(i);
                p1 = curr.first->pt[p[0]];//f->getPointsTransformed(p[0]);
                p2 = curr.first->pt[p[1]];
                p3 = curr.first->pt[p[2]];
                p4 = curr.first->pt[p[3]];
            
                if(p1[2] >= 0 && p2[2] >=0 && p3[2] >=0 && p4[2] >=0)
                {
                    ct = cos(angle*M_PI/180)/sin(angle*M_PI/180) * scale;
                    s1 =  ct / p1[2];
                    s2 =  ct / p2[2];
                    s3 =  ct / p3[2];
                    s4 =  ct / p4[2];
                    
                    czworoscian.setPoint(0,sf::Vector2f(s1*p1[0] + width/2,-s1*p1[1] + height/2));
                    czworoscian.setPoint(1,sf::Vector2f(s2*p2[0] + width/2,-s2*p2[1] + height/2));
                    czworoscian.setPoint(2,sf::Vector2f(s3*p3[0] + width/2,-s3*p3[1] + height/2));
                    czworoscian.setPoint(3,sf::Vector2f(s4*p4[0] + width/2,-s4*p4[1] + height/2));
                    czworoscian.setFillColor(curr.first->color);
                   /* if(p1[2]<=0)
                    {
                        z1 = p1[2];
                        z2 = p2[2];
                        x1 = (p2[0]- p1[0])* (z2/(z2-z1));
                        x2 =  p2[0] -x1;
                        y1 = (p2[1]- p1[1])* (z2/(z2-z1));
                        y2 =  p2[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        czworoscian.setPoint(0,sf::Vector2f(10.0*ct*x2 + width/2,-10.0*ct*y2 + height/2));
                    }
                    if(p2[2]<=0)
                    {
                        z1 = p2[2];
                        z2 = p3[2];
                        x1 = (p3[0]- p2[0])* (z2/(z2-z1));
                        x2 =  p3[0] -x1;
                        y1 = (p3[1]- p2[1])* (z2/(z2-z1));
                        y2 =  p3[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        czworoscian.setPoint(0,sf::Vector2f(10.0*ct*x2 + width/2,-10.0*ct*y2 + height/2));
                    }
                    if(p3[2]<=0)
                    {
                        z1 = p3[2];
                        z2 = p4[2];
                        x1 = (p4[0]- p3[0])* (z2/(z2-z1));
                        x2 =  p4[0] -x1;
                        y1 = (p4[1]- p3[1])* (z2/(z2-z1));
                        y2 =  p4[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        czworoscian.setPoint(0,sf::Vector2f(10.0*ct*x2 + width/2,-10.0*ct*y2 + height/2));
                    }
                    if(p4[2]<=0)
                    {
                        z1 = p4[2];
                        z2 = p1[2];
                        x1 = (p1[0]- p4[0])* (z2/(z2-z1));
                        x2 =  p1[0] -x1;
                        y1 = (p1[1]- p4[1])* (z2/(z2-z1));
                        y2 =  p1[1] -y1;
                        x2 = abs(x2)<0.1? 1:x2;
                        y2 = abs(y2)<0.1? 1:y2;
                        czworoscian.setPoint(0,sf::Vector2f(10.0*ct*x2 + width/2,-10.0*ct*y2 + height/2));
                    }*/
                    window.draw(czworoscian);
                }
            }
        }
        /*
        for(int i = 0 ; i< walls.size();i++)
        {
            p = walls[i];// f->getWall(i);
            p1 = pointw[i][p[0]];//f->getPointsTransformed(p[0]);
            p2 = pointw[i][p[1]];
            p3 = pointw[i][p[2]];
            p4 = pointw[i][p[3]];
            
            if(p1[2] >= 0 || p2[2] >=0 || p3[2] >=0 || p4[2] >=0)
            {
                ct = cos(angle*M_PI/180)/sin(angle*M_PI/180) * scale;
                s1 =  ct / p1[2];
                s2 =  ct / p2[2];
                s3 =  ct / p3[2];
                s4 =  ct / p4[2];
                    
                czworoscian.setPoint(0,sf::Vector2f(s1*p1[0] + width/2,-s1*p1[1] + height/2));
                czworoscian.setPoint(1,sf::Vector2f(s2*p2[0] + width/2,-s2*p2[1] + height/2));
                czworoscian.setPoint(2,sf::Vector2f(s3*p3[0] + width/2,-s3*p3[1] + height/2));
                czworoscian.setPoint(3,sf::Vector2f(s4*p4[0] + width/2,-s4*p4[1] + height/2));
                czworoscian.setFillColor(colors[i]);
                window.draw(czworoscian);
            }
        }*/
        
        
        window.display();
        sf::sleep(sf::microseconds(1000));
    }

    return 0;
}