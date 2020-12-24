#pragma once
#ifndef _SectPx_CurveQMaker_Header
#define _SectPx_CurveQMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pole;
	class SectPx_FrameRegistry;

	namespace maker
	{


		class CurveQ
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/



		public:

			explicit CurveQ
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pole>
				SelectBoundary
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pole>
				SelectSlider
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_CurveQ>
				SelectCurve
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer 
				CreateCurve
				(
					const std::shared_ptr<SectPx_Pole>& thePole0,
					const std::shared_ptr<SectPx_Pole>& thePole1
				);
		};
	}
}

#endif // !_SectPx_CurveQMaker_Header
