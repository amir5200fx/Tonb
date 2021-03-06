#pragma once
#ifndef _GModel_Edge_Header
#define _GModel_Edge_Header

#include <GModel_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class GModel_ParaCurve;
	class GModel_Curve;

	class GModel_Edge
		: public GModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<GModel_ParaCurve> thePar_;
		std::shared_ptr<GModel_Curve> theCurve_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


		//- default constructor

		GModel_Edge()
		{}

	public:


		//- constructors

		TnbCad_EXPORT GModel_Edge
		(
			const std::shared_ptr<GModel_ParaCurve>& thePar,
			const std::shared_ptr<GModel_Curve>& theCurve
		);

		TnbCad_EXPORT GModel_Edge
		(
			std::shared_ptr<GModel_ParaCurve>&& thePar,
			std::shared_ptr<GModel_Curve>&& theCurve
		);

		TnbCad_EXPORT GModel_Edge
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<GModel_ParaCurve>& thePar,
			const std::shared_ptr<GModel_Curve>& theCurve
		);


		//- public functions and operators

		const auto& Par() const
		{
			return thePar_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GModel_Edge);

#endif // !_GModel_Edge_Header
