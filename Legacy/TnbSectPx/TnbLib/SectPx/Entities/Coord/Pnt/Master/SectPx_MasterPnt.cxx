#include <SectPx_MasterPnt.hxx>

#include <SectPx_Overrider.hxx>

Standard_Boolean 
tnbLib::SectPx_MasterPnt::IsComponent() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_MasterPnt::IsGeoField() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_MasterPnt::IsOffset() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_MasterPnt::IsMaster() const
{
	return Standard_True;
}

void tnbLib::SectPx_MasterPnt::SetOverrider
(
	const std::shared_ptr<SectPx_Overrider>& theOverrider
)
{
	if (NOT theOverrider_)
	{
		std::shared_ptr<SectPx_MasterPnt> null;
		theOverrider_->SetPnt(null);
	}

	theOverrider_ = theOverrider;

	if (theOverrider)
	{		
		theOverrider->SetPnt(std::dynamic_pointer_cast<SectPx_MasterPnt>(This()));
	}
}