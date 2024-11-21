#include <Entity2d_Eigen.hxx>

#include <armadillo>

using namespace arma;

void tnbLib::Entity2d_Eigen::CalcGenEigen
(
	const Entity2d_Metric1 & theA,
	const Entity2d_Metric1 & theB
)
{
	//- note: for some reasons "auto" declaration does not work here in "release" mode!
	arma::mat22 A = theA.Arma();
	arma::mat22 B = theB.Arma();
	arma::mat22 L = chol(B, "lower");

	arma::mat22 invL = arma::inv(L);
	arma::mat22 t_invL = arma::trans(invL);
	arma::mat22 C = invL * A*t_invL;

	Entity2d_Eigen gnlzEigen;
	gnlzEigen.CalcEigen(C);

	vec2 e1, e2;
	e1(0) = gnlzEigen.E1().X();
	e1(1) = gnlzEigen.E1().Y();

	e2(0) = gnlzEigen.E2().X();
	e2(1) = gnlzEigen.E2().Y();

	e1 = t_invL * e1;
	e2 = t_invL * e2;

	theLamda1_ = gnlzEigen.Lamda1();
	theLamda2_ = gnlzEigen.Lamda2();

	theH1_ = gnlzEigen.H1();
	theH2_ = gnlzEigen.H2();

	theE1_.X() = e1(0);
	theE1_.Y() = e1(1);

	theE2_.X() = e2(0);
	theE2_.Y() = e2(1);
}