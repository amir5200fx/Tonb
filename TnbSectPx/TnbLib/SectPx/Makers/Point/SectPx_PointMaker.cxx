#include <SectPx_PointMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Pnt> 
tnbLib::maker::Point::SelectPnt
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto pnt = std::dynamic_pointer_cast<SectPx_Pnt>(item);
	if (NOT pnt)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pnt> SectPx_PntMaker::SelectPnt()")
			<< "the item is not a pnt!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(pnt);
}

Standard_Integer 
tnbLib::maker::Point::CreateOuterComponent
(
	const std::shared_ptr<SectPx_Par>& xPar,
	const std::shared_ptr<SectPx_Par>& yPar
) const
{
	auto pnt = 
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Compnt>>();
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);

	pnt->SetX(xPar);
	pnt->SetY(yPar);

	return id;
}

Standard_Integer 
tnbLib::maker::Point::CreateInnerComponent
(
	const std::shared_ptr<SectPx_Par>& xPar, 
	const std::shared_ptr<SectPx_Par>& yPar
) const
{
	auto pnt = 
		std::make_shared<sectPxLib::InnerPnt<sectPxLib::Pnt_Compnt>>();
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);

	pnt->SetX(xPar);
	pnt->SetY(yPar);

	return id;
}

Standard_Integer 
tnbLib::maker::Point::CreateOuterOffset
(
	const Standard_Real x, 
	const Standard_Real y
) const
{
	auto pnt = 
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>(x, y);
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);
	return id;
}

Standard_Integer
tnbLib::maker::Point::CreateOuterOffset
(
	const Pnt2d& theCoord
) const
{
	auto pnt =
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>(theCoord.X(), theCoord.Y());
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);
	return id;
}

Standard_Integer
tnbLib::maker::Point::CreateInnerOffset
(
	const Standard_Real x,
	const Standard_Real y
) const
{
	auto pnt =
		std::make_shared<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>>(x, y);
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);
	return id;
}

Standard_Integer
tnbLib::maker::Point::CreateInnerOffset
(
	const Pnt2d& theCoord
) const
{
	auto pnt =
		std::make_shared<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>>(theCoord.X(), theCoord.Y());
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(pnt);
	return id;
}

Standard_Integer 
tnbLib::maker::Point::CreateField
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

	auto pnt = std::make_shared<sectPxLib::InnerPnt<sectPxLib::Pnt_GeoField>>();
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

Standard_Integer 
tnbLib::maker::Point::CreateEmpty
(
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
) const
{
	auto pnt = 
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Empty>>(theMaster);
	Debug_Null_Pointer(pnt);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(pnt));
}

std::shared_ptr<tnbLib::SectPx_Pnt> 
tnbLib::maker::Point::RemovePnt
(
	const Standard_Integer theIndex
) const
{
	auto pnt = SelectPnt(theIndex);
	Debug_Null_Pointer(pnt);

	if (NOT SectPx_PntTools::IsRemovable(pnt))
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_Pnt> RemovePnt(const Standard_Integer theIndex)"
		)
			<< "the pnt is not removable!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Registry());
	Registry()->Remove(pnt);
	return std::move(pnt);
}