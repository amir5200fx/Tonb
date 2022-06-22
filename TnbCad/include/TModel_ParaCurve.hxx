#pragma once
#ifndef _TModel_ParaCurve_Header
#define _TModel_ParaCurve_Header

#include <Cad_ParaCurve.hxx>

namespace tnbLib
{

	class TModel_ParaCurve
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

		TModel_ParaCurve()
		{}

	public:

		typedef Geom2d_Curve geomType;

		//- constructors

		explicit TModel_ParaCurve
		(
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theGeometry)
		{}

		TModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theIndex, theGeometry)
		{}

		TModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Cad_ParaCurve(theIndex, theName, theGeometry)
		{}

		TModel_ParaCurve
		(
			Handle(Geom2d_Curve) && theGeometry
		)
			: Cad_ParaCurve(std::move(theGeometry))
		{}

		TModel_ParaCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		)
			: Cad_ParaCurve(theIndex, std::move(theGeometry))
		{}

		TModel_ParaCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeometry
		)
			: Cad_ParaCurve(theIndex, theName, theGeometry)
		{}


		//- public functions and operators


		TnbCad_EXPORT std::shared_ptr<TModel_ParaCurve> Copy() const;
		TnbCad_EXPORT std::shared_ptr<TModel_ParaCurve> Copy(const gp_Trsf2d&) const;

		static TnbCad_EXPORT std::pair<std::shared_ptr<TModel_ParaCurve>, std::shared_ptr<TModel_ParaCurve>>
			Split
			(
				const Standard_Real thePar,
				const std::shared_ptr<TModel_ParaCurve>&
			);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_ParaCurve);

#endif // !_TModel_ParaCurve_Header
