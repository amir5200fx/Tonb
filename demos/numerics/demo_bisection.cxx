//
// Created by amir on 11/9/25.
//
#include <tonb/numerics/bisection.hxx>
#include <iostream>

int main() {
    using namespace tonb::numerics;
    auto f = [](const double x) {return std::cos(x) - x;}; // root near 0.739085...

    BisectionOptions opt; opt.max_iters = 200; opt.ftol = 1e-12; opt.xtol = 1e-12;
    auto r = bisection(f, 0.0, 1.0, opt);

    std::cout << "root = " << r.root << ", fval = " << r.fval << ", iters = " << r.iters
            << ", conv = " << r.converged << ", reason = " << static_cast<int>(r.reason) << "\n";
    return EXIT_SUCCESS;
}