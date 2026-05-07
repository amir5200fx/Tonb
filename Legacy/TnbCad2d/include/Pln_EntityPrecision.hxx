#pragma once
#ifndef _Pln_EntityPrecision_Header
#define _Pln_EntityPrecision_Header

#include <Cad2d_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Pln_EntityPrecision
	{

		/*Private Data*/

		Standard_Real thePrecision_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_PRECISION;

		Pln_EntityPrecision()
			: thePrecision_(DEFAULT_PRECISION)
		{}

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(Standard_Real, Precision)
	};
}

#endif // !_Pln_EntityPrecision_Header
