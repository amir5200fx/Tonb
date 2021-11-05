#pragma once
#ifndef _ShapePx_Patch_Header
#define _ShapePx_Patch_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_Section;
	class SectPx_Limits;
	class SectPx_Registry;

	class ShapePx_Patch
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<ShapePx_Section> theSection_;
		std::shared_ptr<SectPx_Registry> theRegistry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	protected:

		//- default constructor

		ShapePx_Patch()
		{}


		//- constructors

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
			const std::shared_ptr<SectPx_Registry>& theRegistry,
			const std::shared_ptr<ShapePx_Section>& theSection
		);

		TnbShapePx_EXPORT ShapePx_Patch
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<SectPx_Registry>& theRegistry,
			const std::shared_ptr<ShapePx_Section>& theSection
		);

	public:

		static TnbShapePx_EXPORT const std::string extension;

		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		const auto& Registry() const
		{
			return theRegistry_;
		}

		void LoadSection
		(
			const std::shared_ptr<ShapePx_Section>& theSection
		)
		{
			theSection_ = theSection;
		}

		void LoadRegistry
		(
			const std::shared_ptr<SectPx_Registry>& theReg
		)
		{
			theRegistry_ = theReg;
		}

		TnbShapePx_EXPORT virtual Standard_Boolean IsExtruded() const;

		TnbShapePx_EXPORT virtual Standard_Boolean IsRevolved() const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ShapePx_Patch);

#endif // !_ShapePx_Patch_Header
