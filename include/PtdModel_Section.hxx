#pragma once
#ifndef _PtdModel_Section_Header
#define _PtdModel_Section_Header

#include <PtdModel_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_SectionCurve;

	class PtdModel_Section
		: public PtdModel_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<PtdModel_SectionCurve>> theCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor
		PtdModel_Section()
		{}


		//- constructors

		PtdModel_Section(const Standard_Integer theIndex, const word& theName);


		//- public functions and operators

		Standard_Integer NbCurves() const;

		const auto& Curves() const
		{
			return theCurves_;
		}

		auto& CurvesRef()
		{
			return theCurves_;
		}
	};
}

#include <PtdModel_SectionI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_Section);

#endif // !_PtdModel_Section_Header
