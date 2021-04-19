#include <Mesh3d_Element.hxx>

//#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	Mesh3d_Element::array4 Mesh3d_Element::InterpWeights(const Pnt3d& theCoord) const
	{
		NotImplemented;
		array4 t;
		return std::move(t);
	}
}