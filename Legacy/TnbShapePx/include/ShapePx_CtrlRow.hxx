#pragma once
#ifndef _ShapePx_CtrlRow_Header
#define _ShapePx_CtrlRow_Header

#include <Pnt2d.hxx>
#include <Global_Serialization.hxx>
#include <ShapePx_Module.hxx>

#include <vector>

namespace tnbLib
{

	class ShapePx_CtrlRow
	{

		/*Private Data*/

		std::vector<std::pair<Pnt2d, Standard_Real>> thePnts_;

		Standard_Real theX_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		ShapePx_CtrlRow()
			: theX_(0)
		{}

		ShapePx_CtrlRow
		(
			const std::vector<std::pair<Pnt2d, Standard_Real>>& thePnts,
			const Standard_Real x
		)
			: thePnts_(thePnts)
			, theX_(x)
		{}

		ShapePx_CtrlRow
		(
			std::vector<std::pair<Pnt2d, Standard_Real>>&& thePnts,
			const Standard_Real x
		)
			: thePnts_(std::move(thePnts))
			, theX_(x)
		{}


		auto NbPnts() const
		{
			return (Standard_Integer)thePnts_.size();
		}

		const auto& Pnts() const
		{
			return thePnts_;
		}

		auto X() const
		{
			return theX_;
		}

		auto& PntsRef()
		{
			return thePnts_;
		}

		void SetX
		(
			const Standard_Real x
		)
		{
			theX_ = x;
		}
	};
}

#endif // !_ShapePx_CtrlRow_Header
