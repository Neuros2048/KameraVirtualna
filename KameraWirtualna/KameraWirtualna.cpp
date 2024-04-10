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
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Kamera Wirtualan");
    sf::CircleShape shape(100.f);
    sf::Vertex line[]{
        sf::Vertex(sf::Vector2f(45,100)),
        sf::Vertex(sf::Vector2f(30,200))
    };
    shape.setFillColor(sf::Color::Green);

    vector<figura*> figury = get_base();
    double x1,y1,x2,y2,z1,z2,s1,s2,ct;
    int* p;
    double* p1, *p2;
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
        window.clear();
        
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
        }
        
       
        window.display();
       
        sf::sleep(sf::microseconds(1000));
    }

    return 0;
}