#pragma once
#ifndef _ShapePx_Section_Header
#define _ShapePx_Section_Header

#include <ShapePx_Entity.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FrameRegistry;
	class SectPx_TopoSegment;
	class SectPx_CurveQ;
	class SectPx_Par;
	class ShapePx_ParValue;

	class ShapePx_Section
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FrameRegistry> theRegistry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		//- default constructor

		ShapePx_Section()
		{}

		//- constructors

		TnbShapePx_EXPORT ShapePx_Section
		(
			const Standard_Integer theIndex
		);

		TnbShapePx_EXPORT ShapePx_Section
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbShapePx_EXPORT ShapePx_Section
		(
			const std::shared_ptr<SectPx_FrameRegistry>& theReg
		);

		TnbShapePx_EXPORT ShapePx_Section
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<SectPx_FrameRegistry>& theReg
		);


		//- public functions and operators

		const auto& Registry() const
		{
			return theRegistry_;
		}

		TnbShapePx_EXPORT Standard_Integer 
			NbProfiles() const;

		TnbShapePx_EXPORT Standard_Integer 
			NbCurveQs() const;

		TnbShapePx_EXPORT std::vector<std::shared_ptr<SectPx_Par>> 
			RetrieveParameters() const;

		TnbShapePx_EXPORT std::vector<std::shared_ptr<SectPx_TopoSegment>> 
			RetrieveProfiles() const;

		TnbShapePx_EXPORT std::vector<std::shared_ptr<SectPx_CurveQ>>
			RetrieveCurveQs() const;

		void SetRegistry(const std::shared_ptr<SectPx_FrameRegistry>& theReg)
		{
			theRegistry_ = theReg;
		}

		TnbShapePx_EXPORT void 
			SetValues
			(
				const std::shared_ptr<ShapePx_ParValue>& theValues
			);

	};
}

#endif // !_ShapePx_Section_Header
