#include <MeshPost_Gambit.hxx>

#include <Geo3d_FVMesh.hxx>
#include <Geo_ElemGeom.hxx>

#define END_SECTION_EXPR "ENDOFSECTION"
#define VERSION_EXPR "1.2.1"
#define NB_VALUES_EACH_DATA_RECORD 0

#include <iostream>
#include <ctime>

namespace tnbLib
{

	const char* monthNames[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};

	static std::map<std::string, unsigned short> element_geom_type;

	class ElementGeomType_RunTime
	{

		/*Private Data*/

		void RunTime();

	public:

		// default constructor [8/15/2023 aamir]

		ElementGeomType_RunTime()
		{
			RunTime();
		}

	};

	static std::map<std::string, unsigned short> boundary_entity_type;

	class BoundaryEntityType_RunTime
	{

		/*Private Data*/

		void RunTime();

	public:

		// default constructor [8/15/2023 aamir]

		BoundaryEntityType_RunTime()
		{
			RunTime();
		}

	};
}

void tnbLib::ElementGeomType_RunTime::RunTime()
{
	element_geom_type.insert(std::make_pair("edge", 1));
	element_geom_type.insert(std::make_pair("quadrilateral", 2));
	element_geom_type.insert(std::make_pair("triangle", 3));
	element_geom_type.insert(std::make_pair("brick", 4));
	element_geom_type.insert(std::make_pair("wedge", 5));
	element_geom_type.insert(std::make_pair("tetrahedron", 6));
	element_geom_type.insert(std::make_pair("pyramid", 7));
}

