#pragma once
#ifndef _Marine_Model_Header
#define _Marine_Model_Header

#include <Marine_Entity.hxx>
#include <Marine_ModelType.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class Marine_Model
		: public Marine_Entity
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

	protected:

		Marine_Model(const TopoDS_Shape& theShape);

		Marine_Model
		(
			const Standard_Integer theIndex,
			const TopoDS_Shape& theShape
		);

		Marine_Model
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

		virtual Marine_ModelType Type() const = 0;

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

#endif // !_Marine_Model_Header
