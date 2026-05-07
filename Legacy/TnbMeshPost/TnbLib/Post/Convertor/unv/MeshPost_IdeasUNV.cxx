#include <MeshPost_IdeasUNV.hxx>

#include <Geo3d_FVMesh.hxx>
#include <Geo_ElemGeom.hxx>

#include <map>

#define FE_DESCRIPTOR 11

namespace tnbLib
{
	static std::map<std::string, unsigned int> unv_element_geom_type;

	class UNV_ElementGeomType_RunTime
	{

		/*Private Data*/

		void RunTime();

	public:

		// default constructor [8/15/2023 aamir]

		UNV_ElementGeomType_RunTime()
		{
			RunTime();
		}

	};

	const char* system_type[] =
	{ "Meter (newton)", "Foot (pround f)", "Meter (Killogram f)", "Foot (poundal)", "mm (milli newton)", "cm (centi newton)", "Inch (pround f)", "mm (kilogram f)", "USER_DEFINED", "mm (newton)" };
}

void tnbLib::UNV_ElementGeomType_RunTime::RunTime()
{
	unv_element_geom_type.insert({ "edge", 11 });
	unv_element_geom_type.insert({ "quadrilateral", 44 });
	unv_element_geom_type.insert({ "triangle", 41 });
	unv_element_geom_type.insert({ "brick", 115 });
	unv_element_geom_type.insert({ "wedge", 112 });
	unv_element_geom_type.insert({ "tetrahedron", 111 });
	unv_element_geom_type.insert({ "pyramid", 112 });
}

static const tnbLib::UNV_ElementGeomType_RunTime myUNV_ElementGeomType_RunTimeObj;

