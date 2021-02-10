#pragma once
#ifndef _ShapePx_ExtrudedPatch_Header
#define _ShapePx_ExtrudedPatch_Header

#include <ShapePx_Patch.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_Profile;
	class ShapePx_ParValue;

	class ShapePx_ExtrudedPatch
		: public ShapePx_Patch
	{

		/*Private Data*/

		std::map
			<
			Standard_Integer, 
			std::shared_ptr<ShapePx_Profile>
			> theParToProfile_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:


		//- default constructor

		ShapePx_ExtrudedPatch()
		{}


		//- constructors

		TnbShapePx_EXPORT ShapePx_ExtrudedPatch
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbShapePx_EXPORT ShapePx_ExtrudedPatch
		(
			const std::shared_ptr<SectPx_Registry>& theRegistry,
			const std::shared_ptr<ShapePx_Section>& theSect
		);

		TnbShapePx_EXPORT ShapePx_ExtrudedPatch
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_Registry>& theRegistry,
			const std::shared_ptr<ShapePx_Section>& theSect
		);


		TnbShapePx_EXPORT Standard_Boolean IsExtruded() const override;


		//- public functions and operators

		auto NbSectionParameters() const
		{
			return (Standard_Integer)theParToProfile_.size();
		}

		const auto& SectionParameterToProfileMap() const
		{
			return theParToProfile_;
		}

		//TnbShapePx_EXPORT Standard_Real MinLower() const;

		//TnbShapePx_EXPORT Standard_Real MaxUpper() const;

		TnbShapePx_EXPORT std::shared_ptr<ShapePx_Profile>
			RemoveProfile
			(
				const Standard_Integer theParIndex
			);

		TnbShapePx_EXPORT std::shared_ptr<ShapePx_ParValue> 
			RetrieveParValues(const Standard_Real x) const;

		TnbShapePx_EXPORT void ImportProfileForParameter
		(
			const Standard_Integer theParIndex, 
			const std::shared_ptr<ShapePx_Profile>& theProfile
		);

		TnbShapePx_EXPORT void ImportProfileForParameter
		(
			const Standard_Integer theParIndex,
			std::shared_ptr<ShapePx_Profile>&& theProfile
		);

		TnbShapePx_EXPORT void UpdateProfiles();
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_ExtrudedPatch);

#endif // !_ShapePx_ExtrudedPatch_Header
