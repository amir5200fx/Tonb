#pragma once
#ifndef _Cad_ModifySingularPlaneTools_Header
#define _Cad_ModifySingularPlaneTools_Header

#include <Cad_ModifySingularPlaneTraits.hxx>
#include <Cad_SubdivideHorizon.hxx>
#include <Cad_SingularZone.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <vector>
#include <list>
#include <map>

namespace tnbLib
{

	// Forward Declarations [4/2/2022 Amir]

	template<class WireType, bool RandSamples>
	class Cad_ApprxWire;

	class Geo_ApprxCurve_Info;

	class Cad_ModifySingularPlaneToolsBase
	{

	public:

		enum class pCurveType
		{
			horizon,
			outerWire,
			innerWire
		};

		
	};

	template<class SurfPlnType>
	class Cad_ModifySingularPlaneTools
		: public Cad_ModifySingularPlaneToolsBase
	{

		/*Private Data*/

	public:	

		typedef typename cad_modify_singular_plane_traits<SurfPlnType>::curveType curveType;
		typedef typename cad_modify_singular_plane_traits<SurfPlnType>::wireType wireType;

		static std::pair
			<
			std::shared_ptr<curveType>, 
			std::shared_ptr<curveType>
			> 
			Split
			(
				const Standard_Real x, 
				const std::shared_ptr<curveType>&
			);

		//static std::pair<std::shared_ptr<curveType>, std::shared_ptr<curveType>> SplitCurve(const std::shared_ptr<curveType>&, const Standard_Real x, const Standard_Real theTol);
		static std::vector<std::shared_ptr<curveType>>
			SubCurves
			(
				const std::shared_ptr<curveType>&,
				const std::list<Standard_Real>& thePars, 
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<wireType>> 
			ModifyWires
			(
				const std::vector<std::shared_ptr<wireType>>&,
				const std::map<std::shared_ptr<curveType>, std::shared_ptr<std::list<Standard_Real>>>&, 
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<curveType>> 
			ModifyHorizons
			(
				const std::vector<std::shared_ptr<curveType>>&,
				const std::map<std::shared_ptr<curveType>, std::shared_ptr<std::list<Standard_Real>>>&,
				const Standard_Real theTol
			);
		
		static std::list<std::shared_ptr<Cad_SubdivideHorizon<curveType>>> 
			CalcParts
			(
				const std::vector<std::shared_ptr<Cad_SingularZone<SurfPlnType>>>& theZones, 
				const std::vector<std::shared_ptr<curveType>>& theCurves
			);

		static std::map<std::shared_ptr<wireType>, Standard_Integer> 
			WireToIndexMap
			(
				const std::vector<std::shared_ptr<wireType>>&
			);	

		static std::map<std::shared_ptr<curveType>, pCurveType> 
			CurveToTypeMap
			(
				const std::vector<std::shared_ptr<curveType>>& theHorizons,
				const std::vector<std::shared_ptr<wireType>>& theWires
			);

		static std::shared_ptr<Entity2d_Polygon> 
			GetPolygon
			(
				const std::shared_ptr<wireType>&, 
				const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
			);

		static std::vector<std::shared_ptr<Entity2d_Polygon>> 
			GetPolygons
			(
				const std::vector<std::shared_ptr<wireType>>& theWires,
				const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
			);

		static std::vector<std::shared_ptr<curveType>> 
			RetrieveCurves
			(
				const wireType&
			);

		static std::vector<std::shared_ptr<curveType>> 
			RetrieveCurves
			(
				const std::vector<std::shared_ptr<wireType>>&
			);
	};
}

#include <Cad_ModifySingularPlaneToolsI.hxx>

#include <Cad_gModifySingularPlaneTools.hxx>
#include <Cad_tModifySingularPlaneTools.hxx>

#endif // !_Cad_ModifySingularPlaneTools_Header
