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

double dotProduct(vector<double> &A, vector<double> &B)
{
    double result = 0.0;
    for(int i = 0; i< A.size(); i++)
    {
        result+=A[i]*B[i];
    }
    return result;
}

vector<double> calculateColor(vector<double> &initialColor, double ambientCoe, vector<double> &normal, vector<double> &lightPosition, vector<double> &reflectionDirection, vector<double>& viewDirection, double diffCoe, double specCoe, int n)
{
    vector<double> color(3);
    vector<double> ambientColor(3);
    vector<double> diffusionColor(3);
    vector<double> specular(3);
    for(int i = 0 ; i< 3; i++)
    {
        ambientColor[i] = initialColor[i] * ambientCoe;
    }
    for(int i = 0 ; i< 3; i++)
    {
        diffusionColor[i] = std::max(initialColor[i] * dotProduct(normal, lightPosition), 0.0) * diffCoe;
    }

    double specularColor = std::pow(std::max(dotProduct(reflectionDirection, viewDirection), 0.0), n) * 255 * specCoe;

    for(int i = 0; i< 3; i++)
    {
        color[i] = std::min(ambientColor[i] + diffusionColor[i] + specularColor, 255.0);
        
    }
    return color;
}
void calcuclateNormal(vector<double> &A,vector<double> &B,vector<double> &wynik)
{
    for(int i =0 ; i< A.size();i++)
    {
        wynik[i] = (A[i]-B[i]);
    }
    double length = std::sqrt(wynik[0] * wynik[0] + wynik[1] * wynik[1] + wynik[2] * wynik[2]);
    for (int i = 0; i < A.size(); i++)
    {
        wynik[i] = wynik[i]/length;
    }

}
void subtractVectors(vector<double>& A, vector<double>& B, vector<double>& wynik) {
    for (int i = 0; i < A.size(); i++)
    {
        wynik[i] = (A[i] - B[i]);
    }
}
void calcuclateReflection(vector<double>& normal, vector<double>& lightDirection, vector<double>& reflectionDirection) {
    double product = dotProduct(normal, lightDirection);
    for (int i = 0; i < 3; i++) {
        reflectionDirection[i] = 2 * product * normal[i] - lightDirection[i];
    }
    double length = std::sqrt(reflectionDirection[0] * reflectionDirection[0] + reflectionDirection[1] * reflectionDirection[1] + reflectionDirection[2] * reflectionDirection[2]);
    for (int i = 0; i < 3; i++) {
        reflectionDirection[i] /= length;
    }
}
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

    /////////////////////////////
    double lightSpeed = 100;
    int radius = 100;
    vector<double> initialColor = { 0.0, 0.0, 255.0 };
    vector<double> viewerPosition = { width / 2.0, height / 2.0, 100 };
    vector<double> sphereCenter = { width / 2.0, height / 2.0, 0.0 };
    vector<double> lightSource = { 0,0, 100 };
    double diff = 1;
    double spec = 1;
    int n = 8;
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
    sf::Vertex *points = new sf::Vertex[360*180 *4];
   
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
            /*last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotZprawo,0.1);
            revers_transformation.multiplication(opertion,last);*/
            lightSource[1] -= lightSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            /*last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotZlewo,0.1);
            revers_transformation.multiplication(opertion,last);*/
            lightSource[1] += lightSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            /*last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotPrawo,0.1);
            revers_transformation.multiplication(opertion,last);*/
            lightSource[0] += lightSpeed;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            /*last.swap(revers_transformation);
            opertion.set_matrix_4_to(obrotLewo,0.1);
            revers_transformation.multiplication(opertion,last);*/
            lightSource[0] -= lightSpeed;

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
            //last.swap(revers_transformation);
            //opertion.set_matrix_4_to(ruchtyl,1);
            //revers_transformation.multiplication(opertion,last);
            lightSource[2] -= lightSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            /*last.swap(revers_transformation);
            opertion.set_matrix_4_to(ruchprzod,1);
            revers_transformation.multiplication(opertion,last);*/
            lightSource[2] += lightSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
            angle -= 0.1;
            angle = angle>=1? angle: 1; 
            //scale-=1;
            //scale = scale < 10? 10: scale;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            initialColor = { 0, 0, 255.0 };
            diff = 1;
            spec = 1;
            n = 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
            initialColor = { 0, 255.0, 0 };
            diff = 1;
            spec = 0;
            n = 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            initialColor = { 255.0, 0, 0 };
            diff = 0;
            spec = 1;
            n = 16;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
            initialColor = { 100.0, 100.0, 200.0};
            diff = 0.75;
            spec = 0.3;
            n = 8;
        }
        sf::CircleShape shape(50);
        shape.setPosition(sf::Vector2f(100, 100));
        shape.setFillColor(sf::Color(150, 50, 250));

        for(int thetaB = 0; thetaB < 360*2; thetaB++)
        {
            for(int phiB = 0; phiB < 180*2; phiB++)
            {
                double theta = thetaB/2.0;
                double phi = phiB/2.0;
                double x = radius * sin(theta/180.0 * M_PI) * cos(phi/180.0 * M_PI ) + sphereCenter[0];
                double y = radius * cos(theta / 180.0 * M_PI) + sphereCenter[1];
                double z = radius* sin(theta/180.0 * M_PI) * sin(phi/180.0 * M_PI) + sphereCenter[2];
                vector<double> pointCoordinates = {x, y, z};
                vector<double> normal(3);
                calcuclateNormal(sphereCenter, pointCoordinates, normal);
                vector<double> lightDirection(3);
                calcuclateNormal(lightSource, pointCoordinates, lightDirection);
                vector<double> reflectionDirection(3);
                calcuclateReflection(normal, lightDirection, reflectionDirection);
                vector<double> viewDirection(3);
                calcuclateNormal(viewerPosition, pointCoordinates, viewDirection);
                vector<double> color = calculateColor(initialColor, 0.2, normal, lightDirection, reflectionDirection, viewDirection, diff, spec, n);
                //if(dotProduct(viewDirection ,normal)>=0)
                //{
                points[180*2*thetaB + phiB] = sf::Vertex(sf::Vector2f(x, y), sf::Color(color[0], color[1], color[2]));   
                //}else
                //{
                 //   points[180*2*thetaB + phiB] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black);   
                //}
            }
        }
        
        //shape.setOutlineThickness(10);
        
        window.draw(points, 180*360*4, sf::Points);

        
        window.display();
        sf::sleep(sf::microseconds(1000));
        
    }
    return 0;
}