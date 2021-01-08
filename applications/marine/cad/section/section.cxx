#include <Marine_PlnCurves.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Section.hxx>
#include <Marine_CmpSection.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Marine_TankModeler.hxx>
#include <Marine_SailModeler.hxx>
#include <Marine_DisplacerModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>




namespace tnbLib
{
	static std::vector<std::shared_ptr<Marine_PlnCurve>> curves;
	static size_t nbCurves = 0;

	static marineLib::curveType sectionType;
	static std::shared_ptr<Cad2d_Modeler> modeler;
	static double xLoc = 0;
	static bool setLoc = false;

	static std::shared_ptr<Marine_CmpSection> myCmpSection;


	void loadCurves(const std::string& name)
	{
		curves.reserve(nbCurves);
		for (size_t i = 0; i < nbCurves; i++)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			boost::archive::polymorphic_text_iarchive oa(file);

			std::shared_ptr<Pln_Curve> curve;

			oa >> curve;
			auto mcurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
			if (!mcurve)
			{
				FatalErrorIn(FunctionSIG)
					<< "the curve is not marine type" << endl
					<< abort(FatalError);
			}
			curves.push_back(std::move(mcurve));
		}

		if (curves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been loaded" << endl
				<< abort(FatalError);
		}
		const auto& curve = curves[0];

		switch (curve->CurveType())
		{
		case marineLib::curveType::displacer:
			sectionType = marineLib::curveType::displacer;
			break;
		case marineLib::curveType::sail:
			sectionType = marineLib::curveType::sail;
			break;
		case marineLib::curveType::tank:
			sectionType = marineLib::curveType::tank;
			break;
		default:
			FatalErrorIn(FunctionSIG)
				<< "the curve type is not supported" << endl
				<< abort(FatalError);
		}

		for (const auto& x : curves)
		{
			if (x->CurveType() NOT_EQUAL sectionType)
			{
				FatalErrorIn(FunctionSIG)
					<< "curve types must be the same." << endl
					<< abort(FatalError);
			}
		}

	}

	auto makeEdge(const std::shared_ptr<Marine_PlnCurve>& curve)
	{
		auto v0 = std::make_shared<Pln_Vertex>(curve->Value(curve->FirstParameter()));
		auto v1 = std::make_shared<Pln_Vertex>(curve->Value(curve->LastParameter()));

		auto edge = std::make_shared<Pln_Edge>(v0, v1, curve);

		return std::move(edge);
	}

	void makeModeler()
	{
		switch (sectionType)
		{
		case marineLib::curveType::displacer:
			modeler = std::make_shared<Marine_DisplacerModeler>();
			break;
		case marineLib::curveType::sail:
			modeler = std::make_shared<Marine_SailModeler>();
			break;
		case marineLib::curveType::tank:
			modeler = std::make_shared<Marine_TankModeler>();
			break;
		default:
			FatalErrorIn(FunctionSIG)
				<< "something went wrong." << endl
				<< abort(FatalError);
		}
	}

	auto makeSections(const std::map<Standard_Integer, std::shared_ptr<Cad2d_Plane>>& planes)
	{
		std::vector<std::shared_ptr<Marine_Section>> sections;
		sections.reserve(planes.size());
		switch (sectionType)
		{
		case marineLib::curveType::displacer:
		{
			for (const auto& x : planes)
			{
				auto section = Marine_SectTools::ConvertToSection(x.second, Marine_SectionType::displacer);
				sections.push_back(std::move(section));
			}
			break;
		}
		case marineLib::curveType::sail:
		{
			for (const auto& x : planes)
			{
				auto section = Marine_SectTools::ConvertToSection(x.second, Marine_SectionType::sail);
				sections.push_back(std::move(section));
			}
			break;
		}
		case marineLib::curveType::tank:
		{
			for (const auto& x : planes)
			{
				auto section = Marine_SectTools::ConvertToSection(x.second, Marine_SectionType::tank);
				sections.push_back(std::move(section));
			}
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "something went wrong." << endl
				<< abort(FatalError);
			break;
		}

		return std::move(sections);

	}

	void execute()
	{
		if (!setLoc)
		{
			FatalErrorIn(FunctionSIG)
				<< "no location has been set for the section" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		edges.reserve(nbCurves);
		for (const auto& x : curves)
		{
			auto edge = makeEdge(x);
			edges.push_back(std::move(edge));
		}

		makeModeler();

		modeler->Import(std::move(edges));

		Cad2d_Modeler::selctList l;
		modeler->SelectAll(l);
		modeler->MakePlanes(l, gp::YOZ());

		const auto& planes = modeler->Planes();
		if (planes.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been constructed." << endl
				<< abort(FatalError);
		}

		auto sections = makeSections(planes);
		auto compSection = Marine_SectTools::CmpSectionCreator(sections);
		Marine_SectTools::SetLocation(compSection, xLoc);

		myCmpSection = std::move(compSection);
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);
		
		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myCmpSection;
		
	}

}


#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void SectionMaker(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void { loadCurves(name); }), "loadCurve");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			SectionMaker(mod);

			chai.add(mod);

			fileName myFileName("section");

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