#pragma once
#ifndef _ShapePx_ConicSection_Header
#define _ShapePx_ConicSection_Header

#include <Global_Done.hxx>
#include <ShapePx_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSection;

	class ShapePx_ConicSection
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_TopoSection> theSection_;

		Standard_Real theWeight_;

	public:

		//- default constructor

		ShapePx_ConicSection()
		{}


		//- constructors

		ShapePx_ConicSection
		(
			const std::shared_ptr<ShapePx_TopoSection>& theSection
		)
			: theSection_(theSection)
		{}


		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		auto BaseWeight() const
		{
			return theWeight_;
		}

		TnbShapePx_EXPORT void Perform();

		void LoadSection
		(
			const std::shared_ptr<ShapePx_TopoSection>& theSection
		)
		{
			theSection_ = theSection;
		}

		void SetBaseWeight(const Standard_Real x)
		{
			theWeight_ = x;
		}
	};
}

#endif // !_ShapePx_ConicSection_Header
