#include <Entity2d_Metric1.hxx>

#include <Entity2d_Eigen.hxx>

using namespace tnbLib;
using namespace arma;

//Entity2d_Metric1 Entity2d_Metric1::IntersectionSR(const metric & M1, const metric & M2)
//{
//	mat22 m1 = M1.Arma();
//	mat22 m2 = M2.Arma();
//
//	mat22 N1 = inv(m1)*m2;
//
//	metric N(N1(0, 0), N1(0, 1), N1(1, 1));
//
//	Entity2d_Eigen Eigen;
//	Eigen.CalcEigen(N);
//
//	vec2 E1, E2;
//	E1(0) = Eigen.E1().X();
//	E1(1) = Eigen.E1().Y();
//	E2(0) = Eigen.E2().X();
//	E2(1) = Eigen.E2().Y();
//
//	mat Lamda1 = trans(E1)*m1*E1;
//	mat Lamda2 = trans(E2)*m1*E2;
//	mat Mu1 = trans(E1)*m2*E1;
//	mat Mu2 = trans(E2)*m2*E2;
//
//	mat22 S;
//	S(0, 0) = Eigen.E1().X();
//	S(1, 0) = Eigen.E1().Y();
//	S(0, 1) = Eigen.E2().X();
//	S(1, 1) = Eigen.E2().Y();
//
//	Entity2d_Eigen Eigen1, Eigen2;
//	Eigen1.CalcEigen(M1);
//	Eigen2.CalcEigen(M2);
//
//	mat22 H;
//	H(0, 0) = MAX(Lamda1(0, 0), Mu1(0, 0));
//	H(1, 0) = H(0, 1) = 0;
//	H(1, 1) = MAX(Lamda2(0, 0), Mu2(0, 0));
//
//	S = inv(trans(S))*H*inv(S);
//
//	Entity2d_Metric1 m(S(0, 0), S(1, 0), S(1, 1));
//	return std::move(m);
//}

tnbLib::Entity2d_Metric1::metric 
tnbLib::Entity2d_Metric1::IntersectionSR
(
	const metric & M1, 
	const metric & M2
)
{
	auto m1 = M1.Arma();
	auto m2 = M2.Arma();

	Entity2d_Eigen eigen;
	eigen.CalcGenEigen(M1, M2);

	mat22 S;
	S(0, 0) = eigen.E1().X();
	S(1, 0) = eigen.E1().Y();
	S(0, 1) = eigen.E2().X();
	S(1, 1) = eigen.E2().Y();

	vec2 E1, E2;
	E1(0) = eigen.E1().X();
	E1(1) = eigen.E1().Y();
	E2(0) = eigen.E2().X();
	E2(1) = eigen.E2().Y();

	mat Lamda1 = trans(E1)*m1*E1;
	mat Lamda2 = trans(E2)*m1*E2;
	mat Mu1 = trans(E1)*m2*E1;
	mat Mu2 = trans(E2)*m2*E2;

	Entity2d_Eigen eigen1, eigen2;
	eigen1.CalcEigen(M1);
	eigen2.CalcEigen(M2);

	mat22 H;
	H(0, 0) = MAX(Lamda1(0, 0), Mu1(0, 0));
	H(1, 0) = H(0, 1) = 0;
	H(1, 1) = MAX(Lamda2(0, 0), Mu2(0, 0));

	S = inv(trans(S))*H*inv(S);

	Entity2d_Metric1 m(S(0, 0), S(1, 0), S(1, 1));
	return std::move(m);
}

tnbLib::Entity2d_Metric1::metric 
tnbLib::Entity2d_Metric1::IntersectionPD
(
	const metric & M1,
	const metric & M2
)
{
	Entity2d_Eigen Eigen1, Eigen2;
	Eigen1.CalcEigen(M1);
	Eigen2.CalcEigen(M2);

	Standard_Real Omega = 
		MAX(1, MAX(Eigen2.Lamda1() / Eigen1.Lamda1(), Eigen2.Lamda2() / Eigen1.Lamda2()));

	return metric(M1*Omega);
}

