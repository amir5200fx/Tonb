//
// Created by amir on 8/28/25.
//
#include <gtest/gtest.h>

#include <tonb/io/vtk/mesh_writer.hxx>
#include <tonb/io/vtk/mesh_reader.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace tonb;

// Returns false if pts is empty; on success, bounds = [xmin, xmax, ymin, ymax, zmin, zmax]
static bool compute_bounds_from_points(const std::vector<std::array<double, 3>>& pts, std::array<double, 6>& bounds) {
    if (pts.empty()) return false;

    double xmin =  std::numeric_limits<double>::infinity();
    double ymin =  std::numeric_limits<double>::infinity();
    double zmin =  std::numeric_limits<double>::infinity();
    double xmax = -std::numeric_limits<double>::infinity();
    double ymax = -std::numeric_limits<double>::infinity();
    double zmax = -std::numeric_limits<double>::infinity();

    for (const auto& p : pts) {
        if (p[0] < xmin) xmin = p[0];
        if (p[0] > xmax) xmax = p[0];
        if (p[1] < ymin) ymin = p[1];
        if (p[1] > ymax) ymax = p[1];
        if (p[2] < zmin) zmin = p[2];
        if (p[2] > zmax) zmax = p[2];
    }

    bounds = {xmin, xmax, ymin, ymax, zmin, zmax};
    return true;
}

TEST(VtkQuadSurfaceMeshIO, RoundTripWriteRead) {
    using P3 = std::array<real, 3>;
    using Q4 = std::array<index_t, 4>;

    // Build a simple 3D quad mesh (two quads)
    std::vector<P3> pts{
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}
    };
    std::vector<Q4> quads = {{0,1,2,3}, {4,5,6,5}};

    // Temp file
    const fs::path out = fs::temp_directory_path() / "tonb_gtest_quad_surface_mesh.vtp";

    ASSERT_TRUE(io::vtk::MeshWriter::write_quad_surface_vtp(pts, quads, out.string(), true));

    std::vector<P3> rpts;
    std::vector<Q4> rquads;
    ASSERT_TRUE(io::vtk::MeshReader::read_quad_surface_vtp(out.string(), rpts, rquads));

    // Counts
    EXPECT_EQ(rpts.size(), pts.size());
    EXPECT_EQ(rquads.size(), quads.size());

    // Bounds (no VTK)
    std::array<real, 6> b{};
    ASSERT_TRUE(compute_bounds_from_points(rpts, b));
    EXPECT_DOUBLE_EQ(b[0], 0.0); EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 0.0); EXPECT_DOUBLE_EQ(b[3], 1.0);
    EXPECT_DOUBLE_EQ(b[4], 0.0); EXPECT_DOUBLE_EQ(b[5], 1.0);
}