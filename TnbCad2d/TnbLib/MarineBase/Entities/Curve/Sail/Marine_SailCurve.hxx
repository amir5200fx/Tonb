#pragma once
#ifndef _Marine_SailCurve_Header
#define _Marine_SailCurve_Header

#include <Marine_PlnCurve.hxx>

namespace tnbLib
{

	class Marine_SailCurve
		: public Marine_PlnCurve
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_PlnCurve>(*this);
		}

	public:

		TnbCad2d_EXPORT Marine_SailCurve();

		TnbCad2d_EXPORT Marine_SailCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT explicit Marine_SailCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbCad2d_EXPORT Marine_SailCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_SailCurve(Pln_Curve&& theCurve)
			: Marine_PlnCurve(std::move(theCurve))
		{}


		//- public functions and operators

		Standard_Boolean IsOnSail() const override
		{
			return Standard_True;
		}

		marineLib::curveType CurveType() const override
		{
			return marineLib::curveType::sail;
		}

		TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			operator()
			(
				const Handle(Geom2d_Curve) & theCurve
				) const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			operator()
			(
				Handle(Geom2d_Curve) && theCurve
				) const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			Copy() const override;

		TnbCad2d_EXPORT std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			Split
			(
				const Standard_Real x
			) const override;

		TnbCad2d_EXPORT void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		TnbCad2d_EXPORT void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		TnbCad2d_EXPORT std::tuple
			<
			std::shared_ptr<Pln_Curve>,
			std::shared_ptr<Pln_Curve>,
			std::shared_ptr<Pln_Curve>
			>
			Split
			(
				const Cad2d_IntsctEntity_TangSegment& x
			) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_SailCurve);

#endif // !_Marine_SailCurve_Header
