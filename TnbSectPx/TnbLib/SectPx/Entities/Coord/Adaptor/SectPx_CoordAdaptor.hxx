#pragma once
#ifndef _SectPx_CoordAdaptor_Header
#define _SectPx_CoordAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	class SectPx_GeoMap;

	class SectPx_CoordAdaptor
	{

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<SectPx_GeoMap>> theGeoMaps_;


		/*Private functions and operators*/

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		//- default constructor

		SectPx_CoordAdaptor()
		{}

	public:

		typedef std::map<Standard_Integer, std::weak_ptr<SectPx_GeoMap>>::const_iterator mapIter;

		auto NbGeoMaps() const
		{
			return (Standard_Integer)theGeoMaps_.size();
		}

		auto HasGeoMap() const
		{
			return (Standard_Boolean)NbGeoMaps();
		}

		const auto& GeoMaps() const
		{
			return theGeoMaps_;
		}

		auto EndGeoMap() const
		{
			return theGeoMaps_.end();
		}

		TnbSectPx_EXPORT void ImportToGeoMaps(const std::shared_ptr<SectPx_GeoMap>& theMap);

		TnbSectPx_EXPORT mapIter SelectGeoMap(const Standard_Integer theIndex);
		TnbSectPx_EXPORT std::shared_ptr<SectPx_GeoMap> RemoveGeoMap(const mapIter&);
		TnbSectPx_EXPORT std::shared_ptr<SectPx_GeoMap> RemoveGeoMap(const Standard_Integer theIndex);
	};
}

#endif // !_SectPx_CoordAdaptor_Header
