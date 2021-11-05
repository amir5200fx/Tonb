#pragma once
#ifndef _PtdModel_VesselSection_Header
#define _PtdModel_VesselSection_Header

#include <PtdModel_VesselEntity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_VesselSectionQ;
	class PtdModel_Vessel;

	class PtdModel_VesselSection
		: public PtdModel_VesselEntity
	{

		/*Private Data*/


	protected:

		//- default constructor

		PtdModel_VesselSection()
		{}


		//- constructors


	public:

		//- public functions and operators

		virtual std::shared_ptr<PtdModel_VesselSectionQ> SectionQ(const Standard_Integer, const std::shared_ptr<PtdModel_Vessel>&) const = 0;
	};
}

#endif // !_PtdModel_VesselSection_Header
