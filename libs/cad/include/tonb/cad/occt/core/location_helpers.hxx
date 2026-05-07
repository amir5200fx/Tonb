//
// Created by amir on 8/26/25.
//
#pragma once
#include <tonb/cad/occt/location.hxx>
#include <opencascade/TopLoc_Location.hxx>

namespace tonb::cad::occt {
    struct Location::Impl {
        TopLoc_Location l;
        TNB_NODISCARD bool identity() const {return l.IsIdentity();}
    };
}

namespace tonb::cad::occt::core {
    struct occt_location_access {
        static Location make(const TopLoc_Location& l) {
            return Location{std::make_shared<Location::Impl>(l)};
        }
        static TopLoc_Location get(const Location& l) {
            return (l.pimpl_ ? l.pimpl_->l : TopLoc_Location());
        }
    };
}
