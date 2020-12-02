#include <SectPx_TopoSegment.hxx>

const char* tnbLib::SectPx_TopoSegment::typeName_ = "topoSegment";

tnbLib::SectPx_TopoSegment::SectPx_TopoSegment
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: SectPx_RegObj(theIndex, theName)
{
	// empty body
}

tnbLib::SectPx_TopoSegment::SectPx_TopoSegment
(
	const std::shared_ptr<SectPx_BndPole>& thePole0, 
	const std::shared_ptr<SectPx_BndPole>& thePole1
)
	: thePole0_(thePole0)
	, thePole1_(thePole1)
{
	// empty body
}

tnbLib::SectPx_TopoSegment::SectPx_TopoSegment
(
	std::shared_ptr<SectPx_BndPole>&& thePole0,
	std::shared_ptr<SectPx_BndPole>&& thePole1
)
	: thePole0_(std::move(thePole0))
	, thePole1_(std::move(thePole1))
{
	//- empty body
}

tnbLib::SectPx_TopoSegment::SectPx_TopoSegment
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<SectPx_BndPole>& thePole0, 
	const std::shared_ptr<SectPx_BndPole>& thePole1
)
	: SectPx_RegObj(theIndex, theName)
	, thePole0_(thePole0)
	, thePole1_(thePole1)
{
	// empty body
}

tnbLib::SectPx_TopoSegment::SectPx_TopoSegment
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<SectPx_BndPole>&& thePole0, 
	std::shared_ptr<SectPx_BndPole>&& thePole1
)
	: SectPx_RegObj(theIndex, theName)
	, thePole0_(std::move(thePole0))
	, thePole1_(std::move(thePole1))
{
	// empty body
}

tnbLib::word 
tnbLib::SectPx_TopoSegment::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_TopoSegment::RegObjType() const
{
	return sectPxLib::regObjType::topoSegment;
}

Standard_Boolean 
tnbLib::SectPx_TopoSegment::IsTopoSegment() const
{
	return Standard_True;
}