#pragma one

namespace rt {
    class Vector2 {
        public:
            Vector2();
            Vector2(float X_, float Y);

            bool operator==(const Vector2& other) const;
            bool operator!=(const Vector2& other) const;
            Vector2 operator+(const Vector2& right) const;
            Vector2 operator-(const Vector2& right) const;
            Vector2 operator*(const float& other) const;
        
        private:
            float   _X;
            float   _Y;
    };
}