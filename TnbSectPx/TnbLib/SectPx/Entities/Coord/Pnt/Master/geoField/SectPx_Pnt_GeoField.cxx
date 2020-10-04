#include <SectPx_Pnt_GeoField.hxx>

#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Pnt_GeoField::typeName_ = "pnt_geoField";

tnbLib::word 
tnbLib::sectPxLib::Pnt_GeoField::RegObjTypeName() const
{
	return typeName_;
}

void tnbLib::sectPxLib::Pnt_GeoField::SetGeoMap
(
	const std::shared_ptr<SectPx_GeoMap>& theMap
)
{
	theMap_ = theMap;
}

Standard_Real
tnbLib::sectPxLib::Pnt_GeoField::xCoord() const
{
	auto pt = Coord();
	return pt.X();
}

Standard_Real 
tnbLib::sectPxLib::Pnt_GeoField::yCoord() const
{
	auto pt = Coord();
	return pt.Y();
}

tnbLib::Pnt2d tnbLib::sectPxLib::Pnt_GeoField::Coord() const
{
	const auto& geoMap = GeoMap();
	if (NOT geoMap)
	{
		FatalErrorIn("Pnt2d Coord() const")
			<< "the GeoFieldFun doesn't have any GeoMap" << endl
			<< abort(FatalError);
	}
	return geoMap->CalcCoord();
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_GeoField::IsComplete() const
{
	return (Standard_Boolean)GeoMap();
}

typename tnbLib::sectPxLib::pntType 
tnbLib::sectPxLib::Pnt_GeoField::PntType() const
{
	return sectPxLib::pntType::fieldFun;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_GeoField::IsGeoField() const
{
	return Standard_True;
}

Standard_Integer
tnbLib::sectPxLib::Pnt_GeoField::NbChildMaps() const
{
	return 1;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_GeoField::HasChildMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::Pnt_GeoField::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent> 
tnbLib::sectPxLib::Pnt_GeoField::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(theIndex, "invalid index");
	return GeoMap();
}

void tnbLib::sectPxLib::Pnt_GeoField::RemoveThisFromChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_GeoField::AddThisToChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_GeoField::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}

void tnbLib::sectPxLib::Pnt_GeoField::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}
