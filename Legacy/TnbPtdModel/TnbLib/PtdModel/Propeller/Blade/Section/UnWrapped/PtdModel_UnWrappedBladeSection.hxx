#pragma once
#ifndef _PtdModel_UnWrappedBladeSection_Header
#define _PtdModel_UnWrappedBladeSection_Header

#include <PtdModel_BladeSection.hxx>

namespace tnbLib
{

	class PtdModel_UnWrappedBladeSection
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

		PtdModel_UnWrappedBladeSection()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_UnWrappedBladeSection
		(
			const std::vector<Pnt3d>& theFace, 
			const std::vector<Pnt3d>& theBack
		);

		TnbPtdModel_EXPORT PtdModel_UnWrappedBladeSection
		(
			std::vector<Pnt3d>&& theFace, 
			std::vector<Pnt3d>&& theBack
		);


		//- public functions and operators


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_UnWrappedBladeSection);

#endif // !_PtdModel_UnWrappedBladeSection_Header
