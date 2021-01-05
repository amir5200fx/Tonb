#include <SectPx_DatumMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Datum>
tnbLib::maker::Datum::SelectPnt
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto pnt = std::dynamic_pointer_cast<SectPx_Datum>(item);
	if (NOT pnt)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Datum> SectPx_DatumMaker::SelectPnt()")
			<< "the item is not a datum!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(pnt);
}

Standard_Integer
tnbLib::maker::Datum::CreateComponent
(
	const std::shared_ptr<SectPx_Par>& xPar,
	const std::shared_ptr<SectPx_Par>& yPar
) const
{
	auto pnt =
		std::make_shared<sectPxLib::Datum_Compnt>();
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);

	pnt->SetX(xPar);
	pnt->SetY(yPar);

	return id;
}

Standard_Integer
tnbLib::maker::Datum::CreateField
(
	const std::shared_ptr<SectPx_GeoMap>& theMap
) const
{
	if (NOT theMap)
	{
		FatalErrorIn(FunctionSIG)
			<< "the map is empty!" << endl
			<< abort(FatalError);
	}

	auto pnt = std::make_shared<sectPxLib::Datum_GeoField>();
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto selected = Registry()->SelectObj(theMap->Index());
	if (NOT selected)
	{
		FatalErrorIn(FunctionSIG)
			<< "null pointer has been detected!" << endl
			<< abort(FatalError);
	}

	if (selected NOT_EQUAL theMap)
	{
		FatalErrorIn(FunctionSIG)
			<< "the map is not in the registry!" << endl
			<< " map's name = " << theMap->Name() << ", nb. " << theMap->Index() << endl
			<< " typeName = " << theMap->RegObjTypeName() << endl
			<< abort(FatalError);
	}

	pnt->SetGeoMap(theMap);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(pnt));
}

std::shared_ptr<tnbLib::SectPx_Datum>
tnbLib::maker::Datum::RemovePnt
(
	const Standard_Integer theIndex
) const
{
	auto pnt = SelectPnt(theIndex);
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	Registry()->Remove(pnt);
	return std::move(pnt);
}