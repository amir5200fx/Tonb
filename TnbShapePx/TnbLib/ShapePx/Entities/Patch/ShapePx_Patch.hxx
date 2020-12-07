#pragma once
#ifndef _ShapePx_Patch_Header
#define _ShapePx_Patch_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_Section;

	class ShapePx_Patch
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_Section> theSection_;

	protected:

		ShapePx_Patch()
		{}

		ShapePx_Patch
		(
			const Standard_Integer theIndex
		);

		ShapePx_Patch
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		ShapePx_Patch
		(
			const std::shared_ptr<ShapePx_Section>& theSection
		);

		ShapePx_Patch
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<ShapePx_Section>& theSection
		);

	public:

		const auto& Section() const
		{
			return theSection_;
		}

		void SetSection(const std::shared_ptr<ShapePx_Section>& theSection)
		{
			theSection_ = theSection;
		}

	};
}

#endif // !_ShapePx_Patch_Header
