#pragma once
#ifndef _Airfoil_OffsetProfile_Header
#define _Airfoil_OffsetProfile_Header

#include <Airfoil_Module.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [10/30/2022 Amir]

	class Airfoil_OffsetProfile
		: public Global_Done
	{

		/*Private Data*/

		std::vector<std::pair<Standard_Real, Standard_Real>> theQs_;


		// Private functions and operators [10/30/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theQs_;
		}

	protected:

		// default constructor [10/30/2022 Amir]

		Airfoil_OffsetProfile()
		{}


	public:

		// public functions and operators [10/30/2022 Amir]

		const auto& Qs() const
		{
			return theQs_;
		}

		virtual Standard_Real Value(const Standard_Real x) const = 0;
		virtual void Perform() = 0;

		std::vector<Standard_Real> RetrieveXc() const;

		void SetQs(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs)
		{
			theQs_ = theQs;
		}
		
		void SetQs(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs)
		{
			theQs_ = std::move(theQs);
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Airfoil_OffsetProfile);

#endif // !_Airfoil_OffsetProfile_Header
