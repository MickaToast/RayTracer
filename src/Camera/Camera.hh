#pragma once

#include <array>
#include "../Vector/Vector3.hh"
#include "../Vector/Vector2.hh"

namespace rt {
    class Camera {
        public:
            Camera(Vector3 const& pos, Vector3 const& dir);
            virtual ~Camera(void);

            Vector3 generateRay(Vector2 const &pos) const;

            std::array<Vector3, 3> const& getAxis(void) const;

        private:
            Vector3                 _pos = Vector3(0, 0, 0);
            std::array<Vector3, 3>  _axis;
            float                   _fov = 90.0;
            Vector2                 _screenRes = Vector2(1920, 1080);
    };
}