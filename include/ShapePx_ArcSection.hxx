#pragma once
#ifndef _ShapePx_ArcSection_Header
#define _ShapePx_ArcSection_Header

#include <ShapePx_ConicSection.hxx>
#include <ShapePx_ArcSectionIterInfo.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class ShapePx_ArcSection
		: public ShapePx_ConicSection
	{


	private:

		/*Private Data*/

		std::shared_ptr<ShapePx_ArcSectionIterInfo> theIterInfo_;

		Standard_Real theTolerance_;



	public:

		static TnbShapePx_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbShapePx_EXPORT const std::shared_ptr<ShapePx_ArcSectionIterInfo> DEFAULT_ITER_INFO;

		//- default constructor

		ShapePx_ArcSection()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theIterInfo_(DEFAULT_ITER_INFO)
		{}


		//- constructors

		ShapePx_ArcSection
		(
			const std::shared_ptr<ShapePx_TopoSection>& theSection
		)
			: ShapePx_ConicSection(theSection)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theIterInfo_(DEFAULT_ITER_INFO)
		{}


		const auto& IterInfo() const
		{
			return theIterInfo_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		TnbShapePx_EXPORT void Perform() override;

		void SetIterInfo(const std::shared_ptr<ShapePx_ArcSectionIterInfo>& theInfo)
		{
			theIterInfo_ = theInfo;
		}

	};
}

#endif // !_ShapePx_ArcSection_Header
