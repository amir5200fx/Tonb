#pragma once
#ifndef _SectPx_BndPole_Header
#define _SectPx_BndPole_Header

#include <SectPx_Pole.hxx>
#include <SectPx_BndPoleAdaptor.hxx>

namespace tnbLib
{

	class SectPx_BndPole
		: public SectPx_Pole
		, public SectPx_BndPoleAdaptor
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_BndPole(_Types&&... Args)
			: SectPx_Pole(Args...)
		{}

	public:

		Standard_Boolean IsBoundary() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsDangle() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsPaired() const
		{
			return Standard_False;
		}
	};
}

#endif // !_SectPx_BndPole_Header