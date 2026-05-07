#include <PtdModel_BladeSections.hxx>
#include <PtdModel_BladeSection.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static double myTol = 1.0E-6;

	static std::shared_ptr<PtdModel_BladeSections> mySections;

	typedef std::vector<std::shared_ptr<Pln_Edge>> edgeList;
	static std::vector<edgeList> myEdges;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
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
			ar >> mySections;
		}

		if (NOT mySections)
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
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		size_t i = 0;
		for (const auto& x : myEdges)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << x;

			if (verbose)
			{
				Info << " the section, " << i << " is saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}

		if (verbose)
		{
			Info << endl
				<< " - All sections are saved, successfully!" << endl;
		}
	}

	auto retrieveCurve(const std::vector<Pnt2d>& Qs)
	{
		auto curve = Pln_CurveTools::Interpolation(Qs, Standard_False, myTol);
		return std::move(curve);
	}

	auto retrievePoints(const std::vector<Pnt3d>& Qs3d)
	{
		std::vector<Pnt2d> Qs;
		Qs.reserve(Qs3d.size());
		for (const auto& x : Qs3d)
		{
			Pnt2d pt(x.X(), x.Z());
			//pt.Mirror(gp::OY2d());
			Qs.push_back(std::move(pt));
		}
		return std::move(Qs);
	}

	auto retrieveTrailingEdge(const std::vector<Pnt2d>& faceQ, const std::vector<Pnt2d>& backQ)
	{
		const auto& p0 = LastItem(faceQ);
		const auto& p1 = LastItem(backQ);

		if (p0.Distance(p1) <= myTol)
		{
			Handle(Geom2d_Curve) curve;
			return std::move(curve);
		}
		else
		{
			auto curve = Pln_CurveTools::MakeSegment(p0, p1);
			return std::move(curve);
		}
	}

	auto retrieveCurves(const std::shared_ptr<PtdModel_BladeSection>& section)
	{
		const auto faceQ = retrievePoints(section->Face());
		const auto backQ = retrievePoints(section->Back());

		auto trailEdge = retrieveTrailingEdge(faceQ, backQ);

		const auto face = retrieveCurve(faceQ);
		const auto back = retrieveCurve(backQ);
		auto t = std::make_tuple(std::move(face), std::move(back), std::move(trailEdge));
		return std::move(t);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		myEdges.reserve(mySections->Sections().size());
		for (const auto& x : mySections->Sections())
		{
			auto[face, back, t] = retrieveCurves(x);

			std::vector<Handle(Geom2d_Curve)> curves;
			if (face)
			{
				curves.push_back(std::move(face));
			}

			if (back)
			{
				curves.push_back(std::move(back));
			}

			if (t)
			{
				curves.push_back(std::move(t));
			}

			auto edges = Pln_Tools::RetrieveEdges(Pln_Tools::RetrieveCurves(curves));
			myEdges.push_back(std::move(edges));
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
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {LoadModel(name); }), "loadModel");
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

			std::string address = ".\\system\\getSectionCurvesPropNo1";
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