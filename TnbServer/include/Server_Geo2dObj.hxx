#pragma once
#ifndef _Server_Geo2dObj_Header
#define _Server_Geo2dObj_Header

#include <Server_Object.hxx>
#include <Mesh2d_ReferenceValuesFwd.hxx>
#include <Global_Serialization.hxx>

#include <vector>

namespace tnbLib
{

	class Mesh2d_UniformBoundarySizeMapControl;
	class Mesh2d_UniformVolumetricSizeMapControl;
	class BoundarySizeMap2d_UniformSegmentTool_Info;
	class BoundarySizeMap2d_UniformSegmentTool;
	class Mesh2d_VolumeSizeMapTool_Info;
	class Mesh2d_VolumeSizeMapTool;
	class Mesh2d_BoundarySizeMapTool;
	class Mesh_Conditions;
	class Mesh_Values;
	class Mesh_SurfaceSizeValues;
	class Cad2d_Plane;

	class Server_Geo2dObj_ApproxCrv
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(approx);
			defineTnbServerParam(min_size);

			defineTnbServerParam(max_nb_subs);
			defineTnbServerParam(min_nb_subs);

			defineTnbServerParam(nb_samples);
		};

		static const std::string command_name;

		Server_Geo2dObj_ApproxCrv() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_SizeMap_BndControl
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(approx);
			defineTnbServerParam(unbalance);
			defineTnbServerParam(bucket_size);
			defineTnbServerParam(post_balance);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_BndControl);
	};

	class Server_Geo2dObj_SizeMap_VolControl
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(unbalance);
			defineTnbServerParam(bucket_size);
			defineTnbServerParam(nb_samples);
			defineTnbServerParam(post_balance);
			defineTnbServerParam(max_nb_iters);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_VolControl);
	};

	class Server_Geo2dObj_SizeMap_Uniform
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string bnd_box;
			static const std::string size;
		};

		static const std::string command_name;

		Server_Geo2dObj_SizeMap_Uniform() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_SizeMap_Adaptive
		: public Server_Object
	{
	public:
		struct IO
		{
			std::shared_ptr<Cad2d_Plane> model;
			std::vector<std::shared_ptr<Cad2d_Plane>> volumes;

			std::shared_ptr<Mesh2d_ReferenceValues> ref;

			std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info> bnd_settings;
			std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info> vol_settings;

			std::shared_ptr<Mesh2d_UniformBoundarySizeMapControl> bnd_control;
			std::shared_ptr<Mesh2d_UniformVolumetricSizeMapControl> vol_control;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		struct Params
		{
			defineTnbServerParam(ref);
			defineTnbServerParam(model);
			defineTnbServerParam(volumes);
			defineTnbServerParam(bnd_sizemap_settings);
			defineTnbServerParam(vol_sizemap_settings);
		};

		static const std::string command_name;

		Server_Geo2dObj_SizeMap_Adaptive() = default;

		void Construct(const std::string& theValue) override;
	};

	class Server_Geo2dObj_SizeMap_MakeBnd
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Adaptive adaptive;
		struct IO
		{
			std::shared_ptr<adaptive::IO> size_map;
			std::shared_ptr<Mesh2d_BoundarySizeMapTool> bnd;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		struct Params
		{
			defineTnbServerParam(name);
			defineTnbServerParam(size_map);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_MakeBnd);
	};

	class Server_Geo2dObj_SizeMap_MakeVol
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Adaptive adaptive;
		struct IO
		{
			std::shared_ptr<adaptive::IO> size_map;
			std::shared_ptr<Mesh2d_VolumeSizeMapTool> vol;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(volumes);
			defineTnbServerParam(name);
			defineTnbServerParam(target);
			defineTnbServerParam(growth_rate);
			defineTnbServerParam(value_type);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_MakeVol);
	};

	defineTnbServerObject(Server_Geo2dObj_SizeMap_Adapt_Perform);

	// Importing the geometries

	class Server_Geo2dObj_SizeMap_ImptPatch
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeBnd::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(name);
			defineTnbServerParam(size_map);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_ImptPatch);
	};

	class Server_Geo2dObj_SizeMap_ImptVol
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeVol::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(id);
			defineTnbServerParam(size_map);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_ImptVol);
	};

	// getting the conditions

	class Server_Geo2dObj_SizeMap_Bnd_GetCond
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeBnd::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_Conditions> conditions;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_GetCond);
	};

	class Server_Geo2dObj_SizeMap_Vol_GetCond
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeVol::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_Conditions> conditions;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetCond);
	};

	// getting the values

	class Server_Geo2dObj_SizeMap_Bnd_GetValues
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeBnd::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_Values> values;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_GetValues);
	};

	class Server_Geo2dObj_SizeMap_Vol_GetValues
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_MakeVol::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_Values> values;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetValues);
	};

	class Server_Geo2dObj_SizeMap_Bnd_ValuesGr
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetValues::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(rate);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_ValuesGr);
	};

	class Server_Geo2dObj_SizeMap_Vol_ValuesGr
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Vol_GetValues::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(rate);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_ValuesGr);
	};

	// getting the surface values

	class Server_Geo2dObj_SizeMap_Bnd_GetSurfSize
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetValues::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_SurfaceSizeValues> sizes;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_GetSurfSize);
	};

	class Server_Geo2dObj_SizeMap_Vol_GetSurfSize
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Vol_GetValues::IO sizeMap;
		struct IO
		{
			std::shared_ptr<sizeMap> size_map;
			std::shared_ptr<Mesh_SurfaceSizeValues> sizes;

			TNB_SERIALIZATION(TnbServer_EXPORT);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_GetSurfSize);
	};

	// Setting the value type

	class Server_Geo2dObj_SizeMap_Bnd_SetValueType
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetSurfSize::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(value_type);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_SetValueType);
	};

	class Server_Geo2dObj_SizeMap_Vol_SetValueType
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Vol_GetSurfSize::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(value_type);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_SetValueType);
	};

	// Setting the target size

	class Server_Geo2dObj_SizeMap_Bnd_SetTargetSize
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetSurfSize::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(value);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_SetTargetSize);
	};

	class Server_Geo2dObj_SizeMap_Vol_SetTargetSize
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Vol_GetSurfSize::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(value);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Vol_SetTargetSize);
	};

	//

	class Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomSize
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetCond::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(custom_cond);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomSize);
	};

	class Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomGrRate
		: public Server_Object
	{
	public:
		typedef Server_Geo2dObj_SizeMap_Bnd_GetCond::IO sizeMap;
		struct Params
		{
			defineTnbServerParam(size_map);
			defineTnbServerParam(custom_cond);
		};

		constructTnbServerObject(Server_Geo2dObj_SizeMap_Bnd_Conditions_SetCustomGrRate);
	};


	defineTnbServerObject(Server_Geo2dObj_ExportMeshToPlt);

}

#endif