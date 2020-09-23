#pragma once
#ifndef _SectPx_InterPole_Header
#define _SectPx_InterPole_Header

#include <SectPx_Pole.hxx>
#include <SectPx_InterPoleAdaptor.hxx>
#include <SectPx_PntsFwd.hxx>

namespace tnbLib
{

	class SectPx_InterPole
		: public SectPx_Pole
		, public SectPx_InterPoleAdaptor
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_InterPole(_Types&&... Args)
			: SectPx_Pole(Args...)
		{}

	public:

		Standard_Boolean IsInterior() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsCorner() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSlider() const
		{
			return Standard_False;
		}

	};
}

#endif // !_SectPx_InterPole_Header