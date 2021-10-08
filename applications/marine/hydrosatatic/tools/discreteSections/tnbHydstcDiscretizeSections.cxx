#include <Marine_BodyModelType.hxx>
#include <Marine_PlnCurves.hxx>
#include <Marine_SectionsIO.hxx>
#include <Marine_DisctSectionsIO.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_AdTree.hxx>
#include <Cad_Shape.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Geo_AdTree.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned short verbose(0);

	static double myDeflection = 1.0E-3;
	static double myAngle = 2.5;
	static double myMinSize = 1.0E-4;

	static unsigned int myMaxNbSubdivision = 50;
	static unsigned int myInitNbSubdivision = 4;
	static unsigned int myNbSamples = 5;

	static std::shared_ptr<marineLib::io::Sections> mySections;

	void printSettings()
	{
		Info << endl
			<< " - deflection: " << myDeflection << endl
			<< " - angle: " << myAngle << endl
			<< " - min. size: " << myMinSize << endl
			<< " - max. nb. of subdivisions: " << myMaxNbSubdivision << endl
			<< " - nb. of init. subdivisions: " << myInitNbSubdivision << endl
			<< " - nb. of sample points: " << myNbSamples << endl;
	}

	void setDeflection(double x)
	{
		myDeflection = x;
		if (verbose)
		{
			Info << endl
				<< " - deflection is set to: " << myDeflection << endl;
		}
	}

	void setAngle(double x)
	{
		myAngle = x;
		if (verbose)
		{
			Info << endl
				<< " - angle is set to: " << myAngle << endl;
		}
	}

	void setMinSize(double x)
	{
		myMinSize = x;
		if (verbose)
		{
			Info << endl
				<< " - min. size is set to: " << myMinSize << endl;
		}
	}

	void setMaxNbSub(unsigned int n)
	{
		myMaxNbSubdivision = (n < 10 ? 10 : n);
		myMaxNbSubdivision = (n > 200 ? 200 : n);
		if (verbose)
		{
			Info << endl
				<< " - max. nb. of subdivisions is set to: " << myMaxNbSubdivision << endl;
		}
	}

	void setNbInitSub(unsigned int n)
	{
		myInitNbSubdivision = (n < 2 ? 2 : n);
		myInitNbSubdivision = (n > 20 ? 20 : n);
		if (verbose)
		{
			Info << endl
				<< " - nb. of init. subdivisions is set to: " << myInitNbSubdivision << endl;
		}
	}

	void setNbSamples(unsigned int n)
	{
		myNbSamples = (n < 2 ? 2 : n);
		myNbSamples = (n > 10 ? 10 : n);
		if (verbose)
		{
			Info << endl
				<< " - nb. of sample points is set to: " << myNbSamples << endl;
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
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
				<< "the algorithm has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		auto myDisctSections = std::make_shared<marineLib::io::DisctSections>();
		myDisctSections->LoadSections(mySections);
		
		auto myInfo = std::make_shared<marineLib::io::DisctSections::AlgInfo>();
		myInfo->Angle = myAngle;
		myInfo->Deflection = myDeflection;
		myInfo->initNbSubdivision = myInitNbSubdivision;
		myInfo->maxNbSubdivision = myMaxNbSubdivision;
		myInfo->minSize = myMinSize;
		myInfo->nbSmaples = myNbSamples;

		myDisctSections->SetInfo(std::move(myInfo));

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myDisctSections;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto approxCurve(const std::shared_ptr<Pln_Curve>& curve, const std::shared_ptr<Geo_ApprxCurve_Info>& f)
	{
		const auto& geometry = curve->Geometry();
		if (NOT geometry)
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found!" << endl
				<< abort(FatalError);
		}
		const auto d = curve->BoundingBox(0).Diameter();
		f->SetApprox(myDeflection*d);
		f->SetMinSize(myMinSize*d);
		auto alg = std::make_shared<Geo2d_ApprxCurve>(geometry, curve->FirstParameter(), curve->LastParameter(), f);
		alg->Perform();
		return alg->Chain();
	}

	auto calcBoundingBox(const std::vector<std::shared_ptr<Pln_Edge>>& edges)
	{
		auto iter = edges.begin();
		auto b = (*iter)->BoundingBox(0);
		iter++;
		while (iter NOT_EQUAL edges.end())
		{
			b = Geo_BoxTools::Union(b, (*iter)->BoundingBox(0));
			iter++;
		}
		return std::move(b);
	}


	struct node
	{
		Pnt2d coord;
		int id;

		typedef Pnt2d ptType;

		node(Pnt2d&& p, int i)
			: coord(p)
			, id(i)
		{}
	};

	auto mergedPoly(std::vector<Pnt2d>& pnts, const Entity2d_Box& b)
	{
		Geo_AdTree<std::shared_ptr<node>> engine;
		engine.SetGeometryRegion(b);
		engine.SetGeometryCoordFunc([](const std::shared_ptr<node>& n)-> const auto& {return n->coord; });
		
		const auto r = b.Diameter()*1.0E-6;
		int k = 0;
		for (auto& x : pnts)
		{
			//auto bb = Geo_BoxTools::GetBox(x, r);
			auto bb = Entity2d_Box::Box(x, r);

			std::vector<std::shared_ptr<node>> items;
			engine.GeometrySearch(bb, items);

			bool insert = true;
			for (const auto& t : items)
			{
				if (x.Distance(t->coord) <= r)
				{
					insert = false;
					break;
				}
			}

			if (insert)
			{
				auto n = std::make_shared<node>(std::move(x), ++k);
				engine.InsertToGeometry(n);
			}
		}
		std::vector<std::shared_ptr<node>> nodes;
		engine.RetrieveFromGeometryTo(nodes);

		std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<node>& n0, const std::shared_ptr<node>& n1)-> auto{return n0->id < n1->id; });

		engine.Clear();

		std::vector<Pnt2d> coords;
		coords.reserve(nodes.size());
		for (auto& x : nodes)
		{
			coords.push_back(std::move(x->coord));
		}

		auto poly = std::make_shared<Entity2d_Polygon>();
		poly->Points() = std::move(coords);
		return std::move(poly);
	}

	void approxSection(const std::vector<std::shared_ptr<Pln_Edge>>& edges, const std::shared_ptr<Geo_ApprxCurve_Info>& f)
	{
		auto b = calcBoundingBox(edges);
		b.Expand(b.Diameter()*1.0e-4);

		for (const auto& x : edges)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null edge has been detected!" << endl
					<< abort(FatalError);
			}
			const auto& curve = x->Curve();

			auto poly = approxCurve(curve, f);
			
			//auto merged = mergedPoly(poly->Points(), b);

			//x->Mesh() = std::move(merged);
			x->Mesh() = std::move(poly);
			//const auto d = curve->BoundingBox(0).Diameter();
			//f->SetApprox(myDeflection*d);
			//f->SetMinSize(myMinSize*d);

			//x->Approx(f);
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		auto f = std::make_shared<Geo_ApprxCurve_Info>();
		f->SetAngle(myAngle);
		f->SetApprox(myDeflection);
		f->SetInitNbSubdivision(myInitNbSubdivision);
		f->SetMaxNbSubdivision(myMaxNbSubdivision);
		f->SetMinSize(myMinSize);
		f->SetNbSamples(myNbSamples);

		const auto& myEdges = mySections->GetSections();

		size_t k = 0;
		for (const auto& x : myEdges)
		{	
			if (verbose)
			{
				Info << " - section nb. " << k++ << endl;
			}
			approxSection(x->Edges(), f);
		}

		if (verbose)
		{
			Info << endl
				<< " All sections are discretized, successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {printSettings(); }), "printSettings");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setDeflection(x); }), "setDeflection");
		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "setMinSize");
		mod->add(chaiscript::fun([](unsigned int n)->void {setMaxNbSub(n); }), "setMaxNbSubdivisions");
		mod->add(chaiscript::fun([](unsigned int n)-> void {setNbInitSub(n); }), "setNbInitSubdivisions");
		mod->add(chaiscript::fun([](unsigned int n)-> void {setNbSamples(n); }), "setNbSamples");

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
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to discrete the sections of the hull." << endl;
			Info << endl
				<< " Function list:" << endl << endl
				<< " # IO functions: " << endl << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings:" << endl << endl
				<< " - setAngle(double);  " << endl
				<< " - setDeflection(double);  " << endl
				<< " - setMinSize(double);  " << endl
				<< " - setMaxNbSubdivisions(unsigned int);  " << endl
				<< " - setNbInitSubdivisions(unsigned int);  " << endl
				<< " - setNbSamples(unsigned int);  " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - printSettings()" << endl << endl

				<< " # Operators:" << endl << endl
				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--settings"))
		{
			printSettings();
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbHydstcDiscretizeSections";
			fileName myFileName(address);

			try
			{
				chai.eval_file(myFileName);
				return 0;
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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}