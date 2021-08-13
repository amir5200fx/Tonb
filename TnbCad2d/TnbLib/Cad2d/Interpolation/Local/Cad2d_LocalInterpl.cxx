#include <Cad2d_LocalInterpl.hxx>

#include <Cad2d_InterpUbarMap_ChordLen.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Entity_Line.hxx>
#include <Adt_Ary1d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

tnbLib::Cad2d_LocalInterpl::Cad2d_LocalInterpl(const std::vector<Pnt2d>& theQ)
	: theQ_(theQ)
	, theMap_(std::make_shared<Cad2d_InterpUbarMap_ChordLen>())
	, theTol_(1.0E-6)
	, theAlfa_(2.0/3.0)
{
	// empty body [8/10/2021 Amir]
}

tnbLib::Cad2d_LocalInterpl::Cad2d_LocalInterpl
(
	const std::vector<Pnt2d>& theQ,
	const std::shared_ptr<Cad2d_InterpUbarMap>& theMap
)
	: theQ_(theQ)
	, theMap_(theMap)
	, theTol_(1.0E-6)
	, theAlfa_(2.0 / 3.0)
{
	// empty body [8/10/2021 Amir]
}

namespace tnbLib
{
	auto calcInnerPoints
	(
		const Standard_Real gamma0,
		const Standard_Real gamma1,
		const Pnt2d& q0, 
		const Pnt2d& t0, 
		const Pnt2d& q1,
		const Pnt2d& t1
	)
	{
		auto Rk = q0 + gamma0 * t0;
		auto Rk1 = q1 - gamma1 * t1;

		auto Qk = (gamma0*Rk1 + gamma1 * Rk) / (gamma0 + gamma1);
		auto t = std::make_tuple(std::move(Rk), std::move(Qk), std::move(Rk1));
		return std::move(t);
	}

	class InnerPoints
	{

	protected:

		InnerPoints()
		{}
		
	public:

		virtual Standard_Boolean IsOnePoint() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsThreePoint() const
		{
			return Standard_False;
		}
	};

	class OneInnerPoint
		: public InnerPoints
	{

		/*Private Data*/

		Pnt2d theP_;

	public:

		OneInnerPoint(const Pnt2d& theCoord)
			: theP_(theCoord)
		{}

		OneInnerPoint(Pnt2d&& theCoord)
			: theP_(std::move(theCoord))
		{}


		//- public functions and operators

		const auto& Point() const
		{
			return theP_;
		}

		Standard_Boolean IsOnePoint() const override
		{
			return Standard_True;
		}
	};

