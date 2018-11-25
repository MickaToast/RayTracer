#pragma once

#include "../Vector/Vector3.hh"
#include "../Vector/Vector2.hh"

namespace rt {
    class Camera {
        public:
            Camera(Vector3 const& pos, Vector3 const& dir);
            Camera(Vector3 const& dir);
            Camera(void);
            virtual ~Camera(void);

            Vector3 generateRay(Vector2 const &pos) const;

        private:
            Vector3   _pos = Vector3(0, 0, 0);
            Vector3   _dir = Vector3(0, 0, -1);
            float     _screenDist = 5.0;
            Vector2   _screenRes = Vector2(1920, 1080);
    };
}