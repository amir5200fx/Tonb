#include <Aft3d_NodeCalculator_UniSize.hxx>

#include <Aft3d_Tools.hxx>
#include <Aft3d_Volume.hxx>
#include <Pnt3d.hxx>

tnbLib::Pnt3d 
tnbLib::legLib::Aft3d_NodeCalculator_UniSize::CalcCoord
(
	const Standard_Real theSize, 
	const std::shared_ptr<Aft3d_Facet>& theFacet, 
	const Aft3d_VolumeCore* /*theCore*/
) const
{
	Debug_Null_Pointer(theFacet);
	auto pt = Aft3d_Tools::CalcTetrahedronVertex(theSize, *theFacet);
	return std::move(pt);
}