tnbLib::Entity2d_Metric1::metric 
tnbLib::Entity2d_Metric1::UnionSR
(
	const metric & M1,
	const metric & M2
)
{
	auto m1 = M1.Arma();
	auto m2 = M2.Arma();

	Entity2d_Eigen eigen;
	eigen.CalcGenEigen(M1, M2);

	mat22 S;
	S(0, 0) = eigen.E1().X();
	S(1, 0) = eigen.E1().Y();
	S(0, 1) = eigen.E2().X();
	S(1, 1) = eigen.E2().Y();

	vec2 E1, E2;
	E1(0) = eigen.E1().X();
	E1(1) = eigen.E1().Y();
	E2(0) = eigen.E2().X();
	E2(1) = eigen.E2().Y();

	mat Lamda1 = trans(E1)*m1*E1;
	mat Lamda2 = trans(E2)*m1*E2;
	mat Mu1 = trans(E1)*m2*E1;
	mat Mu2 = trans(E2)*m2*E2;

	Entity2d_Eigen eigen1, eigen2;
	eigen1.CalcEigen(M1);
	eigen2.CalcEigen(M2);

	mat22 H;
	H(0, 0) = MIN(Lamda1(0, 0), Mu1(0, 0));
	H(1, 0) = H(0, 1) = 0;
	H(1, 1) = MIN(Lamda2(0, 0), Mu2(0, 0));

	S = inv(trans(S))*H*inv(S);

	Entity2d_Metric1 m(S(0, 0), S(1, 0), S(1, 1));
	return std::move(m);
}

//tnbLib::Entity2d_Metric1::metric 
//tnbLib::Entity2d_Metric1::IntersectionPD_Inverse
//(
//	const metric & M1,
//	const metric & M2
//)
//{
//	Entity2d_Eigen Eigen1, Eigen2;
//	Eigen1.CalcEigen(M1);
//	Eigen2.CalcEigen(M2);
//
//	Standard_Real Omega =
//		MAX(1, MAX(Eigen2.Lamda1() / Eigen1.Lamda1(), Eigen2.Lamda2() / Eigen1.Lamda2()));
//
//	return metric(M1*Omega);
//}

tnbLib::Entity2d_Metric1::metric 
tnbLib::Entity2d_Metric1::InterpolationIM
(
	const Standard_Real t,
	const metric & M1,
	const metric & M2
)
{
	mat22 m1 = inv(M1.Arma());
	mat22 m2 = inv(M2.Arma());

	mat22 M = inv((1.0 - t)*m1 + t * m2);

	return metric(M(0, 0), M(1, 0), M(1, 1));
}

Entity2d_Metric1 tnbLib::Entity2d_Metric1::InterpolationIM
(
	const Standard_Real c1, 
	const Standard_Real c2, 
	const Standard_Real c3,
	const metric & M1,
	const metric & M2,
	const metric & M3
)
{
	mat22 m1, m2, m3;
	Standard_Real C1, C2, C3;

	if (M1.Determinant() < EPS6)
	{
		m1.fill(0);
		C1 = 0;
	}
	else
	{
		m1 = inv(M1.Arma());
		C1 = c1;
	}

	if (M2.Determinant() < EPS6)
	{
		m2.fill(0);
		C2 = 0;
	}
	else
	{
		m2 = inv(M2.Arma());
		C2 = c2;
	}

	if (M3.Determinant() < EPS6)
	{
		m3.fill(0);
		C3 = 0;
	}
	else
	{
		m3 = inv(M3.Arma());
		C3 = c3;
	}

	mat22 m = C1 * m1 + C2 * m2 + C3 * m3;

	if (C1 == 0 AND C2 == 0 AND C3 == 0)
	{
		return metric(0, 0, 0);
	}

	mat22 M = inv(m);

	return metric(M(0, 0), M(1, 0), M(1, 1));
}

