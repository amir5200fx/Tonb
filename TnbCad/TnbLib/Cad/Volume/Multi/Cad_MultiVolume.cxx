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

Standard_Integer tnbLib::Cad_MultiVolume::IsPairedSurface(const Standard_Integer theIndex) const
{
	auto iter = thePairs_.find(theIndex);
	if (iter IS_EQUAL thePairs_.end())
	{
		return 0;
	}
	return iter->second;
}

Standard_Integer tnbLib::Cad_MultiVolume::NbPairs() const
{
	return static_cast<Standard_Integer>(thePairs_.size());
}

void tnbLib::Cad_MultiVolume::SetPairs(const PairedEntity& theSurfaces)
{
	if (NOT thePairs_.insert({theSurfaces.surf0, theSurfaces.surf1}).second)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " duplicate data." << endl
			<< " surf0: " << theSurfaces.surf0 << endl
			<< " surf1: " << theSurfaces.surf1 << endl
			<< abort(FatalError);
	}
	if (NOT thePairs_.insert({theSurfaces.surf1, theSurfaces.surf0}).second)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " duplicate data." << endl
			<< " surf0: " << theSurfaces.surf0 << endl
			<< " surf1: " << theSurfaces.surf1 << endl
			<< abort(FatalError);
	}
}

Standard_Integer 
tnbLib::Cad_MultiVolume::NbVolumes() const
{
	return static_cast<Standard_Integer>(theSolids_.size());
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

std::vector<std::shared_ptr<tnbLib::TModel_Surface>>
tnbLib::Cad_MultiVolume::RetrieveSurfaces() const
{
	std::vector<std::shared_ptr<TModel_Surface>> tot_surfaces;
	for (const auto& x: theSolids_)
	{
		for (const auto& f: x->RetrieveFaces())
		{
			tot_surfaces.emplace_back(f);
		}
	}
	return std::move(tot_surfaces);
}
