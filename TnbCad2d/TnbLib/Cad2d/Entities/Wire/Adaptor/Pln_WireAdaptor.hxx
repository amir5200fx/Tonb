#pragma once
#ifndef _Pln_WireAdaptor_Header
#define _Pln_WireAdaptor_Header

#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	class Pln_WireAdaptor
	{

		/*Private Data*/

		std::weak_ptr<Cad2d_Plane> thePlane_;

	protected:

		Pln_WireAdaptor()
		{}

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<Cad2d_Plane>, Plane)
	};
}

#endif // !_Pln_WireAdaptor_Header
