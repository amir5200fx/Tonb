#pragma once
#ifndef _Marine_WaterCurve_Header
#define _Marine_WaterCurve_Header

#include <Marine_PlnCurve.hxx>

namespace tnbLib
{

	class Marine_WaterCurve
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

		TnbMarine_EXPORT Marine_WaterCurve();

		TnbMarine_EXPORT Marine_WaterCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbMarine_EXPORT explicit Marine_WaterCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		TnbMarine_EXPORT Marine_WaterCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);


		Standard_Boolean IsOnWater() const override
		{
			return Standard_True;
		}

		TnbMarine_EXPORT std::shared_ptr<Pln_Curve>
			Copy() const override;

		TnbMarine_EXPORT std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			Split
			(
				const Standard_Real x
			) const override;

		TnbMarine_EXPORT void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		TnbMarine_EXPORT void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		TnbMarine_EXPORT std::tuple
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

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_WaterCurve);

#endif // !_Marine_WaterCurve_Header
