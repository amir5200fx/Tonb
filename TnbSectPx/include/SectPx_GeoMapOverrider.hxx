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

	public:

		static const char* typeName_;

		word RegObjTypeName() const override;

		Pnt2d CalcCoord() const override;

		const auto& GeoMap() const
		{
			return theGeoMap_;
		}
	};
}

#endif // !_SectPx_GeoMapOverrider_Header
