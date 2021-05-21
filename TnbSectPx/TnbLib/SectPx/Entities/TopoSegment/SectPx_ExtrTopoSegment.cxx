#include <SectPx_ExtrTopoSegment.hxx>

tnbLib::SectPx_ExtrTopoSegment::SectPx_ExtrTopoSegment
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_TopoSegment(theIndex, theName)
{
	//- empty body
}

tnbLib::SectPx_ExtrTopoSegment::SectPx_ExtrTopoSegment
(
	const std::shared_ptr<SectPx_BndPole>& thePole0,
	const std::shared_ptr<SectPx_BndPole>& thePole1
)
	: SectPx_TopoSegment(thePole0, thePole1)
{
	//- empty body
}

tnbLib::SectPx_ExtrTopoSegment::SectPx_ExtrTopoSegment
(
	std::shared_ptr<SectPx_BndPole>&& thePole0, 
	std::shared_ptr<SectPx_BndPole>&& thePole1
)
	: SectPx_TopoSegment(std::move(thePole0), std::move(thePole1))
{
	//- empty body
}

tnbLib::SectPx_ExtrTopoSegment::SectPx_ExtrTopoSegment
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<SectPx_BndPole>& thePole0,
	const std::shared_ptr<SectPx_BndPole>& thePole1
)
	: SectPx_TopoSegment(theIndex, theName, thePole0, thePole1)
{
	//- empty body
}

tnbLib::SectPx_ExtrTopoSegment::SectPx_ExtrTopoSegment
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<SectPx_BndPole>&& thePole0,
	std::shared_ptr<SectPx_BndPole>&& thePole1
)
	: SectPx_TopoSegment(theIndex, theName, std::move(thePole0), std::move(thePole1))
{
	//- empty body
}