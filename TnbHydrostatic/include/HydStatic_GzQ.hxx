#pragma once
#ifndef _HydStatic_GzQ_Header
#define _HydStatic_GzQ_Header

#include <Global_AccessMethod.hxx>
#include <HydStatic_Entity.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{
	
	class HydStatic_GzQ
		: public HydStatic_Entity
	{

		/*Private Data*/

		Standard_Real theHeel_;
		Standard_Real theLeverArm_;

	public:

		HydStatic_GzQ()
			: theHeel_(0)
			, theLeverArm_(0)
		{}

		HydStatic_GzQ
		(
			const Standard_Real theHeel,
			const Standard_Real theLever
		)
			: theHeel_(theHeel)
			, theLeverArm_(theLever)
		{}

		Pnt2d GetPt() const;

		virtual std::shared_ptr<HydStatic_GzQ> Mirrored(const Pnt2d& theO) const;

		virtual std::shared_ptr<HydStatic_GzQ> Mirrored(const gp_Ax2d& theAx) const;

		static Standard_Boolean 
			IsLess
			(
				const HydStatic_GzQ& q0, 
				const HydStatic_GzQ& q1
			)
		{
			return q0.Heel() < q1.Heel();
		}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Heel)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, LeverArm)
	};
}

#endif // !_HydStatic_GzQ_Header
