#pragma once
#ifndef _ShapePx_CtrlNet_Header
#define _ShapePx_CtrlNet_Header

#include <ShapePx_CtrlRow.hxx>

namespace tnbLib
{

	class ShapePx_CtrlNet
	{

		/*Private Data*/

		std::vector<ShapePx_CtrlRow> theRows_;

	public:

		ShapePx_CtrlNet()
		{}

		ShapePx_CtrlNet
		(
			const std::vector<ShapePx_CtrlRow>& theRows
		)
			: theRows_(theRows)
		{}

		ShapePx_CtrlNet
		(
			std::vector<ShapePx_CtrlRow>&& theRows
		)
			: theRows_(std::move(theRows))
		{}


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
	};
}

#endif // !_ShapePx_CtrlNet_Header
