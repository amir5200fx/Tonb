#include <GeoIO_VTK.hxx>

#include <Entity3d_Tetrahedralization.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <token.hxx>

void tnbLib::vtkLib::WriteVersion(OFstream& theFile)
{
	theFile << "# vtk DataFile Version 3.0" << endl;
}

void tnbLib::vtkLib::WriteTitle(const std::string& name, OFstream& theFile)
{
	theFile << name 
		<< endl;
}

void tnbLib::vtkLib::WriteFileType_ASCII(OFstream& theFile)
{
	theFile << "ASCII" 
		<< endl;
}

void tnbLib::vtkLib::WriteUnstructuredGrid(OFstream& theFile)
{
	theFile << "DATASET" 
		<< token::SPACE 
		<< "UNSTRUCTURED_GRID" 
		<< endl;
}

void tnbLib::vtkLib::WriteNbPoints(const Standard_Integer theNbPts, OFstream& theFile)
{
	theFile << "POINTS" 
		<< token::SPACE 
		<< theNbPts 
		<< token::SPACE 
		<< "float" 
		<< endl;
}

void tnbLib::vtkLib::WritePoints(const std::vector<Pnt2d>& thePoints, OFstream& theFile)
{
	for (const auto& x : thePoints)
	{
		theFile << x.X() 
			<< token::SPACE 
			<< x.Y() 
			<< token::SPACE 
			<< 0.0 
			<< endl;
	}
}

void tnbLib::vtkLib::WritePoints(const std::vector<Pnt3d>& thePoints, OFstream& theFile)
{
	for (const auto& x : thePoints)
	{
		theFile << x.X()
			<< token::SPACE
			<< x.Y()
			<< token::SPACE
			<< x.Z()
			<< endl;
	}
}

void tnbLib::vtkLib::WriteNbCells(const Standard_Integer theNbCells, const Standard_Integer theNbEntities, OFstream& theFile)
{
	theFile << "CELLS"
		<< token::SPACE 
		<< theNbCells
		<< token::SPACE
		<< theNbEntities 
		<< endl;
}

void tnbLib::vtkLib::WriteCellTypes(const Standard_Integer theNb, OFstream& theFile)
{
	theFile << "CELL_TYPES" 
		<< token::SPACE 
		<< theNb 
		<< endl;
}

void tnbLib::vtkLib::WriteConnectivity(const std::vector<connectivity::triple>& theIds, OFstream& theFile)
{
	for (const auto& x : theIds)
	{
		theFile << 3 
			<< token::SPACE 
			<< x.Value(0) - 1
			<< token::SPACE 
			<< x.Value(1) - 1
			<< token::SPACE 
			<< x.Value(2) - 1
			<< endl;
	}
	WriteCellTypes((Standard_Integer)theIds.size(), theFile);
	for (const auto& x : theIds)
	{
		theFile << 5 << endl;
	}
}

void tnbLib::vtkLib::WriteConnectivity(const std::vector<connectivity::dual>& theIds, OFstream& theFile)
{
	for (const auto& x : theIds)
	{
		theFile << 3 
			<< token::SPACE 
			<< x.Value(0) - 1
			<< token::SPACE 
			<< x.Value(1) - 1
			<< token::SPACE 
			<< x.Value(0) - 1
			<< endl;
	}
	WriteCellTypes((Standard_Integer)theIds.size(), theFile);
	for (const auto& x : theIds)
	{
		theFile << 5 << endl;
	}
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Triangulation& theTri, 
	const std::string& theTitle,
	OFstream& theFile
)
{
	WriteVersion(theFile);
	WriteTitle(theTitle, theFile);
	WriteFileType_ASCII(theFile);
	WriteUnstructuredGrid(theFile);
	WriteNbPoints(theTri.NbPoints(), theFile);
	WritePoints(theTri.Points(), theFile);
	WriteNbCells(theTri.NbConnectivity(), 4 * theTri.NbConnectivity(), theFile);
	WriteConnectivity(theTri.Connectivity(), theFile);
}

