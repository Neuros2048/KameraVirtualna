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
        sf::Vertex point(sf::Vector2f(20, 20), sf::Color::Blue);
        sf::CircleShape shape(50);
        shape.setPosition(sf::Vector2f(100, 100));
        shape.setFillColor(sf::Color(150, 50, 250));

        //shape.setOutlineThickness(10);
        
        window.draw(&point, 1, sf::Points);
        window.draw(shape);
        
        window.display();
        sf::sleep(sf::microseconds(1000));
    }

    return 0;
}