void tnbLib::BoundaryEntityType_RunTime::RunTime()
{
	boundary_entity_type.insert(std::make_pair("unspecified", (unsigned short)MeshPost_Gambit::UNSPECIFIED));
	boundary_entity_type.insert(std::make_pair("axis", (unsigned short)MeshPost_Gambit::AXIS));
	boundary_entity_type.insert(std::make_pair("conjugate", (unsigned short)MeshPost_Gambit::CONJUGATE));
	boundary_entity_type.insert(std::make_pair("convection", (unsigned short)MeshPost_Gambit::CONVECTION));
	boundary_entity_type.insert(std::make_pair("cyclic", (unsigned short)MeshPost_Gambit::CYCLIC));
	boundary_entity_type.insert(std::make_pair("dead", (unsigned short)MeshPost_Gambit::DEAD));
	boundary_entity_type.insert(std::make_pair("element_side", (unsigned short)MeshPost_Gambit::ELEMENT_SIDE));
	boundary_entity_type.insert(std::make_pair("especies", (unsigned short)MeshPost_Gambit::ESPECIES));
	boundary_entity_type.insert(std::make_pair("exhaust_fan", (unsigned short)MeshPost_Gambit::EXHAUST_FAN));
	boundary_entity_type.insert(std::make_pair("fan", (unsigned short)MeshPost_Gambit::FAN));
	boundary_entity_type.insert(std::make_pair("free_surface", (unsigned short)MeshPost_Gambit::FREE_SURFACE));
	boundary_entity_type.insert(std::make_pair("gap", (unsigned short)MeshPost_Gambit::GAP));
	boundary_entity_type.insert(std::make_pair("inflow", (unsigned short)MeshPost_Gambit::INFLOW));
	boundary_entity_type.insert(std::make_pair("inlet", (unsigned short)MeshPost_Gambit::INLET));
	boundary_entity_type.insert(std::make_pair("inlet_vent", (unsigned short)MeshPost_Gambit::INLET_VENT));
	boundary_entity_type.insert(std::make_pair("intake_fan", (unsigned short)MeshPost_Gambit::INTAKE_FAN));
	boundary_entity_type.insert(std::make_pair("interface", (unsigned short)MeshPost_Gambit::INTERFACE));
	boundary_entity_type.insert(std::make_pair("interior", (unsigned short)MeshPost_Gambit::INTERIOR));
	boundary_entity_type.insert(std::make_pair("internal", (unsigned short)MeshPost_Gambit::INTERNAL));
	boundary_entity_type.insert(std::make_pair("live", (unsigned short)MeshPost_Gambit::LIVE));
	boundary_entity_type.insert(std::make_pair("mass_flow_inlet", (unsigned short)MeshPost_Gambit::MASS_FLOW_INLET));
	boundary_entity_type.insert(std::make_pair("melt", (unsigned short)MeshPost_Gambit::MELT));
	boundary_entity_type.insert(std::make_pair("melt_interface", (unsigned short)MeshPost_Gambit::MELT_INTERFACE));
	boundary_entity_type.insert(std::make_pair("moving_boundary", (unsigned short)MeshPost_Gambit::MOVING_BOUNDARY));
	boundary_entity_type.insert(std::make_pair("node", (unsigned short)MeshPost_Gambit::NODE));
	boundary_entity_type.insert(std::make_pair("outflow", (unsigned short)MeshPost_Gambit::OUTFLOW));
	boundary_entity_type.insert(std::make_pair("outlet", (unsigned short)MeshPost_Gambit::OUTLET));
	boundary_entity_type.insert(std::make_pair("outlet_vent", (unsigned short)MeshPost_Gambit::OUTLET_VENT));
	boundary_entity_type.insert(std::make_pair("periodic", (unsigned short)MeshPost_Gambit::PERIODIC));
	boundary_entity_type.insert(std::make_pair("plot", (unsigned short)MeshPost_Gambit::PLOT));
	boundary_entity_type.insert(std::make_pair("porous", (unsigned short)MeshPost_Gambit::POROUS));
	boundary_entity_type.insert(std::make_pair("porous_jump", (unsigned short)MeshPost_Gambit::POROUS_JUMP));
	boundary_entity_type.insert(std::make_pair("pressure", (unsigned short)MeshPost_Gambit::PRESSURE));
	boundary_entity_type.insert(std::make_pair("pressure_far_field", (unsigned short)MeshPost_Gambit::PRESSURE_FAR_FIELD));
	boundary_entity_type.insert(std::make_pair("pressure_inflow", (unsigned short)MeshPost_Gambit::PRESSURE_INFLOW));
	boundary_entity_type.insert(std::make_pair("pressure_inlet", (unsigned short)MeshPost_Gambit::PRESSURE_INLET));
	boundary_entity_type.insert(std::make_pair("pressure_outflow", (unsigned short)MeshPost_Gambit::PRESSURE_OUTFLOW));
	boundary_entity_type.insert(std::make_pair("pressure_outlet", (unsigned short)MeshPost_Gambit::PRESSURE_OUTLET));
	boundary_entity_type.insert(std::make_pair("radiation", (unsigned short)MeshPost_Gambit::RADIATION));
	boundary_entity_type.insert(std::make_pair("radiator", (unsigned short)MeshPost_Gambit::RADIATOR));
	boundary_entity_type.insert(std::make_pair("recirculation_inlet", (unsigned short)MeshPost_Gambit::RECIRCULATION_INLET));
	boundary_entity_type.insert(std::make_pair("recirculation_outlet", (unsigned short)MeshPost_Gambit::RECIRCULATION_OUTLET));
	boundary_entity_type.insert(std::make_pair("slip", (unsigned short)MeshPost_Gambit::SLIP));
	boundary_entity_type.insert(std::make_pair("sreaction", (unsigned short)MeshPost_Gambit::SREACTION));
	boundary_entity_type.insert(std::make_pair("surface", (unsigned short)MeshPost_Gambit::SURFACE));
	boundary_entity_type.insert(std::make_pair("symmetry", (unsigned short)MeshPost_Gambit::SYMMETRY));
	boundary_entity_type.insert(std::make_pair("traction", (unsigned short)MeshPost_Gambit::TRACTION));
	boundary_entity_type.insert(std::make_pair("trajectory", (unsigned short)MeshPost_Gambit::TRAJECTORY));
	boundary_entity_type.insert(std::make_pair("velocity", (unsigned short)MeshPost_Gambit::VELOCITY));
	boundary_entity_type.insert(std::make_pair("velocity_inlet", (unsigned short)MeshPost_Gambit::VELOCITY_INLET));
	boundary_entity_type.insert(std::make_pair("vent", (unsigned short)MeshPost_Gambit::VENT));
	boundary_entity_type.insert(std::make_pair("wall", (unsigned short)MeshPost_Gambit::WALL));
	boundary_entity_type.insert(std::make_pair("spring", (unsigned short)MeshPost_Gambit::SPRING));
}

static const tnbLib::ElementGeomType_RunTime element_geom_type_runTime_obj;
static const tnbLib::BoundaryEntityType_RunTime boundary_entity_type_runTime_obj;

