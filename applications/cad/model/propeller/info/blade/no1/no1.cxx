#include <PtdModel_PropBladeNo1.hxx>
#include <PtdModel_BladeFormMakersNo1.hxx>
#include <PtdModel_PropSectionNo1_Naca4Digit.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_Face.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include "makers.hxx"

#include "InitCamber.hxx"
#include "InitCamberLoc.hxx"
#include "InitChord.hxx"
#include "InitPitch.hxx"
#include "InitRake.hxx"
#include "InitSkew.hxx"
#include "InitThick.hxx"

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>

#define PropDiaName "PropDia"
#define HubRadiusName "HubRadius"

std::shared_ptr<std::vector<tnbLib::maker_t>> tnbLib::myMakers = std::make_shared<std::vector<tnbLib::maker_t>>();

namespace tnbLib
{

	InitBndParameter(LOWER_DIAM, UPPER_DIAM, DEFAULT_DIAM, 100.0, 600.0, 300.0, myDiaX);
	InitBndParameter(LOWER_HUB_RADIUS, UPPER_HUB_RADIUS, DEFAULT_HUB_RADIUS, 10.0, 60.0, 30.0, myHubRadiusX);

	DefFixedParameter(PropDiaName, myDiaX, myPropDiameter);
	DefFixedParameter(HubRadiusName, myHubRadiusX, myHubRadius);

	static auto DEFAULT_NB_SECTIONS = 25;
	static auto myNbSections = DEFAULT_NB_SECTIONS;

	static auto exeTag = false;
	static auto shapeTag = false;
	static auto myTol = 1.0E-6;
	static unsigned short verbose(0);

	static std::shared_ptr<Cad_Shape> myShape;

	std::shared_ptr<PtdModel_PropBlade> myBlade;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void createMakers()
	{
		createCamberForm();
		createMaxCamberLocForm();
		createChordForm();
		createPitchForm();
		createRakeForm();
		createSkewForm();
		createThickForm();
	}

	void execute()
	{
		createMakers();

		auto mySection = std::make_shared<ptdModel::PropSectionNo1_Naca4Digit>();

		auto myGlobals = std::make_shared<PtdModel_BladeGlobalPars>(myPropDiameter, myHubRadius);

		myBlade = std::make_shared<PtdModel_PropBladeNo1>(myGlobals);
		myBlade->ImportMakers(*myMakers);
		//myBlade->BladeInfo()->SetNbSpans(35);

		auto distb = std::make_shared<Geo_UniDistb>(myNbSections - 1);
		distb->SetLower(myHubRadius->Value()/* + 1.0E-4*(myPropDiameter->Value() / 2.0 - myHubRadius->Value())*/);
		distb->SetUpper(myPropDiameter->Value() / 2.0 /*- 1.0E-4*(myPropDiameter->Value() / 2.0 - myHubRadius->Value())*/);
		distb->Perform();

		myBlade->SetxDistb(std::move(distb));
		myBlade->SetSection(std::move(mySection));

		myBlade->Perform();

		/*if (shapeTag)
		{
			auto face0 = BRepBuilderAPI_MakeFace(myBlade->BackPatch()->Surface(), myTol);
			auto face1 = BRepBuilderAPI_MakeFace(myBlade->FacePatch()->Surface(), myTol);

			TopoDS_Compound myCompound;
			TopoDS_Builder myBuilder;
			myBuilder.MakeCompound(myCompound);

			myBuilder.Add(myCompound, face0);
			myBuilder.Add(myCompound, face1);

			myShape = std::make_shared<Cad_Shape>(0, "myBlade", std::move(myCompound));
		}*/

		exeTag = true;
	}

	void saveGeomTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		auto face0 = std::make_shared<Cad_GeomSurface>(1, "backPatch", myBlade->BackPatch()->Surface());
		auto face1 = std::make_shared<Cad_GeomSurface>(2, "facePatch", myBlade->FacePatch()->Surface());

		{
			std::string address = ".\\" + std::to_string(0) + "\\" + name;
			boost::filesystem::path dir(std::to_string(0));
			boost::filesystem::create_directory(dir);

			std::ofstream myFile(address);

			TNB_oARCH_FILE_TYPE ar(myFile);

			ar << face0;
		}

		{
			std::string address = ".\\" + std::to_string(1) + "\\" + name;
			boost::filesystem::path dir(std::to_string(1));
			boost::filesystem::create_directory(dir);

			std::ofstream myFile(address);

			TNB_oARCH_FILE_TYPE ar(myFile);

			ar << face1;
		}
	}

	void saveShapeTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		ar << myShape;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		/*if (shapeTag)
		{
			saveShapeTo(name);
		}
		else
		{
			saveGeomTo(name);
		}*/

		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		ar << myBlade;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		//mod->add(chaiscript::fun([](bool tag)-> void {shapeTag = tag; }), "setShapeTag");
		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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

	//PtdModel_PropSection::verbose = 2;
	//PtdModel_PropBlade::verbose = 2;

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

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("propBladeInfoNo1");

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