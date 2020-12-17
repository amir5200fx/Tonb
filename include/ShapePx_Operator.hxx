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

	class ShapePx_Operator
		: public Global_Done
	{

		/*Private Data*/

		std::vector<std::shared_ptr<ShapePx_CtrlNet>> theNets_;

	protected:


		ShapePx_Operator()
		{}


		auto& NetRef()
		{
			return theNets_;
		}

		void SetNet
		(
			const std::vector<std::shared_ptr<ShapePx_CtrlNet>>& theNets
		)
		{
			theNets_ = theNets;
		}

		void SetNets
		(
			std::vector<std::shared_ptr<ShapePx_CtrlNet>>&& theNets
		)
		{
			theNets_ = std::move(theNets);
		}

	public:


		const auto& Nets() const
		{
			return theNets_;
		}

		TnbShapePx_EXPORT virtual Standard_Boolean IsExtrude() const;

		TnbShapePx_EXPORT virtual Standard_Boolean IsRevolve() const;
	};
}

#endif // !_ShapePx_Operator_Header
