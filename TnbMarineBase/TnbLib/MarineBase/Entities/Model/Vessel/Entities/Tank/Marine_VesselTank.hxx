#pragma once
#ifndef _Marine_VesselTank_Header
#define _Marine_VesselTank_Header

#include <Marine_VesselEntity.hxx>

namespace tnbLib
{

	class Marine_VesselTank
		: public Marine_VesselEntity
	{

	public:

		Marine_VesselTank
		(
			const TopoDS_Shape& theShape
		);

		Marine_VesselTank
		(
			const Standard_Integer theIndex, 
			const TopoDS_Shape& theShape
		);

		Marine_VesselTank
		(
			const Standard_Integer theIndex,
			const word& theName,
			const TopoDS_Shape& theShape
		);


		Standard_Boolean IsTank() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_Marine_VesselTank_Header
