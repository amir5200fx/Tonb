#pragma once
#ifndef _frameMaker_Header
#define _frameMaker_Header

#include <Dir2d.hxx>
#include <Pnt2d.hxx>
#include <SectPx_ParsFwd.hxx>
#include <SectPx_MakersFwd.hxx>

#include "frameMakerFwd.hxx"
#include "frameMaker_Module.hxx"

#include <memory>

namespace chaiscript
{
	class Module;
}

namespace tnbLib
{

	// Forward Declarations

	namespace appl
	{

		//TnbFrameMaker_EXPORT extern registry_t myRegistry;

		//TnbFrameMaker_EXPORT const registry_t& getRegistry();

		TnbFrameMaker_EXPORT Pnt2d createGeoPoint(double x, double y);

		TnbFrameMaker_EXPORT par_t getPar(const fixed_t&);
		TnbFrameMaker_EXPORT par_t getPar(const free_t&);
		TnbFrameMaker_EXPORT par_t getPar(const const_t&);
		TnbFrameMaker_EXPORT par_t getPar(const par_t&);

		TnbFrameMaker_EXPORT fixed_t getFixedPar(const par_t& p);
		TnbFrameMaker_EXPORT free_t getFreePar(const par_t& p);
		TnbFrameMaker_EXPORT const_t getConstPar(const par_t& p);

		TnbFrameMaker_EXPORT coord_t getCoord(const dtm_t& p);
		TnbFrameMaker_EXPORT coord_t getCoord(const pnt_t& p);
		TnbFrameMaker_EXPORT coord_t getCoord(const coord_t& p);

		TnbFrameMaker_EXPORT fieldFun_t getFieldFun(const exprField_t& f);
		TnbFrameMaker_EXPORT fieldFun_t getFieldFun(const fieldFun_t& f);
		TnbFrameMaker_EXPORT exprField_t getExprField(const fieldFun_t& f);

		TnbFrameMaker_EXPORT mastPnt_t getMaster(const pnt_t& p);

		TnbFrameMaker_EXPORT void printObj(const regObj_t& t);
		TnbFrameMaker_EXPORT void printValue(const par_t& t);
		TnbFrameMaker_EXPORT void printValue(const coord_t& t);
		TnbFrameMaker_EXPORT void printValue(const fieldFun_t& t);
		TnbFrameMaker_EXPORT void print(const par_t& t);
		TnbFrameMaker_EXPORT void print(const fieldFun_t& t);
		TnbFrameMaker_EXPORT void print(const pnt_t& pt);
		TnbFrameMaker_EXPORT void printFrame(const frame_t& f);
		TnbFrameMaker_EXPORT void print(const frame_t& f);

		
		//- makers 

		TnbFrameMaker_EXPORT const parMaker_t& getParameterMaker(const frame_t& f);
		TnbFrameMaker_EXPORT const pntMaker_t& getPointMaker(const frame_t& f);
		TnbFrameMaker_EXPORT const dtmMaker_t& getDatumMaker(const frame_t& f);
		TnbFrameMaker_EXPORT const geoMaker_t& getGeometricMapMaker(const frame_t& f);
		TnbFrameMaker_EXPORT const cmpPrfMaker_t& getCmpProfileMaker(const frame_t& f);
		TnbFrameMaker_EXPORT const fieldMaker_t& getFieldMaker(const frame_t& f);


		TnbFrameMaker_EXPORT int nbProfiles(const frame_t& f);
		TnbFrameMaker_EXPORT int nbEdges(const registry_t&);
		TnbFrameMaker_EXPORT profile_t getProfile(const registry_t&, const frame_t& f, int);
		TnbFrameMaker_EXPORT edge_t getEdge(const registry_t&, int);
		TnbFrameMaker_EXPORT const std::map<Standard_Integer, std::weak_ptr<SectPx_RegObj>>&
			getProfiles(const registry_t&);

		TnbFrameMaker_EXPORT void drawPlt(const registry_t&, const std::string&);
		TnbFrameMaker_EXPORT void saveTo(const std::string&, const frame_t& f);
		TnbFrameMaker_EXPORT void loadFrom(const std::string&, frame_t& f);


		// - default shapes
		TnbFrameMaker_EXPORT void makeSegment(const frame_t& f, const Pnt2d& p0, const Pnt2d& p1);
		TnbFrameMaker_EXPORT void makeCorner(const frame_t& f, const Pnt2d& p0, const Pnt2d& p1);
		TnbFrameMaker_EXPORT void makeCorner
		(
			const frame_t& f,
			const Pnt2d& p0,
			const Dir2d& d0,
			double ang0,
			const Pnt2d& p1,
			const Dir2d& d1,
			double ang1
		);
		TnbFrameMaker_EXPORT void makeUShape(const frame_t& f, const Pnt2d& p0, const Pnt2d& p1, double w);

		// - create the profiles
		TnbFrameMaker_EXPORT profileMaker_t createCustomProfile(const cmpPrfMaker_t& m, const pnt_t& p0, const pnt_t& p1);
		TnbFrameMaker_EXPORT profileMaker_t createInterplProfile(const cmpPrfMaker_t& m, const cloud_t& c);

		// - modify a profile
		TnbFrameMaker_EXPORT edge_t selectEdge(const profileMaker_t& m, int id);
		TnbFrameMaker_EXPORT std::pair<edge_t, edge_t> importPnt(const profileMaker_t& m, const pnt_t& p, const edge_t& ed);
		TnbFrameMaker_EXPORT edge_t retrieveLeftEdge(const std::pair<edge_t, edge_t>& p);
		TnbFrameMaker_EXPORT edge_t retrieveRightEdge(const std::pair<edge_t, edge_t>& p);

