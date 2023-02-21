#include <Entity3d_Triangulation.hxx> 
#include <Entity3d_Box.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <Global_File.hxx>
#include <OFstream.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Triangulation> myMesh;
	static const std::string extension = Entity3d_Triangulation::extension;

	static std::shared_ptr<Entity3d_Triangulation> myMerged;

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static double myTol = 1.0E-6;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTol(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadMesh3d()
	{
		checkFolder("mesh");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\mesh)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();

				myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
				if (NOT myMesh)
				{
					FatalErrorIn(FunctionSIG)
						<< " the mesh file is null!" << endl
						<< abort(FatalError);
				}
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();

			myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
			if (NOT myMesh)
			{
				FatalErrorIn(FunctionSIG)
					<< " the mesh file is null!" << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadMeshFile(const std::string& name)
	{
		file::CheckExtension(name);

		myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
		if (NOT myMesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the mesh is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("mesh"))
		{
			loadMesh3d();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
			loadMeshFile(name);
		}

		loadTag = true;
	}

	void loadFile(const std::string& name)
	{
		loadMeshFile(name);

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myMerged, name + Entity3d_Triangulation::extension, verbose);
	}

	struct Node
	{
		int idx;
		Pnt3d coord;

		typedef Pnt3d ptType;
	};

	auto mergeIndices(const std::vector<connectivity::triple>& unMerged)
	{
		std::map<int, std::vector<int>> idx_to_elmnts;
		int k = 0;
		std::vector<connectivity::triple> indices;
		for (const auto& x : unMerged)
		{
			++k;
			{
				auto v = x.Value(0);				
				auto iter = idx_to_elmnts.find(v);
				if (iter IS_EQUAL idx_to_elmnts.end())
				{
					auto paired = std::make_pair(v, std::vector<int>());
					idx_to_elmnts.insert(std::move(paired));
				}
				else
				{
					bool found = false;
					for (auto elm : iter->second)
					{
						auto v0 = unMerged.at(elm - 1).Value(0);
						auto v1 = unMerged.at(elm - 1).Value(1);
						auto v2 = unMerged.at(elm - 1).Value(2);

						auto q0 = x.Value(0);
						auto q1 = x.Value(1);
						auto q2 = x.Value(2);

						if (Geo_Tools::IsPairedTwoTriangles(v0, v1, v2, q0, q1, q2))
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						continue;
					}
				}
			}
			{
				auto v = x.Value(1);
				auto iter = idx_to_elmnts.find(v);
				if (iter IS_EQUAL idx_to_elmnts.end())
				{
					auto paired = std::make_pair(v, std::vector<int>());
					idx_to_elmnts.insert(std::move(paired));
				}
				else
				{
					bool found = false;
					for (auto elm : iter->second)
					{
						auto v0 = unMerged.at(elm - 1).Value(0);
						auto v1 = unMerged.at(elm - 1).Value(1);
						auto v2 = unMerged.at(elm - 1).Value(2);

						auto q0 = x.Value(0);
						auto q1 = x.Value(1);
						auto q2 = x.Value(2);

						if (Geo_Tools::IsPairedTwoTriangles(v0, v1, v2, q0, q1, q2))
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						continue;
					}
				}
			}
			{
				auto v = x.Value(2);
				auto iter = idx_to_elmnts.find(v);
				if (iter IS_EQUAL idx_to_elmnts.end())
				{
					auto paired = std::make_pair(v, std::vector<int>());
					idx_to_elmnts.insert(std::move(paired));
				}
				else
				{
					bool found = false;
					for (auto elm : iter->second)
					{
						auto v0 = unMerged.at(elm - 1).Value(0);
						auto v1 = unMerged.at(elm - 1).Value(1);
						auto v2 = unMerged.at(elm - 1).Value(2);

						auto q0 = x.Value(0);
						auto q1 = x.Value(1);
						auto q2 = x.Value(2);

						if (Geo_Tools::IsPairedTwoTriangles(v0, v1, v2, q0, q1, q2))
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						continue;
					}
				}
			}
			auto v0 = x.Value(0);
			idx_to_elmnts.at(v0).push_back(k);

			auto v1 = x.Value(1);
			idx_to_elmnts.at(v1).push_back(k);

			auto v2 = x.Value(2);
			idx_to_elmnts.at(v2).push_back(k);

			indices.push_back(x);
		}
		return std::move(indices);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		auto bbx = Geo_BoxTools::GetBox(myMesh->Points(), 0);
		bbx.Expand(bbx.Diameter() * 0.001);

		Geo_AdTree<std::shared_ptr<Node>> tree;
		tree.SetGeometryRegion(bbx);
		tree.SetGeometryCoordFunc([](const std::shared_ptr<Node>& n)->const auto& {return n->coord; });

		std::vector<Pnt3d> coords;
		int k = 0;
		std::map<int, int> indxMap;
		for (const auto& x : myMesh->Connectivity())
		{
			for (size_t j = 0; j < 3; j++)
			{
				auto vtx = x.Value(j);
				const auto& pt = myMesh->Points().at(vtx - 1);

				auto b = Entity3d_Box::Box(pt, myTol);
				std::vector<std::shared_ptr<Node>> items;
				tree.GeometrySearch(b, items);

				std::shared_ptr<Node> found;
				for (const auto& i : items)
				{
					if (i->coord.Distance(pt) <= myTol)
					{
						found = i;
						break;
					}
				}

				if (NOT found)
				{
					Node nodeRef = { ++k,pt };
					auto node = std::make_shared<Node>(std::move(nodeRef));

					auto paired = std::make_pair(vtx, k);
					indxMap.insert(std::move(paired));
					tree.InsertToGeometry(node);
				}
				else
				{
					auto paired = std::make_pair(vtx, found->idx);
					indxMap.insert(std::move(paired));
				}
			}
		}
		std::vector<std::shared_ptr<Node>> nodes;
		tree.RetrieveFromGeometryTo(nodes);

		std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node>& n0, const std::shared_ptr<Node>& n1)-> auto {return n0->idx < n1->idx; });

		std::vector<connectivity::triple> indices;
		indices.reserve(myMesh->NbConnectivity());
		for (const auto& x : myMesh->Connectivity())
		{
			auto v0 = x.Value(0);
			auto v1 = x.Value(1);
			auto v2 = x.Value(2);

			connectivity::triple t;
			t.Value(0) = indxMap.at(v0);
			t.Value(1) = indxMap.at(v1);
			t.Value(2) = indxMap.at(v2);
			indices.push_back(std::move(t));
		}
		std::vector<Pnt3d> pnts;
		pnts.reserve(nodes.size());
		for (const auto& x : nodes)
		{
			pnts.push_back(x->coord);
		}
		nodes.clear();
		auto mesh = std::make_shared<Entity3d_Triangulation>(std::move(pnts), mergeIndices(indices));
		myMerged = std::move(mesh);

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");

		// operators [12/21/2021 Amir]
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << endl;
			Info << " This application is aimed to merge a surface mesh." << endl
				<< " - subdirectories: mesh, shape" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setTolerance(x)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbGeoToolMergeSurfMesh"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}