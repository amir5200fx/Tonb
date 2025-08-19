#pragma once
#ifndef _PtdModel_PropSection_Header
#define _PtdModel_PropSection_Header

#include <PtdModel_PropEntity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeSectionQ;
	class PtdModel_BladeInfo;
	class PtdModel_xPars;
	class PtdModel_PropBlade;

	class PtdModel_PropSection
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

		PtdModel_PropSection()
		{}


		//- constructors


		//- protected functions and operators

		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_BladeInfo>& BladeInfo(const PtdModel_PropBlade&);
		static TnbPtdModel_EXPORT const std::shared_ptr<PtdModel_xPars>& xParameters(const PtdModel_PropBlade&);

	public:

		static TnbPtdModel_EXPORT unsigned short verbose;

		//- public functions and operators

		virtual std::shared_ptr<PtdModel_BladeSectionQ> SectionQ(const Standard_Integer, const PtdModel_PropBlade&) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropSection);

#endif // !_PtdModel_PropSection_Header
