#include <GeoTop_Tools.hxx>
#include <GeoTop2d_Element.hxx>
#include <GeoTop2d_Edge.hxx>
#include <GeoTop2d_Vertex.hxx>
#include <GeoTop2d_Point3d.hxx>
#include <Entity3d_Triangulation.hxx> 
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <Global_File.hxx>
#include <OFstream.hxx>
#include <OSstream.hxx>

#include <set>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Triangulation> myMesh;
	static const std::string extension = Entity3d_Triangulation::extension;

	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myRegions;

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
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
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		auto current = fs::current_path().string();
		std::string address = current + "\\results";
		fs::path dir(address);
		if (NOT fs::is_directory(dir))
		{
			fs::create_directory(dir);
		}
		else
		{
			file::RemoveDirectory(dir);
			fs::create_directory(dir);
		}

		fs::current_path(dir);

		size_t i = 0;
		for (const auto& x : myRegions)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + extension, verbose);

			fs::current_path(dir);

			++i;
		}

		fs::current_path(current);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	static auto cmpElm = [](const std::shared_ptr<GeoTop2d_Element>& e0, const std::shared_ptr<GeoTop2d_Element>& e1)
	{
		return e0->Index() < e1->Index();
	};

	void RetrieveNeighbors(std::set<std::shared_ptr<GeoTop2d_Element>, decltype(cmpElm)>& theSet, const std::shared_ptr<GeoTop2d_Element>& theElm, std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements)
	{
		std::set<std::shared_ptr<GeoTop2d_Element>, decltype(cmpElm)> ql(cmpElm);
		ql.insert(theElm);
		theElements.push_back(theElm);
		while (ql.size())
		{
			auto current = *ql.begin();
			ql.erase(current);
			if (auto n0 = current->Neighbor0())
			{
				auto iter = theSet.find(n0);
				if (iter NOT_EQUAL theSet.end())
				{
					theSet.erase(iter);
					theElements.push_back(n0);
					ql.insert(n0);
				}
			}
			if (auto n1 = current->Neighbor1())
			{
				auto iter = theSet.find(n1);
				if (iter NOT_EQUAL theSet.end())
				{
					theSet.erase(iter);
					theElements.push_back(n1);
					ql.insert(n1);
				}
			}
			if (auto n2 = current->Neighbor2())
			{
				auto iter = theSet.find(n2);
				if (iter NOT_EQUAL theSet.end())
				{
					theSet.erase(iter);
					theElements.push_back(n2);
					ql.insert(n2);
				}
			}
		}
		return;
	//startfunc:
		//auto n0 = elm->Neighbor0();
		//if(n0)
		//{
		//	auto iter = theSet.find(n0);
		//	if (iter NOT_EQUAL theSet.end())
		//	{
		//		theSet.erase(iter);
		//		theElements.push_back(n0);
		//		//elm = n0;
		//		//goto startfunc;
		//		RetrieveNeighbors(theSet, n0, theElements);
		//	}
		//}
		//auto n1 = elm->Neighbor1();
		//if(n1)
		//{
		//	auto iter = theSet.find(n1);
		//	if (iter NOT_EQUAL theSet.end())
		//	{
		//		theSet.erase(iter);
		//		theElements.push_back(n1);
		//		//elm = n1;
		//		//goto startfunc;
		//		RetrieveNeighbors(theSet, n1, theElements);
		//	}
		//}
		//auto n2 = elm->Neighbor2();
		//if(n2)
		//{
		//	auto iter = theSet.find(n2);
		//	if (iter NOT_EQUAL theSet.end())
		//	{
		//		theSet.erase(iter);
		//		theElements.push_back(n2);
		//		//elm = n2;
		//		//goto startfunc;
		//		RetrieveNeighbors(theSet, n2, theElements);
		//	}
		//}
	}

	static auto cmpVertex = [](const std::shared_ptr<GeoTop2d_Vertex>& v0, const std::shared_ptr<GeoTop2d_Vertex>& v1)
	{
		return v0->Index() < v1->Index();
	};

	auto RetrieveTriangulation(const std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements)
	{
		std::set<std::shared_ptr<GeoTop2d_Vertex>, decltype(cmpVertex)> setVtx(cmpVertex);
		for (const auto& x : theElements)
		{
			const auto& v0 = x->Vtx0();
			{
				auto insert = setVtx.insert(v0);
				if (NOT insert.second)
				{

				}
			}
			const auto& v1 = x->Vtx1();
			{
				auto insert = setVtx.insert(v1);
				if (NOT insert.second)
				{

				}
			}
			const auto& v2 = x->Vtx2();
			{
				auto insert = setVtx.insert(v2);
				if (NOT insert.second)
				{

				}
			}
		}
		std::vector<Pnt3d> pnts;
		pnts.reserve(setVtx.size());
		for (const auto& x : setVtx)
		{
			auto p3 = std::dynamic_pointer_cast<GeoTop2d_Point3d>(x->Point());
			pnts.push_back(p3->Coord());
		}
		std::map<int, int> idxMap;
		int k = 0;
		for (const auto& x : setVtx)
		{
			auto iter = idxMap.find(x->Index());
			if (iter IS_EQUAL idxMap.end())
			{
				auto paired = std::make_pair(x->Index(), ++k);
				idxMap.insert(std::move(paired));
			}
		}
		std::vector<connectivity::triple> ids;
		ids.reserve(theElements.size());
		for (const auto& x : theElements)
		{
			const auto& v0 = x->Vtx0();
			const auto& v1 = x->Vtx1();
			const auto& v2 = x->Vtx2();
			connectivity::triple t;
			t.Value(0) = idxMap.at(v0->Index());
			t.Value(1) = idxMap.at(v1->Index());
			t.Value(2) = idxMap.at(v2->Index());
			ids.push_back(std::move(t));
		}
		auto t = std::make_shared<Entity3d_Triangulation>(std::move(pnts), std::move(ids));
		return std::move(t);
	}

	auto RetrieveRegion(std::set<std::shared_ptr<GeoTop2d_Element>, decltype(cmpElm)>& theSet)
	{
		std::vector<std::shared_ptr<GeoTop2d_Element>> elements;
		auto current = (*theSet.begin());
		theSet.erase(current);
		if (current)
		{
			elements.push_back(current);
			RetrieveNeighbors(theSet, current, elements);		
		}

		auto tri = RetrieveTriangulation(elements);
		return std::move(tri);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		auto elements = GeoTop_Tools::CalcTopology(*myMesh);

		std::set<std::shared_ptr<GeoTop2d_Element>, decltype(cmpElm)> elmSet(cmpElm);
		for (const auto& x : elements)
		{
			elmSet.insert(x);
		}

		int k = 0;
		std::vector<std::shared_ptr<Entity3d_Triangulation>> tris;
		while (elmSet.size())
		{
			auto reg = RetrieveRegion(elmSet);
			if (verbose)
			{
				Info << " - region no. " << ++k << ", no. of triangles: " << reg->NbConnectivity() << endl;
			}
			tris.push_back(std::move(reg));
		}

		myRegions = std::move(tris);

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// Operators [2/11/2023 Payvand]
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
			Info << endl;
			Info << " This application is aimed to retrieve the regions of a surface mesh." << endl << endl;
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

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbGeoToolRetrieveMeshRegions"));

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