void tnbLib::MeshPost_Gambit::WriteHeader(OFstream& theFile) const
{
	// Get the current time
	std::time_t currentTime = std::time(nullptr);

	// Convert the time to a struct tm
	std::tm* localTime = std::localtime(&currentTime);

	// Extract the date components
	int year = localTime->tm_year + 1900; // Years since 1900
	int monthIndex = localTime->tm_mon;
	int day = localTime->tm_mday;

	// Extract the time components
	int hours = localTime->tm_hour;
	int minutes = localTime->tm_min;
	int seconds = localTime->tm_sec;

	theFile << "CONTROL INFO" << " " << VERSION_EXPR << endl;
	theFile << "** GAMBIT NEUTRAL FILE" << endl
		<< theTitle_ << endl
		<< "PROGRAM: TONB VERSION: " << endl
		<< day << " " << monthNames[monthIndex] << " " << year << " "
		<< hours << ":" << minutes << ":" << seconds << endl;

	Debug_Null_Pointer(Mesh());
	auto nump = Mesh()->NbPoints();
	auto nelem = Mesh()->NbElements();
	auto ngrps = 1;
	auto nbsets = Mesh()->NbBoundaries();
	auto ndfcd = 3;
	auto ndfvl = 3;

	theFile << "NUMNP NELEM NGRPS NBSETS NDFCD NDFVL" << endl
		<< nump << " " << nelem << " " << ngrps << " " << nbsets << " " << ndfcd << " " << ndfvl << endl;
	theFile << END_SECTION_EXPR << endl;
}

void tnbLib::MeshPost_Gambit::WriteCoordinates(OFstream& theFile) const
{
	theFile << "NODAL COORDINATES" << " " << VERSION_EXPR << endl;
	size_t k = 0;
	for (const auto& p : Mesh()->Coordinates())
	{
		auto [x, y, z] = p.Components();
		theFile << ++k << " "
			<< x << " "
			<< y << " "
			<< z << endl;
	}
	theFile << END_SECTION_EXPR << endl;
}

void tnbLib::MeshPost_Gambit::WriteElements(OFstream& theFile) const
{
	theFile << "ELEMENTS/CELLS" << " " << VERSION_EXPR << endl;
	size_t k = 0;
	for (const auto& i : Mesh()->Elements())
	{
		auto elemType = i->ElementType();
		theFile << ++k << " " << element_geom_type.at(elemType) << " " << i->Size() << " ";
		auto indices = i->IndexList();
		indices = ConnectivityMatrix(indices);
		for (auto id : indices)
		{
			theFile << id + 1 << " ";
		}
		theFile << endl;
	}
	theFile << END_SECTION_EXPR << endl;
}

void tnbLib::MeshPost_Gambit::WriteGroups(OFstream& theFile) const
{
	theFile << "ELEMENT GROUP" << " " << VERSION_EXPR << endl;
	if (Mesh()->HasGroup())
	{
		NotImplemented;
	}
	else
	{
		theFile << "GROUP:" << " 1" << " " << "ELEMENTS:" << " " << Mesh()->NbElements() << " " << "MATERIAL:" << " 2" << " " << "NFLAGS:" << " 1" << endl
			<< "fluid" << endl;
		theFile << "0" << endl;
		for (size_t i = 1; i <= Mesh()->NbElements(); i++)
		{
			theFile << i << " ";
			// Check if we have printed ten numbers, then move to the next line [8/15/2023 aamir]
			if (i % 10 IS_EQUAL 0) theFile << endl;
		}
	}
	theFile << END_SECTION_EXPR << endl;
}

void tnbLib::MeshPost_Gambit::WriteBoundaries(OFstream& theFile) const
{
	theFile << "BOUNDARY CONDITIONS" << " " << VERSION_EXPR << endl;
	for (const auto& x : Mesh()->Boundaries())
	{
		const auto& elements = x->Elements();
		auto bndCond = /*"x->BoundaryCondition()*/"unspecified";
		theFile << x->Name() << " " << (Standard_Integer)DataType::elementOrCell << " " <<
			elements.size() << " " << NB_VALUES_EACH_DATA_RECORD << " " << boundary_entity_type.at(bndCond) << endl;
		for (const auto& elm : elements)
		{
			auto idsList = elm->IndexList();
			for (auto id : idsList)
			{
				theFile << id + 1 << " ";
			}
			theFile << endl;
		}
	}
	theFile << END_SECTION_EXPR << endl;
}

void tnbLib::MeshPost_Gambit::Perform(const std::string& theName)
{
	OFstream myFile(theName + ".msh");
	WriteHeader(myFile);
	WriteCoordinates(myFile);
	WriteElements(myFile);
	WriteGroups(myFile);
	WriteBoundaries(myFile);
}

std::vector<Standard_Integer> 
tnbLib::MeshPost_Gambit::ConnectivityMatrix
(
	const std::vector<Standard_Integer>& theIndices
)
{
	auto indices = theIndices;
	if (indices.size() IS_EQUAL 6)
	{
		std::swap(indices.at(1), indices.at(2));
		std::swap(indices.at(4), indices.at(5));
	}
	else
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Unsupported type of element has been detected." << endl
			<< abort(FatalError);
	}
	return std::move(indices);
}