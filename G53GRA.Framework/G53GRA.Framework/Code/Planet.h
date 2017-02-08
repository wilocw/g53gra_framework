
#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Planet :
    public DisplayableObject,
    public Animation
{
public:
    // constructor to take in the parameters that change for each planet object
    Planet( float size, float distanceFromSun, float axisRotationSpeed, float orbitRotationSpeed );
    ~Planet(){}
    
    // a setter function to allow you to change the colour of the plant without passing it via the constructor
    void SetColour( unsigned char r, unsigned char g, unsigned b );
    
    // overiden draw and update function
    void Display();
    void Update( const double& deltaTime );
    
private:
    
    // the colour of the planet
    unsigned char r,g,b;
    
    // the size / radius of the sphere we use to draw the planet
    float radius;
    
    // the distance we move away from the sun, i.e. the orbit radius
    float distanceFromSun;
    
    // the speed at which the planet turns on its axis
    float axisRotationSpeed;
    
    // the speed at which the planet rotated around the sun
    float orbitRotationSpeed;
    
    // the current rotation (in degrees) for the axis and orbit rotations
    float axisRotation;
    float orbitRotation;
};