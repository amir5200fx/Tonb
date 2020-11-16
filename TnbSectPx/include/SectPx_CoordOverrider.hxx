#pragma once
#ifndef _SectPx_CoordOverrider_Header
#define _SectPx_CoordOverrider_Header


#include <SectPx_Overrider.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;

	class SectPx_CoordOverrider
		: public SectPx_Overrider
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Coord> theCoord_;

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT Pnt2d CalcCoord() const override;

		const auto& Coord() const
		{
			return theCoord_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_CoordOverrider);

#endif // !_SectPx_CoordOverrider_Header
