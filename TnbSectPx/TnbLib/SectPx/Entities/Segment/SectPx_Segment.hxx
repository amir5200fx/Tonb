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

		static const char* typeName_;

		SectPx_Segment()
		{}

		SectPx_Segment
		(
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		SectPx_Segment
		(
			std::shared_ptr<SectPx_Pole>&& theP0,
			std::shared_ptr<SectPx_Pole>&& theP1
		);

		SectPx_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		SectPx_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Pole>& theP0,
			const std::shared_ptr<SectPx_Pole>& theP1
		);

		Standard_Integer
			GetIndex(const std::shared_ptr<SectPx_Pole>& theP) const;

		Pnt2d CalcMidCoord() const;

		const std::shared_ptr<SectPx_Pole>& Pole(const Standard_Integer theIndex) const;

		std::shared_ptr<SectPx_Pole> Other(const std::shared_ptr<SectPx_Pole>& theP) const;

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

		word RegObjTypeName() const override;

		sectPxLib::regObjType RegObjType() const override;

		Standard_Boolean IsSegment() const override;
	};
}

#endif // !_SectPx_Segment_Header
