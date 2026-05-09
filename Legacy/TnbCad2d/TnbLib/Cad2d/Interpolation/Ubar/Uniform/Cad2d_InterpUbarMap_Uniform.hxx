#pragma once
#ifndef _Cad2d_InterpUbarMap_Uniform_Header
#define _Cad2d_InterpUbarMap_Uniform_Header

#include <Cad2d_InterpUbarMap.hxx>

namespace tnbLib
{

	class Cad2d_InterpUbarMap_Uniform
		: public Cad2d_InterpUbarMap
	{

		/*Private Data*/

	public:


		//- default constructor

		Cad2d_InterpUbarMap_Uniform()
		{}

		//- constructors
	


		//- public functions and operators

		TnbCad2d_EXPORT std::vector<Standard_Real> CalcUk(const std::vector<Pnt2d>& theQ) const override;

	};
}

#endif // !_Cad2d_InterpUbarMap_Uniform_Header
