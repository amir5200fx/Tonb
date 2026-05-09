//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>
#if defined (TONB_HAS_VTK)
#include <tonb/io/vtk/mesh_writer.hxx>

#include <tonb/io/vtk/error.hxx>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkQuad.h>
#include <vtkTriangle.h>
#include <vtkXMLPolyDataWriter.h>

namespace tonb::io::vtk {

    bool MeshWriter::write_quad_surface_vtp(const std::vector<std::array<real, 3> > &points,
                                            const std::vector<std::array<index_t, 4> > &quads,
                                            const std::string &file_path, const bool binary) {

        // Convert vertices
        const auto vtkPts = vtkSmartPointer<vtkPoints>::New();
        vtkPts->SetDataTypeToDouble();
        vtkPts->SetNumberOfPoints(static_cast<vtkIdType>(points.size()));
        for (vtkIdType i = 0; i < static_cast<vtkIdType>(points.size()); ++i) {
            vtkPts->SetPoint(i, points[i][0], points[i][1], points[i][2]);
        }

        // Convert quads
        const auto cells = vtkSmartPointer<vtkCellArray>::New();
        for (const auto& q: quads) {
            auto quad = vtkSmartPointer<vtkQuad>::New();
            quad->GetPointIds()->SetId(0, static_cast<vtkIdType>(q[0]));
            quad->GetPointIds()->SetId(1, static_cast<vtkIdType>(q[1]));
            quad->GetPointIds()->SetId(2, static_cast<vtkIdType>(q[2]));
            quad->GetPointIds()->SetId(3, static_cast<vtkIdType>(q[3]));
            cells->InsertNextCell(quad);
        }

        // Build polydata
        const auto poly = vtkSmartPointer<vtkPolyData>::New();
        poly->SetPoints(vtkPts);
        poly->SetPolys(cells);

        // Write file
        const auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
        ErrorToException guard(writer);

        writer->SetFileName(file_path.c_str());
        writer->SetInputData(poly);
        writer->SetDataMode(binary ? vtkXMLWriter::Appended : vtkXMLWriter::Ascii);
        writer->SetCompressorTypeToZLib();

        return writer->Write() == 1;
    }

    bool MeshWriter::write_tri_surface_vtp(const std::vector<std::array<real, 3>> &points,
        const std::vector<std::array<index_t, 3>> &tris, const std::string &file_path, bool binary) {
        // Convert vertices
        const auto vtkPts = vtkSmartPointer<vtkPoints>::New();
        vtkPts->SetDataTypeToDouble();
        vtkPts->SetNumberOfPoints(static_cast<vtkIdType>(points.size()));
        for (vtkIdType i = 0; i < static_cast<vtkIdType>(points.size()); ++i) {
            vtkPts->SetPoint(i, points[i][0], points[i][1], points[i][2]);
        }

        // Convert triangles
        const auto cells = vtkSmartPointer<vtkCellArray>::New();
        for (const auto& t : tris) {
            auto tri = vtkSmartPointer<vtkTriangle>::New();
            tri->GetPointIds()->SetId(0, static_cast<vtkIdType>(t[0]));
            tri->GetPointIds()->SetId(1, static_cast<vtkIdType>(t[1]));
            tri->GetPointIds()->SetId(2, static_cast<vtkIdType>(t[2]));
            cells->InsertNextCell(tri);
        }

        // Build polydata
        const auto poly = vtkSmartPointer<vtkPolyData>::New();
        poly->SetPoints(vtkPts);
        poly->SetPolys(cells);

        // Write file
        const auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
        ErrorToException guard(writer);

        writer->SetFileName(file_path.c_str());
        writer->SetInputData(poly);
        writer->SetDataMode(binary ? vtkXMLWriter::Appended : vtkXMLWriter::Ascii);
        writer->SetCompressorTypeToZLib();

        return writer->Write() == 1;
    }
}
#else
#endif
