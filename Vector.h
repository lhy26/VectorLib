//  This file is part of the Vector library.
//
//  The Vector library is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  The Vector library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with the Vector library.  If not, see <http://www.gnu.org/licenses/>.
//
//  Copyright 2013-2014 Kevin Balke (fughilli@gmail.com)

#ifndef VECTOR_X_H
#define VECTOR_X_H

#ifdef __cplusplus

#define VECTORS

#if defined(ARDUINO) || defined(ENERGIA)
#include "Energia.h"
#ifdef OVERRIDE_FPTYPE_DOUBLE
    typedef double fp_type;
#else
    typedef float fp_type;
#endif
#else

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cfloat>
#ifdef OVERRIDE_FPTYPE_FLOAT
    typedef float fp_type;
#else
    typedef double fp_type;
#endif

#ifndef PI
#define PI (3.1415926535897932384626433832795)
#endif

#ifndef TWO_PI
#define TWO_PI (2*PI)
#endif

#define VECTOR_PRINT_PRECISION 5

using namespace std;
#endif // ARDUINO

#define COMPARE_ACCURACY 0

#define LIMIT_RAD_RANGE(_RAD_) (((_RAD_)>PI)?((_RAD_)-TWO_PI):(((_RAD_)<(-PI))?((_RAD_)+TWO_PI):(_RAD_)))
#define LIMIT_DEG_RANGE(_DEG_) (((_DEG_)>180)?((_DEG_)-360):(((_DEG_)<(-180))?((_DEG_)+360):(_DEG_)))

/**
ALL ANGLES ARE IN RADIANS
**/

#ifdef ARDUINO
#define DEG2RAD(_DEG) (((_DEG) * 71 / 4068))
#define RAD2DEG(_RAD) (((_RAD) * 4068 / 71))
#else
#define DEG2RAD(_DEG) (((_DEG) * PI / 180.0))
#define RAD2DEG(_RAD) (((_RAD) * 180.0 / PI))
#endif // ARDUINO

class Vector2d;
class Vector3d;
class Quaternion;

class Quaternion
{
public:
    fp_type x, y, z, w;

    Quaternion(fp_type _x, fp_type _y, fp_type _z, fp_type _w);
    Quaternion();

    Quaternion operator+(const Quaternion& other) const;
    void operator+=(const Quaternion& other);
    Quaternion operator-(const Quaternion& other) const;
    void operator-=(const Quaternion& other);
    Quaternion operator*(const Quaternion& other) const;
    void operator*=(const Quaternion& other);

    Quaternion operator*(fp_type scalar) const;
    void operator*=(fp_type scalar);
    Quaternion operator/(fp_type scalar) const;
    void operator/=(fp_type scalar);

    bool operator==(const Quaternion& other) const;

    Quaternion operator-() const;

    Quaternion conjugate() const;
    fp_type norm();
    Quaternion unit();
    fp_type distance(const Quaternion& other) const;
    fp_type dot(const Quaternion& other) const;

    Quaternion slerp(const Quaternion& endpt, fp_type t) const;     // Perform a spherical linear interpolation between this quaternion and an end quaternion

    static Quaternion fromAxisAngle(const Vector3d& axis, fp_type theta);
    static Quaternion rotationBetween(const Vector3d& a, const Vector3d& b);

    // Quaternion constants
    static const Quaternion zero;
    static const Quaternion identity;
    static const Quaternion i;
    static const Quaternion j;
    static const Quaternion k;
    static const Quaternion l;
};

class Vector2d
{
public:
    fp_type x, y;
    Vector2d(fp_type _x, fp_type _y);
    Vector2d();
    Vector2d operator+(const Vector2d& other) const;        // Adds two Vector2d's together (component-wise)
    void operator+=(const Vector2d& other);			        // Adds two Vector2d's together (component-wise)
    Vector2d operator-(const Vector2d &other) const;        // Subtracts a Vector2d from another Vector2d (component-wise)
    void operator-=(const Vector2d &other);			        // Subtracts a Vector2d from another Vector2d (component-wise)
    Vector2d operator*(fp_type scalar) const;		        // Scalar multiply
    void operator*=(fp_type scalar);				        // Scalar multiply
    Vector2d operator/(fp_type scalar) const;		        // Scalar divide
    void operator/=(fp_type scalar);				        // Scalar divide

