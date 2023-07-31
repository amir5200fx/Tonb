#include <MeshPost2d_ConvertToOpenFOAM.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <token.hxx>

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::PointList& thePoints
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << " version";
	os.indent();
	os << " 2.0;" << endl;
	os.indent();
	os << " format";
	os.indent();
	os << " ascii;" << endl;
	os.indent();
	os << " class";
	os.indent();
	os << " vectorField;" << endl;
	os.indent();
	os << " object";
	os.indent();
	os << " points;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);

	os << endl
		<< endl
		<< endl;
	os << thePoints.Coords().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : thePoints.Coords())
	{
		auto [xi, yi, zi] = x.Components();
		os
			<< token::BEGIN_LIST
			<< xi
			<< token::SPACE
			<< yi
			<< token::SPACE
			<< zi
			<< token::END_LIST
			<< endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::FaceList& theFaces
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << " version";
	os.indent();
	os << " 2.0;" << endl;
	os.indent();
	os << " format";
	os.indent();
	os << " ascii;" << endl;
	os.indent();
	os << " class";
	os.indent();
	os << " faceList;" << endl;
	os.indent();
	os << " object";
	os.indent();
	os << " faces;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);

	os << endl
		<< endl
		<< endl;
	os << theFaces.Faces().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : theFaces.Faces())
	{
		const auto& nodes = x.Nodes();
		os << nodes.size() << token::BEGIN_LIST << nodes.at(0);
		for (size_t ii = 1; ii < nodes.size(); ii++)
		{
			os << token::SPACE << nodes.at(ii);
		}
		os << token::END_LIST << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::CellList& theCells
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << " version";
	os.indent();
	os << " 2.0;" << endl;
	os.indent();
	os << " format";
	os.indent();
	os << " ascii;" << endl;
	os.indent();
	os << " class";
	os.indent();
	os << " cellList;" << endl;
	os.indent();
	os << " object";
	os.indent();
	os << " cells;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theCells.Cells().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : theCells.Cells())
	{
		const auto& faces = x.Faces();
		os << faces.size() << token::BEGIN_LIST << faces.at(0);
		for (size_t ii = 1; ii < faces.size(); ii++)
		{
			os << token::SPACE << faces.at(ii);
		}
		os << token::END_LIST << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::OwnerList& theOwners
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << " version";
	os.indent();
	os << " 2.0;" << endl;
	os.indent();
	os << " format";
	os.indent();
	os << " ascii;" << endl;
	os.indent();
	os << " class";
	os.indent();
	os << " labelList;" << endl;
	os.indent();
	os << " object";
	os.indent();
	os << " owner;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theOwners.Owners().size() << endl
		<< token::BEGIN_LIST << endl;
	for (auto i : theOwners.Owners())
	{
		os << i << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::NeighborList& theNeighbors
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << " version";
	os.indent();
	os << " 2.0;" << endl;
	os.indent();
	os << " format";
	os.indent();
	os << " ascii;" << endl;
	os.indent();
	os << " class";
	os.indent();
	os << " labelList;" << endl;
	os.indent();
	os << " object";
	os.indent();
	os << " neighbour;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theNeighbors.Neighbors().size() << endl
		<< token::BEGIN_LIST << endl;
	for (auto i : theNeighbors.Neighbors())
	{
		os << i << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(Ostream& os)
{
	os << R"(/*--------------------------------*- C++ -*----------------------------------*\)" << endl
		<< R"(| =========                 |                                                 |)" << endl
		<< R"(| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |)" << endl
		<< R"(|  \\    /   O peration     | Version:  5.0                                   |)" << endl
		<< R"(|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |)" << endl
		<< R"(|    \\/     M anipulation  |                                                 |)" << endl
		<< R"(\*---------------------------------------------------------------------------*/)" << endl;
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(Ostream& os)
{
	os << R"(// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //)" << endl;
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::Export() const
{
	OFstream points("points");
	points << thePoints_;

	OFstream cells("cells");
	cells << theCells_;

	OFstream faces("faces");
	faces << theFaces_;

	OFstream neighbors("neighbour");
	neighbors << theNeighbors_;

	OFstream owner("owner");
	owner << theOwners_;

	OFstream boundary("boundary");
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(boundary);
	boundary << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	boundary.indent();
	boundary << " version";
	boundary.indent();
	boundary << " 2.0;" << endl;
	boundary.indent();
	boundary << " format";
	boundary.indent();
	boundary << " ascii;" << endl;
	boundary.indent();
	boundary << " class";
	boundary.indent();
	boundary << " polyBoundaryMesh;" << endl;
	boundary.indent();
	boundary << " object";
	boundary.indent();
	boundary << " boundary;" << endl;
	boundary << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(boundary);
	boundary << endl
		<< endl
		<< endl;

	boundary << theBoundaryConditions_.size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& bnd : theBoundaryConditions_)
	{
		boundary << "    " << bnd.first << endl;
		boundary << token::BEGIN_BLOCK << endl;
		const auto& d = bnd.second;

		for (const auto& ent : d)
		{
			boundary << "        " << ent.first << "     " << ent.second << ";" << endl;
		}
		boundary << token::END_BLOCK << endl;
	}
	boundary << "    frontAndBack" << endl;
	boundary << token::BEGIN_BLOCK << endl;
	boundary << "        type            empty;" << endl;
	boundary << "        physicalType    empty;" << endl;
	boundary << "        inGroups        1(empty);" << endl;
	boundary << "        nFaces          " << theCells_.Cells().size() << ";" << endl;
	boundary << "        startFace       " << theLastFace_ << ";" << endl;
	boundary << token::END_BLOCK << endl;

	boundary << token::END_LIST << endl;
	boundary << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(boundary);
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::SetBoundaryCondition
(
	const word& theRegion,
	const std::vector<std::pair<word, word>>& theDictionay
)
{
	auto paired = std::make_pair(theRegion, theDictionay);
	theBoundaryConditions_.insert(std::move(paired));
}