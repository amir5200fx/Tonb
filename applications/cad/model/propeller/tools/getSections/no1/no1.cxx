#include <PtdModel_PropBladeNo1.hxx>
#include <PtdModel_BladeView.hxx>
#include <PtdModel_UnWrappedBladeSection.hxx>
#include <PtdModel_xPars.hxx>
#include <PtdModel_BladeFormMakersNo1.hxx>
#include <PtdModel_BladeExpandedView.hxx>
#include <PtdModel_BladeSections.hxx>
#include <PtdModel_BladeSection.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<PtdModel_PropBlade> myBlade;
	static std::shared_ptr<PtdModel_BladeSections> mySections;

	static bool doSkew = true;
	static bool doRake = true;
	static bool doPitch = true;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setDoSkew(bool c)
	{
		doSkew = c;
		if (verbose)
		{
			Info << endl
				<< " - the skew tag is set to: " << (doSkew ? "TRUE" : "FALSE") << endl;
		}
	}

	void setDoRake(bool c)
	{
		doRake = c;
		if (verbose)
		{
			Info << endl
				<< " - the rake tag is set to: " << (doRake ? "TRUE" : "FALSE") << endl;
		}
	}

	void setDoPitch(bool c)
	{
		doPitch = c;
		if (verbose)
		{
			Info << endl
				<< " - the pitch tag is set to: " << (doPitch ? "TRUE" : "FALSE") << endl;
		}
	}

	void LoadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> myBlade;
		}

		if (NOT myBlade)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		ar << mySections;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no blade has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& bladeView = myBlade->BladeView();
		if (NOT bladeView)
		{
			FatalErrorIn(FunctionSIG)
				<< "no blade view has been detected in the blade!" << endl
				<< abort(FatalError);
		}

		const auto& unWrapped = bladeView->UnWrappedSections();
		if (unWrapped.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list of the unwrapped sections is empty" << endl
				<< abort(FatalError);
		}

		const auto& xPars = myBlade->xParameters();
		if (NOT xPars)
		{
			FatalErrorIn(FunctionSIG)
				<< "no xParameters has been found!" << endl
				<< abort(FatalError);
		}

		const auto& X = xPars->Xs();

		const auto xSkew = xPars->SelectParameter(ptdModel::BladeFormNo1_Skew::TypeName_);
		const auto xRake = xPars->SelectParameter(ptdModel::BladeFormNo1_Rake::TypeName_);
		const auto xPitch = xPars->SelectParameter(ptdModel::BladeFormNo1_Pitch::TypeName_);
		const auto xChord = xPars->SelectParameter(ptdModel::BladeFormNo1_Chord::TypeName_);

		const auto& xSkewRef = *xSkew;
		const auto& xRakeRef = *xRake;
		const auto& xPitchRef = *xPitch;
		const auto& xChordRef = *xChord;

		const auto& expandedViews = bladeView->ExpandedViews();
		if (expandedViews.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no expanded view has been found!" << endl
				<< abort(FatalError);
		}

		const auto nbSpans = expandedViews[0]->NbSpans();

		std::vector<std::shared_ptr<PtdModel_BladeSection>> bladeSections;
		bladeSections.reserve(xPars->NbSections());

		for (size_t section = 0; section < xPars->NbSections(); section++)
		{
			auto sk = xSkewRef[section];
			auto rk = xRakeRef[section];
			auto xpitch = xPitchRef[section];
			auto xchord = xChordRef[section];

			if (NOT doPitch)
			{
				xpitch = 0;
			}

			if (NOT doSkew)
			{
				sk = 0;
			}

			if (NOT rk)
			{
				rk = 0;
			}

			auto t = std::make_shared<PtdModel_UnWrappedBladeSection>();
			Debug_Null_Pointer(t);

			std::vector<Pnt3d> face;
			std::vector<Pnt3d> back;

			face.reserve(nbSpans);
			back.reserve(nbSpans);


			const auto& expandedView = expandedViews[section];

			const auto& Xs = expandedView->Xs();
			const auto& Tb = expandedView->Tb();
			const auto& Tf = expandedView->Tf();

			auto cosPitch = std::cos(xpitch);
			auto sinPitch = std::sin(xpitch);

			for (size_t i = 0; i < nbSpans; i++)
			{
				auto xs = Xs[i];
				auto tb = Tb[i];
				auto tf = Tf[i];

				Pnt3d ptBack
				(
					sk*cosPitch + xs * cosPitch - tb * sinPitch,
					X[section],
					sk*sinPitch + rk - xs * sinPitch - tb * cosPitch
				);
				Pnt3d ptFace
				(
					sk*cosPitch + xs * cosPitch - tf * sinPitch,
					X[section],
					sk*sinPitch + rk - xs * sinPitch - tf * cosPitch
				);

				back.push_back(std::move(ptBack));
				face.push_back(std::move(ptFace));
			}

			t->SetBack(std::move(back));
			t->SetFace(std::move(face));

			bladeSections.push_back(std::move(t));
		}

		mySections = std::make_shared<PtdModel_BladeSections>(std::move(bladeSections));

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
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](bool c)-> void {setDoPitch(c); }), "doPitch");
		mod->add(chaiscript::fun([](bool c)-> void {setDoSkew(c); }), "doSkew");
		mod->add(chaiscript::fun([](bool c)-> void {setDoRake(c); }), "doRake");

		mod->add(chaiscript::fun([](const std::string& name)-> void {LoadModel(name); }), "loadModel");
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

			std::string address = ".\\system\\getSectionsPropNo1";
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