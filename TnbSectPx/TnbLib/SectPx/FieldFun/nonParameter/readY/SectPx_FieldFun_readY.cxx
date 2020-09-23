#include <SectPx_FieldFun_readY.hxx>

#include <SectPx_Coord.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::FieldFun_readY::typeName_ = "fieldFun_readY";

tnbLib::sectPxLib::FieldFun_readY::FieldFun_readY
(
	const std::shared_ptr<SectPx_Coord>& theCoord
)
	: theCoord_(theCoord)
{
}

tnbLib::sectPxLib::FieldFun_readY::FieldFun_readY
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Coord>& theCoord
)
	: SectPx_nonParFieldFun(theIndex)
	, theCoord_(theCoord)
{
}

tnbLib::sectPxLib::FieldFun_readY::FieldFun_readY
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Coord>& theCoord
)
	: SectPx_nonParFieldFun(theIndex, theName)
	, theCoord_(theCoord)
{
}

tnbLib::word 
tnbLib::sectPxLib::FieldFun_readY::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::sectPxLib::FieldFun_readY::Value() const
{
	Debug_Null_Pointer(theCoord_);
	return theCoord_->yCoord();
}