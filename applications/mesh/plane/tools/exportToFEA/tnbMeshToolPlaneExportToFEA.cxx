#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_Element.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_RegionPlaneAnIso.hxx>
#include <Aft2d_PlnWire.hxx>
#include <Aft2d_PlnWireAnIso.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_Node.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Aft_Tools.hxx>
#include <Mesh_Physic.hxx>
#include <MeshIO2d_FEA.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_SolutionDataBase::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;
	static std::string myFileName;

	static const std::string sub_directory = "soluData";
	static std::map<word, std::shared_ptr<std::vector<connectivity::dual>>> myPhysics;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);
		myFileName = name;
		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();		
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}
		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);
			const auto& elements = soluData->Elements();
			if (elements.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no element has been detected!" << endl
					<< abort(FatalError);
			}
			auto mesh = Aft_Tools::RetrieveTriangleMesh(elements);
			auto fea = std::make_shared<MeshIO2d_FEA>();
			fea->SetMesh(std::move(mesh));
			fea->SetBoundaries(myPhysics);

			file::SaveTo(fea, name + MeshIO2d_FEA::extension, verbose);
		}
		else
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);
			const auto& elements = soluData->Elements();
			if (elements.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "no element has been detected!" << endl
					<< abort(FatalError);
			}
			auto mesh = Aft_Tools::RetrieveTriangleMesh(elements);
			auto fea = std::make_shared<MeshIO2d_FEA>();
			fea->SetMesh(std::move(mesh));
			fea->SetBoundaries(myPhysics);

			file::SaveTo(fea, name + MeshIO2d_FEA::extension, verbose);
		}
		
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	void findPhysics
	(
		const std::map<word, std::vector<std::shared_ptr<Entity2d_Polygon>>>& theMap,
		const std::vector<std::shared_ptr<Aft2d_Node>>& theNodes
	)
	{
		auto coords = Aft_Tools::RetrieveGeometry(theNodes);
		auto b = Geo_BoxTools::GetBox(coords, 0);
		Geo_AdTree<std::shared_ptr<Aft2d_Node>> engine;
		engine.SetGeometryRegion(b.Expanded(b.Diameter() * 0.15));
		engine.SetGeometryCoordFunc(&Aft2d_Node::GetCoord);
		engine.InsertToGeometry(theNodes);

		for (const auto& x : theMap)
		{
			auto physic = x.first;
			std::vector<connectivity::dual> indices;
			for (const auto& poly : x.second)
			{
				const auto& pnts = poly->Points();
				for (size_t i = 1; i < pnts.size(); i++)
				{
					const auto& p0 = pnts.at(i - 1);
					const auto& p1 = pnts.at(i);

					int i0, i1;
					{
						auto bi = Entity2d_Box::Box(p0, 1.0E-6);
						std::vector<std::shared_ptr<Aft2d_Node>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Aft2d_Node> node;
						for (const auto& it : items)
						{
							if (p0.Distance(it->Coord()) <= 1.0E-16)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< abort(FatalError);
						}
						i0 = node->Index();
					}
					{
						auto bi = Entity2d_Box::Box(p1, 1.0E-6);
						std::vector<std::shared_ptr<Aft2d_Node>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Aft2d_Node> node;
						for (const auto& it : items)
						{
							if (p1.Distance(it->Coord()) <= 1.0E-16)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< abort(FatalError);
						}
						i1 = node->Index();
					}

					connectivity::dual d;
					d.Value(0) = i0;
					d.Value(1) = i1;

					indices.push_back(std::move(d));
				}
			}
			auto paired = std::make_pair(physic, std::make_shared<std::vector<connectivity::dual>>(std::move(indices)));
			myPhysics.insert(std::move(paired));
		}
	}

	void findPhysics
	(
		const std::map<word, std::vector<std::shared_ptr<Entity2d_Polygon>>>& theMap, 
		const std::vector<std::shared_ptr<Aft2d_NodeAnIso>>& theNodes
	)
	{
		auto coords = Aft_Tools::RetrieveGeometry(theNodes);
		auto b = Geo_BoxTools::GetBox(coords, 0);
		Geo_AdTree<std::shared_ptr<Aft2d_NodeAnIso>> engine;
		engine.SetGeometryRegion(b.Expanded(b.Diameter() * 0.15));
		engine.SetGeometryCoordFunc(&Aft2d_NodeAnIso::GetCoord);
		engine.InsertToGeometry(theNodes);

		for (const auto& x : theMap)
		{
			auto physic = x.first;
			std::vector<connectivity::dual> indices;
			for (const auto& poly : x.second)
			{
				const auto& pnts = poly->Points();
				for (size_t i = 1; i < pnts.size(); i++)
				{
					const auto& p0 = pnts.at(i - 1);
					const auto& p1 = pnts.at(i);

					int i0, i1;
					{
						auto bi = Entity2d_Box::Box(p0, 1.0E-6);
						std::vector<std::shared_ptr<Aft2d_NodeAnIso>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Aft2d_NodeAnIso> node;
						for (const auto& it : items)
						{
							if (p0.Distance(it->Coord()) <= 1.0E-16)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< abort(FatalError);
						}
						i0 = node->Index();
					}
					{
						auto bi = Entity2d_Box::Box(p1, 1.0E-6);
						std::vector<std::shared_ptr<Aft2d_NodeAnIso>> items;
						engine.GeometrySearch(bi, items);
						std::shared_ptr<Aft2d_NodeAnIso> node;
						for (const auto& it : items)
						{
							if (p1.Distance(it->Coord()) <= 1.0E-16)
							{
								node = it;
								break;
							}
						}
						if (NOT node)
						{
							FatalErrorIn(FunctionSIG)
								<< "contradictory data between the boundary mesh and the mesh has been detected." << endl
								<< abort(FatalError);
						}
						i1 = node->Index();
					}

					connectivity::dual d;
					d.Value(0) = i0;
					d.Value(1) = i1;

					indices.push_back(std::move(d));
				}
			}
			auto paired = std::make_pair(physic, std::make_shared<std::vector<connectivity::dual>>(std::move(indices)));
			myPhysics.insert(std::move(paired));
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		std::map<word, std::vector<std::shared_ptr<Entity2d_Polygon>>> physicMap;
		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);
			
			const auto& region = soluData->Region();
			std::vector<std::shared_ptr<Aft2d_PlnWire>> wires;
			region->RetrieveWiresTo(wires);

			for (const auto& w : wires)
			{
				for (const auto& c : w->Curves())
				{
					const auto& bmesh = c->GetMesh();
					if (NOT bmesh)
					{
						FatalErrorIn(FunctionSIG)
							<< "the curve has no mesh." << endl
							<< abort(FatalError);
					}
					auto physic = c->Physic()->Name();
					auto iter = physicMap.find(physic);
					if (iter IS_EQUAL physicMap.end())
					{
						auto paired = std::make_pair(physic, std::vector<std::shared_ptr<Entity2d_Polygon>>());
						physicMap.insert(std::move(paired));
					}
					physicMap.at(physic).push_back(bmesh);
				}
			}

			if (verbose)
			{
				Info << " # no. of physics: " << physicMap.size() << endl;
				for (const auto& x : physicMap)
				{
					Info << " - " << x.first << endl;
				}
			}
			
			auto nodes = Aft_Tools::RetrieveNodes(soluData->Elements());
			std::vector<std::shared_ptr<Aft2d_Node>> bnodes;
			for (const auto& x : nodes)
			{
				if (x->IsBoundary())
				{
					bnodes.push_back(x);
				}
			}

			findPhysics(physicMap, bnodes);
		}
		else
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);

			const auto& region = soluData->Region();
			std::vector<std::shared_ptr<Aft2d_PlnWireAnIso>> wires;
			region->RetrieveWiresTo(wires);

			for (const auto& w : wires)
			{
				for (const auto& c : w->Curves())
				{
					const auto& bmesh = c->GetMesh();
					if (NOT bmesh)
					{
						FatalErrorIn(FunctionSIG)
							<< "the curve has no mesh." << endl
							<< abort(FatalError);
					}
					auto physic = c->Physic()->Name();
					auto iter = physicMap.find(physic);
					if (iter IS_EQUAL physicMap.end())
					{
						auto paired = std::make_pair(physic, std::vector<std::shared_ptr<Entity2d_Polygon>>());
						physicMap.insert(std::move(paired));
					}
					physicMap.at(physic).push_back(bmesh);
				}
			}

			if (verbose)
			{
				Info << " # no. of physics: " << physicMap.size() << endl;
				for (const auto& x : physicMap)
				{
					Info << " - " << x.first << endl;
				}
			}

			auto nodes = Aft_Tools::RetrieveNodes(soluData->Elements());
			std::vector<std::shared_ptr<Aft2d_NodeAnIso>> bnodes;
			for (const auto& x : nodes)
			{
				if (x->IsBoundary())
				{
					bnodes.push_back(x);
				}
			}

			findPhysics(physicMap, bnodes);
		}

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is successfully performed." << endl;
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions 
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings 

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators 
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to export a finite element mesh from a solution data of a mesh." << endl << endl;

			Info << " subdirectory: {" << sub_directory << "}" << endl;
			Info << " input: *" << Aft2d_SolutionDataBase::extension << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl
				
				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshToolPlaneExportToFEA"));

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}