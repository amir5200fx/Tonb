#pragma once
#ifndef _ShapePx_Operator_Header
#define _ShapePx_Operator_Header

#include <Global_Done.hxx>
#include <ShapePx_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_CtrlNet;
	class SectPx_CurveQ;

	class ShapePx_Operator
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<SectPx_CurveQ> theCurve_;

		std::shared_ptr<ShapePx_CtrlNet> theNet_;

	protected:


		ShapePx_Operator()
		{}

		ShapePx_Operator
		(
			const std::shared_ptr<SectPx_CurveQ>& theCurve
		)
			: theCurve_(theCurve)
		{}


		auto& NetRef()
		{
			return theNet_;
		}

		void SetNet
		(
			const std::shared_ptr<ShapePx_CtrlNet>& theNet
		)
		{
			theNet_ = theNet;
		}

		void SetNet
		(
			std::shared_ptr<ShapePx_CtrlNet>&& theNet
		)
		{
			theNet_ = std::move(theNet);
		}

	public:

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& Net() const
		{
			return theNet_;
		}

		TnbShapePx_EXPORT virtual Standard_Boolean IsExtrude() const;

		TnbShapePx_EXPORT virtual Standard_Boolean IsRevolve() const;

		void SetCurve(const std::shared_ptr<SectPx_CurveQ>& theCurve)
		{
			theCurve_ = theCurve;
		}

	};
}

#endif // !_ShapePx_Operator_Header