	class ThreeInnerPoints
		: public InnerPoints
	{

		/*Private Data*/

		Pnt2d theP0_;
		Pnt2d theP1_;
		Pnt2d theP2_;

	public:

		ThreeInnerPoints(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
			: theP0_(p0)
			, theP1_(p1)
			, theP2_(p2)
		{}

		ThreeInnerPoints(Pnt2d&& p0, Pnt2d&& p1, Pnt2d&& p2)
			: theP0_(std::move(p0))
			, theP1_(std::move(p1))
			, theP2_(std::move(p2))
		{}

		//- public functions and operators

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

		Standard_Boolean IsThreePoint() const
		{
			return Standard_True;
		}
	};
}

void tnbLib::Cad2d_LocalInterpl::Perform()
{
	if (Qs().size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid data: not enough offset points!" << endl
			<< abort(FatalError);
	}

	if (NOT UbarMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "no Ubar map has been found!" << endl
			<< abort(FatalError);
	}
	const auto tol = Geo_BoxTools::GetBox(Qs(), 0).Diameter()*Tolerance();

	const auto n = Qs().size() - 1;

	auto uk = UbarMap()->CalcUk(Qs());

	const auto& qs = Qs();

	Adt_Ary1d<Pnt2d> qk(-1, n + 2);
	for (size_t k = 1; k <= n; k++)
	{
		qk[k] = qs[k] - qs[k - 1];
	}

	if (theType_ IS_EQUAL neighborType::fivePoint)
	{
		qk[0] = 2.0*qk[1] - qk[2];
		qk[-1] = 2.0*qk[0] - qk[1];

		qk[n + 1] = 2.0*qk[n] - qk[n - 1];
		qk[n + 2] = 2.0*qk[n + 1] - qk[n];
	}

	Adt_Ary1d<Standard_Real> duk(0, n);
	for (size_t k = 1; k <= n; k++)
	{
		duk[k] = uk[k] - uk[k - 1];
	}

	Adt_Ary1d<Pnt2d> dk(0, n);
	for (size_t k = 1; k <= n; k++)
	{
		dk[k] = qk[k] / duk[k];
	}

	Adt_Ary1d<Standard_Real> alfk(0, n);
	Adt_Ary1d<Pnt2d> Tk(0, n);
	Adt_Ary1d<Pnt2d> Vk(0, n);
	if (theType_ IS_EQUAL neighborType::threePoint)
	{
		for (size_t k = 1; k <= n - 1; k++)
		{
			alfk[k] = duk[k] / (duk[k] + duk[k + 1]);
		}

		for (size_t k = 1; k < n; k++)
		{
			Tk[k] = (1.0 - alfk[k])*dk[k] + alfk[k] * dk[k + 1];
		}

		Tk[0] = 2.0*dk[1] - Tk[1];
		Tk[n] = 2.0*dk[n] - Tk[n - 1];

		for (size_t k = 0; k <= n; k++)
		{
			Tk[k] /= Tk[k].TwoNorm();
		}
	}
	else if (theType_ IS_EQUAL neighborType::fivePoint)
	{
		for (size_t k = 0; k <= n; k++)
		{
			auto cross = std::abs(CrossProduct(qk[k - 1], qk[k]));
			auto denom = cross + std::abs(CrossProduct(qk[k + 1], qk[k + 2]));

			if (denom < tol)
			{
				alfk[k] = 0.5;
			}
			else
			{
				alfk[k] = cross / denom;
			}
		}

		for (size_t k = 0; k <= n; k++)
		{
			Vk[k] = (1.0 - alfk[k])*qk[k] + alfk[k] * qk[k + 1];
		}

		for (size_t k = 0; k <= n; k++)
		{
			Tk[k] = Vk[k] / Vk[k].TwoNorm();
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of the neighboring point has been detected!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<InnerPoints>> inners;
	inners.reserve(n + 1);
	for (size_t k = 1; k <= n; k++)
	{
		Vec2d d0(Tk[k - 1].XY());
		Vec2d d1(Tk[k].XY());

		Standard_Real alf0, alf1;
		const auto ent = Geo_Tools::IntersectTwoLines(qs[k - 1], d0, qs[k], d1, alf0, alf1, tol);
		const auto& rk = ent.first;

		if (ent.second)
		{
			if (alf0 < 0)
			{
				// This indicates either an inflection point or a turn of more than 180 deg [8/9/2021 Amir]
				
				auto u1 = Dir2d((rk - qs[k - 1]).XY());
				auto u2 = Dir2d((qs[k] - qs[k - 1]).XY());

				auto theta0 = u1.Angle(u2);

				auto v1 = Dir2d((qs[k - 1] - qs[k]).XY());
				auto v2 = Dir2d((rk - qs[k]).XY());

				auto theta1 = v1.Angle(v2);

				const auto numerator = (qs[k] - qs[k]).TwoNorm();
				const auto cosTheta0 = std::cos(theta0);
				const auto cosTheta1 = std::cos(theta1);
				const auto gamma0 = 0.25*numerator / (Alpha()*cosTheta1 + (1.0 - Alpha())*cosTheta0);
				const auto gamma1 = 0.25*numerator / (Alpha()*cosTheta0 + (1.0 - Alpha())*cosTheta1);

				auto[p0, p1, p2] = calcInnerPoints(gamma0, gamma1, qs[k - 1], Tk[k - 1], qs[k], Tk[k]);
				auto ip = std::make_shared<ThreeInnerPoints>(std::move(p0), std::move(p1), std::move(p2));
				inners.push_back(std::move(ip));
			}
			else
			{
				auto ip = std::make_shared<OneInnerPoint>(std::move(rk));
				inners.push_back(std::move(ip));
			}
		}
		else
		{
			Vec2d dd((qs[k] - qs[k - 1]).XY());
			if (dd.IsParallel(d0, tol) AND dd.IsParallel(d1, tol))
			{
				// This can indicate collinear segments [8/9/2021 Amir]
				auto rk = MEAN(qs[k - 1], qs[k]);

				auto ip = std::make_shared<OneInnerPoint>(std::move(rk));
				inners.push_back(std::move(ip));
			}
			else
			{
				// a 180 deg turn in the curve has been detected [8/9/2021 Amir]

				const auto m = 0.5*(qs[k] - qs[k - 1]).TwoNorm();

				auto[p0, p1, p2] = calcInnerPoints(m, m, qs[k - 1], Tk[k - 1], qs[k], Tk[k]);

				auto ip = std::make_shared<ThreeInnerPoints>(std::move(p0), std::move(p1), std::move(p2));
				inners.push_back(std::move(ip));
			}
		}


		//Dir2d d0(Tk[k - 1].XY());
		//Dir2d d1(Tk[k].XY());

		//

		//Entity2d_Line l0(qs[k - 1], d0);
		//Entity2d_Line l1(qs[k], d1);

		//

		//auto ent = Geo_Tools::Intersection_cgal(l0, l1);

		//if (ent->Result)
		//{
		//	if (ent->IsPoint())
		//	{
		//		auto rk = std::dynamic_pointer_cast<Geo_Tools::PointIntersectEntity2d>(ent)->IntPnt;

		//		auto gamma = (rk - qs[k - 1]).TwoNorm() / Tk[k - 1].TwoNorm();

		//		auto QR = rk - qs[k - 1];
		//		auto N = Tk[k - 1];
		//		N.Rotate90ccw();

		//		if (CrossProduct(QR, N) < 0)
		//		{
		//			gamma *= (-1.0);

		//			std::cout << std::endl;
		//			std::cout << "l0: " << l0.P() <<"; "<< l0.Dir() << std::endl;
		//			std::cout << "l1: " << l1.P()<<"; "<<l1.Dir() << std::endl;
		//			std::cout << "rk: " << rk << std::endl;
		//			std::cout << std::endl;
		//		}

		//		if (gamma < 0)
		//		{
		//			// This indicates either an inflection point or a turn of more than 180 deg [8/9/2021 Amir]
		//			std::cout << " - gamma" << std::endl;
		//			auto u1 = Dir2d((rk - qs[k - 1]).XY());
		//			auto u2 = Dir2d((qs[k] - qs[k - 1]).XY());

		//			auto theta0 = u1.Angle(u2);

		//			auto v1 = Dir2d((qs[k - 1] - qs[k]).XY());
		//			auto v2 = Dir2d((rk - qs[k]).XY());

		//			auto theta1 = v1.Angle(v2);

		//			const auto numerator = (qs[k] - qs[k]).TwoNorm();
		//			const auto cosTheta0 = std::cos(theta0);
		//			const auto cosTheta1 = std::cos(theta1);
		//			const auto gamma0 = 0.25*numerator / (Alpha()*cosTheta1 + (1.0 - Alpha())*cosTheta0);
		//			const auto gamma1 = 0.25*numerator / (Alpha()*cosTheta0 + (1.0 - Alpha())*cosTheta1);

		//			auto[p0, p1, p2] = calcInnerPoints(gamma0, gamma1, qs[k - 1], Tk[k - 1], qs[k], Tk[k]);
		//			auto ip = std::make_shared<ThreeInnerPoints>(std::move(p0), std::move(p1), std::move(p2));
		//			inners.push_back(std::move(ip));
		//		}
		//		else
		//		{
		//			auto ip = std::make_shared<OneInnerPoint>(std::move(rk));
		//			inners.push_back(std::move(ip));
		//		}
		//	}
		//	else if (ent->IsLine())
		//	{
		//		// This can indicate collinear segments [8/9/2021 Amir]
		//		auto rk = MEAN(qs[k - 1], qs[k]);
		//		std::cout << " - line" << std::endl;
		//		auto ip = std::make_shared<OneInnerPoint>(std::move(rk));
		//		inners.push_back(std::move(ip));
		//	}
		//}
		//else
		//{
		//	// a 180 deg turn in the curve has been detected [8/9/2021 Amir]
		//	std::cout << " - turning point" << std::endl;
		//	const auto m = 0.5*(qs[k] - qs[k - 1]).TwoNorm();
		//	
		//	auto[p0, p1, p2] = calcInnerPoints(m, m, qs[k - 1], Tk[k - 1], qs[k], Tk[k]);
		//	auto ip = std::make_shared<ThreeInnerPoints>(std::move(p0), std::move(p1), std::move(p2));
		//	inners.push_back(std::move(ip));
		//}
	}

	std::vector<Pnt2d> Pts;
	std::vector<Pnt2d> nQs;
	std::vector<Pnt2d> Rk;
	std::vector<Pnt2d> Qk;
	if (Continuity() IS_EQUAL continuity::G1)
	{
		for (size_t k = 0; k < n; k++)
		{
			Pts.push_back(qs[k]);
			nQs.push_back(qs[k]);
			Qk.push_back(qs[k]);
			const auto& ip = inners[k];

			if (ip->IsOnePoint())
			{
				auto onePt = std::dynamic_pointer_cast<OneInnerPoint>(ip);
				Debug_Null_Pointer(onePt);

				Pts.push_back(onePt->Point());
				Rk.push_back(onePt->Point());
			}
			else
			{
				auto threePoints = std::dynamic_pointer_cast<ThreeInnerPoints>(ip);
				Debug_Null_Pointer(threePoints);

				Pts.push_back(threePoints->P0());
				Pts.push_back(threePoints->P1());
				Pts.push_back(threePoints->P2());

				nQs.push_back(threePoints->P1());
				Qk.push_back(threePoints->P1());

				Rk.push_back(threePoints->P0());
				Rk.push_back(threePoints->P2());
			}
		}
		Pts.push_back(qs[n]);
		nQs.push_back(qs[n]);
		Qk.push_back(qs[n]);
	}
	else if (Continuity() IS_EQUAL continuity::C1)
	{
		Pts.push_back(qs[0]);
		Rk.push_back(Pnt2d(RealFirst(), RealFirst()));
		for (size_t k = 0; k < n; k++)
		{
			const auto& ip = inners[k];

			nQs.push_back(qs[k]);		
			Qk.push_back(qs[k]);

			if (ip->IsOnePoint())
			{
				auto onePt = std::dynamic_pointer_cast<OneInnerPoint>(ip);
				Debug_Null_Pointer(onePt);

				Pts.push_back(onePt->Point());
				Rk.push_back(onePt->Point());
			}
			else
			{
				auto threePoints = std::dynamic_pointer_cast<ThreeInnerPoints>(ip);
				Debug_Null_Pointer(threePoints);

				Pts.push_back(threePoints->P0());
				Pts.push_back(threePoints->P1());
				Pts.push_back(threePoints->P2());

				nQs.push_back(threePoints->P1());
				Qk.push_back(threePoints->P1());

				Rk.push_back(threePoints->P0());
				Rk.push_back(threePoints->P2());
			}
		}
		Pts.push_back(qs[n]);
		nQs.push_back(qs[n]);
		Qk.push_back(qs[n]);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unrecognized continuity has been detected!" << endl
			<< abort(FatalError);
	}

	TColgp_Array1OfPnt2d poles;
	TColStd_Array1OfReal knots;
	TColStd_Array1OfInteger mult;

	if (Continuity() IS_EQUAL continuity::G1)
	{
		uk = UbarMap()->CalcUk(nQs);

		poles.Resize(1, Pts.size(), Standard_False);
		size_t k = 0;
		for (const auto& x : Pts)
		{
			poles.SetValue(++k, x);
		}

		knots.Resize(1, uk.size(), Standard_False);
		mult.Resize(1, uk.size(), Standard_False);
		k = 0;
		for (auto x : uk)
		{
			knots.SetValue(++k, x);
			mult.SetValue(k, 2);
		}

		mult.SetValue(1, 3);
		mult.SetValue(mult.Size(), 3);
	}
	else if (Continuity() IS_EQUAL continuity::C1)
	{
		poles.Resize(1, Rk.size() + 1, Standard_False);
		size_t k = 0;
		poles.SetValue(++k, Qk[0]);

		for (size_t i = 1; i < Rk.size(); i++)
		{
			poles.SetValue(++k, Rk[i]);
		}

		poles.SetValue(++k, Qk[Qk.size() - 1]);

		const auto n1 = Qk.size() - 1;
		uk.resize(n1 + 1, 0);

		uk[1] = 1.0;
		for (size_t k = 2; k <= n1; k++)
		{
			uk[k] = uk[k - 1] + 
				(uk[k - 1] - uk[k - 2])*(Rk[k] - Qk[k - 1]).TwoNorm() / (Qk[k - 1] - Rk[k - 1]).TwoNorm();
		}

		knots.Resize(1, uk.size(), Standard_False);
		mult.Resize(1, uk.size(), Standard_False);
		for (size_t k = 0; k <= n1; k++)
		{
			knots.SetValue(k + 1, uk[k] / uk[uk.size() - 1]);
			mult.SetValue(k + 1, 1);
		}
		knots.SetValue(1, 0);
		knots.SetValue(knots.Size(), 1);

		mult.SetValue(1, 3);
		mult.SetValue(mult.Size(), 3);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unrecognized continuity has been detected!" << endl
			<< abort(FatalError);
	}

	try
	{
		Handle(Geom2d_Curve) myCurve = new Geom2d_BSplineCurve(poles, knots, mult, 2);
		theCurve_ = std::move(myCurve);
	}
	catch (const Standard_Failure&)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to create bspline curve" << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}

const Handle(Geom2d_Curve)& tnbLib::Cad2d_LocalInterpl::Curve() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}
	return theCurve_;
}

void tnbLib::Cad2d_LocalInterpl::SetUbarMap(const std::shared_ptr<Cad2d_InterpUbarMap>& theMap)
{
	theMap_ = theMap;
}

void tnbLib::Cad2d_LocalInterpl::SetType(const neighborType t)
{
	theType_ = t;
}

void tnbLib::Cad2d_LocalInterpl::SetContinuity(const continuity t)
{
	theContinuity_ = t;
}

void tnbLib::Cad2d_LocalInterpl::SetAlpha(const Standard_Real x)
{
	theAlfa_ = x;
}

void tnbLib::Cad2d_LocalInterpl::SetTolerance(const Standard_Real x)
{
	theTol_ = x;
}