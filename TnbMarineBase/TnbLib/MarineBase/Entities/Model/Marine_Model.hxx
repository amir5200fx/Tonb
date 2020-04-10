#pragma once
#ifndef _Marine_Model_Header
#define _Marine_Model_Header

#include <Marine_Entity.hxx>

namespace tnbLib
{

	class Marine_Model
		: public Marine_Entity
	{

		/*Private Data*/

	protected:

		Marine_Model();

		Marine_Model
		(
			const Standard_Integer theIndex
		);

		Marine_Model
		(
			const Standard_Integer theIndex,
			const word& theName
		);

	public:

		virtual Standard_Boolean IsVessel() const
		{
			return Standard_False;
		}

		
	};
}

#endif // !_Marine_Model_Header
