#include <TecPlot.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

void tnbLib::Io::WriteVariables
(
	const word & theVariables,
	OFstream & theFile
)
{
	theFile << " VARIABLES = " << theVariables << endl;
}

void tnbLib::Io::WritePointsVariables
(
	const std::vector<Pnt2d>& thePoints,
	OFstream & File
)
{
	std::vector<Standard_Real> X, Y;
	X.reserve(thePoints.size());
	Y.reserve(thePoints.size());

	for (const auto& x : thePoints)
	{
		X.push_back(x.X());
		Y.push_back(x.Y());
	}

	for (const auto& x : X)
		File << x << "  ";
	File << endl;
	for (const auto& x : Y)
		File << x << "  ";
	File << endl;
}

void tnbLib::Io::WriteFeTriangleZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTriangles,
	OFstream & theFile
)
{
	theFile
		<< " ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTriangles
		<< ", DATAPACKING= POINT, ZONETYPE= FETRIANGLE";
	theFile << endl;
}

void tnbLib::Io::WriteFeTetrahedralZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTets,
	OFstream & theFile
)
{
	theFile
		<< "ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTets
		<< ", DATAPACKING= POINT, ZONETYPE= FETETRAHEDRON";
	theFile << endl;
}

void tnbLib::Io::WriteCellCenteredFeTriangularZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTris,
	const Standard_Integer NbVar,
	OFstream & theFile
)
{
	theFile
		<< "ZONE N= "
		<< NbNodes
		<< ", E= "
		<< NbTris
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theFile << 3 + K;
		++K;
		if (K >= NbVar) break;
		theFile << "  ";
	}
	theFile << "]=CELLCENTERED)\n";
	theFile << endl;
}

void tnbLib::Io::WriteCellCenteredFeTriangular3DZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTris,
	const Standard_Integer NbVar,
	OFstream & theFile
)
{
	theFile
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbTris
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2,3]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theFile << 4 + K;
		++K;
		if (K >= NbVar) break;
		theFile << "  ";
	}
	theFile << "]=CELLCENTERED)\n";
	theFile << endl;
}

void tnbLib::Io::WriteCellCenteredFeTetrahedralZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTets,
	const Standard_Integer NbVar,
	OFstream & theFile
)
{
	theFile
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbTets
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETETRAHEDRON, VARLOCATION=([1,2,3]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theFile << 4 + K;
		++K;
		if (K >= NbVar) break;
		theFile << "  ";
	}
	theFile << "]=CELLCENTERED)\n";
	theFile << endl;
}

void tnbLib::Io::WriteFeBrickZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbBricks,
	OFstream & theFile
)
{
	theFile
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbBricks
		<< ", DATAPACKING=POINT, ZONETYPE=FEBRICK";
	theFile << endl;
}

void tnbLib::Io::WriteIorderedZone
(
	const Standard_Integer NbNodes,
	OFstream & theFile
)
{
	theFile
		<< "ZONE I= "
		<< NbNodes
		<< ", DATAPACKING=BLOCK";
	theFile << endl;
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt2d>& Points,
	const std::vector<connectivity::triple>& Triangles,
	OFstream & File
)
{
	if (Points.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y", File);

	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Triangles.size(), File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	for (const auto& x : Triangles)
	{
		File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt2d>& Points,
	const std::vector<connectivity::dual>& Triangles,
	OFstream & File
)
{
	if (Points.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y", File);

	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Triangles.size(), File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	for (const auto& x : Triangles)
	{
		File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(0) << endl;
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& Points,
	const std::vector<connectivity::triple>& Triangles,
	OFstream & File
)
{
	if (Points.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y Z", File);

	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Triangles.size(), File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	for (const auto& x : Triangles)
	{
		File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& Points,
	const std::vector<connectivity::dual>& Triangles,
	OFstream & File
)
{
	if (Points.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y Z", File);

	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Triangles.size(), File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	for (const auto& x : Triangles)
	{
		File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(1) << endl;
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& thePoints,
	const std::vector<connectivity::quadruple>& theTets, 
	OFstream& File
)
{
	if (thePoints.empty()) return;
	if (theTets.empty()) return;

	WriteVariables("X Y Z", File);

	WriteFeTetrahedralZone((Standard_Integer)thePoints.size(), (Standard_Integer)theTets.size(), File);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(File);
		File << endl;
	}

	for (const auto& x : theTets)
	{
		File << x.Value(0) << " " << x.Value(1) << " " << x.Value(2) << " " << x.Value(3) << endl;
	}
}

void tnbLib::Io::ExportCurve
(
	const std::vector<Pnt3d>& Points,
	OFstream & File
)
{
	if (Points.empty()) return;

	WriteVariables("X Y Z", File);
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size() - 1, File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	forThose(Index, 1, Points.size() - 1)
	{
		File << Index << "  " << Index + 1 << "  " << Index << endl;
	}
}

void tnbLib::Io::ExportCurve
(
	const std::vector<Pnt2d>& Points,
	OFstream & File
)
{
	if (Points.empty()) return;

	WriteVariables("X Y", File);
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size() - 1, File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	forThose(Index, 1, Points.size() - 1)
	{
		File << Index << "  " << Index + 1 << "  " << Index << endl;
	}
}

void tnbLib::Io::ExportPoints
(
	const std::vector<Pnt3d>& Points,
	OFstream & File
)
{
	if (Points.empty()) return;

	WriteVariables("X Y Z", File);
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size() - 1, File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	forThose(Index, 1, Points.size())
	{
		File << Index << "  " << Index << "  " << Index << endl;
	}
}

void tnbLib::Io::ExportPoints
(
	const std::vector<Pnt2d>& Points,
	OFstream & File
)
{
	if (Points.empty()) return;

	WriteVariables("X Y", File);
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size() - 1, File);

	for (const auto& x : Points)
	{
		x.AddToPlt(File);
		File << endl;
	}

	forThose(Index, 1, Points.size())
	{
		File << Index << "  " << Index << "  " << Index << endl;
	}
}