#pragma once
#ifndef _VoyageMesh_AltrOptNode_NelderMeadObj_Header
#define _VoyageMesh_AltrOptNode_NelderMeadObj_Header

#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>

#include <memory>

namespace tnbLib
{

	struct VoyageMesh_AltrOptNode_NelderMeadObj_Cache
	{

	protected:

		mutable Standard_Real d0;
		mutable Standard_Real d1;
	};

	class VoyageMesh_AltrOptNode_NelderMeadObj
		: public VoyageMesh_AltrOptNode_NelderMeadObj_Cache
	{

		std::shared_ptr<Geo2d_MetricPrcsrAnIso> theMap_;

		Pnt2d theP0_;
		Pnt2d theP1_;
		Pnt2d theP2_;

		Standard_Real theTol_;

		static TnbVoyage_EXPORT Standard_Real EstimateError(const Standard_Real d0, const Standard_Real d1);

	public:

		static TnbVoyage_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbVoyage_EXPORT const int nbVariables;

		enum
		{
			dim = 2
		};

		typedef Pnt2d varType;

		// default constructor [5/6/2022 Amir]

		VoyageMesh_AltrOptNode_NelderMeadObj()
			: theTol_(DEFAULT_TOLERANCE)
		{}


		// constructors [5/6/2022 Amir]


		// public functions and operators [5/6/2022 Amir]

		const auto& MetricMap() const
		{
			return theMap_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		const auto& P1() const
		{
			return theP1_;
		}

		const auto& P2() const
		{
			return theP2_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		TnbVoyage_EXPORT Standard_Real Value(const Pnt2d& theCoord) const;
		TnbVoyage_EXPORT Standard_Boolean IsConverged() const;

		void SetP0(const Pnt2d& theP0)
		{
			theP0_ = theP0;
		}

		void SetP1(const Pnt2d& theP1)
		{
			theP1_ = theP1;
		}

		void SetP2(const Pnt2d& theP2)
		{
			theP2_ = theP2;
		}

		void Initial(Pnt2d var[3])
		{
			var[0] = P0();
			var[1] = P1();
			var[2] = P2();
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}

		void SetMetricMap(const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap)
		{
			theMap_ = theMap;
		}

		static Standard_Real V(const Standard_Integer Dim, const Pnt2d& P)
		{
			return P.Coord(Dim);
		}

		TnbVoyage_EXPORT void SetV(const Standard_Integer Dim, const Standard_Real x, Pnt2d& P);

	};
}

#endif // !_VoyageMesh_AltrOptNode_NelderMeadObj_Header
