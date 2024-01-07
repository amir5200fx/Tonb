#include <Server_Geo2dObj.hxx>

#include <Mesh2d_UniformBoundarySizeMapControl.hxx>
#include <Mesh2d_UniformVolumetricSizeMapControl.hxx>
#include <BoundarySizeMap2d_UniformSegmentTool.hxx>
#include <Mesh2d_VolumeSizeMapTool.hxx>
#include <Mesh2d_VolumeSizeMapTool_Info.hxx>
#include <Mesh2d_BoundarySizeMapTool.hxx>
#include <Mesh2d_SizeMapShape.hxx>
#include <Mesh2d_SizeMapPolygon.hxx>
#include <Mesh_SizeMethodInfo.hxx>
#include <Mesh_VariationRateInfo.hxx>
#include <Mesh2d_ReferenceValues.hxx>
#include <Geo2d_SegmentCloud_SamplesLev1.hxx>
#include <Geo2d_SegmentCloud_SamplesLev0.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo_BasicApprxCurve_Info.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>

#include <json.hpp>

#include <Geo_BasicApprxCurve_Info.hxx>

namespace tnbLib
{
	auto switch_to_variation_rate_type(const std::string name)
	{
		if (name == "custom")
		{
			return Mesh_VariationRateInfo::custom;
		}
		else if (name == "very_slow")
		{
			return Mesh_VariationRateInfo::verySlow;
		}
		else if (name == "slow")
		{
			return Mesh_VariationRateInfo::slow;
		}
		else if (name == "moderate")
		{
			return Mesh_VariationRateInfo::moderate;
		}
		else if (name == "fast")
		{
			return Mesh_VariationRateInfo::fast;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of growth rate has been detected." << endl
				<< " - valid types: 'custom', 'verySlow', 'slow', 'moderate', and 'fast'" << endl
				<< " - selected type: " << name << endl
				<< abort(FatalError);
			return Mesh_VariationRateInfo::custom;
		}
	}
}

#include <Mesh_RelativeAbsoluteInfo.hxx>

namespace tnbLib
{
	auto switch_to_value_type(const std::string name)
	{
		if (name == "relative")
		{
			return Mesh_RelativeAbsoluteInfo::relativeToBase;
		}
		else if (name == "absolute")
		{
			return Mesh_RelativeAbsoluteInfo::absolute;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of value has been detected." << endl
				<< " - valid types: 'relative', and 'absolute'" << endl
				<< " - selected type: " << name << endl
				<< abort(FatalError);
			return Mesh_RelativeAbsoluteInfo::relativeToBase;
		}
	}
}

implementTnbServerParam(Server_Geo2dObj_ApproxCrv, approx, "approx");
implementTnbServerParam(Server_Geo2dObj_ApproxCrv, min_size, "min_size");
implementTnbServerParam(Server_Geo2dObj_ApproxCrv, max_nb_subs, "max_nb_subs");
implementTnbServerParam(Server_Geo2dObj_ApproxCrv, min_nb_subs, "min_nb_subs");
implementTnbServerParam(Server_Geo2dObj_ApproxCrv, nb_samples, "nb_samples");

void tnbLib::Server_Geo2dObj_ApproxCrv::Construct(const std::string& theValue)
{
	double approx;
	double min_size;
	int max_nb_subs;
	int min_nb_subs;
	int nb_samples;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(approx);
		}
		{
			loadTnbServerObject(min_size);
		}
		{
			loadTnbServerObject(max_nb_subs);
		}
		{
			loadTnbServerObject(min_nb_subs);
		}
		{
			loadTnbServerObject(nb_samples);
		}
	}
	auto value = std::make_shared<Geo_BasicApprxCurve_Info>();
	value->SetMinSize(min_size);
	value->SetApprox(approx);
	value->SetInitNbSubdivision(min_nb_subs);
	value->SetMaxNbSubdivision(max_nb_subs);
	value->SetNbSamples(nb_samples);
	streamGoodTnbServerObject(value);
}

#include <BoundarySizeMap2d_UniformSegmentTool_Info.hxx>

