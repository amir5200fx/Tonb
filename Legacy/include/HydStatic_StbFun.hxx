#pragma once
#ifndef _HydStatic_StbFun_Header
#define _HydStatic_StbFun_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	class HydStatic_StbFun
		: public HydStatic_Entity
	{

		/*Private Data*/

	protected:

		HydStatic_StbFun()
		{}

		HydStatic_StbFun
		(
			const Standard_Integer theIndex
		)
			: HydStatic_Entity(theIndex)
		{}

		HydStatic_StbFun
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: HydStatic_Entity(theIndex, theName)
		{}

	public:

		virtual Standard_Boolean IsRighting() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsHeeling() const
		{
			return Standard_False;
		}

		virtual Standard_Real MinHeel() const = 0;

		virtual Standard_Real MaxHeel() const = 0;

		virtual Standard_Real Value(const Standard_Real thePhi) const = 0;
	};
}

#endif // !_HydStatic_StbFun_Header
