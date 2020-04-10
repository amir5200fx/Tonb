#include <Geo_MxCifQuadtree.hxx>

tnbLib::Geo_MxCifQuadtree_Base::Geo_MxCifQuadtree_Base
(
	const Entity2d_Box & theBox
)
	: theDomain_(theBox)
	, theMaxDivide_(DEFAULT_MAX_DIVIDE)
{
	const auto[dx, dy] = Domain().Length();
	const auto dmax = MAX(dx, dy);

	theDmin_ = dmax / (Standard_Real)pow(2.0, (Standard_Real)MaxDivide());
}