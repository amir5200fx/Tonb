#include <Aft3d_Element.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::array4 
		Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::InterpWeights(const Pnt3d& theCoord) const
	{
		NotImplemented;
		array4 t;
		return std::move(t);
	}
}