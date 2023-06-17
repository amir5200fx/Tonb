#include <Cad_MultiVolume.hxx>

#include <Cad_Solid.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad_MultiVolume::Check()
{
	for (const auto& x : theSolids_)
	{
		if (x->CalcVolume() <= 0.0)
		{
			FatalErrorIn(FunctionSIG)
				<< "the volume of the solid is minus!" << endl
				<< abort(FatalError);
		}
	}
}

tnbLib::Cad_MultiVolume::Cad_MultiVolume
(
	const std::vector<std::shared_ptr<Cad_Solid>>& theSolids
)
	: theSolids_(theSolids)
{
	Check();
}

tnbLib::Cad_MultiVolume::Cad_MultiVolume
(
	std::vector<std::shared_ptr<Cad_Solid>>&& theSolids
)
	: theSolids_(std::move(theSolids))
{
	Check();
}

tnbLib::Cad_MultiVolume::Cad_MultiVolume
(
	const Standard_Integer theIndex, 
	const word& theName, 
	const std::vector<std::shared_ptr<Cad_Solid>>& theSolids
)
	: Cad_Volume(theIndex, theName)
	, theSolids_(theSolids)
{
	Check();
}

tnbLib::Cad_MultiVolume::Cad_MultiVolume
(
	const Standard_Integer theIndex,
	const word& theName,
	std::vector<std::shared_ptr<Cad_Solid>>&& theSolids
)
	: Cad_Volume(theIndex, theName)
	, theSolids_(std::move(theSolids))
{
	Check();
}

Standard_Integer 
tnbLib::Cad_MultiVolume::NbVolumes() const
{
	return Standard_Integer(theSolids_.size());
}

std::shared_ptr<tnbLib::Cad_Solid> 
tnbLib::Cad_MultiVolume::Volume(const Standard_Integer theIndex) const
{
	return theSolids_.at(theIndex);
}

std::vector<std::shared_ptr<tnbLib::Cad_Solid>> 
tnbLib::Cad_MultiVolume::Volumes() const
{
	return theSolids_;
}