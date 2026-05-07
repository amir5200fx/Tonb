#include <SectPx_Pole_Slider.hxx>

#include <SectPx_Pnt_GeoField.hxx>

const char* tnbLib::sectPxLib::Pole_Slider::typeName_ = "slider pole";

tnbLib::sectPxLib::Pole_Slider::Pole_Slider
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pnt_GeoField>& thePnt
)
	: SectPx_InterPole(theIndex)
	, thePnt_(thePnt)
{
}

tnbLib::sectPxLib::Pole_Slider::Pole_Slider
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<Pnt_GeoField>& thePnt
)
	: SectPx_InterPole(theIndex, theName)
	, thePnt_(thePnt)
{
}

tnbLib::word 
tnbLib::sectPxLib::Pole_Slider::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d
tnbLib::sectPxLib::Pole_Slider::Coord() const
{
	Debug_Null_Pointer(Pnt());
	auto pt = Pnt()->Coord();
	return std::move(pt);
}

std::shared_ptr<tnbLib::SectPx_Pnt>
tnbLib::sectPxLib::Pole_Slider::Pnt() const
{
	return thePnt_;
}