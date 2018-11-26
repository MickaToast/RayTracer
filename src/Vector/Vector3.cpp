#include <math.h>
#include <iostream>
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

    Vector3::~Vector3(void) {
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

    void Vector3::Normalize(void) {
        float norm = this->Norm();
        _X = _X / norm;
        _Y = _Y / norm;
        _Z = _Z / norm;
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

    std::ostream& operator<<(std::ostream& os, const Vector3& v) {  
        os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
        return os;
    }

    float const& Vector3::getX(void) const {
        return _X;
    }
    
    void Vector3::SetX(const float& X) {
        _X = X;
    }

    float const& Vector3::getY(void) const {
        return _Y;
    }
    
    void Vector3::SetY(const float& Y) {
        _Y = Y;
    }

    float const& Vector3::getZ(void) const {
        return _Z;
    }
    
    void Vector3::SetZ(const float& Z) {
        _Z = Z;
    }
}