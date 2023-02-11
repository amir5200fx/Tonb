#pragma once
#ifndef _Model_CmpProfile_Header
#define _Model_CmpProfile_Header

#include <Model_ParamProfile.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	class Model_CmpProfile
		: public Model_ParamProfile
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Model_ParamProfile>> theProfiles_;


		// Private functions and operators [12/29/2022 Payvand]

		TnbModel_EXPORT void CheckProfiles();

		static TnbModel_EXPORT Standard_Boolean 
			IsContinuous
			(
				const std::shared_ptr<Model_ParamProfile>& thePr0,
				const std::shared_ptr<Model_ParamProfile>& thePr1
			);

		static TnbModel_EXPORT std::shared_ptr<Model_ParamProfile> 
			FindProfile
			(
				const Standard_Real x,
				const std::vector<std::shared_ptr<Model_ParamProfile>>&
			);

	protected:

		// default constructor [12/29/2022 Payvand]

		Model_CmpProfile()
		{}

	public:

		
		// constructors [12/29/2022 Payvand]

		Model_CmpProfile
		(
			const std::vector<std::shared_ptr<Model_ParamProfile>>& theProfiles
		)
			: theProfiles_(theProfiles)
		{
			CheckProfiles();
		}

		Model_CmpProfile
		(
			std::vector<std::shared_ptr<Model_ParamProfile>>&& theProfiles
		)
			: theProfiles_(std::move(theProfiles))
		{
			CheckProfiles();
		}

		// Public functions and operators [12/29/2022 Payvand]

		const auto& Profiles() const
		{
			return theProfiles_;
		}

		Standard_Boolean IsComposite() const override
		{
			return Standard_True;
		}

		TnbModel_EXPORT Standard_Real Lower() const override;
		TnbModel_EXPORT Standard_Real Upper() const override;

		TnbModel_EXPORT Standard_Real Value(const Standard_Real) const override;
		TnbModel_EXPORT std::vector<Standard_Real> Breacks() const override;
	};
}

#endif // !_Model_CmpProfile_Header
