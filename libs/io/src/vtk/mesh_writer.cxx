//
// Created by amir on 8/27/25.
//
#include <tonb/io/vtk/mesh_writer.hxx>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkQuad.h>
#include <vtkCallbackCommand.h>
#include <vtkXMLPolyDataWriter.h>

namespace tonb::io::vtk {

    void vtk_throwing_error_callback(vtkObject *caller, unsigned long event_id, void * client_data, void* cell_data) {
        const auto msg = static_cast<const char*>(cell_data);
        throw std::runtime_error(std::string("VTK error: ") + (msg ? msg : ""));
    }

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

        const auto cb = vtkSmartPointer<vtkCallbackCommand>::New();
        cb->SetCallback(vtk_throwing_error_callback);

        // Write file
        const auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
        writer->AddObserver(vtkCommand::ErrorEvent, cb);

        writer->SetFileName(file_path.c_str());
        writer->SetInputData(poly);
        writer->SetDataMode(binary ? vtkXMLWriter::Appended : vtkXMLWriter::Ascii);
        writer->SetCompressorTypeToZLib();

        try {
            return writer->Write() == 1;
        } catch (const std::exception &e) {
            throw std::runtime_error(std::string("MeshWriter::write_quad_surface_vtp: ") + e.what());
        }
    }

}