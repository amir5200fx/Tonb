#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <gp_Pln.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Compound.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepBndLib.hxx>
#include <BRep_Builder.hxx>
#include <Bnd_Box.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepFeat_SplitShape.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool exeTag = false;
	static bool loadTag = false;
	static bool runParallel = false;

	static std::shared_ptr<Cad_Shape> myShape;

	static std::shared_ptr<Cad_Shape> mySub0;
	static std::shared_ptr<Cad_Shape> mySub1;

	static Pnt3d myLoc = gp::Origin();
	static Dir3d myDir = gp::DX();

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setRunParallel(bool c)
	{
		runParallel = c;
		if (verbose)
		{
			Info << endl
				<< " - run parallel is set to: " << (runParallel ? "TRUE" : "FALSE") << endl;
		}
	}

	void setLoc(const Pnt3d& pt)
	{
		myLoc = pt;
		if (verbose)
		{
			Info << endl
				<< " - the location of plane is set to: " << pt << endl;
		}
	}

	void setNormal(const Dir3d& n)
	{
		myDir = n;
		if (verbose)
		{
			Info << endl
				<< " - the direction of plane is set to: " << n << endl;
		}
	}

	auto selectPlane(const Entity3d_Box& b)
	{
		auto c = b.CalcCentre();
		auto n = gp::DX();
		const auto[lx, ly, lz] = b.Length();
		if (lx > std::max(ly, lz))
		{
			const auto x0 = b.P0().X();
			const auto x1 = b.P1().X();
			c.X() = MEAN(x0, x1);
		}
		else if (ly > std::max(lx, lz))
		{
			const auto x0 = b.P0().Y();
			const auto x1 = b.P1().Y();
			c.Y() = MEAN(x0, x1);
			n = gp::DY();
		}
		else if (lz > std::max(lx, ly))
		{
			const auto x0 = b.P0().Z();
			const auto x1 = b.P1().Z();
			c.Z() = MEAN(x0, x1);
			n = gp::DZ();
		}
		auto pln = std::make_pair(std::move(c), std::move(n));
		return std::move(pln);
	}

	void init(const std::shared_ptr<Cad_Shape>& shape)
	{
		auto[pt, n] = selectPlane(*shape->BoundingBox());
		myLoc = pt;
		myDir = n;
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

		init(myShape);

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		{
			size_t i = 0;
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);
			oa << mySub0;

			file.close();
		}

		{
			size_t i = 1;
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);
			oa << mySub1;

			file.close();
		}

		if (verbose)
		{
			Info << endl;
			Info << " the files are saved, successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no model has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		try
		{
			BRepAlgoAPI_Section aSection(myShape->Shape(), gp_Pln(myLoc, myDir), Standard_False);
			aSection.ComputePCurveOn1(Standard_True);
			aSection.Approximation(Standard_True);
			aSection.SetRunParallel(runParallel);
			aSection.Build();

			BRepFeat_SplitShape spliter(myShape->Shape());
			for (TopExp_Explorer iter(aSection.Shape(), TopAbs_EDGE); iter.More(); iter.Next())
			{
				TopoDS_Shape anEdge = iter.Current();
				TopoDS_Face aFace;
				
				if (aSection.HasAncestorFaceOn1(anEdge, aFace))
				{
					TopoDS_Edge E = TopoDS::Edge(anEdge);
					TopoDS_Face F = TopoDS::Face(aFace);

					spliter.Add(E, F);
				}
			}

			spliter.Build();

			// Rebuild left and right shape.
			BRep_Builder aBuilder;
			TopoDS_Compound aLeftCompound;
			TopoDS_Compound aRightCompound;

			aBuilder.MakeCompound(aLeftCompound);
			aBuilder.MakeCompound(aRightCompound);

			// Left shape.
			TopTools_MapOfShape aLeftShapeMap;
			const TopTools_ListOfShape& aLeftShapes = spliter.Left();
			for (auto i = aLeftShapes.cbegin(); i != aLeftShapes.cend(); i++)
			{
				aLeftShapeMap.Add(*i);
				aBuilder.Add(aLeftCompound, *i);
			}

			// Right shape.
			TopTools_IndexedMapOfShape aShapeMap;
			TopExp::MapShapes(spliter.Shape(), TopAbs_FACE, aShapeMap);

			for (auto i = aShapeMap.cbegin(); i != aShapeMap.cend(); i++)
			{
				if (!aLeftShapeMap.Contains(*i))
				{
					aBuilder.Add(aRightCompound, *i);
				}
			}

			mySub0 = std::make_shared<Cad_Shape>(0, "left side of " + myShape->Name(), aLeftCompound);
			mySub1 = std::make_shared<Cad_Shape>(0, "right side of " + myShape->Name(), aRightCompound);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}

		exeTag = true;
	}
}

//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo

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
		mod->add(chaiscript::fun([](const Pnt3d& loc)-> void {setLoc(loc); }), "setLocation");
		mod->add(chaiscript::fun([](const Dir3d& dir)-> void {setNormal(dir); }), "setNormal");

		//- functions

		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Pnt3d(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Dir3d(x, y, z); }), "createDirection");
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
			Info << " This application is aimed to split a shape by a plane." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: "<< endl
				<< " - setRunParallel(bool)" << endl
				<< " - setLocation(Point)" << endl
				<< " - setNormal(Direction)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - execute()" << endl
				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [Direction] createDirection(double, double, double)" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\splitShape";
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