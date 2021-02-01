#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Chain.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Cad_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <StbGMaker_Model.hxx>
#include <HydStatic_Model.hxx>
#include <HydStatic_FloatBody.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<HydStatic_Model> model_t;
	typedef std::shared_ptr<Marine_Wave> wave_t;

	static model_t myModel;
	static size_t verbose = 0;

	enum class waveTessellation
	{
		low,
		medium,
		high
	};

	static waveTessellation level;

	void setLevel(const std::string& l)
	{
		if (l IS_EQUAL "low")
		{
			level = waveTessellation::low;
		}
		else if (l IS_EQUAL "medium")
		{
			level = waveTessellation::medium;
		}
		else if (l IS_EQUAL "high")
		{
			level = waveTessellation::high;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified wave tessellation level" << endl
				<< abort(FatalError);
		}
	}

	const auto& getHydrModel()
	{
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}
		return myModel;
	}

	const auto& getWave()
	{
		return getHydrModel()->Wave();
	}

	auto getDisplacer()
	{
		if (NOT getHydrModel()->StbModel())
		{
			FatalErrorIn(FunctionSIG)
				<< "no stability model has been loaded" << endl
				<< abort(FatalError);
		}

		const auto& hull = getHydrModel()->StbModel()->Hull();
		if (NOT hull)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model has no hull!" << endl
				<< abort(FatalError);
		}

		const auto& body = hull->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no body in the hull!" << endl
				<< abort(FatalError);
		}

		auto displacer =
			std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
		return std::move(displacer);
	}

	auto to3Dx(const Entity2d_Polygon& poly2, const double xi)
	{
		auto poly3 = std::make_shared<Entity3d_Polygon>();
		auto& pts = poly3->Points();
		pts.reserve(poly2.NbPoints());
		for (const auto& x : poly2.Points())
		{
			auto pt3 = Pnt3d(xi, x.X(), x.Y());
			pts.push_back(std::move(pt3));
		}
		return std::move(poly3);
	}

	auto to3Dz(const Entity2d_Polygon& poly2, const double zi)
	{
		auto poly3 = std::make_shared<Entity3d_Polygon>();
		auto& pts = poly3->Points();
		pts.reserve(poly2.NbPoints());
		for (const auto& x : poly2.Points())
		{
			auto pt3 = Pnt3d(x.X(), x.Y(), zi);
			pts.push_back(std::move(pt3));
		}
		return std::move(poly3);
	}

	auto getMesh(const std::shared_ptr<Marine_Section>& s)
	{
		const auto& wire = s->Wire();
		auto poly = wire->Polygon();
		return std::move(poly);
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ar(f);
		ar >> myModel;

		if (verbose)
		{
			Info << " the model is loaded from: " << fn << ", successfully!" << endl;
		}
	}

	/*void exportToPlt(const wave_t& w, const std::string& name)
	{
		if (w)
		{
			if (NOT w->IsDone())
			{
				w->Perform();
			}
			OFstream f(name);
			const auto& geom = w->SurfaceGeometry();

			auto tri = Cad_Tools::Triangulation(geom, 15, 15);
			tri->ExportToPlt(f);
		}
	}*/

	void exportToPlt(const wave_t& w, OFstream& f)
	{
		if (w)
		{
			if (NOT w->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the wave algorithm is not performed!" << endl
					<< abort(FatalError);
			}
			const auto& geom = w->SurfaceGeometry();

			if (verbose)
			{
				Info << " - Tessellation level: ";
				switch (level)
				{
				case tnbLib::waveTessellation::low:
					Info << " low" << endl;
					break;
				case tnbLib::waveTessellation::medium:
					Info << " medium" << endl;
					break;
				case tnbLib::waveTessellation::high:
					Info << " high" << endl;
					break;
				default:
					FatalErrorIn(FunctionSIG)
						<< "unspecified level of tessellation has been detected" << endl
						<< abort(FatalError);
					break;
				}
			}

			switch (level)
			{
			case tnbLib::waveTessellation::low:
			{
				auto tri = Cad_Tools::Triangulation(geom, 15, 15);
				tri->ExportToPlt(f);
				break; 
			}
			case tnbLib::waveTessellation::medium:
			{
				auto tri = Cad_Tools::Triangulation(geom, 25, 25);
				tri->ExportToPlt(f);
				break;
			}
			case tnbLib::waveTessellation::high:
			{
				auto tri = Cad_Tools::Triangulation(geom, 45, 45);
				tri->ExportToPlt(f);
				break;
			}
			default:
				FatalErrorIn(FunctionSIG)
					<< "unspecified level of tessellation has been detected" << endl
					<< abort(FatalError);
				break;
			}
		}
	}

	/*void exportToPlt(const std::shared_ptr<Marine_Section>& s, OFstream& f)
	{
		s->ExportToPlt(f);
	}*/

	auto getMesh(const std::shared_ptr<Marine_CmpSection>& s)
	{
		auto totTri = std::make_shared<Entity3d_Chain>();
		if (s->IsXsection())
		{
			for (const auto& x : s->Sections())
			{
				auto poly2 = getMesh(x);
				if (poly2)
				{
					auto poly3 = to3Dx(*poly2, s->X());
					auto tri = std::make_shared<Entity3d_Chain>(poly3->Points(), dualConnectivityList_Chain(poly3->NbPoints() - 1));
					totTri->Add(*tri);
				}
			}
		}
		else if (s->IsZsection())
		{
			for (const auto& x : s->Sections())
			{
				auto poly2 = getMesh(x);
				if (poly2)
				{
					auto poly3 = to3Dz(*poly2, s->X());
					auto tri = std::make_shared<Entity3d_Chain>(poly3->Points(), dualConnectivityList_Chain(poly3->NbPoints() - 1));
					totTri->Add(*tri);
				}
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unknown cmp-section" << endl
				<< abort(FatalError);
		}
		return std::move(totTri);
	}

	void exportToPlt(const std::shared_ptr<Marine_Body>& b, OFstream& f)
	{
		const auto& sections = b->Sections();
		auto totTri = std::make_shared<Entity3d_Chain>();
		for (const auto& x : sections)
		{
			auto mesh = getMesh(x);
			totTri->Add(*mesh);
		}
		totTri->ExportToPlt(f);
	}

	void exportFloatBodyToPlt(const std::string& name)
	{
		fileName myFileName(name);
		OFstream f(myFileName);
		if (NOT getHydrModel()->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the hydrostatic algorithm is not performed!" << endl
				<< abort(FatalError);
		}
		const auto& fl = getHydrModel()->FloatBody();
		const auto& wetted = fl->Wetted();
		const auto& dry = fl->Dry();

		if (wetted)
		{
			exportToPlt(wetted, f);
		}

		if (dry)
		{
			exportToPlt(dry, f);
		}

		if (verbose)
		{
			Info << " the float body is exported to the TecPlot, successfully!" << endl;
		}
	}

	void exportDomainToPlt(const std::string& name)
	{
		fileName myFileName(name);
		OFstream f(myFileName);

		if (getHydrModel())
		{
			const auto& d = getHydrModel()->Domain();
			auto tri = Cad_PreviewTools::Box(*d->Dim());
			if (tri) tri->ExportToPlt(f);

			const auto& model = getHydrModel()->StbModel();
			if (model->Hull())
			{
				const auto& hull = model->Hull();
				if (hull->Body())
				{
					exportToPlt(hull->Body(), f);
				}
			}

			for (const auto& x : model->Tanks())
			{
				if (x->Body())
				{
					exportToPlt(x->Body(), f);
				}
			}

			for (const auto& x : model->Sails())
			{
				auto sail = std::dynamic_pointer_cast<marineLib::Model_ShapeSail>(x);
				if (sail)
				{
					exportToPlt(sail->Body(), f);
				}
			}

			if (getHydrModel()->Wave())
			{
				exportToPlt(getHydrModel()->Wave(), f);
			}
		}

		if (verbose)
		{
			Info << " the domain is exported to the TecPlot, successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportDomainToPlt(name); }), "exportDomainToPlt");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportFloatBodyToPlt(name); }), "exportFloatBodyToPlt");

		mod->add(chaiscript::fun([](const std::string& l)-> void {setLevel(l); }), "setWaveTessellation");

		mod->add(chaiscript::fun([](unsigned int i)-> void {verbose = i; }), "setVerbose");
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

			chai.add(mod);

			fileName myFileName("TnbHydStaticModelViewer");

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