implementTnbServerParam(Server_Geo2dObj_SizeMap_BndControl, approx, "approx");
implementTnbServerParam(Server_Geo2dObj_SizeMap_BndControl, unbalance, "unbalance");
implementTnbServerParam(Server_Geo2dObj_SizeMap_BndControl, bucket_size, "bucket_size");
implementTnbServerParam(Server_Geo2dObj_SizeMap_BndControl, post_balance, "post_balance");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_BndControl)
{
	std::shared_ptr<Geo_BasicApprxCurve_Info> approx;
	int unbalance;
	int bucket_size;
	bool post_balance;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(approx);
		}
		{
			loadTnbServerObject(unbalance);
		}
		{
			loadTnbServerObject(bucket_size);
		}
		{
			loadTnbServerObject(post_balance);
		}
	}
	try
	{
		if (!approx)
		{
			throw Server_Error("the approximation object is null.");
		}
		auto value = std::make_shared<BoundarySizeMap2d_UniformSegmentTool_Info>();
		value->SetApproxInfo(approx);
		value->SetBucketSize(bucket_size);
		value->SetPostBalance(post_balance);
		value->SetUnBalancing(unbalance);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()

}

#include <Mesh2d_VolumeSizeMapTool_Info.hxx>

implementTnbServerParam(Server_Geo2dObj_SizeMap_VolControl, unbalance, "unbalance");
implementTnbServerParam(Server_Geo2dObj_SizeMap_VolControl, bucket_size, "bucket_size");
implementTnbServerParam(Server_Geo2dObj_SizeMap_VolControl, nb_samples, "nb_samples");
implementTnbServerParam(Server_Geo2dObj_SizeMap_VolControl, post_balance, "post_balance");
implementTnbServerParam(Server_Geo2dObj_SizeMap_VolControl, max_nb_iters, "max_nb_iters");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_VolControl)
{
	int unbalance;
	int bucket_size;
	int nb_samples;
	bool post_balance;
	int max_nb_iters;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(unbalance);
		}
		{
			loadTnbServerObject(bucket_size);
		}
		{
			loadTnbServerObject(nb_samples);
		}
		{
			loadTnbServerObject(post_balance);
		}
		{
			loadTnbServerObject(max_nb_iters);
		}
	}
	try
	{
		auto value = std::make_shared<Mesh2d_VolumeSizeMapTool_Info>();
		value->SetUnbalancing(unbalance);
		value->SetBucketSize(bucket_size);
		value->SetNbSamples(nb_samples);
		value->SetPostBalance(post_balance);
		value->SetMaxNbCorrIters(max_nb_iters);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Geo2dObj_SizeMap_Uniform::Params::size("size");
const std::string tnbLib::Server_Geo2dObj_SizeMap_Uniform::Params::bnd_box("domain");

void tnbLib::Server_Geo2dObj_SizeMap_Uniform::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> bnd_box;
	double size;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(bnd_box);
		}
		{
			loadTnbServerObject(size);
		}
	}
	try
	{
		if (!bnd_box)
		{
			throw Server_Error("the bounding box object is null");
		}
		if (size <= gp::Resolution())
		{
			throw Server_Error("invalid value for a size function: " + std::to_string(size));
		}
		std::shared_ptr<Geo2d_SizeFunction> value = 
			std::make_shared<GeoSizeFun2d_Uniform>(size, *bnd_box);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

#include <Mesh2d_ReferenceValues.hxx>
#include <Mesh2d_UniformBoundarySizeMapControl.hxx>
#include <Mesh2d_UniformVolumetricSizeMapControl.hxx>
#include <Cad2d_Plane.hxx>
#include <Geo2d_SegmentCloud.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Adaptive::IO)
{
	ar& model;
	ar& volumes;
	ar& ref;
	ar& bnd_control;
	ar& vol_control;

	ar& bnd_settings;
	ar& vol_settings;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Adaptive::IO)
{
	ar& model;
	ar& volumes;

	ar& ref;

	ar& bnd_control;
	ar& vol_control;

	ar& bnd_settings;
	ar& vol_settings;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Volume_F1)
{
	std::shared_ptr<Cad2d_Plane> shape;
	{
		loadNonJSONTnbServer(shape);
	}
	try
	{
		auto value = std::make_shared<Mesh2d_SizeMapShape>(shape);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Volume_F2)
{
	std::shared_ptr<Entity2d_Polygon> shape;
	{
		loadNonJSONTnbServer(shape);
	}
	try
	{
		auto value = std::make_shared<Mesh2d_SizeMapPolygon>(shape);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Adaptive, ref, "ref");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Adaptive, model, "model");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Adaptive, volumes, "volumes");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Adaptive, bnd_sizemap_settings, "bnd_sizemap_settings");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Adaptive, vol_sizemap_settings, "vol_sizemap_settings");

