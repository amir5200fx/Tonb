#pragma once
#ifndef _PtdModel_HubCurve_Header
#define _PtdModel_HubCurve_Header

#include <PtdModel3d_Curve.hxx>

namespace tnbLib
{

	class PtdModel_HubCurve
		: public PtdModel3d_Curve
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel3d_Curve>(*this);
		}

	protected:

		//- default constructor

		PtdModel_HubCurve()
		{}


		//- constructors

		PtdModel_HubCurve(const Handle(Geom_Curve)& theGeometry)
			: PtdModel3d_Curve(theGeometry)
		{}

		PtdModel_HubCurve(Handle(Geom_Curve)&& theGeometry)
			: PtdModel3d_Curve(std::move(theGeometry))
		{}


	public:

		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_HubCurve);

#endif // !_PtdModel_HubCurve_Header
