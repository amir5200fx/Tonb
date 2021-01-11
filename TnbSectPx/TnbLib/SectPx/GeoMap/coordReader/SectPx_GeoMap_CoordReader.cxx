#include <SectPx_GeoMap_CoordReader.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Coord.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::GeoMap_CoordReader::typeName_ = "coord_reader";

tnbLib::sectPxLib::GeoMap_CoordReader::GeoMap_CoordReader
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_GeoMap(theIndex, theName)
{
	//- empty body
}

void tnbLib::sectPxLib::GeoMap_CoordReader::SetCoord
(
	const std::shared_ptr<SectPx_Coord>& theQ
)
{
	theCoord_ = theQ;
}

tnbLib::word 
tnbLib::sectPxLib::GeoMap_CoordReader::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d 
tnbLib::sectPxLib::GeoMap_CoordReader::CalcCoord() const
{
	if (NOT IsComplete())
	{
		FatalErrorIn("Pnt2d CalcCoord() const")
			<< "the map is not complete!" << endl
			<< abort(FatalError);
	}

	return theCoord_->Coord();
}

Standard_Integer 
tnbLib::sectPxLib::GeoMap_CoordReader::NbChildren() const
{
	return 0;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_CoordReader::IsComplete() const
{
	if (NOT Coord()) return Standard_False;

	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_CoordReader::HasChildren() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_CoordReader::HasChild
(
	const std::shared_ptr<SectPx_Child>& /*thePar*/
) const
{
	return Standard_False;
}

void tnbLib::sectPxLib::GeoMap_CoordReader::RemoveThisFromChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::GeoMap_CoordReader::AddThisToChildren() const
{
	//- empty body
}

void tnbLib::sectPxLib::GeoMap_CoordReader::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& /*thePar*/
) const
{
	//- empty body
}

void tnbLib::sectPxLib::GeoMap_CoordReader::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& /*thePar*/
) const
{
	//- empty body
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::GeoMap_CoordReader::RetrieveChildren() const
{
	return std::vector<std::shared_ptr<SectPx_Child>>();
}

std::shared_ptr<tnbLib::sectPxLib::GeoMap_CoordReader>
tnbLib::sectPxLib::GeoMap_CoordReader::MakeReader
(
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
{
	const auto geoMap =
		std::make_shared<GeoMap_CoordReader>
		(
			0,
			GeoMap_CoordReader::typeName_
			);
	Debug_Null_Pointer(geoMap);

	theReg->Import(geoMap);
	return std::move(geoMap);
}