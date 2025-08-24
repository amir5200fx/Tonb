//
// Created by amir on 8/24/25.
//
#pragma once
#include <tonb/geometry/occt/bbox.hxx>
#include <opencascade/Bnd_Box.hxx>
namespace tonb::geometry::occt::core {

    TNB_NODISCARD inline BBox to_bbox(const Bnd_Box& box) {
        Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
        box.Get(xmin, ymin, zmin, xmax, ymax, zmax);

        return BBox::from_min_max({static_cast<real>(xmin), static_cast<real>(ymin), static_cast<real>(zmin)}, {
                                      static_cast<real>(xmax), static_cast<real>(ymax), static_cast<real>(zmax)
                                  });
    }
}