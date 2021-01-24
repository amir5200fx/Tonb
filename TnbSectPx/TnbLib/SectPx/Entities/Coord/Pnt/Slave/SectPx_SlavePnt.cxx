#include <SectPx_SlavePnt.hxx>

tnbLib::SectPx_SlavePnt::SectPx_SlavePnt
(
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: theMaster_(theMaster)
{
	// empty body
}

tnbLib::SectPx_SlavePnt::SectPx_SlavePnt
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: SectPx_TPnt(theIndex)
	, theMaster_(theMaster)
{
	// empty body
}

tnbLib::SectPx_SlavePnt::SectPx_SlavePnt
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
	: SectPx_TPnt(theIndex, theName)
	, theMaster_(theMaster)
{
	// empty body
}

void tnbLib::SectPx_SlavePnt::SetMaster
(
	const std::shared_ptr<SectPx_MasterPnt>& theMaster
)
{
	theMaster_ = theMaster;
}

Standard_Boolean 
tnbLib::SectPx_SlavePnt::IsEmpty() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_SlavePnt::IsSlave() const
{
	return Standard_True;
}