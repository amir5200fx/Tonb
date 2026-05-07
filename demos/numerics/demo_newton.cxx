//
// Created by amir on 11/9/25.
//
#include <tonb/numerics/newton.hxx>
#include <iostream>

int main() {
    using namespace tonb::numerics;
    // Solve cos(x) - x = 0, bracketed and unbracketed
    auto f = [](const double x) {return std::cos(x) - x;};
    auto df = [](const double x) {return -std::sin(x) - 1.0;};

    NewtonOptions opt;
    opt.max_iter = 50;
    opt.min_iter = 2;
    opt.xtol = 1e-12;
    opt.ftol = 1e-12;
    const auto r1 = newton(f, df, 0.5, opt);
    std::cout << "x=" << r1.x << " f=" << r1.f << " iters=" << r1.iters << " conv=" << r1.converged << "\n";

    NewtonOptions s = opt; s.bracket = std::pair(0.0, 1.0); s.require_bracket = true;
    const auto r2 = newton(f, df, 0.5, s);
    std::cout << "[a,b]=[" << r2.a << "," << r2.b << "] x=" << r2.x << " f=" << r2.f << " conv=" << r2.converged << "\n";
    return EXIT_SUCCESS;
}