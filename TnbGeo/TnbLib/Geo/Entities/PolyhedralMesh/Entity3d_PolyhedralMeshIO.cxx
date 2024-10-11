#include <Entity3d_PolyhedralMesh.hxx>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyhedron.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>

void tnbLib::Entity3d_PolyhedralMesh::ExportToVtk(std::fstream& file) const
{
    // 1. Create the points (vertices of the polyhedron)
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (const auto& x: theCoords_)
    {
        points->InsertNextPoint(x.X(), x.Y(), x.Z());
    }
    // 2. Create the unstructured grid that will hold the polyhedron
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    unstructuredGrid->SetPoints(points);

    for (const auto& elm : theElements_)
    {
        vtkSmartPointer<vtkIdList> faces = vtkSmartPointer<vtkIdList>::New();
        for (const auto& f : elm.Faces())
        {
            // Creating the new face
            faces->InsertNextId(f.NbIndices());
            for (const auto i : f.Indices())
            {
                faces->InsertNextId(i);
            }
        }
        vtkSmartPointer<vtkIdList> pointIds = vtkSmartPointer<vtkIdList>::New();
        const auto ids = elm.NodeIds();
        pointIds->SetNumberOfIds(ids.size());
        for (int i = 0; i < ids.size(); i++)
        {
            pointIds->SetId(i, ids.at(i));
        }

        unstructuredGrid->InsertNextCell(VTK_POLYHEDRON, pointIds->GetNumberOfIds(), pointIds->GetPointer(0), elm.NbFaces(), faces->GetPointer(0));
    }

    vtkSmartPointer<vtkUnstructuredGridWriter> legacyWriter = vtkSmartPointer<vtkUnstructuredGridWriter>::New();
    legacyWriter->SetFileName("polyhedron_mesh.vtk");
    legacyWriter->SetInputData(unstructuredGrid);
    legacyWriter->Write();
}