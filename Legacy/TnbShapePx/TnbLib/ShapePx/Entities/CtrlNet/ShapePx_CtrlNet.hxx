#pragma once
#ifndef _ShapePx_CtrlNet_Header
#define _ShapePx_CtrlNet_Header

#include <ShapePx_CtrlRow.hxx>
#include <ShapePx_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class ShapePx_CtrlNet
	{

		/*Private Data*/

		std::vector<ShapePx_CtrlRow> theRows_;
		std::vector<std::pair<Standard_Real, Standard_Integer>> theKnots_;

		Standard_Integer theRowDeg_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		ShapePx_CtrlNet()
			: theRowDeg_(3)
		{}

		ShapePx_CtrlNet
		(
			const std::vector<ShapePx_CtrlRow>& theRows
		)
			: theRows_(theRows)
			, theRowDeg_(3)
		{}

		ShapePx_CtrlNet
		(
			std::vector<ShapePx_CtrlRow>&& theRows
		)
			: theRows_(std::move(theRows))
			, theRowDeg_(3)
		{}

		auto RowDegree() const
		{
			return theRowDeg_;
		}

		auto NbColumns() const
		{
			if (theRows_.empty())
			{
				return (Standard_Integer)0;
			}
			return theRows_[0].NbPnts();
		}

		auto NbRows() const
		{
			return (Standard_Integer)theRows_.size();
		}

		const auto& Rows() const
		{
			return theRows_;
		}

		auto& RowsRef()
		{
			return theRows_;
		}

		const auto& Knots() const
		{
			return theKnots_;
		}

		auto& KnotsRef()
		{
			return theKnots_;
		}

		void SetRowDegree(const Standard_Integer theDeg)
		{
			theRowDeg_ = theDeg;
		}
	};
}

#endif // !_ShapePx_CtrlNet_Header
