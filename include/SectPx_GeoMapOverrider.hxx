#pragma once
#ifndef _SectPx_GeoMapOverrider_Header
#define _SectPx_GeoMapOverrider_Header

#include <SectPx_Overrider.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_GeoMap;

	class SectPx_GeoMapOverrider
		: public SectPx_Overrider
	{

		/*Private Data*/

		std::shared_ptr<SectPx_GeoMap> theGeoMap_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT Pnt2d CalcCoord() const override;

		const auto& GeoMap() const
		{
			return theGeoMap_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_GeoMapOverrider);

#endif // !_SectPx_GeoMapOverrider_Header
