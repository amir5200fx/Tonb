#include <HydStatic_SolutionData_Coeffs.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_ModelShape.hxx>
#include <HydStatic_Shapes.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Models.hxx>
#include <Marine_BodyTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<Marine_Wave> wave_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	static unsigned short verbose(0);

	static soluData_t mySolutionData;
	static wave_t myWave;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> mySolutionData;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::displacerDim))
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is not updated" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}

		const auto& myModel = mySolutionData->Hull();
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "the stability model is null" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->Domain())
		{
			FatalErrorIn(FunctionSIG)
				<< "the solution data has no domain" << endl
				<< abort(FatalError);
		}
		myWave = std::make_shared<Marine_FlatWave>(mySolutionData->Domain());
		const auto& wave = myWave;
		wave->Current().SetX(-1);
		wave->Current().SetY(0);
		wave->Current().SetZ(0);

		wave->Wind().SetX(-1);
		wave->Wind().SetY(0);
		wave->Wind().SetZ(0);

		const auto& displacer = mySolutionData->Hull();
		auto b = Marine_BodyTools::BoundingBox(*displacer);

		wave->SetPointOnWater(b.CalcCentre());
		wave->SetVerticalDirection(Dir3d(0, 0, 1));
	}

	void checkWave()
	{
		if (NOT myWave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no stability model has been loaded!" << endl
				<< abort(FatalError);
		}
	}

	void setCurrent(const Vec3d& v)
	{
		checkWave();
		myWave->SetCurrent(v);
	}

	void setWind(const Vec3d& v)
	{
		checkWave();
		myWave->SetWind(v);
	}

	void setPointOnWater(const Pnt3d& p)
	{
		checkWave();
		myWave->SetPointOnWater(p);
	}

	void setVerticalDir(const Dir3d& d)
	{
		checkWave();
		myWave->SetVerticalDirection(d);
	}

	void createFlatWave()
	{
		checkWave();

		if (verbose)
		{
			Info << endl;
			Info << " Wave properties:" << endl;
			Info << " - type: flat" << endl;
			Info << " - current: " << myWave->Current() << endl;
			Info << " - wind: " << myWave->Wind() << endl;
			Info << " - point on water: " << myWave->PointOnWater() << endl;
			Info << " - vertical direction: " << myWave->VerticalDirection() << endl;
			Info << endl;
		}

		myWave->Perform();
		mySolutionData->LoadWave(myWave);
		mySolutionData->SetCurrentSolution(hydStcLib::SolutionData_Coeffs::solutionOrder::wave);
	}

	auto createPoint(double x, double y, double z)
	{
		auto p = Pnt3d(x, y, z);
		return std::move(p);
	}

	auto createVec(double x, double y, double z)
	{
		auto v = Vec3d(x, y, z);
		return std::move(v);
	}

	auto createDir(double x, double y, double z)
	{
		auto v = Dir3d(x, y, z);
		return std::move(v);
	}

	void saveWaveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);
		boost::archive::polymorphic_text_oarchive oa(f);

		if (NOT myWave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wave has been created!" << endl
				<< abort(FatalError);
		}

		if (NOT myWave->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		oa << myWave;

		if (verbose)
		{
			Info << " the wave is saved in: " << fn << ", successfully!" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolutionData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
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

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createPoint(x, y, z); return std::move(t); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createVec(x, y, z); return std::move(t); }), "createVector");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createDir(x, y, z); return std::move(t); }), "createDirection");

		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveWaveTo(name); }), "saveWaveTo");

		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");
	}

	void setWaves(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {createFlatWave(); }), "execute");
		mod->add(chaiscript::fun([](const Pnt3d& p)->void {setPointOnWater(p); }), "setPointOnWater");
		mod->add(chaiscript::fun([](const Dir3d& d)->void {setVerticalDir(d); }), "setVerticalDirection");
		mod->add(chaiscript::fun([](const Vec3d& v)->void {setCurrent(v); }), "setCurrent");
		mod->add(chaiscript::fun([](const Vec3d& v)->void {setWind(v); }), "setWind");

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setWaves(mod);

			chai.add(mod);

			std::string address = ".\\system\\hullDataFlatWave";
			fileName myFileName(address);

			try
			{
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