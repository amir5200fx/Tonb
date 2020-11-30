#include <SectPx_GeometricMapMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_GeoMap_LinearInterpl.hxx>
#include <SectPx_GeoMap_Intersection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_GeoMap> 
tnbLib::maker::GeometricMap::SelectGeoMap
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto geoMap = std::dynamic_pointer_cast<SectPx_GeoMap>(item);
	if (NOT geoMap)
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree or is not a map!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(geoMap);
}

Standard_Integer 
tnbLib::maker::GeometricMap::CreateLinearInterpolation
(
	const std::shared_ptr<SectPx_Coord>& theQ0, 
	const std::shared_ptr<SectPx_Coord>& theQ1, 
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	Debug_Null_Pointer(Registry());

	auto geoMap = std::make_shared<sectPxLib::GeoMap_LinearInterpl>();
	Debug_Null_Pointer(geoMap);

	geoMap->SetQ0(theQ0);
	geoMap->SetQ1(theQ1);
	geoMap->SetPar(thePar);

	const auto id = Registry()->Import(geoMap);
	geoMap->SetName("linear interpolation map" + std::to_string(id));

	return id;
}

Standard_Integer 
tnbLib::maker::GeometricMap::CreateLinearInterpolation() const
{
	Debug_Null_Pointer(Registry());

	auto geoMap = std::make_shared<sectPxLib::GeoMap_LinearInterpl>();
	Debug_Null_Pointer(geoMap);

	const auto id = Registry()->Import(geoMap);
	geoMap->SetName("linear interpolation map" + std::to_string(id));

	return id;
}

Standard_Integer 
tnbLib::maker::GeometricMap::CreateIntersection
(
	const std::shared_ptr<SectPx_Coord>& theQ0, 
	const Dir2d & theDir0,
	const std::shared_ptr<SectPx_Par>& theAng0,
	const std::shared_ptr<SectPx_Coord>& theQ1,
	const Dir2d & theDir1, 
	const std::shared_ptr<SectPx_Par>& theAng1
) const
{
	Debug_Null_Pointer(Registry());

	auto geoMap = std::make_shared<sectPxLib::GeoMap_Intersection>();
	Debug_Null_Pointer(geoMap);

	const auto id = Registry()->Import(geoMap);
	geoMap->SetName("intersection map" + std::to_string(id));

	geoMap->SetQ0(theQ0);
	geoMap->SetDir0(theDir0);
	geoMap->SetAngle0(theAng0);

	geoMap->SetQ1(theQ1);
	geoMap->SetDir1(theDir1);
	geoMap->SetAngle1(theAng1);

	return id;
}

Standard_Integer 
tnbLib::maker::GeometricMap::CreateIntersection() const
{
	Debug_Null_Pointer(Registry());

	auto geoMap = std::make_shared<sectPxLib::GeoMap_Intersection>();
	Debug_Null_Pointer(geoMap);

	const auto id = Registry()->Import(geoMap);
	geoMap->SetName("intersection map" + std::to_string(id));

	return id;
}

std::shared_ptr<tnbLib::SectPx_GeoMap>
tnbLib::maker::GeometricMap::RemoveGeoMap
(
	const Standard_Integer theIndex
) const
{
	auto item = SelectGeoMap(theIndex);
	Debug_Null_Pointer(item);

	if (item->NbChildren())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map has at least one child!"
			<< "nb. of children: " << item->NbChildren() << endl
			<< abort(FatalError);
	}
	Registry()->Remove(item);
	return std::move(item);
}