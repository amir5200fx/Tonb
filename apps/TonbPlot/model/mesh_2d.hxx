//
// Created by amir on 9/1/25.
//
#pragma once
#include <array>
#include <vector>

struct Mesh2d {
    std::vector<std::array<double, 2>> verts;   // Nx2
    std::vector<std::vector<int>> faces;
};