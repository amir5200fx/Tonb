#pragma once
#ifndef _GModel_ParaCurve_Header
#define _GModel_ParaCurve_Header

#include <Cad_ParaCurve.hxx>

namespace tnbLib
{

	class GModel_ParaCurve
		: public Cad_ParaCurve
	{

		/*Private Data*/


		// private functions and operators [5/12/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Cad_ParaCurve>(*this);
		}


	protected:


		//- default constructor

		GModel_ParaCurve()
		{}

	public:

		typedef Geom2d_Curve geomType;

		//- constructors

		explicit GModel_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theGeometry)
		{}

		GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theIndex, theGeometry)
		{}

		GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theIndex, theName, theGeometry)
		{}

		GModel_ParaCurve
		(
			Handle(Geom2d_Curve)&& theGeometry
		)
			: Cad_ParaCurve(std::move(theGeometry))
		{}

		GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		)
			: Cad_ParaCurve(theIndex, std::move(theGeometry))
		{}

		GModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theGeometry
		)
			: Cad_ParaCurve(theIndex, theName, theGeometry)
		{}


		//- public functions and operators


		static TnbCad_EXPORT std::pair<std::shared_ptr<GModel_ParaCurve>, std::shared_ptr<GModel_ParaCurve>> 
			Split
			(
				const Standard_Real thePar,
				const std::shared_ptr<GModel_ParaCurve>&
			);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GModel_ParaCurve);

#endif // !_GModel_ParaCurve_Header
