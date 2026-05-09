#pragma once
#ifndef _frameMakerFwd_Header
#define _frameMakerFwd_Header

#include <SectPx_ParsFwd.hxx>
#include <SectPx_MakersFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;
	class SectPx_Frame;
	class SectPx_Coord;
	class SectPx_Pnt;
	class SectPx_MasterPnt;
	class SectPx_Cloud;

	class SectPx_FieldFun;
	class SectPx_GeoMap;
	class SectPx_TopoProfile;

	class SectPx_RegObj;
	class SectPx_Edge;

	class SectPx_Datum;

	namespace sectPxLib
	{

		class FieldFun_Expr;
	}

	namespace appl
	{

		typedef std::shared_ptr<SectPx_Registry> registry_t;
		typedef std::shared_ptr<SectPx_Frame> frame_t;
		typedef std::shared_ptr<SectPx_TopoProfile> profile_t;

		typedef std::shared_ptr<SectPx_Par> par_t;
		typedef std::shared_ptr<SectPx_FixedPar> fixed_t;
		typedef std::shared_ptr<SectPx_FreePar> free_t;
		typedef std::shared_ptr<SectPx_ConstPar> const_t;

		typedef std::shared_ptr<SectPx_Coord> coord_t;
		typedef std::shared_ptr<SectPx_Pnt> pnt_t;
		typedef std::shared_ptr<SectPx_Datum> dtm_t;
		typedef std::shared_ptr<SectPx_MasterPnt> mastPnt_t;
		typedef std::shared_ptr<SectPx_Cloud> cloud_t;

		typedef std::shared_ptr<SectPx_FieldFun> fieldFun_t;
		typedef std::shared_ptr<sectPxLib::FieldFun_Expr> exprField_t;
		typedef std::shared_ptr<SectPx_GeoMap> geoMap_t;

		typedef std::shared_ptr<SectPx_Edge> edge_t;
		typedef std::shared_ptr<SectPx_RegObj> regObj_t;


		//- makers 
		typedef std::shared_ptr<maker::Parameter> parMaker_t;
		typedef std::shared_ptr<maker::FieldFun> fieldMaker_t;
		typedef std::shared_ptr<maker::Point> pntMaker_t;
		typedef std::shared_ptr<maker::Datum> dtmMaker_t;
		typedef std::shared_ptr<maker::GeometricMap> geoMaker_t;
		typedef std::shared_ptr<maker::CmptProfile> cmpPrfMaker_t;
		typedef std::shared_ptr<maker::Profile> profileMaker_t;
	}
}

#endif // !_frameMakerFwd_Header