    bool operator==(const Vector2d& other) const;           // Boolean compare

    Vector2d operator-() const;

    fp_type dot(const Vector2d &other) const;		        // Compute the dot product of two Vector2d's
    Vector2d rotate(fp_type theta) const;			        // Rotates the vector around the origin by an angle theta

    Vector2d project(const Vector2d& axis) const;           // Project a vector onto another

    Vector2d lerp(const Vector2d& endpt, fp_type t) const;  // Perform a linear interpolation between this position vector and an endpoint vector

    fp_type angleTo(const Vector2d &other) const;	        // Compute the angle between two Vector2d's
    fp_type magnitude() const;					            // Compute the magnitude of the Vector2d
    Vector2d unit() const;					                // Compute the normalized form of the Vector2d
    fp_type theta() const;						            // Compute the angle the Vector2d points along (polar theta)

    // 2D Vector constants
    static const Vector2d zero;
    static const Vector2d i;
    static const Vector2d j;
    static const Vector2d one;
};

class Vector3d
{
public:
    fp_type x, y, z;
    Vector3d(fp_type _x, fp_type _y, fp_type _z);
    Vector3d();
    Vector3d operator+(const Vector3d& other) const;			// Adds two Vector3d's together (component-wise)
    void operator+=(const Vector3d& other);			// Adds two Vector3d's together (component-wise)
    Vector3d operator-(const Vector3d& other) const;			// Subtracts a Vector3d from another Vector3d (component-wise)
    void operator-=(const Vector3d& other);			// Subtracts a Vector3d from another Vector3d (component-wise)
    Vector3d operator*(fp_type scalar) const;			// Scalar multiply
    void operator*=(fp_type scalar);				// Scalar multiply
    Vector3d operator/(fp_type scalar) const;			// Scalar divide
    void operator/=(fp_type scalar);				// Scalar divide

    bool operator==(const Vector3d& other) const;            // Boolean compare

    Vector3d operator-() const;

    fp_type dot(const Vector3d& other) const;					// Compute dot product of two Vector3d's
    Vector3d cross(const Vector3d& other) const;				// Compute the cross product of two Vector3d's (orthogonal Vector3d)

    Vector3d project(const Vector3d& axis) const;            // Project a vector onto another

    Vector3d lerp(const Vector3d& endpt, fp_type t) const;     // Perform a linear interpolation between this position vector and an endpoint vector

    Vector3d rotate(const Vector3d& axis, fp_type theta) const;// Rotate the vector around the axis axis by the angle theta (+theta is CCW if vector points towards observer)
    Vector3d rotate(const Quaternion& rot_q) const;          // Rotate the vector by a quaternion

    fp_type angleTo(const Vector3d& other) const;				// Compute the angle between two Vector3d's
    Quaternion quaternionTo(const Vector3d& other) const;    // Compute the quaternion rotation between two vectors

    Quaternion rotationAroundAxis(fp_type theta) const; // compute the quaternion rotation of angle theta around a vector

    fp_type magnitude() const;							// Compute the magnitude of the Vector3d
    Vector3d unit() const;							// Compute the normalized form of the Vector3d
    fp_type theta() const;								// Compute the angle the (x,y) components of the Vector3d point along (spherical theta)
    fp_type rho() const;								// Compute the angle of elevation of the Vector3d out of the (x,y) plane (spherical rho)

    static Vector3d min2(const Vector3d& a, const Vector3d& b);
    static Vector3d max2(const Vector3d& a, const Vector3d& b);

    // 3D Vector constants
    static const Vector3d zero;
    static const Vector3d i;
    static const Vector3d j;
    static const Vector3d k;
    static const Vector3d one;
    static const Vector3d max;
    static const Vector3d min;
};

#if defined(ARDUINO) || defined(ENERGIA)
void printVector2d(Vector2d arg);
void printVector3d(Vector3d arg);
#else
std::ostream& operator<<(std::ostream& os, const Vector2d& vec);
std::ostream& operator<<(std::ostream& os, const Vector3d& vec);
std::ostream& operator<<(std::ostream& os, const Quaternion& vec);
#endif

#endif

#endif
