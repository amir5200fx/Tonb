//
// Created by amir on 8/28/25.
//
#include <tonb/config.hxx>
#if defined(TONB_HAS_VTK)
#include <tonb/io/vtk/mesh_reader.hxx>

#include <tonb/io/vtk/error.hxx>

#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>

namespace tonb::io::vtk {

    bool MeshReader::read_quad_surface_vtp(const std::string &file_path, std::vector<std::array<real, 3> > &points, std::vector<std::array<index_t, 4> > &quads) {
        const auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
        ErrorToException guard(reader);
        reader->SetFileName(file_path.c_str());
        reader->Update();

        vtkPolyData *pd = reader->GetOutput();
        if (!pd) {
            return false;
        }

        // Extract points
        points.resize(static_cast<size_t>(pd->GetNumberOfPoints()));
        for (vtkIdType i = 0; i < pd->GetNumberOfPoints(); ++i) {
            double p[3];
            pd->GetPoint(i, p);
            points[i] = {static_cast<real>(p[0]), static_cast<real>(p[1]), static_cast<real>(p[2])};
        }

        // Extract quads
        quads.clear();
        vtkCellArray *polys = pd->GetPolys();

#if VTK_MAJOR_VERSION >= 9
        vtkIdType npts;
        const vtkIdType *pts;
        polys->InitTraversal();
        while (polys->GetNextCell(npts, pts)) {
            if (npts == 4) {
                quads.push_back({
                static_cast<index_t>(pts[0]),
                static_cast<index_t>(pts[1]),
                static_cast<index_t>(pts[2]),
                static_cast<index_t>(pts[3])});
            }
        }
#else
        // Fallback for pre-VTK 9
        auto idList = vtkSmartPointer<vtkIdList>::New();
        polys->InitTraversal();
        while (polys->GetNextCell(idList)) {
            if (idList->GetNumberOfIds() == 4) {
                quads.push_back({
                static_cast<index_t>(idList->GetId(0)),
                static_cast<index_t>(idList->GetId(1)),
                static_cast<index_t>(idList->GetId(2)),
                static_cast<index_t>(idList->GetId(3))
                });
            }
        }
#endif
        return true;
    }

}
#else
#endif