namespace tnbLib
{
	auto calc_bounding_box(const std::shared_ptr<Mesh2d_ReferenceValues>& ref, const std::vector<std::shared_ptr<Mesh2d_SizeMapVolume>>& volumes)
	{
		auto b = *ref->Region();
		for (const auto& x:volumes)
		{
			b = Geo_BoxTools::Union(b, x->CalcBoundingBox());
		}
		auto reg = std::make_shared<Entity2d_Box>(b.Expanded(b.Diameter() * 0.25));
		return std::move(reg);
	}
}

void tnbLib::Server_Geo2dObj_SizeMap_Adaptive::Construct(const std::string& theValue)
{
	std::shared_ptr<Mesh2d_ReferenceValues> ref;
	std::shared_ptr<Cad2d_Plane> model;
	std::vector<std::shared_ptr<Mesh2d_SizeMapVolume>> volumes;
	std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info> bnd_sizemap_settings;
	std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info> vol_sizemap_settings;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(ref);
		}
		{
			loadTnbServerObject(model);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::volumes).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element: json_array)
				{
					std::shared_ptr<Cad2d_Plane> area;
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> area;
					auto vol = std::make_shared<Mesh2d_SizeMapShape>(area);
					volumes.emplace_back(std::move(vol));
				}
			}
			else
			{
				throw Server_Error("Couldn't load the volume list");
			}
		}
		{
			loadTnbServerObject(bnd_sizemap_settings);
		}
		{
			loadTnbServerObject(vol_sizemap_settings);
		}
	}
	try
	{
		if (!ref)
		{
			throw Server_Error("the ref. object is null.");
		}
		int k = 0;
		for (const auto& x: volumes)
		{
			x->SetIndex(++k);
		}
		auto domain = calc_bounding_box(ref, volumes);
		auto value = std::make_shared<IO>();
		value->model = model;
		value->volumes = std::move(volumes);
		value->ref = ref;
		value->bnd_settings = std::move(bnd_sizemap_settings);
		value->vol_settings = std::move(vol_sizemap_settings);
		{
			auto control = std::make_shared<Mesh2d_UniformBoundarySizeMapControl>(ref, domain, nullptr);
			value->bnd_control = std::move(control);
		}
		{
			auto control = std::make_shared<Mesh2d_UniformVolumetricSizeMapControl>(ref, domain, nullptr);
			value->vol_control = std::move(control);
		}
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_MakeBnd::IO)
{
	ar& size_map;
	ar& bnd;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_MakeBnd::IO)
{
	ar& size_map;
	ar& bnd;
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, patches, "patches");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, name, "name");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, target, "target");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, growth_rate, "growth_rate");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeBnd, value_type, "value_type");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_MakeBnd)
{
	std::string name;
	std::vector<std::string> patches;
	double target;
	std::string value_type;
	std::string growth_rate;
	std::shared_ptr<Server_Geo2dObj_SizeMap_Adaptive::IO> size_map;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerString(name);
		}
		{
			loadTnbServerObject(size_map);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::patches).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element : json_array) {
					patches.emplace_back(element.get<std::string>());
					/*int id;
					std::stringstream stream;
					std::cout << element.get<std::string>() << std::endl;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> id;
					volumes.emplace_back(id);*/
				}
			}
			else
			{
				throw Server_Error("Couldn't load the volume list");
			}
		}
		{
			loadTnbServerObject(target);
		}
		{
			loadTnbServerString(growth_rate);
		}
		{
			loadTnbServerString(value_type);
		}
	}
	try
	{
		if (!size_map)
		{
			throw Server_Error("the adaptive size map object is null");
		}
		auto model = size_map->model;
		auto controler = size_map->bnd_control;
		auto info = size_map->bnd_settings;
		controler->CreateSizeMap(name, model, info);
		auto bnd = controler->SelectMap(name);
		for (const auto& x: patches)
		{
			bnd->ImportPatch(x);
		}
		bnd->MeshConditions()->SetCustomBoundaryGrowthRate(true);
		bnd->MeshConditions()->SetCustomSurfaceSize(true);

		bnd->MeshValues()->SurfaceSize()->SetMinSize(target);
		bnd->MeshValues()->SurfaceSize()->SetTargetSize(target);
		bnd->MeshValues()->SurfaceSize()->SetRelativeAbsolute(switch_to_value_type(value_type));
		bnd->MeshValues()->SurfaceSize()->SetSizeMethod(Mesh_SizeMethodInfo::minAndTerget);

		bnd->MeshValues()->SetBoundaryGrowthRate(switch_to_variation_rate_type(growth_rate));
		try
		{
			streamGoodTnbServerObject(size_map);
		}
		catch (std::exception& x)
		{
			std::cout << x.what() << std::endl;
		}
	}
	catchTnbServerErrors()
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_MakeVol::IO)
{
	ar& size_map;
	ar& vol;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_MakeVol::IO)
{
	ar& size_map;
	ar& vol;
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, volumes, "volumes");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, name, "name");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, target, "target");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, growth_rate, "growth_rate");
implementTnbServerParam(Server_Geo2dObj_SizeMap_MakeVol, value_type, "value_type");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_MakeVol)
{
	std::shared_ptr<Server_Geo2dObj_SizeMap_Adaptive::IO> size_map;
	std::vector<int> volumes;
	std::string name;
	double target;
	std::string growth_rate;
	std::string value_type;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerString(name);
		}
		{
			loadTnbServerObject(size_map);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::volumes).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element : json_array) {
					volumes.emplace_back(element.get<int>());
					/*int id;
					std::stringstream stream;
					std::cout << element.get<std::string>() << std::endl;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> id;
					volumes.emplace_back(id);*/
				}
			}
			else
			{
				throw Server_Error("Couldn't load the volume list");
			}
		}
		{
			loadTnbServerObject(target);
		}
		{
			loadTnbServerString(growth_rate);
		}
		{
			loadTnbServerString(value_type);
		}
	}
	try
	{
		if (!size_map)
		{
			throw Server_Error("the adaptive size map object is null");
		}
		if (volumes.empty())
		{
			throw Server_Error("the volume list is empty");
		}
		auto vol_0 = volumes.at(0);
		if (NOT INSIDE(vol_0, 0, size_map->volumes.size()))
		{
			std::stringstream MSG;
			MSG << "the index exceeds the size of the volume list!\n"
				<< " - nb. of the volumes: " << size_map->volumes.size() << "\n"
				<< " - index: " << vol_0 << "\n";
			throw Server_Error(MSG.str());
		}
		auto model = size_map->model;
		auto controler = size_map->vol_control;
		controler->CreateSizeMap(name, model, size_map->vol_settings);
		auto vol = controler->SelectMap(name);
		for (size_t i = 0; i < volumes.size(); i++)
		{
			vol->ImportVolume(size_map->volumes.at(volumes.at(i))->Index(), size_map->volumes.at(volumes.at(i)));
		}
		vol->MeshConditions()->SetCustomBoundaryGrowthRate(true);
		vol->MeshConditions()->SetCustomSurfaceSize(true);

		vol->MeshValues()->SurfaceSize()->SetMinSize(target);
		vol->MeshValues()->SurfaceSize()->SetTargetSize(target);
		vol->MeshValues()->SurfaceSize()->SetRelativeAbsolute(switch_to_value_type(value_type));
		vol->MeshValues()->SurfaceSize()->SetSizeMethod(Mesh_SizeMethodInfo::minAndTerget);

		vol->MeshValues()->SetBoundaryGrowthRate(switch_to_variation_rate_type(growth_rate));
		/*auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->vol = vol;*/
		try
		{
			streamGoodTnbServerObject(size_map);
		}
		catch (std::exception& x)
		{
			std::cout << x.what() << std::endl;
		}
	}
	catchTnbServerErrors()
}

