#pragma once
#ifndef _Marine_VesselHull_Header
#define _Marine_VesselHull_Header

#include <Marine_VesselEntity.hxx>

namespace tnbLib
{

	class Marine_VesselHull
		: public Marine_VesselEntity
	{

		/*Private Data*/

	public:

		Marine_VesselHull
		(
			const TopoDS_Shape& theShape
		);

		Marine_VesselHull
		(
			const Standard_Integer theIndex, 
			const TopoDS_Shape& theShape
		);

		Marine_VesselHull
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const TopoDS_Shape& theShape
		);


		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_Marine_VesselHull_Header