void tnbLib::vtkLib::WriteMesh(const Entity3d_Triangulation& theTri, const std::string& theTitle, OFstream& theFile)
{
	WriteVersion(theFile);
	WriteTitle(theTitle, theFile);
	WriteFileType_ASCII(theFile);
	WriteUnstructuredGrid(theFile);
	WriteNbPoints(theTri.NbPoints(), theFile);
	WritePoints(theTri.Points(), theFile);
	WriteNbCells(theTri.NbConnectivity(), 4 * theTri.NbConnectivity(), theFile);
	WriteConnectivity(theTri.Connectivity(), theFile);
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Chain& theTri,
	const std::string& theTitle,
	OFstream& theFile
)
{
	WriteVersion(theFile);
	WriteTitle(theTitle, theFile);
	WriteFileType_ASCII(theFile);
	WriteUnstructuredGrid(theFile);
	WriteNbPoints(theTri.NbPoints(), theFile);
	WritePoints(theTri.Points(), theFile);
	WriteNbCells(theTri.NbConnectivity(), 4 * theTri.NbConnectivity(), theFile);
	WriteConnectivity(theTri.Connectivity(), theFile);
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Polygon& thePoly,
	const std::string& theTitle,
	OFstream& theFile
)
{
	auto chain = Geo_Tools::RetrieveChain(thePoly);
	WriteMesh(*chain, theTitle, theFile);
}

void tnbLib::vtkLib::WriteVersion(std::stringstream& theFile)
{
	theFile << "# vtk DataFile Version 3.0" << endl;
}

void tnbLib::vtkLib::WriteTitle(const std::string& name, std::stringstream& theFile)
{
	theFile << name
		<< endl;
}

void tnbLib::vtkLib::WriteFileType_ASCII(std::stringstream& theFile)
{
	theFile << "ASCII"
		<< endl;
}

void tnbLib::vtkLib::WriteUnstructuredGrid(std::stringstream& theFile)
{
	theFile << "DATASET"
		<< token::SPACE
		<< "UNSTRUCTURED_GRID"
		<< endl;
}

void tnbLib::vtkLib::WriteNbPoints(const Standard_Integer theNbPts, std::stringstream& theFile)
{
	theFile << "POINTS"
		<< token::SPACE
		<< theNbPts
		<< token::SPACE
		<< "float"
		<< endl;
}

void tnbLib::vtkLib::WritePoints(const std::vector<Pnt2d>& thePoints, std::stringstream& theFile)
{
	for (const auto& x : thePoints)
	{
		theFile << x.X()
			<< token::SPACE
			<< x.Y()
			<< token::SPACE
			<< 0.0
			<< endl;
	}
}

void tnbLib::vtkLib::WriteNbCells(const Standard_Integer theNbCells, const Standard_Integer theNbEntities, std::stringstream& theFile)
{
	theFile << "CELLS"
		<< token::SPACE
		<< theNbCells
		<< token::SPACE
		<< theNbEntities
		<< endl;
}

void tnbLib::vtkLib::WriteCellTypes(const Standard_Integer theNb, std::stringstream& theFile)
{
	theFile << "CELL_TYPES"
		<< token::SPACE
		<< theNb
		<< endl;
}

void tnbLib::vtkLib::WriteConnectivity(const std::vector<connectivity::triple>& theIds, std::stringstream& theFile)
{
	for (const auto& x : theIds)
	{
		theFile << 3
			<< token::SPACE
			<< x.Value(0) - 1
			<< token::SPACE
			<< x.Value(1) - 1
			<< token::SPACE
			<< x.Value(2) - 1
			<< endl;
	}
	WriteCellTypes((Standard_Integer)theIds.size(), theFile);
	for (const auto& x : theIds)
	{
		theFile << 5 << endl;
	}
}

void tnbLib::vtkLib::WriteConnectivity(const std::vector<connectivity::dual>& theIds, std::stringstream& theFile)
{
	for (const auto& x : theIds)
	{
		theFile << 3
			<< token::SPACE
			<< x.Value(0) - 1
			<< token::SPACE
			<< x.Value(1) - 1
			<< token::SPACE
			<< x.Value(0) - 1
			<< endl;
	}
	WriteCellTypes((Standard_Integer)theIds.size(), theFile);
	for (const auto& x : theIds)
	{
		theFile << 5 << endl;
	}
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Triangulation& theTri,
	const std::string& theTitle,
	std::stringstream& theFile
)
{
	WriteVersion(theFile);
	WriteTitle(theTitle, theFile);
	WriteFileType_ASCII(theFile);
	WriteUnstructuredGrid(theFile);
	WriteNbPoints(theTri.NbPoints(), theFile);
	WritePoints(theTri.Points(), theFile);
	WriteNbCells(theTri.NbConnectivity(), 4 * theTri.NbConnectivity(), theFile);
	WriteConnectivity(theTri.Connectivity(), theFile);
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Chain& theTri,
	const std::string& theTitle,
	std::stringstream& theFile
)
{
	WriteVersion(theFile);
	WriteTitle(theTitle, theFile);
	WriteFileType_ASCII(theFile);
	WriteUnstructuredGrid(theFile);
	WriteNbPoints(theTri.NbPoints(), theFile);
	WritePoints(theTri.Points(), theFile);
	WriteNbCells(theTri.NbConnectivity(), 4 * theTri.NbConnectivity(), theFile);
	WriteConnectivity(theTri.Connectivity(), theFile);
}