#include <Mesh2d_MultiSizeMap.hxx>
#include <GeoSizeFun2d_Background.hxx>

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Adapt_Perform)
{
	std::shared_ptr<Server_Geo2dObj_SizeMap_Adaptive::IO> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		Mesh2d_VolumeSizeMapTool::verbose = 1;
		if (!size_map)
		{
			throw Server_Error("the adaptive size map object is null");
		}
		const auto& ref = size_map->ref;
		auto domain = std::make_shared<Entity2d_Box>(ref->Region()->Expanded(ref->Region()->Diameter() * 0.25));
		if (size_map->vol_control->NbMaps())
		{
			size_map->vol_control->Perform();
		}
		if (size_map->bnd_control->NbMaps())
		{
			size_map->bnd_control->Perform();
		}
		std::vector<std::shared_ptr<GeoMesh2d_Background>> backs;
		if (size_map->bnd_control->NbMaps())
		{
			backs.emplace_back(size_map->bnd_control->BackgroundMesh());
		}
		if (size_map->vol_control->NbMaps())
		{
			backs.emplace_back(size_map->vol_control->BackgroundMesh());
		}
		if (backs.empty())
		{
			throw Server_Error("no size map has been created.");
		}
		auto d = *domain;
		auto background = std::make_shared<Mesh2d_MultiSizeMap>(backs);
		background->SetBoundingBox(*domain);

		std::shared_ptr<Geo2d_SizeFunction> value =
			std::make_shared<GeoSizeFun2d_Background>
			(0, "", std::move(d), std::move(background));
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_ImptPatch, name, "name");
implementTnbServerParam(Server_Geo2dObj_SizeMap_ImptPatch, size_map, "size_map");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_ImptPatch)
{
	std::shared_ptr<sizeMap> size_map;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadNonJSONTnbServer(name);
		}
	}
	try
	{
		auto bnd = size_map->bnd;
		bnd->ImportPatch(name);
	}
	catchTnbServerErrors()
	
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_ImptVol, id, "id");
implementTnbServerParam(Server_Geo2dObj_SizeMap_ImptVol, size_map, "size_map");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_ImptVol)
{
	std::shared_ptr<sizeMap> size_map;
	int id;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(id);
		}
		{
			loadTnbServerObject(size_map);
		}
	}
	try
	{
		const auto& vols = size_map->size_map->volumes;
		if (NOT INSIDE(id, 0, vols.size()))
		{
			throw Server_Error("Bad index: Exceeds the boundary");
		}
		size_map->vol->ImportVolume(id + 1, vols.at(id));
	}
	catchTnbServerErrors()
}

