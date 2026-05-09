#pragma once
#ifndef _PtdModel_PropHubSection_Header
#define _PtdModel_PropHubSection_Header

#include <Standard_Handle.hxx>
#include <PtdModel_Entity.hxx>

class Geom_Curve;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropHub;
	class PtdModel_PropHubPars;
	class PtdModel_HubCurve;

	class PtdModel_PropHubSection
		: public PtdModel_Entity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_Entity>(*this);
		}

	protected:

		//- default constructor

		PtdModel_PropHubSection()
		{}

		//- constructors



		//- protected functions and operators


	public:


		//- public functions and operators

		virtual std::vector<std::shared_ptr<PtdModel_HubCurve>> SectionCurves(const PtdModel_PropHub&) const = 0;


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropHubSection);

#endif // !_PtdModel_PropHubSection_Header
