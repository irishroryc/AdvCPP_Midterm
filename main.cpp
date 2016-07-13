/*
 * File:   main.cpp
 * Author: Rory Connolly
 * Assignment: Midterm exam
 *
 * Created on July 11, 2016, 6:46 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/* Implement base class shape and derived classes for specific shapes (circle,
 * rectangle, right triangle) and a further class doughnut derived from circle.
 *
 * Shapes will contain data about the X,Y coordinates for center of mass for the
 * given shape as well as the area of the shape. 
 *
 */

#define DEBUG 1
static float PI=3.14159;

namespace COLORS{
    enum Color{R,O,Y,G,B,I,V};
}

void debugOut(string S){
    if(DEBUG){
        cout << "DEBUG: " << S << endl;
    }
}

class Shape{
private:
    int X; // X-coordinate of shape
    int Y; // Y-coordinate of shape
    float Area; // Area of the shape
    COLORS::Color shapeColor; // Color for the shape
    string shapeType; // The type of shape that the object is
    static int count; // Count of shapes in existence
    Shape(){}; // Default constructor should never be called for base class Shape
public:
    Shape(int x, int y, COLORS::Color color, string type);
    // Parameterized constructor for class Shape
    Shape(const Shape& S);
    // Copy constructor for class Shape
    virtual Shape& operator=(const Shape& rhs);
    // Assignment operator is invalid for abstract base class
    virtual ~Shape();
    // Virtual destructor for base class Shape
    int getX()const;
    // Accessor function for X-coordinate of Shape
    int getY()const;
    // Accessor function for Y-coordinate of Shape
    void setX(int x);
    // Mutator function to set X-coordinate of Shape
    void setY(int y);
    // Mutator function to set Y-coordinate of Shape
    virtual float CalcArea() = 0;
    // Pure virtual function for calculating area of Shape
    virtual void drawObject() = 0;
    // Pure virtual function for drawing Shape
    void ResetLocation(int newX, int newY);
    // Mutator function to set both X and Y-coordinates of Shape
    void setArea(float newArea);
    // Mutator function to set the area of Shape
    float getArea()const;
    // Accessor function for area of Shape
    void setColor(COLORS::Color newColor);
    // Mutator function to set color of Shape
    COLORS::Color getColor()const;
    // Accessor function for color of Shape
    string getColorText()const;
    // Accessor function for color of Shape as a string
    void setType(string newType);
    // Mutator function for type of Shape
    string getType()const;
    // Accessor function for type of Shape
};

int Shape::count = 0;

class Circle : public Shape{
private:
    float Radius; // Radius of the Circle
public:
    Circle();
    Circle(int x, int y, COLORS::Color color, int radius);
    Circle(const Circle& C);
    virtual Circle& operator=(const Circle& rhs);
    virtual ~Circle();
    virtual float CalcArea();
    virtual void drawObject();
    float getRadius();
};

int main(int argc, char** argv) {
    COLORS::Color myColor=COLORS::G;
    cout << "myColor = " << myColor << endl;

   
    Circle testCircle(1,2,COLORS::Y,2), testCircleTwo(3,4,COLORS::G,10);
    Circle newTest(testCircle);
   
    testCircle.drawObject();
    cout << "testCircle color = " << testCircle.getColor() << endl;
    cout << "testCircle color = " << testCircle.getColorText() << endl;
    cout << "testCircle area = " << testCircle.getArea() << endl << endl;

    cout << "testCircleTwo color = " << testCircleTwo.getColorText() << endl;
    cout << "testCircleTwo area = " << testCircleTwo.getArea() << endl;
    cout << "testCircleTwo radius = " << testCircleTwo.getRadius() << endl;

    return 0;
}

// Function definitions for class Shape
Shape::Shape(int x, int y, COLORS::Color color, string type)
        :X(x),Y(y),shapeColor(color),shapeType(type){
    debugOut("Shape constructor called.");
    Shape::count++;
    //Area=CalcArea();
    cout << "There are now " << Shape::count << " shapes.\n";
}

Shape::Shape(const Shape& S)
        :X(S.X),Y(S.Y),shapeColor(S.shapeColor),shapeType(S.shapeType),Area(S.Area){
    debugOut("Shape copy constructor called.");
    Shape::count++;
    cout << "There are now " << Shape::count << " shapes.\n";
}

Shape& Shape::operator=(const Shape& rhs){
    if(this != &rhs){
        X=rhs.X;
        Y=rhs.Y;
        shapeColor=rhs.shapeColor;
        shapeType=rhs.shapeType;
        Area=rhs.Area;
    }
    return *this;
}

Shape::~Shape(){
    debugOut("Shape destructor called.");
    Shape::count--;
    cout << "There are now " << Shape::count << " shapes.\n";
}

int Shape::getX()const{
    return X;
}

int Shape::getY()const{
    return Y;
}

void Shape::setX(int x){
    X=x;
}

void Shape::setY(int y){
    Y=y;
}

void Shape::ResetLocation(int newX, int newY){
    X=newX;
    Y=newY;
}

void Shape::setArea(float newArea){
    Area = newArea;
}

float Shape::getArea()const{
    return Area;
}

void Shape::setColor(COLORS::Color newColor){
    shapeColor = newColor;
}

COLORS::Color Shape::getColor()const{
    return shapeColor;
}

string Shape::getColorText()const{
    switch(shapeColor){
        case COLORS::R:
            return "Red";
            break;
        case COLORS::O:
            return "Orange";
            break;
        case COLORS::Y:
            return "Yellow";
            break;
        case COLORS::G:
            return "Green";
            break;
        case COLORS::B:
            return "Blue";
            break;
        case COLORS::I:
            return "Indigo";
            break;
        case COLORS::V:
            return "Violet";
            break;
        default:
            return "Unknown color";                  
    }
}

void Shape::setType(string newType){
    shapeType = newType;
}

string Shape::getType()const{
    return shapeType;
}

// Function definitions for class Circle

Circle::Circle():Shape(0,0,COLORS::B,"Circle"),Radius(0){
    debugOut("Circle default constructor called.");
    setArea(0);
}

Circle::Circle(int x, int y, COLORS::Color color, int radius)
        :Shape(x, y, color, "Circle"), Radius(radius){
    debugOut("Circle parameterized constructor called.");
    setArea(CalcArea());
}

Circle::Circle(const Circle& C)
    :Shape(C.getX(),C.getY(),C.getColor(),"Circle"),Radius(C.Radius){
    debugOut("Circle copy constructor called.");
    setArea(C.getArea());
}

Circle& Circle::operator=(const Circle& rhs){
    if(this != &rhs){
        setX(rhs.getX());
        setY(rhs.getY());
        setColor(rhs.getColor());
        setType("Circle");
        Radius = rhs.Radius;
        setArea(rhs.getArea());
    }
}

Circle::~Circle(){
    debugOut("Circle destructor called.");
}

float Circle::CalcArea(){
    return(PI * (Radius*Radius));
}

void Circle::drawObject(){
    cout << "Drawing Circle...\n";
}

float Circle::getRadius(){
    return Radius;
}