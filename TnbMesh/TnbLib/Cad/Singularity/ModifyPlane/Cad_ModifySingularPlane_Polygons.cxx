#include <Cad_ModifySingularPlane.hxx>

#include <Cad_ModifySingularPlane_PolygonLib.hxx>
#include <Entity2d_PolygonTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad_ModifySingularPlaneBase::RegisterPolygon(const Entity2d_Polygon & thePoly)
{
	auto poly = meshLib::singularity::PolygonLib::GetWire(thePoly);
	PolygonsRef().push_back(std::move(poly));
}

void tnbLib::Cad_ModifySingularPlaneBase::Reserve(const size_t n)
{
	PolygonsRef().reserve(n);
}

Standard_Boolean 
tnbLib::Cad_ModifySingularPlaneBase::InsidePolygon
(
	const Standard_Integer theIndex,
	const Pnt2d & thePt
) const
{
	auto pt = Point_2(thePt.X(), thePt.Y());

	Debug_Null_Pointer(thePolygons_.at(theIndex));
	auto& poly = thePolygons_.at(theIndex)->PointsRef();

	const auto side = Entity2d_PolygonTools::GetSide(pt, &FirstItem(poly), &LastItem(poly));
	if (side IS_EQUAL Entity2d_PolygonSide::unbounded)
		return Standard_False;
	else if (side IS_EQUAL Entity2d_PolygonSide::bounded)
		return Standard_True;
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Unpredicted situation has been occurred!" << endl
			<< abort(FatalError);
	}
	return Standard_True;
}