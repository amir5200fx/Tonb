#pragma once
#ifndef _Mesh3d_UnionSizeMap_Header
#define _Mesh3d_UnionSizeMap_Header

#include <Mesh_Module.hxx>
#include <GeoMesh3d_BackgroundFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/15/2022 Amir]
	class Cad_TModel;
	class GeoMesh_Background_SmoothingHvCorrection_Info;
	class Geo3d_PatchCloud;

	class Mesh3d_UnionSizeMap
		: public Global_Done
	{

		/*Private Data*/

		Standard_Integer theMaxUnbalancing_;
		Standard_Real theTol_;

		std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info> theInfo_;

		std::shared_ptr<Entity3d_Box> theDomain_;

		std::vector<std::shared_ptr<Cad_TModel>> theModels_;
		std::vector<std::shared_ptr<GeoMesh3d_Background>> theBackgrounds_;

		std::shared_ptr<Geo3d_PatchCloud> theCloud_;

		// results [7/18/2022 Amir]

		std::shared_ptr<GeoMesh3d_Background> theUnifiedMap_;

		// private functions and operators [7/15/2022 Amir]

		TnbMesh_EXPORT Standard_Real ElementSize(const Pnt3d&) const;

		TnbMesh_EXPORT void UpdateSources(const std::shared_ptr<GeoMesh3d_Background>&) const;

		static TnbMesh_EXPORT std::vector<Pnt3d> RetrieveCoords(const Cad_TModel&, const Geo3d_PatchCloud&);
		static TnbMesh_EXPORT std::vector<Pnt3d> RetrieveCoords(const std::vector<std::shared_ptr<Cad_TModel>>&, const Geo3d_PatchCloud&);

	public:

		static TnbMesh_EXPORT unsigned short verbose;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_UNBALANCING;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOELRANCE;

		// default constructor [7/15/2022 Amir]

		Mesh3d_UnionSizeMap()
			: theMaxUnbalancing_(DEFAULT_MAX_UNBALANCING)
			, theTol_(DEFAULT_TOELRANCE)
		{}


		// constructors [7/15/2022 Amir]


		// public functions and operators [7/15/2022 Amir]

		auto MaxUnbalancing() const
		{
			return theMaxUnbalancing_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		const auto& SmoothingInfo() const
		{
			return theInfo_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Models() const
		{
			return theModels_;
		}

		const auto& Backgrounds() const
		{
			return theBackgrounds_;
		}

		const auto& Cloud() const
		{
			return theCloud_;
		}

		const auto& UnifiedMap() const
		{
			return theUnifiedMap_;
		}

		TnbMesh_EXPORT void Perform();

		void SetMaxUnbalancing(const Standard_Integer theMaxUnBalancing)
		{
			theMaxUnbalancing_ = theMaxUnBalancing;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}

		void SetDomain(const std::shared_ptr<Entity3d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetDomain(std::shared_ptr<Entity3d_Box>&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}

		void SetSmoothingInfo(const std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetSmoothingInfo(std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}

		void SetModels(const std::vector<std::shared_ptr<Cad_TModel>>& theModels)
		{
			theModels_ = theModels;
		}

		void SetModels(std::vector<std::shared_ptr<Cad_TModel>>&& theModels)
		{
			theModels_ = std::move(theModels);
		}

		void SetBackgrounds(const std::vector<std::shared_ptr<GeoMesh3d_Background>>& theBacks)
		{
			theBackgrounds_ = theBacks;
		}

		void SetBackgrounds(std::vector<std::shared_ptr<GeoMesh3d_Background>>&& theBacks)
		{
			theBackgrounds_ = std::move(theBacks);
		}

		void SetCloud(const std::shared_ptr<Geo3d_PatchCloud>& theCloud)
		{
			theCloud_ = theCloud;
		}

		void SetCloud(std::shared_ptr<Geo3d_PatchCloud>&& theCloud)
		{
			theCloud_ = std::move(theCloud);
		}

	};
}

#endif // !_Mesh3d_UnionSizeMap_Header
