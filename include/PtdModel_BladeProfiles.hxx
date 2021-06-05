#pragma once
#ifndef _PtdModel_BladeProfiles_Header
#define _PtdModel_BladeProfiles_Header

#include <PtdModel_PropEntity.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeProfile;

	class PtdModel_BladeProfiles
		: public PtdModel_PropEntity
	{

		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_BladeProfile>> theProfiles_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_BladeProfiles()
		{}

		inline PtdModel_BladeProfiles
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		//- constructors


		//- public functions and operators

		inline Standard_Integer NbProfiles() const;

		const auto& Profiles() const
		{
			return theProfiles_;
		}

		void Import(const std::shared_ptr<PtdModel_BladeProfile>&);
		void Import(std::shared_ptr<PtdModel_BladeProfile>&&);
	};
}

#include <PtdModel_BladeProfilesI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_BladeProfiles);

#endif // !_PtdModel_BladeProfiles_Header
