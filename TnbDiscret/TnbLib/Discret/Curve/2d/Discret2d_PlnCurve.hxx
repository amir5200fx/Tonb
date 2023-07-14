#pragma once
#ifndef _Discret2d_PlnCurve_Header
#define _Discret2d_PlnCurve_Header

#include <Discret_CurveInfo.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [11/7/2022 Amir]

	class Discret2d_PlnCurve_Function;
	class Pln_Curve;

	class Discret2d_PlnCurve
		: public Global_Done
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

	private:

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theU1_;

		std::shared_ptr<Pln_Curve> theCurve_;

		std::shared_ptr<Discret2d_PlnCurve_Function> theFun_;
		std::shared_ptr<Discret_CurveInfo> theInfo_;

		// results [11/7/2022 Amir]

		std::shared_ptr<std::vector<Standard_Real>> theMesh_;


		// Private functions and operators [11/7/2022 Amir]

		TnbDiscret_EXPORT void Subdivide(std::vector<Segment>&) const;

	public:

		// default constructor [11/7/2022 Amir]

		Discret2d_PlnCurve()
		{}


		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]

		auto U0() const
		{
			return theU0_;
		}

		auto U1() const
		{
			return theU1_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& Function() const
		{
			return theFun_;
		}

		const auto& DiscretInfo() const
		{
			return theInfo_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbDiscret_EXPORT void Perform();

		void SetCurve(const std::shared_ptr<Pln_Curve>& theCurve)
		{
			theCurve_ = theCurve;
		}

		void SetFunction(const std::shared_ptr<Discret2d_PlnCurve_Function>& theFun)
		{
			theFun_ = theFun;
		}

		void SetInfo(const std::shared_ptr<Discret_CurveInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetU0(const Standard_Real x)
		{
			theU0_ = x;
		}

		void SetU1(const Standard_Real x)
		{
			theU1_ = x;
		}
	};
}

#endif // !_Discret2d_PlnCurve_Header
