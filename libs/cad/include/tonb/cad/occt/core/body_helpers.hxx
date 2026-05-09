//
// Created by amir on 8/24/25.
//
#pragma once
#include <tonb/cad/module.hxx>
// Forward Declarations
namespace tonb::cad::occt {
    class Body;
}
class TopoDS_Shape;

namespace tonb::cad::occt::core {

    /// Create a Body that owns a copy of the OCCT handle
    TNBCAD_ND_EXPORT Body from_topo(const TopoDS_Shape& shape);

    /// Extract the OCCT handle (null if Body not OCCT-backend)
    TNBCAD_ND_EXPORT TopoDS_Shape to_topo(const Body& body);
}