void tnbLib::vtkLib::WriteMesh
(
	const Entity2d_Polygon& thePoly,
	const std::string& theTitle,
	std::stringstream& theFile
)
{
	auto chain = Geo_Tools::RetrieveChain(thePoly);
	WriteMesh(*chain, theTitle, theFile);
}

#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkPoints.h>
#include <vtk/vtkPointData.h>
#include <vtk/vtkCellArray.h>
#include <vtk/vtkDoubleArray.h>
#include <vtk/vtkPolyData.h>
#include <vtk/vtkDataSetWriter.h>

void tnbLib::vtkLib::ExportField(const Entity2d_Triangulation& theMesh, const std::vector<Standard_Real>& theField, std::stringstream& os)
{
	// Create a vtkPoints object to store the vertex coordinates
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	// Add vertex coordinates to the vtkPoints object
	for (const auto& x: theMesh.Points())
	{
		points->InsertNextPoint(x.X(), x.Y(), 0.0);
	}

	// Create a vtkCellArray object to store the connectivity information (triangles)
	vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
	for (const auto& x: theMesh.Connectivity())
	{
		triangles->InsertNextCell(3);
		triangles->InsertCellPoint(x.Value(0) - 1);
		triangles->InsertCellPoint(x.Value(1) - 1);
		triangles->InsertCellPoint(x.Value(2) - 1);
	}

	// Create a vtkPolyData object to store the points, cells, and scalar values
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);
	polyData->SetPolys(triangles);

	// Create a vtkDoubleArray to store scalar values
	vtkSmartPointer<vtkDoubleArray> scalarValues = vtkSmartPointer<vtkDoubleArray>::New();
	scalarValues->SetNumberOfValues(theMesh.NbPoints()); // Set the number of vertices

	// Set scalar values for each vertex
	Standard_Integer k = 0;
	for (auto x: theField)
	{
		scalarValues->SetValue(k++, x);
	}

	// Set the scalar array and name for the scalar data
	polyData->GetPointData()->SetScalars(scalarValues);
	scalarValues->SetName("Scalars");


	vtkSmartPointer<vtkDataSetWriter> writer = vtkSmartPointer<vtkDataSetWriter>::New();
	// For XML-based VTK files, you can use vtkXMLPolyDataWriter
	// vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();

	writer->SetInputData(polyData);
	writer->SetFileName("output.vtk"); // This line is still required, but the file won't be created
	writer->SetWriteToOutputString(1);
	writer->Write();

	
	// Get the string buffer
	os << writer->GetOutputStdString();
}

void tnbLib::vtkLib::ExportField(const Entity3d_Tetrahedralization& theMesh, const std::vector<Standard_Real>& theField,
	std::stringstream& os)
{
	// Create a vtkPoints object to store the vertex coordinates
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	// Add vertex coordinates to the vtkPoints object
	for (const auto& x : theMesh.Points())
	{
		points->InsertNextPoint(x.X(), x.Y(), x.Z());
	}

	// Create a vtkCellArray object to store the connectivity information (triangles)
	vtkSmartPointer<vtkCellArray> triangles = vtkSmartPointer<vtkCellArray>::New();
	for (const auto& x : theMesh.Connectivity())
	{
		triangles->InsertNextCell(3);
		triangles->InsertCellPoint(x.Value(0) - 1);
		triangles->InsertCellPoint(x.Value(1) - 1);
		triangles->InsertCellPoint(x.Value(2) - 1);
	}

	// Create a vtkPolyData object to store the points, cells, and scalar values
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);
	polyData->SetPolys(triangles);

	// Create a vtkDoubleArray to store scalar values
	vtkSmartPointer<vtkDoubleArray> scalarValues = vtkSmartPointer<vtkDoubleArray>::New();
	scalarValues->SetNumberOfValues(theMesh.NbPoints()); // Set the number of vertices

	// Set scalar values for each vertex
	Standard_Integer k = 0;
	for (auto x : theField)
	{
		scalarValues->SetValue(k++, x);
	}

	// Set the scalar array and name for the scalar data
	polyData->GetPointData()->SetScalars(scalarValues);
	scalarValues->SetName("Scalars");


	vtkSmartPointer<vtkDataSetWriter> writer = vtkSmartPointer<vtkDataSetWriter>::New();
	// For XML-based VTK files, you can use vtkXMLPolyDataWriter
	// vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();

	writer->SetInputData(polyData);
	writer->SetFileName("output.vtk"); // This line is still required, but the file won't be created
	writer->SetWriteToOutputString(1);
	writer->Write();


	// Get the string buffer
	os << writer->GetOutputStdString();
}
