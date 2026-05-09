#pragma once
#ifndef _ShapePx_ExtrudeOp_Header
#define _ShapePx_ExtrudeOp_Header

#include <ShapePx_Operator.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_ExtrudedPatch;
	class SectPx_Spacing;

	class ShapePx_ExtrudeOp
		: public ShapePx_Operator
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_ExtrudedPatch> thePatch_;
		std::shared_ptr<SectPx_Spacing> theSpacing_;

		Standard_Integer theDegreeU_;

	public:

		ShapePx_ExtrudeOp()
			: theDegreeU_(3)
		{}


		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& Spacing() const
		{
			return theSpacing_;
		}

		auto DegreeU() const
		{
			return theDegreeU_;
		}

		TnbShapePx_EXPORT void Perform();

		TnbShapePx_EXPORT Standard_Boolean IsExtrude() const override;

		void SetPatch(const std::shared_ptr<ShapePx_ExtrudedPatch>& thePatch)
		{
			thePatch_ = thePatch;
		}

		void SetSpacing(const std::shared_ptr<SectPx_Spacing>& theSpacing)
		{
			theSpacing_ = theSpacing;
		}

		void SetDegreeU(const Standard_Integer d)
		{
			theDegreeU_ = d;
		}
	};
}

#endif // !_ShapePx_ExtrudeOp_Header
