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


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	protected:

		ShapePx_Patch()
		{}

		TnbShapePx_EXPORT ShapePx_Patch
		(
			const Standard_Integer theIndex
		);

		TnbShapePx_EXPORT ShapePx_Patch
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbShapePx_EXPORT ShapePx_Patch
		(
			const std::shared_ptr<ShapePx_Section>& theSection
		);

		TnbShapePx_EXPORT ShapePx_Patch
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

		TnbShapePx_EXPORT virtual Standard_Boolean IsExtruded() const;

		TnbShapePx_EXPORT virtual Standard_Boolean IsRevolved() const;
	};
}

#endif // !_ShapePx_Patch_Header
