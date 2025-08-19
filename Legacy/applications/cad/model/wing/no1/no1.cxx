#include <PtdModel_WingNo1.hxx>
#include <PtdModel_WingFormMakersNo1.hxx>
#include <PtdModel_WingGlobalPars.hxx>
#include <PtdModel_WingSectionNo1_Naca4Digit.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_Face.hxx>
#include <Cad_GeomSurface.hxx>
#include <Geo_UniDistb.hxx>

#include <boost/filesystem.hpp>

#define IMPORT_FORM(FORM, Par)						\
	auto form = std::make_shared<FORM>();			\
	form->SetParameter(form->Parameter(0), Par);			\
	myMakers.push_back(std::move(form));

namespace tnbLib
{

	typedef std::shared_ptr<PtdModel_FormMaker> maker_t;

	static std::shared_ptr<PtdModel_WingNo1> myWing;

	static std::vector<maker_t> myMakers;
	static unsigned short verbose = 0;

	static const auto LOWER_CAMBER = 0;
	static const auto UPPER_CAMBER = 0.2;
	static const auto DEFAULT_CAMBER = 0.03;
	static auto myCamberX = PtdModel_BndValue(LOWER_CAMBER, UPPER_CAMBER, DEFAULT_CAMBER);

	static const auto LOWER_MAXCAMBER_LOC = 0.1;
	static const auto UPPER_MAXCAMBER_LOC = 0.9;
	static const auto DEFAULT_MAXCAMBER = 0.4;
	static auto myCambLocX = PtdModel_BndValue(LOWER_MAXCAMBER_LOC, UPPER_MAXCAMBER_LOC, DEFAULT_MAXCAMBER);

	static const auto LOWER_CHORD = 0.001;
	static const auto UPPER_CHORD = 5.0;
	static const auto DEFAULT_CHORD = 1.0;
	static auto myChordX = PtdModel_BndValue(LOWER_CHORD, UPPER_CHORD, DEFAULT_CHORD);

	static const auto LOWER_THICK = 0.001;
	static const auto UPPER_THICK = 0.5;
	static const auto DEFAULT_THICK = 0.025;
	static auto myThickX = PtdModel_BndValue(LOWER_THICK, UPPER_THICK, DEFAULT_THICK);


	static const auto LOWER_SPAN = 0.1;
	static const auto UPPER_SPAN = 15.0;
	static const auto DEFAULT_SPAN = 5.0;
	static auto mySpanX = PtdModel_BndValue(LOWER_SPAN, UPPER_SPAN, DEFAULT_SPAN);


	static auto myCamberPar = std::make_shared<PtdModel_FixedPar>(0, "Camber", myCamberX);
	static auto myCambLocPar = std::make_shared<PtdModel_FixedPar>(0, "MaxCamberLoc", myCambLocX);
	static auto myChordPar = std::make_shared<PtdModel_FixedPar>(0, "Chord", myChordX);
	static auto myThickPar = std::make_shared<PtdModel_FixedPar>(0, "Thick", myThickX);

	static auto mySpanPar = std::make_shared<PtdModel_FixedPar>(0, "Span", mySpanX);


	static auto DEFAULT_NB_SECTIONS = 5;
	static auto myNbSections = DEFAULT_NB_SECTIONS;

	void createCamberForm()
	{
		IMPORT_FORM(ptdModel::WingFormNo1_Camber, myCamberPar);
	}

	void createMaxCamberLocForm()
	{
		IMPORT_FORM(ptdModel::WingFormNo1_MaxCamberLoc, myCambLocPar);
	}

	void createChordForm()
	{
		IMPORT_FORM(ptdModel::WingFormNo1_Chord, myChordPar);
	}

	void createThickForm()
	{
		IMPORT_FORM(ptdModel::WingFormNo1_Thickness, myThickPar);
	}

	void createMakers()
	{
		createCamberForm();
		createMaxCamberLocForm();
		createChordForm();
		createThickForm();
	}

	void execute()
	{
		createMakers();
		
		auto myGlobal = std::make_shared<PtdModel_WingGlobalPars>(mySpanPar);

		auto mySection = std::make_shared<ptdModel::WingSectionNo1_Naca4Digit>();

		myWing = std::make_shared<PtdModel_WingNo1>(myGlobal);
		myWing->ImportMakers(myMakers);

		auto distb = std::make_shared<Geo_UniDistb>(myNbSections - 1);
		distb->SetLower(0);
		distb->SetUpper(mySpanPar->Value());
		distb->Perform();

		myWing->SetxDistb(std::move(distb));
		myWing->SetSection(std::move(mySection));
		
		myWing->Perform();
	}

	void saveTo(const word& name)
	{
		if (NOT myWing)
		{
			FatalErrorIn(FunctionSIG)
				<< "the app. is not executed!" << endl
				<< abort(FatalError);
		}

		if (NOT myWing->UpperPatch())
		{
			FatalErrorIn(FunctionSIG)
				<< "no face has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT myWing->LowerPatch())
		{
			FatalErrorIn(FunctionSIG)
				<< "no face has been found!" << endl
				<< abort(FatalError);
		}
		auto face0 = std::make_shared<Cad_GeomSurface>(1, "Upper", myWing->UpperPatch()->Surface());
		auto face1 = std::make_shared<Cad_GeomSurface>(2, "Lower", myWing->LowerPatch()->Surface());

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
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

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

			fileName myFileName("wingMakerNo1");

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