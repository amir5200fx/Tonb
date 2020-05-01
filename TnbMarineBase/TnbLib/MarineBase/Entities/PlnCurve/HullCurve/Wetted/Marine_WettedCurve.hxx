#pragma once
#ifndef _Marine_WettedCurve_Header
#define _Marine_WettedCurve_Header

#include <Marine_HullCurve.hxx>

namespace tnbLib
{

	class Marine_WettedCurve
		: public Marine_HullCurve
	{

		/*Private Data*/

	public:

		Marine_WettedCurve();

		Marine_WettedCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_WettedCurve
		(
			const Handle(Geom2d_Curve)& theGeom
		);

		Marine_WettedCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeom
		);

		Standard_Boolean IsWetted() const override
		{
			return Standard_True;
		}

		std::shared_ptr<Pln_Curve>
			Copy() const override;

		std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			Split
			(
				const Standard_Real x
			) const override;

		void Split
		(
			const Standard_Real x,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		void Split
		(
			const Standard_Real x,
			Pnt2d& theCoord,
			std::shared_ptr<Pln_Curve>& theLeft,
			std::shared_ptr<Pln_Curve>& theRight
		) const override;

		std::tuple
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

#endif // !_Marine_WettedCurve_Header
