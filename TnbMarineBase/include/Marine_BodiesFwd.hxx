#pragma once
#ifndef _Marine_BodiesFwd_Header
#define _Marine_BodiesFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;

	namespace marineLib
	{

		class Body_Displacer;
		class Body_Dry;
		class Body_Sail;
		class Body_Tank;
		class Body_Wetted;

		template<class BodyType>
		class BodyConstructor_Shape;

		template<class BodyType>
		class BodyConstructor_noShape;
	}
}

#endif // !_Marine_BodiesFwd_Header
