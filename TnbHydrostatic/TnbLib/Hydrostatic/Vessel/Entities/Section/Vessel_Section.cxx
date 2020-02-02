#include <Vessel_Section.hxx>

#include <error.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::Vessel_Section::NbOuters() const
{
	if (NOT theOuter_)
		return 0;
	return (Standard_Integer)theOuter_->size();
}

Standard_Integer tnbLib::Vessel_Section::NbInners() const
{
	if (NOT theInner_)
		return 0;
	return (Standard_Integer)theInner_->size();
}