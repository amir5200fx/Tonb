#pragma once
#ifndef _Mesh_ApproxCurve_Header
#define _Mesh_ApproxCurve_Header

#include <Mesh_ApproxCurveInfo.hxx>
#include <Entity_Polygon.hxx>
#include <Geo_Traits.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

#include <memory>
#include <vector>

#include <opencascade/Geom_Curve.hxx>

namespace tnbLib
{

	class Mesh_ApproxCurveBase
	{

	public:

		struct Segment
		{

			Standard_Real X0;
			Standard_Real X1;

			// default constructor
			Segment()
				: X0(0)
				, X1(0)
			{}

			// constructors
			Segment(const Standard_Real x0, const Standard_Real x1)
				: X0(x0)
				, X1(x1)
			{}

			// Public functions and operators
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

		static TnbMesh_EXPORT std::vector<Standard_Real> Tessellate(const std::vector<Standard_Real>& us,
		                                                            Standard_Integer theMinSamples);
	};

	template<class CurveType>
	class Mesh_ApproxCurve
		: public Mesh_ApproxCurveBase
		, public Global_Done
	{

	public:

		typedef typename remove_pointer<CurveType>::type CurveTypeR;
		typedef typename cascadeLib::pt_type_from_curve<CurveTypeR>::ptType Point;

		typedef std::vector<Standard_Real> chain;

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
		Mesh_ApproxCurve();


		// constructors [11/4/2022 Amir]
		Mesh_ApproxCurve(CurveType theCurve, Standard_Real theU0, Standard_Real theU1,
			std::shared_ptr<Mesh_ApproxCurveInfo> theInfo);

		// public functions and operators [11/4/2022 Amir]

		const auto& Curve() const { return theCurve_; }
		auto U0() const { return theU0_; }
		auto U1() const { return theU1_; }
		const auto& AlgInfo() const { return theInfo_; }

		void Perform();

		const auto& Mesh() const { return theMesh_; }

		void SetCurve(CurveType theCurve);
		void SetU0(Standard_Real);
		void SetU1(Standard_Real);
		void SetInfo(std::shared_ptr<Mesh_ApproxCurveInfo> theInfo);

	};
}

#include <Mesh_ApproxCurveI.hxx>

#endif // !_Mesh_ApproxCurve_Header
