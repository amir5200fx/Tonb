#include <PtdShapeFit_ProjMeshToFace.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomSurface.hxx>
#include <GeoTop_Tools.hxx>
#include <GeoTop2d_Element.hxx>
#include <Geo_Tools.hxx>
#include <GeoSlicer2d_PolyLine.hxx>
#include <Geo_AdTree.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <Poly_Triangulation.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Handle.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Triangulation> myMesh;
	static std::shared_ptr<Cad_Shape> myShape;

	static std::shared_ptr<Entity3d_Triangulation> myMerged;

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadShape()
	{
		checkFolder("shape");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\shape)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				{
					auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();

					myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
					if (NOT myShape)
					{
						FatalErrorIn(FunctionSIG)
							<< " the shape is null." << endl
							<< abort(FatalError);
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl;
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();

			myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
			if (NOT myShape)
			{
				FatalErrorIn(FunctionSIG)
					<< " the shape is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadMesh3d()
	{
		checkFolder("mesh");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\mesh)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();

				myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
				if (NOT myMesh)
				{
					FatalErrorIn(FunctionSIG)
						<< " the mesh file is null!" << endl
						<< abort(FatalError);
				}
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();

			myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
			if (NOT myMesh)
			{
				FatalErrorIn(FunctionSIG)
					<< " the mesh file is null!" << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadMeshFile(const std::string& name)
	{
		file::CheckExtension(name);

		myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
		if (NOT myMesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the mesh is null." << endl
				<< abort(FatalError);
		}
	}

	void loadShapeFile(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "the shape is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("shape"))
		{
			loadShape();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();
			loadShapeFile(name);
		}

		if (boost::filesystem::is_directory("mesh"))
		{
			loadMesh3d();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
			loadMeshFile(name);
		}

		loadTag = true;
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

		file::SaveTo(myMerged, name + Entity3d_Triangulation::extension, verbose);
	}

	auto getSurface(const Cad_Shape& sh)
	{
		auto faces = Cad_Tools::RetrieveFaces(sh.Shape());
		if (faces.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be one surface in the shape." << endl
				<< abort(FatalError);
		}
		return faces.at(0);
	}

	auto retrieveParaPolygon(const std::vector<std::shared_ptr<PtdShapeFit_ProjMeshToFace::Node3d>>& theNodes)
	{
		std::vector<Pnt2d> pnts;
		pnts.reserve(theNodes.size() - 1);
		for (size_t i = 0; i < theNodes.size() - 1; i++)
		{
			const auto& x = theNodes.at(i);
			auto pt = x->parNode->coord;
			pnts.push_back(std::move(pt));
		}
		/*for (const auto& x : theNodes)
		{
			auto pt = x->parNode->coord;
			pnts.push_back(std::move(pt));
		}*/
		auto poly = std::make_shared<Entity2d_Polygon>(std::move(pnts), 0);
		return std::move(poly);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		auto elements = GeoTop_Tools::CalcTopology(*myMesh);
		auto boundaries = GeoTop_Tools::CalcBoundaries(elements);
		if (boundaries.size() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to identify the boundary" << endl
				<< " - size : " << boundaries.size() << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl
				<< " - projecting the boundaries to the shape..." << endl;
		}

		auto projector = std::make_shared<PtdShapeFit_ProjMeshToFace>();
		projector->SetMesh(myMesh);
		projector->SetBoundary(boundaries.at(0));

		auto face = getSurface(*myShape);
		auto gFace = GModel_Tools::GetSurface(face);

		projector->SetFace(gFace->GeomSurface());

		projector->Perform();

		const auto& poly = projector->Projected();
		if (verbose)
		{
			Info << endl
				<< " - the boundaries have been projected." << endl;
		}

		auto polyFace = Cad_Tools::RetrieveTriangulation(face);
		auto paraMesh = Cad_Tools::ParaTriangulation(*polyFace);

		auto paraPoly = retrieveParaPolygon(poly);

		{
			struct meshNode
			{
				Pnt3d coord;

				meshNode(const Pnt3d p)
					: coord(p)
				{}

				typedef Pnt3d ptType;
			};

			std::vector<std::shared_ptr<meshNode>> nodes;
			auto& Pts = myMesh->Points();
			for (const auto& x : Pts)
			{
				auto p3 = std::make_shared<meshNode>(x);
				nodes.push_back(std::move(p3));
			}
			auto b = Entity3d_Box::BoundingBoxOf(Pts);

			Geo_AdTree<std::shared_ptr<meshNode>> tree;
			tree.SetGeometryRegion(b.Expanded(b.Diameter() * 1.0E-2));
			tree.SetGeometryCoordFunc([](const std::shared_ptr<meshNode>& n)-> const auto& {return n->coord; });
			//tree.InsertToGeometry(nodes);

			for (const auto& bPt : poly)
			{
				const auto& bpt2d = bPt->parNode->coord;
				auto prj_pt = gFace->Value(bpt2d);
				//std::vector<std::shared_ptr<meshNode>> items;
				//tree.GeometrySearch(Entity3d_Box::Box(bPt->coord, 1.0E-6), items);
				//std::cout << "size= " << items.size() << std::endl;
				//std::shared_ptr<meshNode> found;
				/*for (const auto& x : nodes)
				{
					if (x->coord.Distance(bPt->coord) <= 1.0E-8)
					{
						found = x;
						break;
					}
				}*/
				bool found = false;
				for (auto& x : myMesh->Points())
				{
					if (x.Distance(bPt->coord) <= 1.0E-8)
					{
						x = gFace->Value(bpt2d);
						found = true;
						break;
					}
				}
				if (NOT found)
				{
					std::cout<<"WARNING"<<std::endl;
					/*FatalErrorIn(FunctionSIG)
						<< "couldn't project the boundary" << endl
						<< abort(FatalError);*/
				}
				/*if (NOT found)
				{
					std::cout << bPt->coord << std::endl;
					for (const auto& xx : myMesh->Points())
					{
						if (xx.Distance(bPt->coord) <= 1.0E-8)
						{
							std::cout << "founded" << std::endl;
						}
					}
					FatalErrorIn(FunctionSIG)
						<< "couldn't project the boundary" << endl
						<< abort(FatalError);
				}
				found->coord = gFace->Value(bpt2d);*/
			}
			/*Pts.clear();
			for (const auto& x : nodes)
			{
				Pts.push_back(x->coord);
			}*/
		}
		//paraPoly->Reverse();

		{
			std::ofstream outputMesh;
			outputMesh.open("projected_mesh.obj");
			Geo_Tools::ExportAsOBJ_cgal(*myMesh, outputMesh);
		}

		{ // parametric plane io [2/19/2023 Payvand]
			

			OFstream myFile("para.plt");
			paraMesh->ExportToPlt(myFile);
			paraPoly->ExportToPlt(myFile);
		}
		
		auto slicer = std::make_shared<GeoSlicer2d_PolyLine>();
		slicer->SetMesh(paraMesh);
		slicer->SetPolyline(paraPoly);
		slicer->Perform();

		{
			OFstream myFile("slicer.plt");
			slicer->Clipped()->ExportToPlt(myFile);
		}

		auto tri3d = Cad_Tools::Triangulation(*gFace->GeomSurface()->Geometry(), *slicer->Clipped());
		/*{
			OFstream myFile("sliced3d.plt");
			tri3d->ExportToPlt(myFile);
		}*/
		{
			std::ofstream outputMesh;
			outputMesh.open("cylider.obj");
			Geo_Tools::ExportAsOBJ_cgal(*tri3d, outputMesh);
		}
		{
			std::ofstream outputMesh;
			outputMesh.open("plate.obj");
			Geo_Tools::ExportAsOBJ_cgal(*myMesh, outputMesh);
		}
		{
			auto faces = Cad_Tools::RetrieveFaces(myShape->Shape());
			auto poly = Cad_Tools::RetrieveTriangulation(faces.at(0));
			auto tri = Cad_Tools::Triangulation(*poly);
			std::ofstream outputMesh;
			outputMesh.open("intact_cylinder.obj");
			Geo_Tools::ExportAsOBJ_cgal(*tri, outputMesh);
		}
		tri3d->Add(*myMesh);

		//auto recon = Geo_Tools::PoissonSurfaceRecon_cgal(*tri3d);

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
		/*if (recon)
		{
			myMerged = std::move(recon);
		}*/
		//else
		//{
			myMerged = std::move(tri3d);
		//}
		
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		//mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");

		// operators [12/21/2021 Amir]
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

int main(int argc, char* argv[])
{
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to project a surface mesh to a surface." << endl
				<< " - subdirectories: mesh, shape" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute()" << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitProjectMeshToFace"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}