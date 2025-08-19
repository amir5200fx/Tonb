#include <Cad_gSingularity.hxx>
#include <Cad_SingularityHorizons.hxx>
#include <Cad_ApprxMetric.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Cad_GeomSurface.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Cad_GModel.hxx>
#include <Cad_Shape.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = Cad_Shape::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;

	static std::shared_ptr<Cad_Shape> myShape;

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

	auto retrieveGeometry(const std::shared_ptr<GModel_Surface>& surf)
	{
		const auto& cadGeom = surf->GeomSurface();
		auto geom = cadGeom->Geometry();
		auto b = surf->ParaBoundingBox();
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		auto surfaces = GModel_Tools::GetSurfaces(myShape->Shape());
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface is found!" << endl
				<< abort(FatalError);
		}

		for (const auto& surf : surfaces)
		{
			auto geom = GModel_Tools::RetrieveGeometry(*surf);
			auto apprxMetricAlg = std::make_shared<Cad_ApprxMetric>(geom, surf->ParaBoundingBox());
			apprxMetricAlg->Perform();

			auto tri = apprxMetricAlg->Triangulation();

			auto singularity = std::make_shared<Cad_gSingularity>();
			
		}
	}
}