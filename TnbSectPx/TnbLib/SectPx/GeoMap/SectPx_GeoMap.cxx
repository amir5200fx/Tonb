#include <SectPx_GeoMap.hxx>

#include <SectPx_Coord.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::SectPx_GeoMap::~SectPx_GeoMap()
{
	auto coords = RetrieveCoords();
	for (const auto& x : coords)
	{
#ifdef _DEBUG
		if (!x)
		{
			std::cout << "null pointer has been detected!" << std::endl;
			std::exit(1);
		}
#endif // _DEBUG

		auto iter = x->SelectGeoMap(Index());
		if (iter NOT_EQUAL x->EndGeoMap())
		{
			auto geoMap = x->RemoveGeoMap(iter);
#ifdef _DEBUG
			if (!x)
			{
				std::cout << "null pointer has been detected!" << std::endl;
				std::exit(1);
			}
#endif // _DEBUG
#ifdef _DEBUG
			if (geoMap NOT_EQUAL std::dynamic_pointer_cast<SectPx_GeoMap>(This()))
			{
				std::cout << "contradictory data has been detected!" << std::endl;
				std::exit(1);
					
			}
#endif // _DEBUG
		}
		else
		{
			std::cout << "contradictory data has been detected!" << std::endl;
			std::cout << "this geoMap uses a unregistered coord!" << std::endl;
			std::exit(1);
		}
	}
}

Standard_Boolean
tnbLib::SectPx_GeoMap::IsGeoMap() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_GeoMap::IsFrameRegObj() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_GeoMap::RegObjType() const
{
	return sectPxLib::regObjType::geoMap;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Coord>> tnbLib::SectPx_GeoMap::RetrieveCoords() const
{
	return std::vector<std::shared_ptr<SectPx_Coord>>();
}