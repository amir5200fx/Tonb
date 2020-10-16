#pragma once
#ifndef _SectPx_KnotVector_Header
#define _SectPx_KnotVector_Header

#include <SectPx_Entity.hxx>

#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;

	class SectPx_KnotVector
		: public SectPx_Entity
	{

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theU1_;

		void SetDefaults();

	protected:

		template<class... _Types>
		SectPx_KnotVector(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{
			SetDefaults();
		}

		void SetU0(const Standard_Real u)
		{
			theU0_ = u;
		}

		void SetU1(const Standard_Real u)
		{
			theU1_ = u;
		}

		static std::vector<Standard_Real> 
			toKnots
			(
				const std::vector<Standard_Real>& Ubar, 
				const Standard_Integer theDeg
			);

	public:

		typedef TColStd_Array1OfReal knotList;
		typedef TColStd_Array1OfInteger multList;

		auto U0() const
		{
			return theU0_;
		}

		auto U1() const
		{
			return theU1_;
		}

		virtual std::vector<Standard_Real>
			CreateKnots
			(
				const std::vector<std::shared_ptr<SectPx_Coord>>& theCoords,
				const Standard_Integer degree
			) const = 0;

		static std::tuple<knotList, multList> 
			Convert
			(
				const std::vector<Standard_Real>& seqKnots
			);
	};
}

#endif // !_SectPx_KnotVector_Header
