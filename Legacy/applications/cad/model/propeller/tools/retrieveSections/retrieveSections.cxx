#include <PtdModel_Shape.hxx>
#include <PtdModel_RadialSection.hxx>
#include <PtdModel_BladeRadialSections.hxx>
#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <PtdModel_Par.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <gp_Trsf.hxx>
#include <gp_Ax3.hxx>
#include <gp_Cylinder.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <ProjLib_ProjectOnSurface.hxx>
#include <GeomProjLib.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned int myNbSections = 20;
	static std::string myDistbAlg = "uniform";

	static double myOffset = 1.0E-3;
	static bool myApprox = true;
	static bool myParallel = true;

	static std::shared_ptr<PtdModel_Shape> myShape;
	static std::shared_ptr<PtdModel_BladeRadialSections> myBlade;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setNbSections(unsigned int n)
	{
		myNbSections = n;
		if (verbose)
		{
			Info << endl
				<< " - the nb. of sections is set to: " << myNbSections << endl;
		}
	}

	void setDistbAlg(const std::string& name)
	{
		myDistbAlg = name;
		if (verbose)
		{
			Info << endl
				<< " - the distb. alg. is set to: " << name << endl;
		}
	}

	void setApprox(bool c)
	{
		myApprox = c;
		if (verbose)
		{
			Info << endl
				<< " - the approx. is set to: " << (myApprox ? "TRUE" : "FALSE") << endl;
		}
	}

	void setRunParallel(bool c)
	{
		myParallel = c;
		if (verbose)
		{
			Info << endl
				<< " - the parallel mode is set to: " << (myParallel ? "TRUE" : "FALSE") << endl;
		}
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
			ar >> myShape;
		}

		if (NOT myShape)
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

		ar << myBlade;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	std::shared_ptr<Geo_xDistb> createDistbSpace(double r0, double r1)
	{
		if (myDistbAlg IS_EQUAL "uniform")
		{
			auto alg = std::make_shared<Geo_UniDistb>(myNbSections);
			alg->SetLower(r0);
			alg->SetUpper(r1);

			alg->Perform();
			return std::move(alg);
		}
		else if (myDistbAlg IS_EQUAL "cosine")
		{
			auto alg = std::make_shared<Geo_CosineDistb>(myNbSections);
			alg->SetLower(r0);
			alg->SetUpper(r1);

			alg->Perform();
			return std::move(alg);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " invalid type of spacing has been found!" << endl
				<< " - algorithms: uniform, cosine" << endl
				<< abort(FatalError);

			std::shared_ptr<Geo_xDistb> alg;
			return std::move(alg);
		}
	}

	auto retrieveSpan(const std::shared_ptr<ptdModel::Shape_PropBladeParent>& blade)
	{
		const auto& info = blade->BladeInfo();
		
		const auto dr = info->Diameter()->Value() / 2 - info->HubRadius()->Value();
		auto t = std::make_pair(info->HubRadius()->Value() + myOffset * dr, info->Diameter()->Value() / 2 - myOffset * dr);
		return std::move(t);
	}

	auto createCylinder(double r, const gp_Ax2& ax)
	{
		gp_Ax3 ax3(ax);
		gp_Cylinder cyl(ax3, r);

		Handle(Geom_CylindricalSurface) surf = new Geom_CylindricalSurface(cyl);
		return std::move(surf);
	}

	auto retrieveH(const std::shared_ptr<Cad_Shape>& shape)
	{
		const auto& b = shape->BoundingBox();
		const auto d = b->Diameter();
		return d;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no blade has been loaded!" << endl
				<< abort(FatalError);
		}

		auto blade = std::dynamic_pointer_cast<ptdModel::Shape_PropBladeParent>(myShape);
		if (NOT blade)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is not parent blade" << endl
				<< abort(FatalError);
		}

		const auto& shape = blade->Shape();
		if (NOT shape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been found!" << endl
				<< abort(FatalError);
		}

		const auto[r0, r1] = retrieveSpan(blade);

		const auto distb = createDistbSpace(r0, r1);
		const auto h = retrieveH(shape);

		const auto& ax = blade->Axis();

		auto prop = std::make_shared<PtdModel_BladeRadialSections>();
		prop->SetOrigin(ax);

		std::vector<std::shared_ptr<PtdModel_RadialSection>> radialSections;
		radialSections.reserve(distb->Size());

		if (verbose)
		{
			Info << endl;
		}
		size_t k = 0;
		for (auto r : distb->Values())
		{
			if (verbose)
			{
				Info << " section id: " << k++ << ", radius: " << r << endl;
			}

			auto s = createCylinder(r, ax);
			auto face = BRepBuilderAPI_MakeFace(s, 1.0E-6);

			BRepAlgoAPI_Section section(shape->Shape(), face, Standard_False);
			section.SetRunParallel(myParallel);
			section.SetUseOBB(Standard_True);
			//section.Approximation(myApprox);
			//section.ComputePCurveOn2(Standard_True);

			section.Build();

			const auto& IntShape = section.Shape();

			std::vector<Handle(Geom2d_Curve)> curves;
			for (TopExp_Explorer iter(IntShape, TopAbs_EDGE); iter.More(); iter.Next())
			{
				TopoDS_Edge anEdge = TopoDS::Edge(iter.Current());

				Standard_Real f, l;
				auto curve = BRep_Tool::Curve(anEdge, f, l);

				auto curve2d = GeomProjLib::Curve2d(curve, s);
				curves.push_back(std::move(curve2d));

				//std::cout << "edge" << std::endl;
				//TopoDS_Shape anEdge = iter.Current();
				//TopoDS_Face aFace;

				/*if (section.HasAncestorFaceOn2(anEdge, aFace))
				{
					std::cout << "yess!" << std::endl;
					TopoDS_Edge E = TopoDS::Edge(anEdge);
					TopoDS_Face F = TopoDS::Face(aFace);

					Standard_Real f, l;
					auto paraCurve = BRep_Tool::CurveOnSurface(E, F, f, l);

					curves.push_back(std::move(paraCurve));
				}*/
			}
			//PAUSE;
			auto radialSection = std::make_shared<PtdModel_RadialSection>(std::move(curves), r);
			radialSections.push_back(std::move(radialSection));
		}

		prop->SetSections(std::move(radialSections));

		myBlade = std::move(prop);
		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}
}

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](bool c)-> void {setRunParallel(c); }), "setRunParallel");
		mod->add(chaiscript::fun([](bool c)-> void {setApprox(c); }), "setApprox");

		//- functions

		mod->add(chaiscript::fun([](unsigned int n)-> void {setNbSections(n); }), "setNbSections");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setDistbAlg(name); }), "setDistbAlg");
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
			Info << " This application is aimed to retrieve sections of a blade." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl
				<< " - setRunParallel(bool)" << endl
				<< " - setApprox(bool)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - execute()" << endl
				<< " - setNbSections(unsigned int)" << endl
				<< " - setDistbAlg(string);         - types: uniform, cosine" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\retrieveSections";
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

}