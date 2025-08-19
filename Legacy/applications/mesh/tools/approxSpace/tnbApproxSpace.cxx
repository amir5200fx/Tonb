#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Geo3d_ApprxSpace.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_PrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

namespace tnbLib
{

	class PrNode
	{

		/*Private Data*/

		Pnt3d theCoord_;

	public:

		typedef Pnt3d ptType;

		PrNode(const Pnt3d& theCoord)
			: theCoord_(theCoord)
		{}

		// public functions and operators [7/1/2022 Amir]

		const auto& Coord() const
		{
			return theCoord_;
		}

		static const auto& GetCoord(const std::shared_ptr<PrNode>& node)
		{
			return node->Coord();
		}
	};
}

namespace tnbLib
{

	static const std::string loadExt = Cad_Shape::extension;
	static const std::string saveExt = Entity3d_Tetrahedralization::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad_Shape> myShape;
	static std::shared_ptr<Entity3d_Tetrahedralization> myTet;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + loadExt, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape file is null!" << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myTet, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto RetriveCoords(const Poly_Triangulation& t)
	{
		std::vector<Pnt3d> coords;
		coords.reserve(t.NbNodes());

		const auto& nodes = t.Nodes();
		for (Standard_Integer i = 1; i <= nodes.Size(); i++)
		{
			coords.push_back(nodes.Value(i));
		}
		return std::move(coords);
	}

	auto RetrievePoints(const Cad_Shape& s)
	{
		auto tris = Cad_Tools::RetrieveTriangulation(s.Shape());
		std::vector<Pnt3d> coords;
		for (const auto& x : tris)
		{
			auto pts = RetriveCoords(*x);
			for (const auto& p : pts)
			{
				coords.push_back(p);
			}
		}
		return std::move(coords);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		auto pts = RetrievePoints(*myShape);
		auto domain = Geo_BoxTools::GetBox(pts, 0);
		domain.Expand(domain.Diameter()*1.0E-6);

		{
			Geo3d_BalPrTree<std::shared_ptr<PrNode>> approxSpace;

			std::vector<std::shared_ptr<Entity3d_Box>> boxes;
			{
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);
			
				approxSpace.SetMaxUnbalancing(2);
				approxSpace.SetGeometryCoordFunc(&PrNode::GetCoord);
				approxSpace.SetGeometryRegion(std::move(domain));

				for (const auto& x : pts)
				{
					auto b = Geo_BoxTools::GetBox(x, 1.0E-4);

					std::vector<std::shared_ptr<PrNode>> items;
					approxSpace.GeometrySearch(b, items);
					if (items.empty())
					{
						auto node = std::make_shared<PrNode>(x);
						approxSpace.InsertToGeometry(node);
					}
					else
					{
						Standard_Real minDis = RealLast();
						for (const auto& i : items)
						{
							auto dis = i->Coord().Distance(x);
							if (dis < minDis)
							{
								minDis = dis;
							}
						}
						if (minDis > 1.0E-4)
						{
							auto node = std::make_shared<PrNode>(x);
							approxSpace.InsertToGeometry(node);
						}
					}
				}

				if (verbose)
				{
					Info << endl
						<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
				}

				// post balancing [7/9/2022 Amir]
				{
					Global_Timer timer;
					timer.SetInfo(Global_TimerInfo_ms);

					approxSpace.PostBalance();
				}

				if (verbose)
				{

					Info << endl
						<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
				}

				std::vector<Geo3d_BalPrTree<std::shared_ptr<PrNode>>::leafNode*> leaves;
				approxSpace.RetrieveLeavesTo(leaves);

				for (const auto& x : leaves)
				{
					const auto& b = x->Box();
					boxes.push_back(b);
				}
			}

			myTet = std::make_shared<Entity3d_Tetrahedralization>();
			// Triangulation [7/9/2022 Amir]
			{
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				Geo_BoxTools::GetTriangulation(boxes, *myTet);
			}

			if (verbose)
			{
				Info << endl
					<< " - the triangulation is created in: " << global_time_duration << " ms." << endl;
			}
		}

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl
				<< " - time: " << global_time_duration << " ms. " << endl;
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
		// io functions [7/9/2022 Amir]
		
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [7/9/2022 Amir]

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [7/9/2022 Amir]

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
	FatalConvError.throwExceptions();

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
			Info << " This application is aimed to create plane boundary info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbApproxSpace"));

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