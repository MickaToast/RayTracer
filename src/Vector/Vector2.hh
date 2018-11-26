#pragma one

namespace rt {
    class Vector2 {
        public:
            Vector2(void);
            Vector2(float X_, float Y);
            ~Vector2(void);

            bool operator==(const Vector2& other) const;
            bool operator!=(const Vector2& other) const;
            Vector2 operator+(const Vector2& right) const;
            Vector2 operator-(const Vector2& right) const;
            Vector2 operator*(const float& other) const;
                
            float const&    getX(void) const;
            void            SetX(const float& X);
            float const&    getY(void) const;
            void            SetY(const float& X);
            
        private:
            float   _X;
            float   _Y;
    };
}