void tnbLib::MeshPost_IdeasUNV::WriteHeader(std::fstream& theFile) const
{
	theFile << std::setw(6) << -1 << "\n"
		<< std::setw(6) << 164 << "\n"
		<< std::setw(10) << (unsigned short)GetSystem()
		<< std::setw(20) << system_type[(unsigned short)GetSystem()] 
		<< std::setw(10) << 2 << "\n";
	theFile << std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0 << "\n";
	theFile << std::setw(25) << std::scientific << std::setprecision(16) << 1.0 << "\n";
	theFile << std::setw(6) << -1 << "\n";

	theFile << std::setw(6) << -1 << "\n";
	theFile << std::setw(6) << 2420 << "\n";
	theFile << std::setw(6) << 1 << "\n";
	theFile << "SMESH_MESH" << "\n"
		<< std::setw(10) << 1 << std::setw(10) << 0 << std::setw(10) << 0 << "\n"
		<< "Global Cartesian Coordinate System" << "\n"
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 1.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 << "\n"
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 1.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 << "\n"
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 1.0 << "\n"
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 
		<< std::setw(25) << std::scientific<< std::setprecision(16) << 0.0 << "\n";
		
	theFile << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteHeader(std::stringstream& theStream) const
{
	theStream << std::setw(6) << -1 << "\n"
		<< std::setw(6) << 164 << "\n"
		<< std::setw(10) << (unsigned short)GetSystem()
		<< std::setw(20) << system_type[(unsigned short)GetSystem()]
		<< std::setw(10) << 2 << "\n";
	theStream << std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0 << "\n";
	theStream << std::setw(25) << std::scientific << std::setprecision(16) << 1.0 << "\n";
	theStream << std::setw(6) << -1 << "\n";

	theStream << std::setw(6) << -1 << "\n";
	theStream << std::setw(6) << 2420 << "\n";
	theStream << std::setw(6) << 1 << "\n";
	theStream << "SMESH_MESH" << "\n"
		<< std::setw(10) << 1 << std::setw(10) << 0 << std::setw(10) << 0 << "\n"
		<< "Global Cartesian Coordinate System" << "\n"
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0 << "\n"
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0 << "\n"
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 1.0 << "\n"
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0
		<< std::setw(25) << std::scientific << std::setprecision(16) << 0.0 << "\n";

	theStream << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteCoordinates(std::fstream& theFile) const
{
	theFile << std::setw(6) << -1 << "\n";
	theFile << std::setw(6) << 2411 << "\n";
	Standard_Integer k = 0;
	for (const auto& p : Mesh()->Coordinates())
	{
		theFile << std::setw(10) << ++k
			<< std::setw(10) << 1
			<< std::setw(10) << 1
			<< std::setw(10) << 11 << "\n";
		auto [x, y, z] = p.Components();
		theFile << std::setw(25) << std::scientific << std::setprecision(16) << x
			<< std::setw(25) << std::scientific << std::setprecision(16) << y
			<< std::setw(25) << std::scientific << std::setprecision(16) << z << "\n";
	}
	theFile << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteCoordinates(std::stringstream& theStream) const
{
	theStream << std::setw(6) << -1 << "\n";
	theStream << std::setw(6) << 2411 << "\n";
	Standard_Integer k = 0;
	for (const auto& p : Mesh()->Coordinates())
	{
		theStream << std::setw(10) << ++k
			<< std::setw(10) << 1
			<< std::setw(10) << 1
			<< std::setw(10) << 11 << "\n";
		auto [x, y, z] = p.Components();
		theStream << std::setw(25) << std::scientific << std::setprecision(16) << x
			<< std::setw(25) << std::scientific << std::setprecision(16) << y
			<< std::setw(25) << std::scientific << std::setprecision(16) << z << "\n";
	}
	theStream << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteElements(std::fstream& theFile) const
{
	theFile << std::setw(6) << -1 << "\n";
	theFile << std::setw(6) << 2412 << "\n";
	std::map<std::shared_ptr<Geo_ElemGeom>, int> elements_to_id;
	Standard_Integer k = 0;
	for (const auto& bnd : Mesh()->Boundaries())
	{
		for (const auto& elm : bnd->Elements())
		{
			elements_to_id.insert({ elm,++k });
			theFile << std::setw(10) << k;
			WriteElement(elm, theFile);
		}
	}
	for (const auto& elm : Mesh()->Elements())
	{
		elements_to_id.insert({ elm,++k });
		theFile << std::setw(10) << k;
		WriteElement(elm, theFile);
	}
	theFile << std::setw(6) << -1 << "\n";

	theFile << std::setw(6) << -1 << "\n";
	theFile << std::setw(6) << 2467 << "\n";
	Standard_Integer groupNb = 0;
	for (const auto& bnd : Mesh()->Boundaries())
	{
		theFile << std::setw(10) << ++groupNb
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << bnd->Elements().size() << "\n";
		theFile << bnd->Name() << "\n";
		size_t flag = 1;
		for (const auto& x : bnd->Elements())
		{
			theFile << std::setw(10) << 8
				<< std::setw(10) << elements_to_id.at(x)
				<< std::setw(10) << 0
				<< std::setw(10) << 0;
			if (flag % 2 == 0)
			{
				//flag = 1;
				theFile << "\n";
			}
			++flag;
		}
		if (flag % 2 == 0) theFile << "\n";
	}
	theFile << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteElements(std::stringstream& theStream) const
{
	theStream << std::setw(6) << -1 << "\n";
	theStream << std::setw(6) << 2412 << "\n";
	std::map<std::shared_ptr<Geo_ElemGeom>, int> elements_to_id;
	Standard_Integer k = 0;
	for (const auto& bnd : Mesh()->Boundaries())
	{
		for (const auto& elm : bnd->Elements())
		{
			elements_to_id.insert({ elm,++k });
			theStream << std::setw(10) << k;
			WriteElement(elm, theStream);
		}
	}
	for (const auto& elm : Mesh()->Elements())
	{
		elements_to_id.insert({ elm,++k });
		theStream << std::setw(10) << k;
		WriteElement(elm, theStream);
	}
	theStream << std::setw(6) << -1 << "\n";

	theStream << std::setw(6) << -1 << "\n";
	theStream << std::setw(6) << 2467 << "\n";
	Standard_Integer groupNb = 0;
	for (const auto& bnd : Mesh()->Boundaries())
	{
		theStream << std::setw(10) << ++groupNb
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << 0
			<< std::setw(10) << bnd->Elements().size() << "\n";
		theStream << bnd->Name() << "\n";
		size_t flag = 1;
		for (const auto& x : bnd->Elements())
		{
			theStream << std::setw(10) << 8
				<< std::setw(10) << elements_to_id.at(x)
				<< std::setw(10) << 0
				<< std::setw(10) << 0;
			if (flag % 2 == 0)
			{
				//flag = 1;
				theStream << "\n";
			}
			++flag;
		}
		if (flag % 2 == 0) theStream << "\n";
	}
	theStream << std::setw(6) << -1 << "\n";
}

void tnbLib::MeshPost_IdeasUNV::WriteElement(const std::shared_ptr<Geo_ElemGeom>& theElement, std::fstream& theFile) const
{
	try
	{
		theFile << std::setw(10) << unv_element_geom_type.at(theElement->ElementType())
			<< std::setw(10) << 2
			<< std::setw(10) << 1
			<< std::setw(10) << 7
			<< std::setw(10) << theElement->Size() << "\n";
		for (auto x : theElement->IndexList())
		{
			theFile << std::setw(10) << x;
		}
		theFile << "\n";
	}
	catch (...)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unspeified type of element: " << endl
			<< " - typename: " << theElement->ElementType() << endl
			<< abort(FatalError);
	}
}

void tnbLib::MeshPost_IdeasUNV::WriteElement(const std::shared_ptr<Geo_ElemGeom>& theElement, std::stringstream& theStream) const
{
	try
	{
		theStream << std::setw(10) << unv_element_geom_type.at(theElement->ElementType())
			<< std::setw(10) << 2
			<< std::setw(10) << 1
			<< std::setw(10) << 7
			<< std::setw(10) << theElement->Size() << "\n";
		for (auto x : theElement->IndexList())
		{
			theStream << std::setw(10) << x;
		}
		theStream << "\n";
	}
	catch (...)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unspeified type of element: " << endl
			<< " - typename: " << theElement->ElementType() << endl
			<< abort(FatalError);
	}
}

void tnbLib::MeshPost_IdeasUNV::Perform(const std::string& theName)
{
	std::fstream myFile;
	myFile.open(theName + ".unv", std::ios::out);
	WriteHeader(myFile);
	WriteCoordinates(myFile);
	WriteElements(myFile);
	myFile.close();
}

void tnbLib::MeshPost_IdeasUNV::Perform(std::stringstream& theStream)
{
	WriteHeader(theStream);
	WriteCoordinates(theStream);
	WriteElements(theStream);
}
