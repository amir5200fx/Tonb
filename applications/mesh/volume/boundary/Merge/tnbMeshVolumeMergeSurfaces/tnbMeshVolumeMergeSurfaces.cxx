#include <GeoTop_Tools.hxx>
#include <GeoTop2d_Element.hxx>
#include <GeoTop2d_Vertex.hxx>
#include <Entity3d_SurfTriangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<std::map<Standard_Integer, std::shared_ptr<Entity3d_SurfTriangulation>>> mySurfaceMesh;


}