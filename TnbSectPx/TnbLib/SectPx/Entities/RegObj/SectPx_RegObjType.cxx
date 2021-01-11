#include <SectPx_RegObjType.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static const word composite_profile_name = "composite profile";
	static const word controller_name = "controller";
	static const word cpts_map_name = "cpts map";
	static const word datum_name = "datum";
	static const word edge_name = "edge";
	static const word field_fun_name = "field function";
	static const word frame_name = "frame";
	static const word geo_map_name = "geometric map";
	static const word interface_name = "interface";
	static const word node_name = "node";
	static const word overrider_name = "overrider";
	static const word parameter_name = "parameter";
	static const word pnt_name = "pnt";
	static const word pole_name = "pole";
	static const word profile_name = "profile";
	static const word segment_name = "segment";
	static const word offset_profile_name = "offset profile";
	static const word cloud_name = "cloud";
	static const word shape_name = "shape";
	static const word topo_segment_name = "topo segment";
	static const word extrude_profile_name = "extrusion profile name";
	static const word curve_q_name = "curveQ";
	static const word limits_name = "limits";
}

tnbLib::word 
tnbLib::getRegObjTypeName(const SectPx_RegObjType t)
{
	switch (t)
	{
	case sectPxLib::regObjType::cmptProfile: return composite_profile_name;
	case sectPxLib::regObjType::controller: return controller_name;
	case sectPxLib::regObjType::cptsMap: return cpts_map_name;
	case sectPxLib::regObjType::datum: return datum_name;
	case sectPxLib::regObjType::edge: return edge_name;
	case sectPxLib::regObjType::fieldFun: return field_fun_name;
	case sectPxLib::regObjType::frame: return frame_name;
	case sectPxLib::regObjType::geoMap: return geo_map_name;
	case sectPxLib::regObjType::Interface: return interface_name;
	case sectPxLib::regObjType::node: return node_name;
	case sectPxLib::regObjType::overrider: return overrider_name;
	case sectPxLib::regObjType::parameter: return parameter_name;
	case sectPxLib::regObjType::pnt: return pnt_name;
	case sectPxLib::regObjType::pole: return pole_name;
	case sectPxLib::regObjType::profile: return profile_name;
	case sectPxLib::regObjType::segment: return segment_name;
	case sectPxLib::regObjType::offsetProfile: return offset_profile_name;
	case sectPxLib::regObjType::cloud: return cloud_name;
	case sectPxLib::regObjType::shape: return shape_name;
	case sectPxLib::regObjType::topoSegment: return topo_segment_name;
	case sectPxLib::regObjType::extrProfile: return extrude_profile_name;
	case sectPxLib::regObjType::curveQ: return curve_q_name;
	case sectPxLib::regObjType::limits: return limits_name;
	default:
		FatalErrorIn(FunctionSIG)
			<< "invalid type of the registry object!" << endl
			<< abort(FatalError);
		return "unknown";
		break;
	}
}