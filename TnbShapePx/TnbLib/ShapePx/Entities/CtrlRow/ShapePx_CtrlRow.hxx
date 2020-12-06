#pragma once
#ifndef _ShapePx_CtrlRow_Header
#define _ShapePx_CtrlRow_Header

#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class ShapePx_CtrlRow
	{

		/*Private Data*/

		std::vector<Pnt2d> thePnts_;

	public:

		ShapePx_CtrlRow()
		{}

		ShapePx_CtrlRow(const std::vector<Pnt2d>& thePnts)
			: thePnts_(thePnts)
		{}

		ShapePx_CtrlRow(std::vector<Pnt2d>&& thePnts)
			: thePnts_(std::move(thePnts))
		{}


		auto NbPnts() const
		{
			return (Standard_Integer)thePnts_.size();
		}

		const auto& Pnts() const
		{
			return thePnts_;
		}

		auto& PntsRef()
		{
			return thePnts_;
		}
	};
}

#endif // !_ShapePx_CtrlRow_Header
