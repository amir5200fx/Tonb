#include <Entity2d_Metric2.hxx>

#include <Entity2d_Metric1.hxx>
#include <armadillo>

using namespace arma;

tnbLib::Entity2d_Metric1 
tnbLib::Entity2d_Metric2::ConvertTo1
(
	const Entity2d_Metric2 & theM2
)
{
	mat22 E;

	E(0, 0) = theM2.E1().X();
	E(1, 0) = theM2.E1().Y();
	E(0, 1) = theM2.E2().X();
	E(1, 1) = theM2.E2().Y();

	mat22 M;

	M(0, 1) = M(1, 0) = 0;
	M(0, 0) = 1.0 / (theM2.H1()*theM2.H1());
	M(1, 1) = 1.0 / (theM2.H2()*theM2.H2());

	M = (E*M)*trans(E);

	auto m = Entity2d_Metric1(M(0, 0), M(0, 1), M(1, 1));
	return std::move(m);
}