
#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Planet2 :
    public DisplayableObject,
    public Animation
{
public:
    Planet2( float size, float distanceFromSun, float axisRotationSpeed, float orbitRotationSpeed, float moonSize, float distMoonFromPlanet, float moonAxisSpeed, float moonOrbitSpeed );
    ~Planet2(){}
    
    void SetColour( unsigned char r, unsigned char g, unsigned b );
    
    void Display();
    void Update( const double& deltaTime );
    
private:
    
    unsigned char r,g,b;
    float radius;
    float distanceFromSun;
    float axisRotationSpeed;
    float orbitRotationSpeed;
    float axisRotation;
    float orbitRotation;
    
    float moonRadius;
    float distanceMoonFromPlanet;
    float moonAxisRotSpeed;
    float moonOrbitRotSpeed;
    float moonAxisRot;
    float moonOrbitRot;
};