#include <cstdlib>
#include "Camera.hh"

namespace rt {
    Camera::Camera(Vector3 const& pos, Vector3 const& dir) {
        this->_pos = pos;
        this->_dir = dir;
    }

    Camera::Camera(Vector3 const& dir) {
        this->_dir = dir;
    }

    Camera::Camera(void) {
    }

    Camera::~Camera(void) {
    }

    Vector3 Camera::generateRay(Vector2 const &pos) const {
        float Rx = ((double) std::rand() / (RAND_MAX)) + 1;
        float Ry = ((double) std::rand() / (RAND_MAX)) + 1;
        Vector3 pixelPos = Vector3();
        return pixelPos - this->_pos;
    }
}