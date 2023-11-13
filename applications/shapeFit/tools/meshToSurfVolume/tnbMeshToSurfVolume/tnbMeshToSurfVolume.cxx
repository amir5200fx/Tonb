#include <Cad_GeomSurface.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Triangle.hxx>
#include <Pnt3d.hxx>
#include <Vec3d.hxx>
#include <Dir3d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GeomAPI_ProjectPointOnSurf.hxx>

namespace tnbLib
{

	static std::shared_ptr<Cad_GeomSurface> my_surface;
	static std::shared_ptr<Entity3d_Triangulation> myMesh;

	static double myUpperValue = 0;
	static double myLowerValue = 0;

	static auto myTol = 1.0E-6;

	static std::string surf_directory = "surface";
	static std::string mesh_directory = "mesh";

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_GLOBAL_PATH;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	void loadSurfaceModel()
	{
		std::string myFileName;
		my_surface =
			file::LoadSingleFile
			<std::shared_ptr<Cad_GeomSurface>>
			(surf_directory, Cad_GeomSurface::extension, verbose, myFileName);
		if (NOT my_surface)
		{
			FatalErrorIn(FunctionSIG)
				<< " the surface file is null." << endl
				<< abort(FatalError);
		}
	}

	void loadMesh()
	{
		std::string myFileName;
		myMesh = 
			file::LoadSingleFile
			<std::shared_ptr<Entity3d_Triangulation>>
			(mesh_directory, /*Entity3d_Triangulation::extension*/".tri3d", verbose, myFileName);
		if (NOT myMesh)
		{
			FatalErrorIn(FunctionSIG)
				<< " the mesh file is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (file::IsDirectory(surf_directory))
		{
			loadSurfaceModel();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " no {" << surf_directory << "} has been found." << endl
				<< abort(FatalError);
		}
		if (file::IsDirectory(mesh_directory))
		{
			loadMesh();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " no {" << mesh_directory << "} has been found." << endl
				<< abort(FatalError);
		}
	}

	enum class PointPosition
	{
		upper,
		lower
	};

	auto isUpper(PointPosition pos)
	{
		return pos == PointPosition::upper;
	}

	auto isLower(PointPosition pos)
	{
		return pos == PointPosition::lower;
	}

	auto CalcVolume(const std::vector<Pnt3d>& coords)
	{
		double tot_vol = 0;
		tot_vol += std::abs(Geo_Tools::Volume_cgal(coords.at(0), coords.at(1), coords.at(2), coords.at(3)));
		tot_vol += std::abs(Geo_Tools::Volume_cgal(coords.at(1), coords.at(2), coords.at(3), coords.at(4)));
		tot_vol += std::abs(Geo_Tools::Volume_cgal(coords.at(2), coords.at(3), coords.at(4), coords.at(5)));
		return tot_vol;
	}

	void CalcVolume(const Entity3d_Triangle& tri, const std::shared_ptr<Cad_GeomSurface>& surf)
	{
		const auto& p0 = tri.P0();
		const auto& p1 = tri.P1();
		const auto& p2 = tri.P2();

		const auto u0 = surf->FirstParameterU();
		const auto u1 = surf->LastParameterU();
		const auto v0 = surf->FirstParameterV();
		const auto v1 = surf->LastParameterV();

		Pnt2d uv0;
		Pnt3d pj0;

		Pnt2d uv1;
		Pnt3d pj1;

		Pnt2d uv2;
		Pnt3d pj2;

		double dis0, dis1, dis2;
		try
		{		
			{
				GeomAPI_ProjectPointOnSurf projObj;
				projObj.Init(p0, surf->Geometry(), u0, u1, v0, v1);
				projObj.Perform(p0);

				projObj.LowerDistanceParameters(uv0.X(), uv0.Y());
				pj0 = projObj.NearestPoint();
				dis0 = projObj.LowerDistance();
			}
		
			{
				GeomAPI_ProjectPointOnSurf projObj;
				projObj.Init(p1, surf->Geometry(), u0, u1, v0, v1);
				projObj.Perform(p1);

				projObj.LowerDistanceParameters(uv1.X(), uv1.Y());
				pj1 = projObj.NearestPoint();
				dis1 = projObj.LowerDistance();
			}
		
			{
				GeomAPI_ProjectPointOnSurf projObj;
				projObj.Init(p2, surf->Geometry(), u0, u1, v0, v1);
				projObj.Perform(p2);

				projObj.LowerDistanceParameters(uv2.X(), uv2.Y());
				pj2 = projObj.NearestPoint();
				dis2 = projObj.LowerDistance();
			}
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< " couldn't project the point: " << endl
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		auto uvm = (uv0 + uv1 + uv2) / 3.0;
		Vec3d ut, vt;
		Pnt3d Pm;
		surf->Geometry()->D1(uvm.X(), uvm.Y(), Pm, ut, vt);
		Dir3d normal = ut.Crossed(vt).XYZ();
		PointPosition pos0;
		if (dis0 > myTol)
		{
			Dir3d n0 = (p0 - pj0).XYZ();
			if (n0.Dot(normal) > 0) pos0 = PointPosition::upper;
			else pos0 = PointPosition::lower;
		}
		PointPosition pos1;
		if (dis1 > myTol)
		{
			Dir3d n1 = (p1 - pj1).XYZ();
			if (n1.Dot(normal) > 0) pos1 = PointPosition::upper;
			else pos1 = PointPosition::lower;
		}
		PointPosition pos2;
		if (dis2 > myTol)
		{
			Dir3d n2 = (p2 - pj2).XYZ();
			if (n2.Dot(normal) > 0) pos2 = PointPosition::upper;
			else pos2 = PointPosition::lower;
		}
		std::vector<Pnt3d> coords_3d;
		coords_3d.push_back(p0);
		coords_3d.push_back(p1);
		coords_3d.push_back(p2);
		coords_3d.push_back(pj0);
		coords_3d.push_back(pj1);
		coords_3d.push_back(pj2);
		std::vector<Pnt2d> pts_2d;
		pts_2d.push_back(std::move(uv0));
		pts_2d.push_back(std::move(uv1));
		pts_2d.push_back(std::move(uv2));
		if (isUpper(pos0) AND isUpper(pos1) AND isUpper(pos2))
		{
			
			if (Geo_Tools::IsCcwOrder(pts_2d))
			{		
				myUpperValue += CalcVolume(coords_3d);
			}
			else
			{
				myUpperValue -= CalcVolume(coords_3d);
			}
		}
		if (isLower(pos0) AND isLower(pos1) AND isLower(pos2))
		{
			if (Geo_Tools::IsCcwOrder(pts_2d))
			{
				myLowerValue += CalcVolume(coords_3d);
			}
			else
			{
				myLowerValue -= CalcVolume(coords_3d);
			}
		}
	}

	void execute()
	{
		const auto& pts = myMesh->Points();
		myUpperValue = 0;
		myLowerValue = 0;
		for (const auto& x : myMesh->Connectivity())
		{
			auto i0 = x.Value(0);
			auto i1 = x.Value(1);
			auto i2 = x.Value(2);

			const auto& p0 = pts.at(Index_Of(i0));
			const auto& p1 = pts.at(Index_Of(i1));
			const auto& p2 = pts.at(Index_Of(i2));

			Entity3d_Triangle t(p0, p1, p2);
			CalcVolume(t, my_surface);
		}

		std::cout << " - The Lower Volume: " << myLowerValue << std::endl;
		std::cout << " - The Upper volume: " << myUpperValue << std::endl;
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
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");

		// operators [8/28/2023 aamir]
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
			Info << " This application is aimed to calculate the volume between a mesh and a surface." << endl
				<< " - Subdirectories: 'surface' and 'mesh'." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute" << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshToSurfVolume"));
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