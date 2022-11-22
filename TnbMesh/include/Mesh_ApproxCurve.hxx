#pragma once
#ifndef _Mesh_ApproxCurve_Header
#define _Mesh_ApproxCurve_Header

#include <Mesh_ApproxCurveInfo.hxx>
#include <Entity_Polygon.hxx>
#include <Geo_Traits.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

#include <Geom_Curve.hxx>
#include <Standard_Handle.hxx>

namespace tnbLib
{

	class Mesh_ApproxCurveBase
	{

	public:

		struct Segment
		{

			Standard_Real X0;
			Standard_Real X1;

			Segment()
			{}

			Segment(const Standard_Real x0, const Standard_Real x1)
				: X0(x0)
				, X1(x1)
			{}

			Segment Left() const
			{
				return Segment(X0, MEAN(X0, X1));
			}

			Segment Right() const
			{
				return Segment(MEAN(X0, X1), X1);
			}

			Standard_Real Mean() const
			{
				return MEAN(X0, X1);
			}

			static Standard_Boolean IsLess(const Segment& s0, const Segment& s1)
			{
				return s0.Mean() < s1.Mean();
			}
		};

	protected:

		// default constructor [11/4/2022 Amir]

		Mesh_ApproxCurveBase()
		{}


		// constructors [11/4/2022 Amir]

	public:

		// public functions and operators [11/4/2022 Amir]
	};

	template<class CurveType>
	class Mesh_ApproxCurve
		: public Mesh_ApproxCurveBase
		, public Global_Done
	{

	public:

		typedef typename remove_pointer<CurveType>::type CurveTypeR;
		typedef typename cascadeLib::pt_type_from_curve<CurveTypeR>::ptType Point;

		typedef Entity_Polygon<Point> chain;


		

	private:

		/*Private Data*/

		CurveType theCurve_;

		Standard_Real theU0_;
		Standard_Real theU1_;

		std::shared_ptr<Mesh_ApproxCurveInfo> theInfo_;

		// results [11/4/2022 Amir]

		std::shared_ptr<chain> theMesh_;


		// Private functions and operators [11/4/2022 Amir]

		void Subdivide(std::vector<Segment>&) const;

	public:

		

		// default constructor [11/4/2022 Amir]

		Mesh_ApproxCurve()
			: theCurve_(0)
		{}


		// constructors [11/4/2022 Amir]


		// public functions and operators [11/4/2022 Amir]

		const auto& Curve() const
		{
			return theCurve_;
		}

		auto U0() const
		{
			return theU0_;
		}

		auto U1() const
		{
			return theU1_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		void Perform();

		void SetU0(const Standard_Real theU)
		{
			theU0_ = theU;
		}

		void SetU1(const Standard_Real theU)
		{
			theU1_ = theU;
		}

		void SetCurve(const CurveType& theCurve)
		{
			theCurve_ = theCurve;
		}

		void SetInfo(const std::shared_ptr<Mesh_ApproxCurveInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#include <Mesh_ApproxCurveI.hxx>

#endif // !_Mesh_ApproxCurve_Header
