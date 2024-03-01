#include <TecPlot.hxx>

#include <Entity3d_CmpConnect.hxx>
#include <Entity2d_CmpConnect.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <token.hxx>

void tnbLib::Io::WriteVariables
(
	const word& theVariables,
	std::stringstream& theStream
)
{
	theStream << " VARIABLES = " << theVariables << "\n";
}

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
	std::stringstream& theStream
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
		theStream << std::setw(15) << x << "  ";
	theStream << "\n";
	for (const auto& x : Y)
		theStream << std::setw(15) << x << "  ";
	theStream << "\n";
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

void tnbLib::Io::WriteFeTriangleZone(const Standard_Integer NbNodes, const Standard_Integer NbTriangles,
	std::stringstream& theStream)
{
	theStream
		<< " ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTriangles
		<< ", DATAPACKING= POINT, ZONETYPE= FETRIANGLE\n";
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

void tnbLib::Io::WriteFeQuadrilateralZone(const Standard_Integer NbNodes, const Standard_Integer NbTriangles,
	std::stringstream& theStream)
{
	theStream
		<< " ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTriangles
		<< ", DATAPACKING= POINT, ZONETYPE= FEQUADRILATERAL\n";
}

void tnbLib::Io::WriteFeQuadrilateralZone
(
	const Standard_Integer NbNodes,
	const Standard_Integer NbTriangles,
	OFstream& theFile
)
{
	theFile
		<< " ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTriangles
		<< ", DATAPACKING= POINT, ZONETYPE= FEQUADRILATERAL";
	theFile << endl;
}

void tnbLib::Io::WriteFeTetrahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbTets,
	std::stringstream& theStream)
{
	theStream
		<< "ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbTets
		<< ", DATAPACKING= POINT, ZONETYPE= FETETRAHEDRON\n";
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

void tnbLib::Io::WriteFeHexahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbElements,
	OFstream& theFile)
{
	theFile
		<< "ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbElements
		<< ", DATAPACKING= POINT, ZONETYPE= FEBRICK";
	theFile << endl;
}

void tnbLib::Io::WriteFeHexahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbElements,
	std::stringstream& theStream)
{
	theStream
		<< "ZONE N = "
		<< NbNodes
		<< ", E = "
		<< NbElements
		<< ", DATAPACKING= POINT, ZONETYPE= FEBRICK\n";
}

void tnbLib::Io::WriteCellCenteredFeTriangularZone(const Standard_Integer NbNodes, const Standard_Integer NbTris,
                                                   const Standard_Integer NbVar, std::stringstream& theStream)
{
	theStream
		<< "ZONE N= "
		<< NbNodes
		<< ", E= "
		<< NbTris
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theStream << 3 + K;
		++K;
		if (K >= NbVar) break;
		theStream << "  ";
	}
	theStream << "]=CELLCENTERED)\n";
	theStream << "\n";
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

void tnbLib::Io::WriteCellCenteredFeTriangular3DZone(const Standard_Integer NbNodes, const Standard_Integer NbTris,
	const Standard_Integer NbVar, std::stringstream& theStream)
{
	theStream
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbTris
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETRIANGLE, VARLOCATION=([1,2,3]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theStream << 4 + K;
		++K;
		if (K >= NbVar) break;
		theStream << "  ";
	}
	theStream << "]=CELLCENTERED)\n";
	theStream << "\n";
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

void tnbLib::Io::WriteCellCenteredFeTetrahedralZone(const Standard_Integer NbNodes, const Standard_Integer NbTets,
	const Standard_Integer NbVar, std::stringstream& theStream)
{
	theStream
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbTets
		<< ", DATAPACKING=BLOCK, ZONETYPE=FETETRAHEDRON, VARLOCATION=([1,2,3]=NODAL, [";
	Standard_Integer K = 0;
	while (Standard_True)
	{
		theStream << 4 + K;
		++K;
		if (K >= NbVar) break;
		theStream << "  ";
	}
	theStream << "]=CELLCENTERED)\n";
	theStream << "\n";
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

void tnbLib::Io::WriteFeBrickZone(const Standard_Integer NbNodes, const Standard_Integer NbBricks,
	std::stringstream& theStream)
{
	theStream
		<< "ZONE N= "
		<< NbNodes
		<< ", E = "
		<< NbBricks
		<< ", DATAPACKING=POINT, ZONETYPE=FEBRICK";
	theStream << "\n";
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
	std::stringstream& theStream
)
{
	theStream
		<< "ZONE I= "
		<< NbNodes
		<< ", DATAPACKING=BLOCK";
	theStream << "\n";
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
	const std::vector<Pnt2d>& thePoints,
	const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theElements,
	OFstream& theFile
)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y", theFile);
	WriteFeQuadrilateralZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		theFile
	);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theFile);
		theFile << endl;
	}
	for (const auto& x : theElements)
	{
		auto ids = x->Components();
		if (ids.size() IS_EQUAL 3)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 4)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< endl;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt2d>& thePoints, const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theElements,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y", theStream);
	WriteFeQuadrilateralZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		theStream
	);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}
	for (const auto& x : theElements)
	{
		auto ids = x->Components();
		if (ids.size() IS_EQUAL 3)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< "\n";
		}
		else if (ids.size() IS_EQUAL 4)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< "\n";
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
		}
	}
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

	WriteFeTriangleZone(static_cast<Standard_Integer>(Points.size()), static_cast<Standard_Integer>(Triangles.size()), File);

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

