#include <cstdlib>
#include <math.h>
#include "Camera.hh"

namespace rt {
    Camera::Camera(Vector3 const& pos, Vector3 const& dir) {
        _pos = pos;
        _dir = dir;
    }

    Camera::Camera(Vector3 const& dir) {
        _dir = dir;
    }

    Camera::Camera(void) {
    }

    Camera::~Camera(void) {
    }

    Vector3 Camera::generateRay(Vector2 const &pos) const {
        float Rx = ((double) std::rand() / (RAND_MAX)) + 1;
        float Ry = ((double) std::rand() / (RAND_MAX)) + 1;

        Vector3 pixel = Vector3(
            ((2 * ((pos.getX() + Rx) / _screenRes.getX()) - 1)
            * (_screenRes.getX() / _screenRes.getY())) * tan(_fov / 2),
            (1 - 2 * ((pos.getY() + Ry) / _screenRes.getY())) * tan(_fov / 2),
            -1
        );
        Vector3 ray = pixel - _pos;
        ray.Normalize();
        //TODO handle camera rotation and position moves
        return ray;
    }
}