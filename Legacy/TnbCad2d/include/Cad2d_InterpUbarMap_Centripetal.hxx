#pragma once
#ifndef _Cad2d_InterpUbarMap_Centripetal_Header
#define _Cad2d_InterpUbarMap_Centripetal_Header

#include <Cad2d_InterpUbarMap.hxx>

namespace tnbLib
{

	class Cad2d_InterpUbarMap_Centripetal
		: public Cad2d_InterpUbarMap
	{

		/*Private Data*/

	public:

		//- default constructor

		Cad2d_InterpUbarMap_Centripetal()
		{}

		//- constructors



		//- public functions and operators

		TnbCad2d_EXPORT std::vector<Standard_Real> CalcUk(const std::vector<Pnt2d>&) const override;

	};
}

#endif // !_Cad2d_InterpUbarMap_Centripetal_Header
