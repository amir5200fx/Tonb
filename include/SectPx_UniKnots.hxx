#pragma once
#ifndef _SectPx_UniKnots_Header
#define _SectPx_UniKnots_Header

#include <SectPx_KnotVector.hxx>

namespace tnbLib
{

	class SectPx_UniKnots
		: public SectPx_KnotVector
	{

		/*Private Data*/

	public:

		template<class... _Types>
		SectPx_UniKnots(_Types&&... _Args)
			: SectPx_KnotVector(_Args...)
		{}

		void SetU0(const Standard_Real u)
		{
			SectPx_KnotVector::SetU0(u);
		}

		void SetU1(const Standard_Real u)
		{
			SectPx_KnotVector::SetU1(u);
		}

		std::vector<Standard_Real> 
			CreateKnots
			(
				const std::vector<std::shared_ptr<SectPx_Coord>>& theCoords,
				const Standard_Integer degree
			) const override;
	};
}

#endif // !_SectPx_UniKnots_Header