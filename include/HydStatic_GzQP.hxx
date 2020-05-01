#pragma once
#ifndef _HydStatic_GzQP_Header
#define _HydStatic_GzQP_Header

#include <HydStatic_GzQ.hxx>

namespace tnbLib
{

	class HydStatic_GzQP
		: public HydStatic_GzQ
	{

		/*Private Data*/

		Standard_Real theParameter_;

	public:

		HydStatic_GzQP()
			: theParameter_(0)
		{}

		HydStatic_GzQP
		(
			const Standard_Real theHeel,
			const Standard_Real theArm,
			const Standard_Real theParameter
		)
			: HydStatic_GzQ(theHeel, theArm)
			, theParameter_(theParameter)
		{}

		std::shared_ptr<HydStatic_GzQ> Mirrored(const Pnt2d& theO) const override;

		std::shared_ptr<HydStatic_GzQ> Mirrored(const gp_Ax2d& theAx) const override;

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter)
	};
}

#endif // !_HydStatic_GzQP_Header