void tnbLib::Io::ExportMesh(const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::triple>& Triangles,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y", theStream);

	WriteFeTriangleZone(static_cast<Standard_Integer>(thePoints.size()), static_cast<Standard_Integer>(Triangles.size()), theStream);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	for (const auto& x : Triangles)
	{
		theStream << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << "\n";
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& thePoints,
	std::vector<std::shared_ptr<Entity3d_CmpConnect>>& theElements,
	OFstream& theFile
)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y Z", theFile);
	WriteFeBrickZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		theFile
	);
	for (const auto& x : thePoints)
	{
		x.AddToPlt(theFile);
		theFile << endl;
	}
	for (const auto& x : theElements)
	{
		auto ids = x->Components();
		if (ids.size() IS_EQUAL 8)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(5)
				<< token::SPACE
				<< ids.at(6)
				<< token::SPACE
				<< ids.at(7)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 6)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(5)
				<< token::SPACE
				<< ids.at(5)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 5)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 4)
		{
			theFile << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< endl;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< " nb. of points = " << ids.size() << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt3d>& thePoints, std::vector<std::shared_ptr<Entity3d_CmpConnect>>& theElements,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y Z", theStream);
	WriteFeBrickZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		theStream
	);
	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}
	for (const auto& x : theElements)
	{
		auto ids = x->Components();
		if (ids.size() IS_EQUAL 8)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(5)
				<< token::SPACE
				<< ids.at(6)
				<< token::SPACE
				<< ids.at(7)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 6)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(5)
				<< token::SPACE
				<< ids.at(5)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 5)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< token::SPACE
				<< ids.at(4)
				<< endl;
		}
		else if (ids.size() IS_EQUAL 4)
		{
			theStream << ids.at(0)
				<< token::SPACE
				<< ids.at(1)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(2)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< token::SPACE
				<< ids.at(3)
				<< endl;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of element has been detected." << endl
				<< " nb. of points = " << ids.size() << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt2d>& thePoints,
	const std::vector<connectivity::quadruple>& theElements,
	OFstream& File
)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y", File);
	WriteFeQuadrilateralZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		File
	);
	for (const auto& x : thePoints)
	{
		x.AddToPlt(File);
		File << endl;
	}
	for (const auto& x : theElements)
	{
		File << x.Value(0)
			<< token::SPACE
			<< x.Value(1)
			<< token::SPACE
			<< x.Value(2)
			<< token::SPACE
			<< x.Value(3)
			<< endl;
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt2d>& thePoints,
	const std::vector<connectivity::quadruple>& theElements, std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y", theStream);
	WriteFeQuadrilateralZone
	(
		static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()),
		theStream
	);
	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}
	for (const auto& x : theElements)
	{
		theStream << x.Value(0)
			<< token::SPACE
			<< x.Value(1)
			<< token::SPACE
			<< x.Value(2)
			<< token::SPACE
			<< x.Value(3)
			<< "\n";
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

void tnbLib::Io::ExportMesh(const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::dual>& Triangles,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y", theStream);

	WriteFeTriangleZone((Standard_Integer)thePoints.size(), (Standard_Integer)Triangles.size(), theStream);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	for (const auto& x : Triangles)
	{
		theStream << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(0) << "\n";
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
		File
		<< x.Value(0)
		<< "  "
		<< x.Value(1)
		<< "  "
		<< x.Value(2)
		<< endl;
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::triple>& Triangles,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y Z", theStream);

	WriteFeTriangleZone((Standard_Integer)thePoints.size(), (Standard_Integer)Triangles.size(), theStream);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	for (const auto& x : Triangles)
	{
		theStream
		<< x.Value(0)
		<< "  "
		<< x.Value(1)
		<< "  "
		<< x.Value(2)
		<< "\n";
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
		File
		<< x.Value(0)
		<< "  "
		<< x.Value(1)
		<< "  "
		<< x.Value(1)
		<< endl;
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::dual>& Triangles,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (Triangles.empty()) return;

	WriteVariables("X Y Z", theStream);

	WriteFeTriangleZone((Standard_Integer)thePoints.size(), (Standard_Integer)Triangles.size(), theStream);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	for (const auto& x : Triangles)
	{
		theStream
		<< x.Value(0)
		<< "  "
		<< x.Value(1)
		<< "  "
		<< x.Value(1)
		<< "\n";
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
		File
		<< x.Value(0)
		<< " "
		<< x.Value(1)
		<< " "
		<< x.Value(2)
		<< " "
		<< x.Value(3)
		<< endl;
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& thePoints,
	const std::vector<connectivity::quadruple>& theTets,
	std::stringstream& theStream
)
{
	if (thePoints.empty()) return;
	if (theTets.empty()) return;

	WriteVariables("X Y Z", theStream);

	WriteFeTetrahedralZone
	(
		(Standard_Integer)thePoints.size(), 
		(Standard_Integer)theTets.size(), 
		theStream
	);

	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	for (const auto& x : theTets)
	{
		theStream
		<< x.Value(0)
		<< " "
		<< x.Value(1)
		<< " "
		<< x.Value(2)
		<< " "
		<< x.Value(3)
		<< "\n";
	}
}

void tnbLib::Io::ExportMesh
(
	const std::vector<Pnt3d>& thePoints,
	const std::vector<connectivity::octuple>& theElements,
	OFstream& theFile
)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y Z", theFile);
	WriteFeHexahedralZone(static_cast<Standard_Integer>(thePoints.size()),
	                      static_cast<Standard_Integer>(theElements.size()), theFile);
	for (const auto& x: thePoints)
	{
		x.AddToPlt(theFile);
		theFile << "\n";
	}
	for (const auto& i: theElements)
	{
		theFile
			<< i.Value(0) << " "
			<< i.Value(1) << " "
			<< i.Value(2) << " "
			<< i.Value(3) << " "
			<< i.Value(4) << " "
			<< i.Value(5) << " "
			<< i.Value(6) << " "
			<< i.Value(7) << "\n";
	}
}

void tnbLib::Io::ExportMesh(const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
	std::stringstream& theStream)
{
	if (thePoints.empty()) return;
	if (theElements.empty()) return;

	WriteVariables("X Y Z", theStream);
	WriteFeHexahedralZone(static_cast<Standard_Integer>(thePoints.size()),
		static_cast<Standard_Integer>(theElements.size()), theStream);
	for (const auto& x : thePoints)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}
	for (const auto& i : theElements)
	{
		theStream
			<< i.Value(0) << " "
			<< i.Value(1) << " "
			<< i.Value(2) << " "
			<< i.Value(3) << " "
			<< i.Value(4) << " "
			<< i.Value(5) << " "
			<< i.Value(6) << " "
			<< i.Value(7) << "\n";
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
	WriteFeTriangleZone
	(
		(Standard_Integer)Points.size(), 
		(Standard_Integer)Points.size() - 1, 
		File
	);

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

void tnbLib::Io::ExportCurve(const std::vector<Pnt3d>& Points, std::stringstream& theStream)
{
	if (Points.empty()) return;

	WriteVariables("X Y Z", theStream);
	WriteFeTriangleZone
	(
		(Standard_Integer)Points.size(),
		(Standard_Integer)Points.size() - 1,
		theStream
	);

	for (const auto& x : Points)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	forThose(Index, 1, Points.size() - 1)
	{
		theStream << Index << "  " << Index + 1 << "  " << Index << "\n";
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

void tnbLib::Io::ExportCurve
(
	const std::vector<Pnt2d>& Points,
	std::stringstream& theStream
)
{
	if (Points.empty()) return;

	WriteVariables("X Y", theStream);
	WriteFeTriangleZone
	(
		(Standard_Integer)Points.size(), 
		(Standard_Integer)Points.size() - 1,
		theStream
	);

	for (const auto& x : Points)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	forThose(Index, 1, Points.size() - 1)
	{
		theStream << Index << "  " << Index + 1 << "  " << Index << "\n";
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
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size(), File);

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
	const std::vector<Pnt3d>& Points,
	std::stringstream& theStream
)
{
	if (Points.empty()) return;

	WriteVariables("X Y Z", theStream);
	WriteFeTriangleZone
	(
		(Standard_Integer)Points.size(),
		(Standard_Integer)Points.size(),
		theStream
	);

	for (const auto& x : Points)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	forThose(Index, 1, Points.size())
	{
		theStream << Index << "  " << Index << "  " << Index << "\n";
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
	WriteFeTriangleZone((Standard_Integer)Points.size(), (Standard_Integer)Points.size(), File);

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
	std::stringstream& theStream
)
{
	if (Points.empty()) return;

	WriteVariables("X Y", theStream);
	WriteFeTriangleZone
	(
		(Standard_Integer)Points.size(),
		(Standard_Integer)Points.size(),
		theStream
	);

	for (const auto& x : Points)
	{
		x.AddToPlt(theStream);
		theStream << "\n";
	}

	forThose(Index, 1, Points.size())
	{
		theStream << Index << "  " << Index << "  " << Index << "\n";
	}
}
