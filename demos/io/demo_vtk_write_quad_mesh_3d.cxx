//
// Created by amir on 8/28/25.
//
#include <tonb/io/vtk/mesh_writer.hxx>
#include <tonb/io/vtk/mesh_reader.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>

#include <filesystem>
#include <iostream>

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

int main(const int argc, char** argv) {
    namespace fs = std::filesystem;
    using namespace tonb;

    try {
        // CLI: optional output path (defaults to $TMP/tonb_demo_quad_mesh.vtp)
        fs::path out_path;
        if (argc > 1) {
            out_path = fs::path(argv[1]);
        } else {
            out_path = fs::temp_directory_path() / "tonb_demo_quad_mesh_3d.vtp";
        }

        // 1) Build a simple 3D quad mesh (two quads forming a rectangle in Z=0 and Z=1)
        std::vector<std::array<real, 3>> points = {
            {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},   // bottom quad
            {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}    // top quad
        };
        std::vector<std::array<index_t, 4>> quads = {
            {0,1,2,3},
            {4,5,6,7}
        };

        std::cout << "Writing: " << out_path << "\n";
        if (!io::vtk::MeshWriter::write_quad_surface_vtp(points, quads, out_path.string())) {
            std::cerr << "Writer failed\n";
            return 2;
        }

        // Read back
        std::vector<std::array<real, 3>> rpts;
        std::vector<std::array<index_t, 4>> rquads;
        if (!io::vtk::MeshReader::read_quad_surface_vtp(out_path.string(), rpts, rquads)) {
            std::cerr << "Reader failed\n";
            return 3;
        }

        // Report
        if (std::array<double,6> bounds{}; compute_bounds_from_points(rpts, bounds)) {
            std::cout << "  Bounds: [" << bounds[0] << "," << bounds[1] << "] x "
                                  << "[" << bounds[2] << "," << bounds[3] << "] x "
                                  << "[" << bounds[4] << "," << bounds[5] << "]\n";
        } else {
            std::cout << "  Bounds: (no points)\n";
        }

        std::cout<<"Done. \n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Demo error: " << e.what() << std::endl;
    }

}