		TnbFrameMaker_EXPORT void removePnt(const profileMaker_t& m, const pnt_t& p);

		//- parameters: 
		TnbFrameMaker_EXPORT par_t createFree(const parMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT par_t createFree(const parMaker_t& m, const word& name, const fieldFun_t& f);
		TnbFrameMaker_EXPORT par_t createFixed(const parMaker_t& m, double x, double xmin, double xmax);
		TnbFrameMaker_EXPORT par_t createFixed(const parMaker_t& m, const word& name, double x, double xmin, double xmax);
		TnbFrameMaker_EXPORT par_t createConstant(const parMaker_t& m, double x);
		TnbFrameMaker_EXPORT par_t createConstant(const parMaker_t& m, const word& name, double x);

		TnbFrameMaker_EXPORT void removePar(const parMaker_t& m, const par_t& p);

		TnbFrameMaker_EXPORT fieldFun_t createUniform(const fieldMaker_t& m, const par_t& p);
		TnbFrameMaker_EXPORT fieldFun_t createMinus(const fieldMaker_t& m, const par_t& p);
		TnbFrameMaker_EXPORT fieldFun_t createRead_x(const fieldMaker_t& m, const coord_t& pt);
		TnbFrameMaker_EXPORT fieldFun_t createRead_y(const fieldMaker_t& m, const coord_t& pt);
		TnbFrameMaker_EXPORT fieldFun_t createLinearForm(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1, const par_t& t);
		TnbFrameMaker_EXPORT fieldFun_t createAdd(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);
		TnbFrameMaker_EXPORT fieldFun_t createSubtract(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);
		TnbFrameMaker_EXPORT fieldFun_t createCross(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);
		TnbFrameMaker_EXPORT fieldFun_t createSubdivide(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);
		TnbFrameMaker_EXPORT fieldFun_t createSin(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createCos(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createTan(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createAsin(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createAcos(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createAtan(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createAbs(const fieldMaker_t& m, const fieldFun_t& f);
		TnbFrameMaker_EXPORT fieldFun_t createSqrt(const fieldMaker_t& m, const fieldFun_t& f);

		TnbFrameMaker_EXPORT fieldFun_t createMin(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);
		TnbFrameMaker_EXPORT fieldFun_t createMax(const fieldMaker_t& m, const fieldFun_t& f0, const fieldFun_t& f1);

		TnbFrameMaker_EXPORT fieldFun_t createExpr(const fieldMaker_t& m, const word& ex);

		/* point maker methods*/
		TnbFrameMaker_EXPORT pnt_t createOuterComponent(const pntMaker_t& m, const par_t& x, const par_t& y);
		TnbFrameMaker_EXPORT pnt_t createInnerComponent(const pntMaker_t& m, const par_t& x, const par_t& y);
		TnbFrameMaker_EXPORT pnt_t createOuterOffset(const pntMaker_t& m, double x, double y);
		TnbFrameMaker_EXPORT pnt_t createOuterOffset(const pntMaker_t& m, const Pnt2d& p);
		TnbFrameMaker_EXPORT pnt_t createInnerOffset(const pntMaker_t& m, double x, double y);
		TnbFrameMaker_EXPORT pnt_t createInnerOffset(const pntMaker_t& m, const Pnt2d& p);
		TnbFrameMaker_EXPORT pnt_t createField(const pntMaker_t& m, const geoMap_t& g);
		TnbFrameMaker_EXPORT pnt_t createEmpty(const pntMaker_t& m, const mastPnt_t& p);

		TnbFrameMaker_EXPORT dtm_t createComponent(const dtmMaker_t& m, const par_t& x, const par_t& y);
		TnbFrameMaker_EXPORT dtm_t createField(const dtmMaker_t& m, const geoMap_t& g);

		/*geometric map maker*/
		TnbFrameMaker_EXPORT geoMap_t createLinearIntrpl(const geoMaker_t& m, const coord_t& q0, const coord_t& q1, const par_t& p);
		TnbFrameMaker_EXPORT geoMap_t createIntersection(const geoMaker_t& m, const coord_t& q0, const Dir2d& d0, const par_t& ang0, const coord_t& q1, const Dir2d& d1, const par_t& ang1);

		TnbFrameMaker_EXPORT void removeField(const fieldMaker_t& m, const fieldFun_t& f);


		/* expr field-function methods*/
		TnbFrameMaker_EXPORT void addVariable(const exprField_t& f, const word& name, const fieldFun_t& x);
		TnbFrameMaker_EXPORT void removeVariable(const exprField_t& f, const word& name);

		typedef std::shared_ptr<chaiscript::Module> module_t;

		namespace frameMaker
		{

			TnbFrameMaker_EXPORT void setParameters(const module_t& mod);
			TnbFrameMaker_EXPORT void setField(const module_t& mod);
			TnbFrameMaker_EXPORT void setPoints(const module_t& mod);
			TnbFrameMaker_EXPORT void setGeometricMaps(const module_t& mod);
			TnbFrameMaker_EXPORT void setProfileMakers(const module_t& mod);
			TnbFrameMaker_EXPORT void setGlobals(const module_t& mod);
		}

		TnbFrameMaker_EXPORT std::string getString(char* argv);
		TnbFrameMaker_EXPORT bool IsEqualCommand(char* argv, const std::string& command);
	}

}

#endif // !_frameMaker_Header
