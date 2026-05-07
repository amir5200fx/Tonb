#pragma once
#ifndef _PtdModel_Form_Header
#define _PtdModel_Form_Header

#include <PtdModel_PropEntity.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;

	class PtdModel_Form
		: public PtdModel_PropEntity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_PropEntity>(*this);
		}

	protected:


		//- default constructor

		//- constructors

		template<class... _Types>
		PtdModel_Form(_Types&&... _Args)
			: PtdModel_PropEntity(_Args...)
		{}


		//- protected functions and operators

		static TnbPtdModel_EXPORT std::map<word, std::shared_ptr<PtdModel_Par>> 
			RetrieveMap
			(
				std::shared_ptr<PtdModel_Par>*,
				const Standard_Integer nbPars
			);

	public:

		//- public functions and operators

		virtual Standard_Integer NbParameters() const = 0;

		//virtual std::shared_ptr<PtdModel_Par> Parameter(const word&) const = 0;

		virtual std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const = 0;

		//virtual void SetParameter(std::shared_ptr<PtdModel_Par>&&) = 0;

		static TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Par> 
			Parameter
			(
				const word&, 
				const std::map<word, std::shared_ptr<PtdModel_Par>>&
			);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_Form);

#endif // !_PtdModel_Form_Header
