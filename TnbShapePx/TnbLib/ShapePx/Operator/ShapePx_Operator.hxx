#pragma once
#ifndef _ShapePx_Operator_Header
#define _ShapePx_Operator_Header

#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_CtrlNet;

	class ShapePx_Operator
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_CtrlNet> theNet_;

	protected:


		ShapePx_Operator()
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


		const auto& Net() const
		{
			return theNet_;
		}

		virtual Standard_Boolean IsExtrude() const;

		virtual Standard_Boolean IsRevolve() const;
	};
}

#endif // !_ShapePx_Operator_Header
