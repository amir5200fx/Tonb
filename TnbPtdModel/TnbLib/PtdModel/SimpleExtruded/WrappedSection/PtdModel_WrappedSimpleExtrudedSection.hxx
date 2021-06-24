#pragma once
#ifndef _PtdModel_WrappedSimpleExtrudedSection_Header
#define _PtdModel_WrappedSimpleExtrudedSection_Header

#include <PtdModel_Section.hxx>

namespace tnbLib
{

	class PtdModel_WrappedSimpleExtrudedSection
		: public PtdModel_Section
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel_Section>(*this);
		}

	public:

		//- default constructor
		PtdModel_WrappedSimpleExtrudedSection()
		{}


		//- constructors


	public:


	};
}

#include <PtdModel_WrappedSimpleExtrudedSectionI.hxx>

#endif // !_PtdModel_WrappedSimpleExtrudedSection_Header
