#include <Cad2d_Plane.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Segment.hxx>
#include <Pln_Ring.hxx>
#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>
#include <Aft2d_PlnWire.hxx>
#include <Aft2d_PlnWireAnIso.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_RegionPlaneAnIso.hxx>
#include <Aft2d_RegionPlaneUniMetric.hxx>
#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Aft2d_Element.hxx>
#include <Mesh_Physic.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = Aft2d_SolutionDataBase::extension;
	static const std::string saveExt = Aft2d_SolutionDataBase::extension;

	static std::string myFileName;

	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned short verbose = 0;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + loadExt, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the solution data file is null!" << endl
				<< abort(FatalError);
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
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(mySoluData, name + saveExt, verbose);
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	auto retrieveCurves(const Aft2d_RegionPlane& theRegion)
	{
		std::vector<std::shared_ptr<Aft2d_PlnWire>> wires;
		theRegion.RetrieveWiresTo(wires);
		std::map<int, std::shared_ptr<Mesh2d_PlnCurve>> curves;
		for (const auto& w : wires)
		{
			for (const auto& x : w->Curves())
			{
				auto paired = std::make_pair(x->Index(), x);
				if (NOT curves.insert(std::move(paired)).second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate curve no. has been detected." << endl
						<< " - id: " << x->Index() << endl
						<< abort(FatalError);
				}
			}
		}
		return std::move(curves);
	}

	auto retrieveCurves(const Aft2d_RegionPlaneAnIso& theRegion)
	{
		std::vector<std::shared_ptr<Aft2d_PlnWireAnIso>> wires;
		theRegion.RetrieveWiresTo(wires);
		std::map<int, std::shared_ptr<Mesh2d_PlnCurveAnIso>> curves;
		for (const auto& w : wires)
		{
			for (const auto& x : w->Curves())
			{
				auto paired = std::make_pair(x->Index(), x);
				if (NOT curves.insert(std::move(paired)).second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate curve no. has been detected." << endl
						<< " - id: " << x->Index() << endl
						<< abort(FatalError);
				}
			}
		}
		return std::move(curves);
	}

	void setPhysics(const Cad2d_Plane& plane, const std::shared_ptr<Aft2d_RegionPlane>& theRegion)
	{
		auto curvesMap = retrieveCurves(*theRegion);
		const auto& segments = plane.Segments();
		for (const auto& x : segments->Blocks())
		{
			for (const auto& e : x.second->RetrieveEntities())
			{
				const auto& c = e->Curve();
				auto iter = curvesMap.find(c->Index());
				if (iter IS_EQUAL curvesMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "couldn't find the curve in the block." << endl
						<< " id: " << c->Index() << endl
						<< abort(FatalError);
				}
				auto physic = std::make_shared<Mesh_Physic>(0, x.first);
				iter->second->SetPhysic(std::move(physic));
			}
		}
	}

	void setPhysics(const Cad2d_Plane& plane, const std::shared_ptr<Aft2d_RegionPlaneAnIso>& theRegion)
	{
		auto curvesMap = retrieveCurves(*theRegion);
		const auto& segments = plane.Segments();
		for (const auto& x : segments->Blocks())
		{
			for (const auto& e : x.second->RetrieveEntities())
			{
				const auto& c = e->Curve();
				auto iter = curvesMap.find(c->Index());
				if (iter IS_EQUAL curvesMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "couldn't find the curve in the block." << endl
						<< " id: " << c->Index() << endl
						<< abort(FatalError);
				}
				auto physic = std::make_shared<Mesh_Physic>(0, x.first);
				iter->second->SetPhysic(std::move(physic));
			}
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySoluData->Plane())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no plane has been found!" << endl
				<< abort(FatalError);
		}

		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);

			auto planeRegion = Aft2d_RegionPlane::MakePlane(soluData->Plane());
			setPhysics(*soluData->Plane(), planeRegion);

			soluData->SetRegion(std::move(planeRegion));
		}
		else if (mySoluData->IsAnIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);

			auto planeRegion = Aft2d_RegionPlaneAnIso::MakePlane(soluData->Plane());
			setPhysics(*soluData->Plane(), planeRegion);

			soluData->SetRegion(std::move(planeRegion));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of solution file has been detected!" << endl
				<< abort(FatalError);
		}

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

	void setFunctions(const module_t& mod)
	{
		// io functions [12/3/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/3/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// Operators [12/4/2021 Amir]
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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

int main(int argc, char *argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a region from a plane." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

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

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshPlaneRegionAft"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}