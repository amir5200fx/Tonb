#pragma once
#ifndef _SectPx_Segment_Header
#define _SectPx_Segment_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_SegmentAdaptor.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pole;
	class Pnt2d;


	class SectPx_Segment
		: public SectPx_RegObj
		, public SectPx_SegmentAdaptor
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Pole> theP0_;
		std::shared_ptr<SectPx_Pole> theP1_;

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		SectPx_Segment()
		{}

		TnbSectPx_EXPORT SectPx_Segment
		(
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		TnbSectPx_EXPORT SectPx_Segment
		(
			std::shared_ptr<SectPx_Pole>&& theP0,
			std::shared_ptr<SectPx_Pole>&& theP1
		);

		TnbSectPx_EXPORT SectPx_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		TnbSectPx_EXPORT SectPx_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		TnbSectPx_EXPORT Standard_Integer
			GetIndex(const std::shared_ptr<SectPx_Pole>& theP) const;

		TnbSectPx_EXPORT Pnt2d CalcMidCoord() const;

		TnbSectPx_EXPORT const std::shared_ptr<SectPx_Pole>& Pole(const Standard_Integer theIndex) const;

		TnbSectPx_EXPORT std::shared_ptr<SectPx_Pole> Other(const std::shared_ptr<SectPx_Pole>& theP) const;

		const auto& Pole0() const
		{
			return theP0_;
		}

		const auto& Pole1() const
		{
			return theP1_;
		}

		void SetPole0(const std::shared_ptr<SectPx_Pole>& theP0)
		{
			theP0_ = theP0;
		}

		void SetPole1(const std::shared_ptr<SectPx_Pole>& theP1)
		{
			theP1_ = theP1;
		}

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsSegment() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_Segment);

#endif // !_SectPx_Segment_Header
