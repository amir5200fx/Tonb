#include <SectPx_Datum_GeoField.hxx>

#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::Datum_GeoField::typeName_ = "datum_geoField";

void tnbLib::sectPxLib::Datum_GeoField::SetGeoMap
(
	const std::shared_ptr<SectPx_GeoMap>& theMap
)
{
	theMap_ = theMap;
}

tnbLib::word 
tnbLib::sectPxLib::Datum_GeoField::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::Datum_GeoField::xCoord() const
{
	auto pt = Coord();
	return pt.X();
}

Standard_Real 
tnbLib::sectPxLib::Datum_GeoField::yCoord() const
{
	auto pt = Coord();
	return pt.Y();
}

tnbLib::Pnt2d 
tnbLib::sectPxLib::Datum_GeoField::Coord() const
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
tnbLib::sectPxLib::Datum_GeoField::IsComplete() const
{
	return (Standard_Boolean)GeoMap();
}

Standard_Integer 
tnbLib::sectPxLib::Datum_GeoField::NbChildMaps() const
{
	return 1;
}

Standard_Boolean 
tnbLib::sectPxLib::Datum_GeoField::HasChildMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::Datum_GeoField::HasChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Parent> 
tnbLib::sectPxLib::Datum_GeoField::ChildMap
(
	const Standard_Integer theIndex
) const
{
	Debug_If_Condition_Message(theIndex, "invalid index");
	return GeoMap();
}

void tnbLib::sectPxLib::Datum_GeoField::RemoveThisFromChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::Datum_GeoField::AddThisToChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::Datum_GeoField::AddThisToChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}

void tnbLib::sectPxLib::Datum_GeoField::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	//- empty body
}