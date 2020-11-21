#pragma once
#ifndef _Marine_GraphAxis_Header
#define _Marine_GraphAxis_Header

#include <Marine_GraphEntity.hxx>
#include <Global_Bound.hxx>

namespace tnbLib
{

	class Marine_GraphAxis
		: public Marine_GraphEntity
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/

	protected:

		TnbMarine_EXPORT Marine_GraphAxis();

		TnbMarine_EXPORT Marine_GraphAxis
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphAxis
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

	public:

		virtual Standard_Boolean IsX() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsY() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Marine_GraphAxis_Header
