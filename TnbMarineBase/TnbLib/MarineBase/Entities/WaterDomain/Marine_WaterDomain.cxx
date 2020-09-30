#include <Marine_WaterDomain.hxx>

#include <Marine_Section.hxx>
#include <Marine_Water.hxx>
#include <Marine_Wave.hxx>

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<Marine_Water>& theWater,
	const std::shared_ptr<Marine_Wave>& theWave
)
	: Marine_CoordinatedEntity(0, "water domain")
	, theDomain_(theDomain)
	, theWater_(theWater)
	, theWave_(theWave)
{
	// empty body
}

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	std::shared_ptr<Marine_Domain>&& theDomain, 
	std::shared_ptr<Marine_Water>&& theWater,
	std::shared_ptr<Marine_Wave>&& theWave
)
	: Marine_CoordinatedEntity(0, "water domain")
	, theDomain_(std::move(theDomain))
	, theWater_(std::move(theWater))
	, theWave_(std::move(theWave))
{
	// empty body
}

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<Marine_Water>& theWater,
	const std::shared_ptr<Marine_Wave>& theWave
)
	: Marine_CoordinatedEntity(theIndex, theName)
	, theDomain_(theDomain)
	, theWater_(theWater)
	, theWave_(theWave)
{
	// empty body
}

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Marine_Domain>&& theDomain,
	std::shared_ptr<Marine_Water>&& theWater, 
	std::shared_ptr<Marine_Wave>&& theWave
)
	: Marine_CoordinatedEntity(theIndex, theName)
	, theDomain_(std::move(theDomain))
	, theWater_(std::move(theWater))
	, theWave_(std::move(theWave))
{
	// empty body
}

void tnbLib::Marine_WaterDomain::ExportToPlt
(
	OFstream & File
) const
{
	Debug_Null_Pointer(Water());
	for (const auto& x : Water()->Sections())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}