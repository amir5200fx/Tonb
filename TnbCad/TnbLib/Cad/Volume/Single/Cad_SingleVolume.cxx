#include <Cad_SingleVolume.hxx>

#include <Cad_Solid.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Cad_SingleVolume::Check()
{
	if (Solid()->CalcVolume() <= 0.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the volume of the solid is negative!" << endl
			<< abort(FatalError);
	}
}

tnbLib::Cad_SingleVolume::Cad_SingleVolume
(
	const std::shared_ptr<Cad_Solid>& theSolid
)
	: theSolid_(theSolid)
{
	Check();
}

tnbLib::Cad_SingleVolume::Cad_SingleVolume
(
	std::shared_ptr<Cad_Solid>&& theSolid
)
	: theSolid_(std::move(theSolid))
{
	Check();
}

tnbLib::Cad_SingleVolume::Cad_SingleVolume
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Cad_Solid>& theSolid
)
	: Cad_Volume(theIndex, theName)
	, theSolid_(theSolid)
{
	Check();
}

tnbLib::Cad_SingleVolume::Cad_SingleVolume
(
	const Standard_Integer theIndex, 
	const word& theName,
	std::shared_ptr<Cad_Solid>&& theSolid
)
	: Cad_Volume(theIndex, theName)
	, theSolid_(std::move(theSolid))
{
	Check();
}

Standard_Integer 
tnbLib::Cad_SingleVolume::NbVolumes() const
{
	return Standard_Integer(1);
}

std::shared_ptr<tnbLib::Cad_Solid> 
tnbLib::Cad_SingleVolume::Volume(const Standard_Integer theIndex) const
{
	return theSolid_;
}

std::vector<std::shared_ptr<tnbLib::Cad_Solid>>
tnbLib::Cad_SingleVolume::Volumes() const
{
	std::vector<std::shared_ptr<Cad_Solid>> solids = { theSolid_ };
	return std::move(solids);
}