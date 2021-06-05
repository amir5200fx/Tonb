#pragma once
#ifndef _PtdModel_WrappedBladeSection_Header
#define _PtdModel_WrappedBladeSection_Header

#include <PtdModel_BladeSection.hxx>

namespace tnbLib
{

	class PtdModel_WrappedBladeSection
		: public PtdModel_BladeSection
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_BladeSection>(*this);
		}

	public:

		//- default constructor

		PtdModel_WrappedBladeSection()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_WrappedBladeSection
		(
			const std::vector<Pnt3d>& theFace, 
			const std::vector<Pnt3d>& theBack
		);

		TnbPtdModel_EXPORT PtdModel_WrappedBladeSection
		(
			std::vector<Pnt3d>&& theFace,
			std::vector<Pnt3d>&& theBack
		);

		//- public functions and operators

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_WrappedBladeSection);

#endif // !_PtdModel_WrappedBladeSection_Header
