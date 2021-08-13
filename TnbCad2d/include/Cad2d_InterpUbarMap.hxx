#pragma once
#ifndef _Cad2d_InterpUbarMap_Header
#define _Cad2d_InterpUbarMap_Header

#include <Pnt2d.hxx>
#include <Cad2d_Module.hxx>

#include <vector>

namespace tnbLib
{

	class Cad2d_InterpUbarMap
	{

		/*Private Data*/

	protected:

		//- default constructor

		Cad2d_InterpUbarMap()
		{}


		//- constructor


	public:

		//- public functions and operators


		virtual std::vector<Standard_Real> CalcUk(const std::vector<Pnt2d>&) const = 0;
	};
}

#endif // !_Cad2d_InterpUbarMap_Header
