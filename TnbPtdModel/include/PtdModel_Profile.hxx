#pragma once
#ifndef _PtdModel_Profile_Header
#define _PtdModel_Profile_Header

#include <PtdModel_PropEntity.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;

	class PtdModel_Profile
		: public PtdModel_PropEntity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_Profile>(*this);
		}

	protected:


		//- default constructor

		//- constructors

		template<class... _Types>
		PtdModel_Profile(_Types&&... _Args)
			: PtdModel_PropEntity(_Args...)
		{}

	public:

		//- public functions and operators

		virtual Standard_Integer NbParameters() const = 0;

		virtual std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_Profile);

#endif // !_PtdModel_Profile_Header
