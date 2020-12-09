#pragma once
#ifndef _HydStatic_HydGphCurve_Header
#define _HydStatic_HydGphCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	class HydStatic_HydGphCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

	protected:

		
		template<class... _Types>
		HydStatic_HydGphCurve(_Types&&... _Args)
			: HydStatic_HydCurve(_Args...)
		{}

	public:

		TnbHydStatic_EXPORT Standard_Real MinValue() const;

		TnbHydStatic_EXPORT Standard_Real MaxValue() const;

		TnbHydStatic_EXPORT Standard_Real Value(const Standard_Real theT) const;
	};
}

#endif // !_HydStatic_HydGphCurve_Header
