#include <SectPx_CPtsMap.hxx>

#include <SectPx_Segment.hxx>

void tnbLib::SectPx_CPtsMap::SetSegment
(
	const std::shared_ptr<SectPx_Segment>& theSegment,
	const Standard_Boolean theSense
)
{
	theSegment_ = theSegment;
	theSense_ = theSense;

	if (Sense())
	{
		theP0_ = theSegment->Pole0();
		theP1_ = theSegment->Pole1();
	}
	else
	{
		theP0_ = theSegment->Pole1();
		theP1_ = theSegment->Pole0();
	}
}

void tnbLib::SectPx_CPtsMap::Reverse()
{
	theSense_ = NOT theSense_;
	std::swap(theP0_, theP1_);
}

typename tnbLib::sectPxLib::regObjType
tnbLib::SectPx_CPtsMap::RegObjType() const
{
	return sectPxLib::regObjType::cptsMap;
}

Standard_Boolean
tnbLib::SectPx_CPtsMap::IsCPtsMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_CPtsMap::IsFrameRegObj() const
{
	return Standard_True;
}

Standard_Boolean
tnbLib::SectPx_CPtsMap::IsOnePar() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::SectPx_CPtsMap::IsMultiPar() const
{
	return Standard_False;
}