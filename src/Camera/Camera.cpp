#include <cstdlib>
#include <math.h>
#include "Camera.hh"

namespace rt {
    Camera::Camera(Vector3 const& pos, Vector3 const& target) {
        _pos = pos;
        _axis[2] = target - _pos;
        _axis[2].Normalize();
        _axis[0] = Vector3(0, -1, 0).Cross(_axis[2]);
        _axis[0].Normalize();
        _axis[1] = _axis[0].Cross(_axis[2]);
        _axis[1].Normalize();
    }

    Camera::~Camera(void) {
    }

    Vector3 Camera::generateRay(Vector2 const &pos) const {
        float Rx = ((double) std::rand() / (RAND_MAX)) + 1;
        float Ry = ((double) std::rand() / (RAND_MAX)) + 1;

        Vector3 pixel = Vector3(
            ((2 * ((pos.getX() + Rx) / _screenRes.getX()) - 1)
            * (_screenRes.getX() / _screenRes.getY())) * tan(_fov / 2 * M_PI /180),
            (1 - 2 * ((pos.getY() + Ry) / _screenRes.getY())) * tan(_fov / 2 * M_PI /180),
            -1
        );
        Vector3 ray = pixel - _pos;
        ray.Normalize();
        //TODO handle camera rotation and position moves
        return ray;
    }

    std::array<Vector3, 3> const& Camera::getAxis(void) const {
        return _axis;
    }
}