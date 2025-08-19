#include <SectPx_OffsetProfile.hxx>

#include <SectPx_Offset.hxx>

const char* tnbLib::SectPx_OffsetProfile::typeName_("offset profile");

tnbLib::SectPx_OffsetProfile::SectPx_OffsetProfile
(
	const Standard_Integer theIndex
)
	: SectPx_RegObj(theIndex)
{
	// empty body
}

tnbLib::SectPx_OffsetProfile::SectPx_OffsetProfile
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_RegObj(theIndex, theName)
{
	// empty body
}

Standard_Boolean 
tnbLib::SectPx_OffsetProfile::IsOffsetProfile() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_OffsetProfile::IsFrameRegObj() const
{
	return Standard_True;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_OffsetProfile::RegObjType() const
{
	return sectPxLib::regObjType::offsetProfile;
}

tnbLib::word 
tnbLib::SectPx_OffsetProfile::RegObjTypeName() const
{
	return typeName_;
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_OffsetProfile::RetrievePoints() const
{
	std::vector<Pnt2d> pnts;
	pnts.reserve(NbOffsets());
	for (const auto& x : theOffsets_)
	{
		auto pt = Pnt2d(x->xCoord(), x->yCoord());
		pnts.push_back(std::move(pt));
	}
	return std::move(pnts);
}

void tnbLib::SectPx_OffsetProfile::Import
(
	const std::shared_ptr<SectPx_Offset>& theQ
)
{
	theOffsets_.push_back(theQ);
}