#pragma once
#ifndef _ShapePx_ExtrudeOp_Header
#define _ShapePx_ExtrudeOp_Header

#include <ShapePx_Operator.hxx>
#include <Geo_xDistb.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_ExtrudedPatch;

	class ShapePx_ExtrudeOp
		: public ShapePx_Operator
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_ExtrudedPatch> thePatch_;
		std::shared_ptr<Geo_xDistb> theDistb_;

	public:

		ShapePx_ExtrudeOp()
		{}


		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& Distribution() const
		{
			return theDistb_;
		}

		void Perform();

		Standard_Boolean IsExtrude() const override;
	};
}

#endif // !_ShapePx_ExtrudeOp_Header
