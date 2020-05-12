#ifndef _Marine_TankBody_Header
#define _Marine_TankBody_Header

#include <Marine_Body.hxx>

namespace tnbLib
{

	class Marine_TankBody
		: public Marine_Body
	{

		/*Private Data*/

	public:

		Marine_TankBody();

		Marine_TankBody
		(
			const Standard_Integer theIndex
		);

		Marine_TankBody
		(
			const Standard_Integer theIndex,
			const word& theName
		);
	};
}

#endif // !_Marine_TankBody_Header
