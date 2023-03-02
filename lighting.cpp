#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include "glew.h"
#endif

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "glut.h"

float White[3] = { 1., 1., 1. };

// function prototypes:

void	SetMaterial( float, float, float,  float );
void	SetPointLight( int, float, float, float,  float, float, float );
void	SetSpotLight( int, float, float, float,  float, float, float, float, float, float );

float * Array3( float, float, float );
float * Array4( float, float, float, float );
float * BlendArray3( float, float [3], float [3] );
float * MulArray3( float, float [3] );

void
SetMaterial( float r, float g, float b,  float shininess )
{
	glMaterialfv( GL_BACK, GL_EMISSION, Array3( 0., 0., 0. ) );
	glMaterialfv( GL_BACK, GL_AMBIENT, Array3( r, g, b ) );
	glMaterialfv( GL_BACK, GL_DIFFUSE, Array3( r, g, b ) );
	glMaterialfv( GL_BACK, GL_SPECULAR, MulArray3( .8f, White ) );
	glMaterialf ( GL_BACK, GL_SHININESS, shininess );

	glMaterialfv( GL_FRONT, GL_EMISSION, Array3( 0., 0., 0. ) );
	glMaterialfv( GL_FRONT, GL_AMBIENT, Array3( r, g, b ) );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, Array3( r, g, b ) );
	glMaterialfv( GL_FRONT, GL_SPECULAR, MulArray3( .8f, White ) );
	glMaterialf ( GL_FRONT, GL_SHININESS, shininess );
}


void
SetPointLight( int ilight, float x, float y, float z,  float r, float g, float b, float i )
{
	glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
	glLightfv( ilight, GL_AMBIENT,   Array3( 0., 0., 0. ) );
	glLightfv( ilight, GL_DIFFUSE,   Array3( r*i, g*i, b*i ) );
	glLightfv( ilight, GL_SPECULAR,  Array3( r*i, g*i, b*i ) );
	glLightf ( ilight, GL_CONSTANT_ATTENUATION, 0. );
	glLightf ( ilight, GL_LINEAR_ATTENUATION, 1. );
	glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
	glEnable( ilight );
}


void
SetSpotLight( int ilight, float x, float y, float z,  float xdir, float ydir, float zdir, float r, float g, float b, float i )
{
	glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
	glLightfv( ilight, GL_SPOT_DIRECTION,  Array3(xdir,ydir,zdir) );
	glLightf(  ilight, GL_SPOT_EXPONENT, 1. );
	glLightf(  ilight, GL_SPOT_CUTOFF, 45. );
	glLightfv( ilight, GL_AMBIENT,   Array3( 0., 0., 0. ) );
	glLightfv( ilight, GL_DIFFUSE,   Array3( r*i, g*i, b*i ) );
	glLightfv( ilight, GL_SPECULAR,  Array3( r*i, g*i, b*i ) );
	glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
	glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
	glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
	glEnable( ilight );
}

float *
Array3( float a, float b, float c )
{
        static float array[4];

        array[0] = a;
        array[1] = b;
        array[2] = c;
        array[3] = 1.;
        return array;
}

float *
Array4( float a, float b, float c, float d )
{
        static float array[4];

        array[0] = a;
        array[1] = b;
        array[2] = c;
        array[3] = d;
        return array;
}

float *
BlendArray3( float factor, float array0[3], float array1[3] )
{
        static float array[4];

        array[0] = factor * array0[0]  +  ( 1.f - factor ) * array1[0];
        array[1] = factor * array0[1]  +  ( 1.f - factor ) * array1[1];
        array[2] = factor * array0[2]  +  ( 1.f - factor ) * array1[2];
        array[3] = 1.;
        return array;
}

float *
MulArray3( float factor, float array0[3] )
{
        static float array[4];

        array[0] = factor * array0[0];
        array[1] = factor * array0[1];
        array[2] = factor * array0[2];
        array[3] = 1.;
        return array;
}
