#pragma once
#ifndef _Cad2d_Modeler_Entity_Header
#define _Cad2d_Modeler_Entity_Header

#include <Pln_Entity.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class Modeler_Entity
			: public Pln_Entity
		{

			/*Private Data*/

		protected:

			Modeler_Entity()
			{}

			Modeler_Entity
			(
				const Standard_Integer theIndex
			)
				: Pln_Entity(theIndex)
			{}

			Modeler_Entity
			(
				const Standard_Integer theIndex, 
				const word& theName
			)
				: Pln_Entity(theIndex, theName)
			{}

		public:


		};
	}
}

#endif // !_Cad2d_Modeler_Entity_Header
