#pragma once
#ifndef _PtdModel_Profiles_Header
#define _PtdModel_Profiles_Header

#include <PtdModel_Entity.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Profile;

	class PtdModel_Profiles
		: public PtdModel_Entity
	{

		/*Private Data*/

		std::map<word, std::shared_ptr<PtdModel_Profile>> theProfiles_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_Profiles()
		{}

		inline PtdModel_Profiles
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

		void Import(const std::shared_ptr<PtdModel_Profile>&);
		void Import(std::shared_ptr<PtdModel_Profile>&&);
	};
}

#include <PtdModel_ProfilesI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_Profiles);

#endif // !_PtdModel_Profiles_Header
