//
// Created by amir on 8/26/25.
//
#pragma once
#include <tonb/geometry/occt/surface.hxx>
#include <opencascade/Geom_Surface.hxx>
#include <opencascade/Standard_Handle.hxx>
namespace tonb::geometry::occt {
    struct Surface::Impl {
        opencascade::handle<Geom_Surface> h;
    };
}
namespace tonb::geometry::occt::core {
    struct occt_surface_access {
        static Surface make(const opencascade::handle<Geom_Surface>& h) {
            if (h.IsNull()) return {};
            return Surface{std::make_shared<Surface::Impl>(Surface::Impl{h})};
        }
        static opencascade::handle<Geom_Surface> get(const Surface& s) {
            return (s.pimpl_ ? s.pimpl_->h : nullptr);
        }
    };
}