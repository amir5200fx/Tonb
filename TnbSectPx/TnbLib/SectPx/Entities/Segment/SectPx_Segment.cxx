#include <SectPx_Segment.hxx>

#include <SectPx_Pole.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_Segment::typeName_("segment");

tnbLib::SectPx_Segment::SectPx_Segment
(
	const std::shared_ptr<SectPx_Pole>& theP0,
	const std::shared_ptr<SectPx_Pole>& theP1
)
	: theP0_(theP0)
	, theP1_(theP1)
{
}

tnbLib::SectPx_Segment::SectPx_Segment
(
	std::shared_ptr<SectPx_Pole>&& theP0,
	std::shared_ptr<SectPx_Pole>&& theP1
)
	: theP0_(std::move(theP0))
	, theP1_(std::move(theP1))
{
}

tnbLib::SectPx_Segment::SectPx_Segment
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_Pole>& theP0,
	const std::shared_ptr<SectPx_Pole>& theP1
)
	: SectPx_RegObj(theIndex)
	, theP0_(theP0)
	, theP1_(theP1)
{
}

tnbLib::SectPx_Segment::SectPx_Segment
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<SectPx_Pole>& theP0,
	const std::shared_ptr<SectPx_Pole>& theP1
)
	: SectPx_RegObj(theIndex, theName)
	, theP0_(theP0)
	, theP1_(theP1)
{
}

Standard_Integer
tnbLib::SectPx_Segment::GetIndex
(
	const std::shared_ptr<SectPx_Pole>& theP
) const
{
	if (theP IS_EQUAL Pole0())
	{
		return 0;
	}
	if (theP IS_EQUAL Pole1())
	{
		return 1;
	}
	FatalErrorIn("Standard_Integer GetIndex(const std::shared_ptr<SectPx_Pole>& theP) const")
		<< "the pole is not belong to the segment" << endl
		<< abort(FatalError);
	return 0;
}

tnbLib::Pnt2d
tnbLib::SectPx_Segment::CalcMidCoord() const
{
	Debug_Null_Pointer(Pole0());
	auto p0 = Pole0()->Coord();

	Debug_Null_Pointer(Pole1());
	auto p1 = Pole1()->Coord();

	auto pm = MEAN(p0, p1);
	return std::move(pm);
}

const std::shared_ptr<tnbLib::SectPx_Pole> &
tnbLib::SectPx_Segment::Pole
(
	const Standard_Integer theIndex
) const
{
#ifdef _DEBUG
	if (NOT INSIDE(theIndex, 0, 1))
	{
		FatalErrorIn("const std::shared_ptr<SectPx_Pole>& Pole(const Standard_Integer theIndex) const")
			<< "invalid index" << theIndex << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	return (&theP0_)[theIndex];
}

std::shared_ptr<tnbLib::SectPx_Pole>
tnbLib::SectPx_Segment::Other
(
	const std::shared_ptr<SectPx_Pole>& theP
) const
{
	const auto id = GetIndex(theP);
	return Pole((id + 1) % 2);
}

tnbLib::word 
tnbLib::SectPx_Segment::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Segment::RegObjType() const
{
	return sectPxLib::regObjType::segment;
}

Standard_Boolean 
tnbLib::SectPx_Segment::IsSegment() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Segment::IsFrameRegObj() const
{
	return Standard_True;
}