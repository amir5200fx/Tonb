#pragma once
#ifndef _PtdModel_PropSectionNo1_Header
#define _PtdModel_PropSectionNo1_Header

#include <PtdModel_PropSection.hxx>

namespace tnbLib
{

	class PtdModel_PropSectionNo1
		: public PtdModel_PropSection
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_PropSection>(*this);
		}

	protected:

		//- default constructor

		PtdModel_PropSectionNo1()
		{}

	public:

		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropSectionNo1);

#endif // !_PtdModel_PropSectionNo1_Header
