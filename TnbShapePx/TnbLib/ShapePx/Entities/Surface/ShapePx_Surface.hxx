#pragma once
#ifndef _ShapePx_Surface_Header
#define _ShapePx_Surface_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_CurveQ;
	class ShapePx_Spacing;
	class ShapePx_Patch;

	class ShapePx_Surface
		: public ShapePx_Entity
	{

		/*private Data*/

		std::shared_ptr<ShapePx_Patch> thePatch_;
		std::shared_ptr<SectPx_CurveQ> theCurve_;
		std::shared_ptr<ShapePx_Spacing> theSpace_;	


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		//- default constructor

		ShapePx_Surface()
		{}


		//- constructors

		TnbShapePx_EXPORT ShapePx_Surface
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbShapePx_EXPORT ShapePx_Surface
		(
			const std::shared_ptr<ShapePx_Patch>& thePatch,
			const std::shared_ptr<SectPx_CurveQ>& theCurve,
			const std::shared_ptr<ShapePx_Spacing>& theSpace
		);

		TnbShapePx_EXPORT ShapePx_Surface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<ShapePx_Patch>& thePatch,
			const std::shared_ptr<SectPx_CurveQ>& theCurve, 
			const std::shared_ptr<ShapePx_Spacing>& theSpace
		);


		//- public functions and operators

		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& CurveQ() const
		{
			return theCurve_;
		}

		const auto& Spacing() const
		{
			return theSpace_;
		}

		void SetPatch
		(
			const std::shared_ptr<ShapePx_Patch>& thePatch
		)
		{
			thePatch_ = thePatch;
		}

		void SetCurve
		(
			const std::shared_ptr<SectPx_CurveQ>& theCurve
		)
		{
			theCurve_ = theCurve;
		}

		void SetSpacing
		(
			const std::shared_ptr<ShapePx_Spacing>& theSpace
		)
		{
			theSpace_ = theSpace;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_Surface);

#endif // !_ShapePx_Surface_Header
