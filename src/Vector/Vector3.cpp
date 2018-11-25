#include <math.h>
#include "Vector3.hh"

namespace rt {  
    Vector3::Vector3() {
        _X = 0.0f;
        _Y = 0.0f;
        _Z = 0.0f;
    }

    Vector3::Vector3(float X, float Y, float Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    Vector3 Vector3::Cross(const Vector3 other) const {
        return Vector3(_Y * other._Z - _Z * other._Y,
        _Z * other._X - _X * other._Z,
        _X * other._Y - _Y * other._X);
    }

    float Vector3::Dot(const Vector3 other) const {
        return (_X * other._X) + (_Y * other._Y) + (_Z * other._Z);
    }

    float Vector3::Norm(void) const {
        return (sqrtf(powf(_X, 2) + powf(_Y, 2) + powf(_Z, 2)));
    }

    bool Vector3::operator==(const Vector3& other) const {
        return (_X == other._X && _Y == other._Y && _Z == other._Z);
    }

    bool Vector3::operator!=(const Vector3& other) const {
        return !(_X == other._X && _Y == other._Y && _Z == other._Z);
    }

    Vector3 Vector3::operator+(const Vector3& right) const {
        return Vector3(_X + right._X, _Y + right._Y, _Z + right._Z);
    }
        
    Vector3 Vector3::operator-(const Vector3& right) const {
        return Vector3(_X - right._X, _Y - right._Y, _Z - right._Z);
    }

    Vector3 Vector3::operator*(const float& other) const {
        return Vector3(_X * other, _Y * other, _Z * other);
    }

    Vector3 Vector3::operator/(const float& other) const {
        return Vector3(_X / other, _Y / other, _Z / other);
    }
}