// getting the conditions

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetCond::IO)
{
	ar& size_map;
	ar& conditions;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetCond::IO)
{
	ar& size_map;
	ar& conditions;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_GetCond)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->conditions = size_map->bnd->MeshConditions();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetCond::IO)
{
	ar& size_map;
	ar& conditions;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetCond::IO)
{
	ar& size_map;
	ar& conditions;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_GetCond)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->conditions = size_map->vol->MeshConditions();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

// getting the values

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetValues::IO)
{
	ar& size_map;
	ar& values;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetValues::IO)
{
	ar& size_map;
	ar& values;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_GetValues)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->values = size_map->bnd->MeshValues();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetValues::IO)
{
	ar& size_map;
	ar& values;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetValues::IO)
{
	ar& size_map;
	ar& values;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_GetValues)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->values = size_map->vol->MeshValues();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}


implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_ValuesGr, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_ValuesGr, rate, "rate");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_ValuesGr)
{
	std::shared_ptr<sizeMap> size_map;
	std::string rate;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerString(rate);
		}
	}
	try
	{
		size_map->values->SetBoundaryGrowthRate(switch_to_variation_rate_type(rate));
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_ValuesGr, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_ValuesGr, rate, "rate");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_ValuesGr)
{
	std::shared_ptr<sizeMap> size_map;
	std::string rate;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerString(rate);
		}
	}
	try
	{
		size_map->values->SetBoundaryGrowthRate(switch_to_variation_rate_type(rate));
	}
	catchTnbServerErrors()
}

