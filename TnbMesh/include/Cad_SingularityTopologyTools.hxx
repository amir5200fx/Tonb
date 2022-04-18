#pragma once
#ifndef _Cad_SingularityTopologyTools_Header
#define _Cad_SingularityTopologyTools_Header

#include <Entity2d_ChainFwd.hxx>
#include <Mesh_Module.hxx>

#include <memory>
#include <vector>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [4/2/2022 Amir]
	class Pnt2d;

	class Cad_SingularityTopologyTools
	{

		/*Private Data*/

	public:

		template<class CurveType, class WireType>
		static std::shared_ptr<std::vector<std::shared_ptr<CurveType>>> 
			RetrieveCurves
			(
				const std::shared_ptr<WireType>&
			);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_Chain> 
			GetChain
			(
				const Pnt2d&,
				const Pnt2d&
			);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_Chain>
			GetChain
			(
				const Handle(Geom2d_Curve)&
			);

		template<class CurveType>
		static std::vector<std::shared_ptr<Entity2d_Chain>> 
			GetChainList
			(
				const std::vector<std::shared_ptr<CurveType>>&
			);

		static TnbMesh_EXPORT std::pair
			<
			std::shared_ptr<Entity2d_Chain>,
			std::shared_ptr<Entity2d_Chain>
			>
			Split
			(
				const Entity2d_Chain&,
				const Pnt2d&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Entity2d_Chain>>
			Split
			(
				const Entity2d_Chain&, 
				const std::vector<Pnt2d>&
			);

		
	};
}

#include <Cad_SingularityTopologyToolsI.hxx>

#include <Cad_gSingularityTopologyTools.hxx>
#include <Cad_tSingularityTopologyTools.hxx>

#endif // !_Cad_SingularityTopologyTools_Header
