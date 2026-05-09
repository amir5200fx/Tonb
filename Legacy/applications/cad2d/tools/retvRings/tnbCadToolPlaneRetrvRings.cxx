#include <Cad2d_IdentRings_Petal.hxx>
#include <Cad2d_IdentRings.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Segment.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Vertex.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Pln_Edge::extension + "list";
	static std::string saveExt = Cad2d_Plane::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Cad2d_Plane>> myWires;
	static std::shared_ptr<Cad2d_Plane> myPlane;

	static bool loadTag = false;
	static bool exeTag = false;

	static std::string myFileName;

	static unsigned short verbose = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);
		for (const auto& x : myCurves)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null pointer has been detected." << endl
					<< abort(FatalError);
			}
			Pln_Tools::Connect(x);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		myFileName = name;
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

		if (myWires.size())
		{
			file::SaveTo(myWires, name + saveExt, verbose);
		}
		if (myPlane)
		{
			file::SaveTo(myPlane, name + Cad2d_Plane::extension, verbose);
		}
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	auto RegisterNodes(const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices)
	{
		static auto cmp = [](const std::shared_ptr<Pln_Vertex>& n0, const std::shared_ptr<Pln_Vertex>& n1)
		{
			return n0->Index() < n1->Index();
		};

		std::set<std::shared_ptr<Pln_Vertex>, decltype(Pln_Vertex::IsLess)*> reg(Pln_Vertex::IsLess);
		for (const auto& x : theVertices)
		{
			reg.insert(x);
		}
		return std::move(reg);
	}

	auto RegisterEdges(const std::vector<std::shared_ptr<Pln_Edge>>& theCurves)
	{
		auto cmp = [](const std::shared_ptr<Pln_Edge>& e0, const std::shared_ptr<Pln_Edge>& e1)
		{
			return e0->Index() < e1->Index();
		};

		std::set<std::shared_ptr<Pln_Edge>, decltype(Pln_Edge::IsLess)*> reg(Pln_Edge::IsLess);
		for (const auto& x : theCurves)
		{
			reg.insert(x);
		}
		return std::move(reg);
	}

	auto SeparateRings(const std::vector<std::shared_ptr<Pln_Edge>>& theCurves)
	{
		auto nodes = Pln_Tools::RetrieveVertices(theCurves);

		auto nodeReg = RegisterNodes(nodes);
		auto edgeReg = RegisterEdges(theCurves);

		for (const auto& x : nodes)
		{
			auto iter = nodeReg.find(x);
			if (iter NOT_EQUAL nodeReg.end())
			{
				if (auto wire = Pln_Tools::RetrieveWire(x))
				{
					if (wire->Orientation() IS_EQUAL Pln_Orientation::Pln_Orientation_CW)
					{
						wire->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
					}

					for (const auto& e : wire->Edges())
					{
						edgeReg.erase(e);
					}

					auto inodes = Pln_Tools::RetrieveVertices(wire->Edges());
					for (const auto& n : inodes)
					{
						nodeReg.erase(n);
					}

					auto pln = Cad2d_Plane::MakePlane(wire, nullptr, gp::XOY());
					myWires.push_back(std::move(pln));
				}
			}
		}

		std::vector<std::shared_ptr<Pln_Edge>> remains;
		remains.reserve(edgeReg.size());
		for (const auto& x : edgeReg)
		{
			remains.push_back(x);
		}
		return std::move(remains);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		if (myCurves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been found." << endl
				<< abort(FatalError);
		}

		auto remains = SeparateRings(myCurves);
		if (remains.size())
		{
			auto alg = std::make_shared<Cad2d_IdentRings>(myCurves);
			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

			const auto& petals = alg->Petals();
			//myWires.reserve(petals.size());

			for (const auto& x : petals)
			{
				Debug_Null_Pointer(x);

				auto wire = cad2dLib::IdentRings_Petal::MakeWire(x);
				Debug_Null_Pointer(wire);

				if (wire->Orientation() IS_EQUAL Pln_Orientation::Pln_Orientation_CW)
				{
					wire->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
				}

				auto pln = Cad2d_Plane::MakePlane(wire, nullptr, gp::XOY());
				myWires.push_back(std::move(pln));
			}		
		}

		if (myWires.size() IS_EQUAL 1)
		{
			myPlane = myWires.at(0);
			myWires.clear();
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - nb. of rings: " << myWires.size() << endl;
		}

		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{
		// io functions [2/13/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// settings [2/13/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short v)-> void {setVerbose(v); }), "setVerbose");

		// operators [2/13/2022 Amir]
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
	FatalError.throwExceptions();

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
			Info << " This application is aimed to identify the rings." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl

				<< " # functions: " << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneRetrvRings"));

				chai.eval_file(myFileName);
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
}