// getting the surface values

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetSurfSize::IO)
{
	ar& size_map;
	ar& sizes;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Bnd_GetSurfSize::IO)
{
	ar& size_map;
	ar& sizes;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_GetSurfSize)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->sizes = size_map->values->SurfaceSize();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetSurfSize::IO)
{
	ar& size_map;
	ar& sizes;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Server_Geo2dObj_SizeMap_Vol_GetSurfSize::IO)
{
	ar& size_map;
	ar& sizes;
}

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_GetSurfSize)
{
	std::shared_ptr<sizeMap> size_map;
	{
		loadNonJSONTnbServer(size_map);
	}
	try
	{
		auto value = std::make_shared<IO>();
		value->size_map = size_map;
		value->sizes = size_map->values->SurfaceSize();
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_SetValueType, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_SetValueType, value_type, "value_type");


implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_SetValueType)
{
	std::shared_ptr<sizeMap> size_map;
	std::string value_type;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerString(value_type);
		}
	}
	try
	{
		size_map->sizes->SetRelativeAbsolute(switch_to_value_type(value_type));
		streamGoodTnbServerObject(size_map);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_SetValueType, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_SetValueType, value_type, "value_type");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_SetValueType)
{
	std::shared_ptr<sizeMap> size_map;
	std::string value_type;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerString(value_type);
		}
	}
	try
	{
		size_map->sizes->SetRelativeAbsolute(switch_to_value_type(value_type));
		streamGoodTnbServerObject(size_map);
	}
	catchTnbServerErrors()
}

// Setting the targets

implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_SetTargetSize, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_SetTargetSize, value, "value");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_SetTargetSize)
{
	std::shared_ptr<sizeMap> size_map;
	double value;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerObject(value);
		}
	}
	try
	{
		size_map->sizes->SetTargetSize(value);
		streamGoodTnbServerObject(size_map);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_SetTargetSize, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Vol_SetTargetSize, value, "value");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Vol_SetTargetSize)
{
	std::shared_ptr<sizeMap> size_map;
	double value;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerObject(value);
		}
	}
	try
	{
		size_map->sizes->SetTargetSize(value);
		streamGoodTnbServerObject(size_map);
	}
	catchTnbServerErrors()
}

//

implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomSize, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomSize, custom_cond, "custom_cond");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomSize)
{
	std::shared_ptr<sizeMap> size_map;
	bool custom_cond;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerObject(custom_cond);
		}
	}
	try
	{
		size_map->conditions->SetCustomSurfaceSize(custom_cond);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomGrRate, size_map, "size_map");
implementTnbServerParam(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomGrRate, custom_cond, "custom_cond");

implementTnbServerConstruction(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomGrRate)
{
	std::shared_ptr<sizeMap> size_map;
	bool custom_cond;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(size_map);
		}
		{
			loadTnbServerObject(custom_cond);
		}
	}
	try
	{
		size_map->conditions->SetCustomBoundaryGrowthRate(custom_cond);
	}
	catchTnbServerErrors()
}

#include <Entity2d_Triangulation.hxx>

void tnbLib::Server_Geo2dObj_ExportMeshToPlt::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Triangulation> tri;
	{
		loadNonJSONTnbServer(tri);
	}
	try
	{
		std::stringstream value;
		tri->StreamToPlt(value);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = value.str();
		theStream_ << jData;
	}
	catchTnbServerErrors()
}
