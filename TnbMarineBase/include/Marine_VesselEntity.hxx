#pragma once
#ifndef _Marine_VesselEntity_Header
#define _Marine_VesselEntity_Header

#include <Marine_Entity.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class Marine_VesselEntity
		: public Marine_Entity
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

	protected:

		Marine_VesselEntity
		(
			const TopoDS_Shape& theShape
		);

		Marine_VesselEntity
		(
			const Standard_Integer theIndex,
			const TopoDS_Shape& theShape
		);

		Marine_VesselEntity
		(
			const Standard_Integer theIndex,
			const word& theName,
			const TopoDS_Shape& theShape
		);

	public:


		const auto& Shape() const
		{
			return theShape_;
		}

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_VesselEntity_Header
