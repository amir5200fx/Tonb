#include <Aft2d_OptNodeSurface_Analytical.hxx>

#include <Entity2d_Metric1.hxx>
#include <armadillo>

using namespace arma;

namespace tnbLib
{

	template<>
	void Aft2d_OptNodeSurface_Analytical::Perform()
	{
		static const Standard_Real c3 = 0.86602540378443864676372317075294;

		const auto h = ElementSize();
		auto m0 = Metric();
		if (m0.A() <= 1.0E-6) m0.A() = 1.0E-6;
		if (m0.C() <= 1.0E-6) m0.C() = 1.0E-6;

		const auto invH2 = (Standard_Real)1.0 / (h * h);
		const auto& centre = Front().Centre();

		Debug_Null_Pointer(Front().Node0());
		Debug_Null_Pointer(Front().Node1());

		const auto& v0 = Front().Node0()->Coord();
		const auto& v1 = Front().Node1()->Coord();

		Entity2d_Metric1 m(invH2*m0.A(), invH2*m0.B(), invH2*m0.C());
		const auto D = std::sqrt(m.Determinant());
		const auto cte = c3 / (D * Entity2d_Metric1::Distance(centre, v1, m));
		//const auto cte = c3 / (D * Length());

		auto dU = v1 - centre;

		vec2 U;
		U(0) = dU.X();
		U(1) = dU.Y();

		mat22 orthM;
		orthM(0, 0) = -m.B();
		orthM(0, 1) = -m.C();
		orthM(1, 0) = m.A();
		orthM(1, 1) = m.B();

		U = cte * (orthM * U);

		Pnt2d P(centre.X() + U(0), centre.Y() + U(1));
		ChangeCoord() = std::move(P);

		Change_IsDone() = Standard_True;
	}
}