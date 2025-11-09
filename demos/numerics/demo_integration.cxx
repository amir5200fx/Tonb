//
// Created by amir on 11/9/25.
//
#include <tonb/numerics/integration.hxx>
#include <iostream>

int main() {
    using namespace tonb::numerics;
    auto poly = [](double x) {return x*x*x*x;}; // ∫_0^1 x^4 dx = 1/5

    IntegrateOptions o1; o1.atol = 1.e-12; o1.rtol = 1.e-12; o1.kind = IntegratorKind::Simpson;
    const auto r1 = integrate(poly, 0.0, 1.0, o1);
    std::cout << "Simpson I=" << r1.value << " err~=" << r1.error_est << " evals=" <<r1.evals<< " ok=" <<r1.converged<<"\n";

    IntegrateOptions o2; o2.atol=1e-12; o2.rtol=1e-12; o2.kind=IntegratorKind::Gauss7;
    const auto r2 = integrate(poly, 0.0, 1.0, o2);
    std::cout << "Gauss7  I=" << r2.value << " err~=" << r2.error_est << " evals=" << r2.evals << " ok=" << r2.converged << "\n";
    return EXIT_SUCCESS;
}