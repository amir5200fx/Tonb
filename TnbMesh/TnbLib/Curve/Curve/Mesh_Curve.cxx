#include <Mesh_Curve.hxx>

tnbLib::Mesh_Curve_Base::Mesh_Curve_Base
(
	const Standard_Real theFirst,
	const Standard_Real theLast,
	const std::shared_ptr<info>& theInfo
)
	: theFirstParameter_(theFirst)
	, theLastParameter_(theLast)
	, theInfo_(theInfo)
{
	// empty body
}

tnbLib::Mesh_Curve_Base::Mesh_Curve_Base()
	: theFirstParameter_(0)
	, theLastParameter_(0)
{
	// empty body
}