#include "Vector2.hh"

namespace rt {
    Vector2::Vector2() {
        _X = 0.0f;
        _Y = 0.0f;
    }

    Vector2::Vector2(float X, float Y) {
        _X = X;
        _Y = Y;
    }

    bool Vector2::operator==(const Vector2& other) const {
        return (_X == other._X && _Y == other._Y);
    }

    bool Vector2::operator!=(const Vector2& other) const {
        return !(_X == other._X && _Y == other._Y);
    }

    Vector2 Vector2::operator+(const Vector2& right) const {
        return Vector2(_X + right._X, _Y + right._Y);
    }

    Vector2 Vector2::operator-(const Vector2& right) const {
        return Vector2(_X - right._X, _Y - right._Y);
    }

    Vector2 Vector2::operator*(const float& other) const {
        return Vector2(_X *other, _Y * other);
    }

    float const& Vector2::getX(void) const {
        return _X;
    }
    
    void Vector2::SetX(const float& X) {
        _X = X;
    }

    float const& Vector2::getY(void) const {
        return _Y;
    }
    
    void Vector2::SetY(const float& Y) {
        _Y = Y;
    }
}