#pragma once
#ifndef _Marine_VesselSail_Header
#define _Marine_VesselSail_Header

#include <Marine_VesselEntity.hxx>

namespace tnbLib
{

	class Marine_VesselSail
		: public Marine_VesselEntity
	{

		/*Private Data*/

	public:

		Marine_VesselSail
		(
			const TopoDS_Shape& theShape
		);

		Marine_VesselSail
		(
			const Standard_Integer theIndex, 
			const TopoDS_Shape& theShape
		);

		Marine_VesselSail
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const TopoDS_Shape& theShape
		);


		Standard_Boolean IsSail() const override
		{
			return Standard_True;
		}

	};
}

#endif // !_Marine_VesselSail_Header
