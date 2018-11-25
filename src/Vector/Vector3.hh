#pragma once

namespace rt {
    class Vector3 {
        public:
            Vector3();
            Vector3(float X, float Y, float Z);

            Vector3 Cross(const Vector3 other) const;
            float   Dot(const Vector3 other) const;
            float   Norm(void) const;

            bool    operator==(const Vector3& other) const;
            bool    operator!=(const Vector3& other) const;
            Vector3 operator+(const Vector3& right) const;
            Vector3 operator-(const Vector3& right) const;
            Vector3 operator*(const float& other) const;
            Vector3 operator/(const float& other) const;
        
        private:
            float   _X;
            float   _Y;
            float   _Z;
    };
}