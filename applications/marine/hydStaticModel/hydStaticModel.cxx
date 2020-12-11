#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
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

	static /*const*/ std::shared_ptr<HydStatic_Model> hydrModel /*= std::make_shared<HydStatic_Model>()*/;

	typedef std::shared_ptr<StbGMaker_Model> stbModel_t;
	typedef std::shared_ptr<Marine_Wave> wave_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	const auto& getHydrModel()
	{
		return hydrModel;
	}

	const auto& getWave()
	{
		return getHydrModel()->Wave();
	}

	void loadStbModel(const stbModel_t& m)
	{
		getHydrModel()->LoadModel(m);
	}

	void loadWave(const wave_t& w)
	{
		if (NOT w->IsDone())
		{
			w->Perform();
		}
		getHydrModel()->LoadWave(w);
	}

	void loadDomain(const domain_t& d)
	{
		getHydrModel()->LoadDomain(d);
	}

	void perform()
	{
		getHydrModel()->Perform();
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

	auto createDomain()
	{
		auto domain = Marine_WaterLib::Domain(*getDisplacer());
		return std::move(domain);
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

	/* wave operators*/

	std::shared_ptr<Marine_Wave> createFlatWave(const domain_t& d)
	{
		auto wave = std::make_shared<Marine_FlatWave>(d->Dim());
		wave->Current().SetX(-1);
		wave->Current().SetY(0);
		wave->Current().SetZ(0);

		wave->Wind().SetX(-1);
		wave->Wind().SetY(0);
		wave->Wind().SetZ(0);

		wave->SetPointOnWater(d->Dim()->CalcCentre());
		wave->SetVerticalDirection(Dir3d(0, 0, 1));

		return wave;
	}

	void setCurrent(const wave_t& w, const Vec3d& v)
	{
		w->SetCurrent(v);
	}

	void setWind(const wave_t& w, const Vec3d& v)
	{
		w->SetWind(v);
	}

	void setPointOnWater(const wave_t& w, const Pnt3d& p)
	{
		w->SetPointOnWater(p);
	}

	void setVerticalDir(const wave_t& w, const Dir3d& d)
	{
		w->SetVerticalDirection(d);
	}

	void perform(const wave_t& w)
	{
		w->Perform();
	}

	/*End of the wave operators*/

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

	//- io functions

	void loadStbModel(const std::string& name)
	{
		fileName myFileName(name);
		std::ifstream myFile(myFileName);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		stbModel_t m;
		ar >> m;

		loadStbModel(m);

		auto d = createDomain();

		loadDomain(d);
	}

	void exportToPlt(const wave_t& w, const std::string& name)
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
	}

	void exportToPlt(const wave_t& w, OFstream& f)
	{
		if (w)
		{
			if (NOT w->IsDone())
			{
				w->Perform();
			}
			const auto& geom = w->SurfaceGeometry();

			auto tri = Cad_Tools::Triangulation(geom, 15, 15);
			tri->ExportToPlt(f);
		}
	}

	void exportToPlt(const std::shared_ptr<Marine_Section>& s, OFstream& f)
	{
		s->ExportToPlt(f);
	}



	void exportToPlt(const std::shared_ptr<Marine_CmpSection>& s, OFstream& f)
	{
		if (s->IsXsection())
		{
			for (const auto& x : s->Sections())
			{
				auto poly2 = getMesh(x);
				if (poly2)
				{
					auto poly3 = to3Dx(*poly2, s->X());
					poly3->ExportToPlt(f);
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
					poly3->ExportToPlt(f);
				}
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unknown cmp-section" << endl
				<< abort(FatalError);
		}
	}

	void exportToPlt(const std::shared_ptr<Marine_Body>& b, OFstream& f)
	{
		const auto& sections = b->Sections();
		for (const auto& x : sections)
		{
			exportToPlt(x, f);
		}
	}

	void exportFloatBodyToPlt(const std::string& name)
	{
		fileName myFileName(name);
		OFstream f(myFileName);
		if (NOT getHydrModel()->IsDone())
		{
			perform();
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
	}

	void exportDomain(const std::string& name)
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
	}

	void saveModelTo(const std::string& name)
	{
		fileName myFileName(name);
		std::ofstream myFile(myFileName);

		boost::archive::polymorphic_text_oarchive ar(myFile);

		if (NOT getHydrModel()->IsDone())
		{
			perform();
		}
		ar << getHydrModel();
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
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createPoint(x, y, z); return std::move(t); }), "createPnt3d");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createVec(x, y, z); return std::move(t); }), "createVec3d");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto{auto t = createDir(x, y, z); return std::move(t); }), "createDir3d");

		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadStbModel(name); }), "loadStbModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(getHydrModel()->Wave(), name); }), "exportWaveToPlt");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportDomain(name); }), "exportDomainToPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportFloatBodyToPlt(name); }), "exportFloatBodyToPlt");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveModelTo(name); }), "saveModelTo");

	}

	void setWaves(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->auto {auto t = createFlatWave(getHydrModel()->Domain()); return std::move(t); }), "createFlatWave");
		mod->add(chaiscript::fun([](const wave_t& w, const Pnt3d& p)->void {setPointOnWater(w, p); }), "setPointOnWater");
		mod->add(chaiscript::fun([](const wave_t& w, const Dir3d& d)->void {setVerticalDir(w, d); }), "setVerticalDirection");
		mod->add(chaiscript::fun([](const wave_t& w, const Vec3d& v)->void {setCurrent(w, v); }), "setCurrent");
		mod->add(chaiscript::fun([](const wave_t& w, const Vec3d& v)->void {setWind(w, v); }), "setWind");
		
		mod->add(chaiscript::fun([](const wave_t& w)-> void {loadWave(w); }), "loadWave");
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
	hydrModel = std::make_shared<HydStatic_Model>();

	Marine_FlatWave::dummy();
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

			fileName myFileName("hydStaticModel");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}