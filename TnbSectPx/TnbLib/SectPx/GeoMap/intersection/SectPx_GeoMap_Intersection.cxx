#include <SectPx_GeoMap_Intersection.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Coord.hxx>
#include <SectPx_ParTools.hxx>
#include <SectPx_Par.hxx>
#include <Geo_Tools.hxx>
#include <Pnt2d.hxx>
#include <Entity_Line.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::GeoMap_Intersection::typeName_ = "intersection_map";

void tnbLib::sectPxLib::GeoMap_Intersection::SetQ0
(
	const std::shared_ptr<SectPx_Coord>& theQ0
)
{
	if (theQ0_)
	{
		auto geoMap = theQ0_->RemoveGeoMap(Index());
#ifdef _DEBUG
		if (geoMap NOT_EQUAL std::dynamic_pointer_cast<SectPx_GeoMap>(This()))
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
	}
	theQ0_ = theQ0;
	theQ0_->ImportToGeoMaps(std::dynamic_pointer_cast<SectPx_GeoMap>(This()));
}

void tnbLib::sectPxLib::GeoMap_Intersection::SetQ1
(
	const std::shared_ptr<SectPx_Coord>& theQ1
)
{
	if (theQ1_)
	{
		auto geoMap = theQ1_->RemoveGeoMap(Index());
#ifdef _DEBUG
		if (geoMap NOT_EQUAL std::dynamic_pointer_cast<SectPx_GeoMap>(This()))
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
	}
	theQ1_ = theQ1;
	theQ1_->ImportToGeoMaps(std::dynamic_pointer_cast<SectPx_GeoMap>(This()));
}

void tnbLib::sectPxLib::GeoMap_Intersection::SetDir0
(
	const Dir2d & theD0
)
{
	theDir0_ = theD0;
}

void tnbLib::sectPxLib::GeoMap_Intersection::SetDir1
(
	const Dir2d & theD1
)
{
	theDir1_ = theD1;
}

void tnbLib::sectPxLib::GeoMap_Intersection::SetAngle0
(
	const std::shared_ptr<SectPx_Par>& theAngle
)
{
	AddParameterToParent
	(
		theAngle0_,
		theAngle,
		"void SetAngle0(const std::shared_ptr<SectPx_Par>& thePar)"
	);
}

void tnbLib::sectPxLib::GeoMap_Intersection::SetAngle1
(
	const std::shared_ptr<SectPx_Par>& theAngle
)
{
	AddParameterToParent
	(
		theAngle1_,
		theAngle,
		"void SetAngle0(const std::shared_ptr<SectPx_Par>& thePar)"
	);
}

tnbLib::word 
tnbLib::sectPxLib::GeoMap_Intersection::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d 
tnbLib::sectPxLib::GeoMap_Intersection::CalcCoord() const
{
	const auto angle0 = Angle0().lock();
	Debug_Null_Pointer(angle0);

	const auto angle1 = Angle1().lock();
	Debug_Null_Pointer(angle1);

	const auto dir0 = Dir2d(Dir0().Rotated(angle0->Value()).XY());
	const auto dir1 = Dir2d(Dir1().Rotated(angle1->Value()).XY());

	if (dir0.IsParallel(dir1, 1.0e-6))
	{
		const auto p0 = Q0()->Coord();
		const auto p1 = Q1()->Coord();

		const auto pt = MEAN(p0, p1);
		FatalErrorIn(FunctionSIG) << endl
			<< "couldn't calculate the intersection point." << endl
			<< " - the two lines are parallel!" << endl
			<< abort(FatalError);
		return std::move(pt);
	}
	else
	{
		const auto p0 = Q0()->Coord();
		const auto p1 = Q1()->Coord();
		Entity2d_Line l0(p0, dir0);
		Entity2d_Line l1(p1, dir1);
		const auto pt =
			Geo_Tools::Intersection_cgal(l0, l1);
		if (NOT pt->IsPoint())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "couldn't calculate the intersection point." << endl
				<< abort(FatalError);
		}
		return std::dynamic_pointer_cast<Geo_Tools::PointIntersectEntity2d>(pt)->IntPnt;
	}
}

Standard_Integer 
tnbLib::sectPxLib::GeoMap_Intersection::NbCoords() const
{
	return 2;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Coord>> 
tnbLib::sectPxLib::GeoMap_Intersection::RetrieveCoords() const
{
	std::vector<std::shared_ptr<SectPx_Coord>> coords;
	coords.reserve(2);
	coords.push_back(Q0());
	coords.push_back(Q1());
	return std::move(coords);
}

Standard_Integer 
tnbLib::sectPxLib::GeoMap_Intersection::NbChildren() const
{
	return 2;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_Intersection::IsComplete() const
{
	if (NOT Q0()) return Standard_False;
	if (NOT Q1()) return Standard_False;
	
	ReturnFalseIfNull(Angle0());
	ReturnFalseIfNull(Angle1());
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_Intersection::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_Intersection::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Angle0(), thePar);
	ReturnTrueIfParBelongsToThisParent(Angle1(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::sectPxLib::GeoMap_Intersection::RetrieveChildren() const
{
	DefineChildList(childs);
	AddParToChildList(Angle0(), childs);
	AddParToChildList(Angle1(), childs);
	return std::move(childs);
}

void tnbLib::sectPxLib::GeoMap_Intersection::RemoveThisFromChildren() const
{
	auto angle0 = Angle0().lock();
	if (angle0)
	{
		RemoveThisFromChild(angle0);
	}

	auto angle1 = Angle1().lock();
	if (angle1)
	{
		RemoveThisFromChild(angle1);
	}
}

void tnbLib::sectPxLib::GeoMap_Intersection::AddThisToChildren() const
{
	AddThisParentToChildren(Angle0());
	AddThisParentToChildren(Angle1());
}

void tnbLib::sectPxLib::GeoMap_Intersection::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::sectPxLib::GeoMap_Intersection::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}