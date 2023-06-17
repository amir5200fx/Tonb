#pragma once
#ifndef _Aft3d_Volume_Header
#define _Aft3d_Volume_Header

#include <Aft3d_Comparison.hxx>
#include <Geo_SearchTree.hxx>
#include <Geo_PriorityList.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/26/2023 Payvand]
		class Aft3d_NodeCalculator;
		class Aft3d_GeoPrcsr;
		class Aft3d_Element;
		class Aft3d_Facet;
		class Aft3d_Edge;
		class Aft3d_Node;

		class Aft3d_VolumeCore
			: public Global_Done
		{

		public:

			class frontHandler
			{

				/*Private Data*/

				Geo_PriorityList<std::shared_ptr<Aft3d_Facet>> theFronts_;

				Standard_Integer theLevel_ = 0;
				Standard_Integer theMaxId_ = 0;

				std::set<std::shared_ptr<Aft3d_Facet>, decltype(cmp_facet)>
					theCurrentLev_;
				std::set<std::shared_ptr<Aft3d_Facet>, decltype(cmp_facet)>
					theNextLev_;

			public:

				// default constructor [2/26/2023 Payvand]

				frontHandler()
					: theCurrentLev_(cmp_facet)
					, theNextLev_(cmp_facet)
				{}

				// constructors [2/26/2023 Payvand]


				// Public functions and operators [2/26/2023 Payvand]

				inline Standard_Boolean IsCurrentEmpty() const;
				inline Standard_Boolean IsNextEmtpy() const;

				TnbLegMesh_EXPORT Standard_Boolean IsOnCurrentLevel(const std::shared_ptr<Aft3d_Facet>&) const;
				inline Standard_Boolean GetFront(std::shared_ptr<Aft3d_Facet>&);

				auto LevelNumber() const { return theLevel_; }
				auto MaxId() const { return theMaxId_; }

				const auto& Fronts() const
				{
					return theFronts_;
				}

				const auto& CurrentLevel() const
				{
					return theCurrentLev_;
				}

				const auto& NextLevel() const
				{
					return theNextLev_;
				}

				inline void InsertToCurrent(const std::shared_ptr<Aft3d_Facet>&);
				inline void InsertToNext(const std::shared_ptr<Aft3d_Facet>&);

				inline void InsertToFronts(const std::vector<std::shared_ptr<Aft3d_Facet>>&);

				inline void ClearCurrent();
				inline void ClearNext();

				inline void SetCurrentLev(const Standard_Integer);
				inline void SetMaxLevel(const Standard_Integer);

				inline std::vector<std::shared_ptr<Aft3d_Facet>> RetrieveCurrentLevel() const;
				inline std::vector<std::shared_ptr<Aft3d_Facet>> RetrieveNexLevel() const;

			};

			enum class cycleMode
			{
				generation = 0,
				repair
			};

			enum class nodeMode
			{
				newPoint = 0,
				pickedUp
			};

			class cycleSpecs
			{

				/*Private Data*/

				Pnt3d theCoord_ = Pnt3d::null;

				std::shared_ptr<Entity3d_Box> theRegion_;

				std::shared_ptr<Aft3d_Node> theTemp_;
				std::shared_ptr<Aft3d_Node> theValid_;

				std::shared_ptr<Aft3d_Facet> theCurrent_;

				std::shared_ptr<Aft3d_Element> theElement_;

				Standard_Boolean appendedNode_;

				Standard_Integer theCandidateSize_ = 0;

				cycleMode theCycleMode_;
				nodeMode theNodeMode_;

				Standard_Real theSize_ = 0;

				Standard_Real theLocalRadius_ = 0;
				Standard_Real theSearchRadius_ = 0;
				Standard_Real theMaxElemLength_ = 0;

				std::array<std::shared_ptr<Aft3d_Facet>, 3> thePairedFacets_;
				std::array<std::shared_ptr<Aft3d_Facet>, 3> theCreatedFacets_;

				std::array<std::shared_ptr<Aft3d_Edge>, 3> thePairedEdges_;
				std::array<std::shared_ptr<Aft3d_Edge>, 3> theCreatedEdges_;

			public:

				// default constructor [2/26/2023 Payvand]

				cycleSpecs()
				{}


				// constructors [2/26/2023 Payvand]

				// Public functions and operators [2/26/2023 Payvand]

				const auto& Coord() const { return theCoord_; }
				auto& CoordRef() { return theCoord_; }

				const auto& Region() const { return theRegion_; }
				auto& RegionRef() { return theRegion_; }

				const auto& TempNode() const { return theTemp_; }
				const auto& ValidNode() const { return theValid_; }
				const auto& Current() const { return theCurrent_; }
				const auto& Element() const { return theElement_; }

				auto AppendedNode() const { return appendedNode_; }
				auto& AppendedNode() { return appendedNode_; }
				auto CycleMode() const { return theCycleMode_; }
				auto NodeMode() const { return theNodeMode_; }

				auto Size() const { return theSize_; }

				auto CandidateSize() const { return theCandidateSize_; }

				auto LocalFrontRadius() const { return theLocalRadius_; }
				auto SquareLocalFrontRadius() const { return theLocalRadius_ * theLocalRadius_; }

				auto SearchRadius() const { return theSearchRadius_; }
				auto SquareSearchRadius() const { return theSearchRadius_ * theSearchRadius_; }
				auto MaxElmLength() const { return theMaxElemLength_; }
				auto SquareMaxElmLength() const { return theMaxElemLength_ * theMaxElemLength_; }

				const auto& PairedFacets() const { return thePairedFacets_; }
				const auto& PairedEdges() const { return thePairedEdges_; }

				const auto& CreatedFacets() const { return theCreatedFacets_; }
				const auto& CreatedEdges() const { return theCreatedEdges_; }

				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet0() const;
				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet1() const;
				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet2() const;

				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge3() const;
				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge4() const;
				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge5() const;

				inline const std::shared_ptr<Aft3d_Facet>& CreatedFacet0() const;
				inline const std::shared_ptr<Aft3d_Facet>& CreatedFacet1() const;
				inline const std::shared_ptr<Aft3d_Facet>& CreatedFacet2() const;

				inline const std::shared_ptr<Aft3d_Edge>& CreatedEdge3() const;
				inline const std::shared_ptr<Aft3d_Edge>& CreatedEdge4() const;
				inline const std::shared_ptr<Aft3d_Edge>& CreatedEdge5() const;

				inline void SetCoord(const Pnt3d& theCoord);
				inline void SetCoord(Pnt3d&&);
				inline void SetTempNode(const std::shared_ptr<Aft3d_Node>&);
				inline void SetValidNode(const std::shared_ptr<Aft3d_Node>&);
				inline void SetRegion(const std::shared_ptr<Entity3d_Box>&);
				inline void SetRegion(std::shared_ptr<Entity3d_Box>&&);
				
				inline void SetCurrent(const std::shared_ptr<Aft3d_Facet>&);
				inline void SetCurrent(std::shared_ptr<Aft3d_Facet>&&);

				inline void SetCandidateSize(const Standard_Integer);
				inline void SetMaxElmLength(const Standard_Real);
				inline void SetLocRadius(const Standard_Real);
				inline void SetSearchRadius(const Standard_Real);
				inline void SetElementSize(const Standard_Real);

				inline void SetCycleMode(const cycleMode);
				inline void SetNodeMode(const nodeMode);

				inline void SetPairedFacet0(const std::shared_ptr<Aft3d_Facet>&);
				inline void SetPairedFacet1(const std::shared_ptr<Aft3d_Facet>&);
				inline void SetPairedFacet2(const std::shared_ptr<Aft3d_Facet>&);

				inline void SetPairedEdge3(const std::shared_ptr<Aft3d_Edge>&);
				inline void SetPairedEdge4(const std::shared_ptr<Aft3d_Edge>&);
				inline void SetPairedEdge5(const std::shared_ptr<Aft3d_Edge>&);

				inline void SetCreatedFacet0(const std::shared_ptr<Aft3d_Facet>&);
				inline void SetCreatedFacet1(const std::shared_ptr<Aft3d_Facet>&);
				inline void SetCreatedFacet2(const std::shared_ptr<Aft3d_Facet>&);

				inline void SetCreatedEdge3(const std::shared_ptr<Aft3d_Edge>&);
				inline void SetCreatedEdge4(const std::shared_ptr<Aft3d_Edge>&);
				inline void SetCreatedEdge5(const std::shared_ptr<Aft3d_Edge>&);

				inline void SetElement(const std::shared_ptr<Aft3d_Element>&);
				inline void SetElement(std::shared_ptr<Aft3d_Element>&&);

				inline void Reset();

			};

			class cavityFronts
			{

				/*Private Data*/

				std::set<std::shared_ptr<Aft3d_Facet>, decltype(cmp_facet)> theUncertainty_;
				std::set<std::shared_ptr<Aft3d_Facet>, decltype(cmp_facet)> theCertainty_;

			public:

				// default constructor [2/26/2023 Payvand]

				cavityFronts();

				// constructors [2/26/2023 Payvand]


				// Public functions and operators [2/26/2023 Payvand]

				inline Standard_Boolean IsUncertaintyEmpty() const;
				inline Standard_Boolean IsCertaintyEmpty() const;

				const auto& Uncertainty() const { return theUncertainty_; }
				const auto& Certainty() const { return theCertainty_; }

				inline std::vector<std::shared_ptr<Aft3d_Facet>> RetrieveUncertainties() const;
				inline std::vector<std::shared_ptr<Aft3d_Facet>> RetrieveCertainties() const;

				inline void InsertToUncertainty(const std::shared_ptr<Aft3d_Facet>&);
				inline void InsertToCertainty(const std::shared_ptr<Aft3d_Facet>&);

				inline void RemoveFromUncertainty(const std::shared_ptr<Aft3d_Facet>&);
				inline void RemoveFromCertainty(const std::shared_ptr<Aft3d_Facet>&);

				inline void ClearUncertainty();
				inline void ClearCertainty();

			};

			class meshData
			{

				/*Private Data*/

				std::shared_ptr<std::set<std::shared_ptr<Aft3d_Element>, decltype(cmp_element)>>
					theElements_;

				Standard_Integer theNbNodes_;

			public:

				// default constructor [2/27/2023 Payvand]

				meshData()
					: theNbNodes_(0)
				{}

				// constructors [2/27/2023 Payvand]


				// Public functions and operators [2/27/2023 Payvand]

				auto NbNodes() const { return theNbNodes_; }
				auto& NbNodesRef() { return theNbNodes_; }

				inline Standard_Integer NbElements() const;

				const auto& Elements() const { return theElements_; }

				inline void Insert(const std::shared_ptr<Aft3d_Element>&);
				inline void Insert(std::shared_ptr<Aft3d_Element>&&);

				inline void Remove(const std::shared_ptr<Aft3d_Element>&);

				inline void SetNbNodes(const Standard_Integer);
				inline void Clear();

			};

			class entCounter
			{

				/*Private Data*/

				Standard_Integer theNbNodes_;
				Standard_Integer theNbEdges_;
				Standard_Integer theNbFacets_;
				Standard_Integer theNbElements_;

			public:

				// default constructor [6/1/2023 Payvand]

				entCounter()
					: theNbNodes_(0)
					, theNbEdges_(0)
					, theNbFacets_(0)
					, theNbElements_(0)
				{}

				// constructors [6/1/2023 Payvand]


				// Public functions and operators [6/1/2023 Payvand]

				auto NbNodes() const { return theNbNodes_; }
				auto NbEdges() const { return theNbEdges_; }
				auto NbFacets() const { return theNbFacets_; }
				auto NbElements() const { return theNbElements_; }

				auto& NbNodes() { return theNbNodes_; }
				auto& NbEdges() { return theNbEdges_; }
				auto& NbFacets() { return theNbFacets_; }
				auto& NbElements() { return theNbElements_; }

			};

		protected:

			/*Private Data*/

			std::shared_ptr<Aft3d_GeoPrcsr> theMetricMap_;
			std::shared_ptr<Geo_SearchTree<std::shared_ptr<Aft3d_Node>>> theEngine_;
			std::shared_ptr<Aft3d_NodeCalculator> theCoordCalculator_;

			Standard_Integer theALLOWED_MAX_LEVEL_;

			Standard_Real theMinDistanceFactor_ = 0;
			Standard_Real theMinEdgeDistanceFactor_ = 0;

			

			// Memories [2/26/2023 Payvand]
			frontHandler FrontHandler;
			cycleSpecs CycleInfo;
			cavityFronts Cavities;
			entCounter Counter;

			// Results [2/26/2023 Payvand]

			meshData Mesh;

			static const Standard_Real SIZE_TO_HIGHT_ELEMENT_COEFF;


			// Private functions and operators [2/26/2023 Payvand]

			void CheckBoundaries();

			inline Standard_Boolean IsNewNode() const;
			TnbLegMesh_EXPORT Standard_Boolean GetCurrent();
			TnbLegMesh_EXPORT Standard_Boolean IsBelongToFront() const;
			TnbLegMesh_EXPORT Standard_Boolean IsNewNodeValid
			(const std::vector<std::shared_ptr<Aft3d_Facet>>&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsNewEdgeValid
			(
				const Pnt3d&, const Pnt3d&,
				const std::vector<std::shared_ptr<Aft3d_Edge>>&
			) const;
			TnbLegMesh_EXPORT Standard_Boolean IsSameLevelSupplied();
			TnbLegMesh_EXPORT Standard_Boolean IsNextLevelSupplied();
			TnbLegMesh_EXPORT Standard_Boolean IsCavityRemoverSupplied();

			//Entity3d_Box CalcSearchingRegion() const;

			auto CycleMode() const { return CycleInfo.CycleMode(); }

			const auto& Current() const { return CycleInfo.Current(); }
			const auto& ValidNode() const { return CycleInfo.ValidNode(); }

			TnbLegMesh_EXPORT void RetrieveEarlyNodes(std::vector<std::shared_ptr<Aft3d_Node>>&) const;
			TnbLegMesh_EXPORT void RetrieveLocalFrontNodes
			(
				std::vector<std::shared_ptr<Aft3d_Node>>& theLocals,
				std::vector<std::shared_ptr<Aft3d_Node>>& theSearching
			);
			TnbLegMesh_EXPORT void RetrieveLocalFrontEntities
			(
				const std::vector<std::shared_ptr<Aft3d_Node>>&,
				std::vector<std::shared_ptr<Aft3d_Facet>>&
			) const;

			TnbLegMesh_EXPORT void RetrieveEffectiveFronts
			(
				const std::vector<std::shared_ptr<Aft3d_Facet>>&,
				std::vector<std::shared_ptr<Aft3d_Facet>>&
			) const;

			TnbLegMesh_EXPORT void SortNodes(std::vector<std::shared_ptr<Aft3d_Node>>&) const;

			TnbLegMesh_EXPORT void AddOptimumNodeTo(std::vector<std::shared_ptr<Aft3d_Node>>&);

			//void SetCurrent(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void CalcLocalFrontRadius();
			TnbLegMesh_EXPORT void ModifyLocalFront(const Standard_Real theFactor);

			TnbLegMesh_EXPORT void RemoveEntitiesFromGeometry();
			TnbLegMesh_EXPORT void RemoveCurrentFromFront();
			TnbLegMesh_EXPORT void CalcElementSize();
			TnbLegMesh_EXPORT void CalcOptimumCoord();
			TnbLegMesh_EXPORT void SetSearchingDepth();

			TnbLegMesh_EXPORT void SetPairedEdges();
			TnbLegMesh_EXPORT void SetPairedFacets();
			TnbLegMesh_EXPORT void SetPairs();

			TnbLegMesh_EXPORT void CalcGeometries(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void CalcGeometries(const std::shared_ptr<Aft3d_Edge>&);

			TnbLegMesh_EXPORT void UpdateEdges();
			TnbLegMesh_EXPORT void UpdateFacets();
			TnbLegMesh_EXPORT void UpdatePairs();

			TnbLegMesh_EXPORT void UpdateElement();

			TnbLegMesh_EXPORT void CreateElement();
			TnbLegMesh_EXPORT void RegisterElement();

			static TnbLegMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Node>>
				NodesInRadius
				(
					const Standard_Real theRadius,
					const Pnt3d& theCoord, 
					const Aft3d_GeoPrcsr& theMetricMap,
					const std::vector<std::shared_ptr<Aft3d_Node>>&
				);
			static TnbLegMesh_EXPORT void Update_Pmin_Pmax
			(const Pnt3d&, Pnt3d& theP0, Pnt3d& theP1);
			static TnbLegMesh_EXPORT Standard_Boolean 
				IsIntersect
				(
					const Pnt3d& Q0,
					const Pnt3d& Q1, 
					const Pnt3d& Pmin,
					const Pnt3d& Pmax
				);
			static TnbLegMesh_EXPORT Standard_Boolean 
				IsIntersect
				(
					const Aft3d_Facet& theFacet,
					const Pnt3d& theP0,
					const Pnt3d& theP1
				);

			// default constructor [2/26/2023 Payvand]

			Aft3d_VolumeCore()
			{}

			// constructors [2/26/2023 Payvand]


		public:

			static TnbLegMesh_EXPORT unsigned short verbose;

			

			// Public functions and operators [2/26/2023 Payvand]

			auto MinDistFactor() const { return theMinDistanceFactor_; }
			auto MinDistEdgeFactor() const { return theMinEdgeDistanceFactor_; }

			const auto& MetricMap() const { return theMetricMap_; }
			const auto& Engine() const { return theEngine_; }
			const auto& CoordCalculator() const { return theCoordCalculator_; }

			void SetCoordCalculator(const std::shared_ptr<Aft3d_NodeCalculator>& theCalculator)
			{
				theCoordCalculator_ = theCalculator;
			}

			static TnbLegMesh_EXPORT void AttachToMeshNodes(const std::shared_ptr<Aft3d_Element>&);
			static TnbLegMesh_EXPORT void AttachToMeshNodes(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void AttachToMeshNodes(const std::shared_ptr<Aft3d_Edge>&);

			static TnbLegMesh_EXPORT void AttachToMeshEdges(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void AttachToMeshEdges(const std::shared_ptr<Aft3d_Element>&);

			static TnbLegMesh_EXPORT void AttachToMesh(const std::shared_ptr<Aft3d_Facet>& theFacet);
			static TnbLegMesh_EXPORT void AttachToMesh(const std::shared_ptr<Aft3d_Element>&);

			static TnbLegMesh_EXPORT void AttachToFrontNodes(const std::shared_ptr<Aft3d_Facet>& theFacet);
			static TnbLegMesh_EXPORT void AttachToFrontNodes(const std::shared_ptr<Aft3d_Edge>& theEdge);
			static TnbLegMesh_EXPORT void AttachToFrontEdges(const std::shared_ptr<Aft3d_Facet>& theFacet);

			static TnbLegMesh_EXPORT void AttachToFronts(const std::shared_ptr<Aft3d_Facet>& theFront);

			static TnbLegMesh_EXPORT void deAttachFromMesh(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void deAttachFromMesh(const std::shared_ptr<Aft3d_Edge>&);

			static TnbLegMesh_EXPORT void deAttachFromMeshNodes(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void deAttachFromMeshEdges(const std::shared_ptr<Aft3d_Facet>&);

			static TnbLegMesh_EXPORT void deAttachFromFronts(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void deAttachFromFronts(const std::shared_ptr<Aft3d_Edge>&);

			static TnbLegMesh_EXPORT void deAttachFromFrontNodes(const std::shared_ptr<Aft3d_Facet>&);
			static TnbLegMesh_EXPORT void deAttachFromFrontEdges(const std::shared_ptr<Aft3d_Facet>&);
			
		};

		struct Aft3d_VolumeConstants
		{

			static Standard_Integer ALLOWED_MAX_LEVEL_GENERATION;

			static Standard_Real DEFAULT_LOCALFRONT_FACTOR;
			static Standard_Real DEFAULT_MIN_DISTANCE_FACTOR;
		};

		class Aft3d_Volume
			: public Aft3d_VolumeCore
			, public Aft3d_VolumeConstants
		{

		public:

			typedef Aft3d_VolumeCore base;

			using base::FrontHandler;

		private:

			/*Private Data*/

			std::shared_ptr<Aft3d_GeoPrcsr> theBoundaryMetricMap_;

			std::shared_ptr<std::vector<std::shared_ptr<Aft3d_Facet>>> theBoundary_;


			// Private functions and operators [3/1/2023 Payvand]

			auto& BoundaryRef() { return theBoundary_; }

			TnbLegMesh_EXPORT Standard_Integer Meshing();

			TnbLegMesh_EXPORT void MeshOneLevel();
			TnbLegMesh_EXPORT void FindValidNode
			(
				const std::vector<std::shared_ptr<Aft3d_Node>>&,
				const std::vector<std::shared_ptr<Aft3d_Facet>>&
			);
			TnbLegMesh_EXPORT void UpdateFront();
			void InsertNewFrontsToLevels();

		public:

			// default constructor [3/1/2023 Payvand]

			Aft3d_Volume()
			{}


			// constructors [3/1/2023 Payvand]


			// Public functions and operators [3/1/2023 Payvand]

			void Perform();


			//- static functions and operators

			static TnbLegMesh_EXPORT Standard_Boolean 
				IsNewFace
				(
					const std::shared_ptr<Aft3d_Node>& theNode0,
					const std::shared_ptr<Aft3d_Node>& theNode1, 
					const std::shared_ptr<Aft3d_Node>& theNode2
				);
			static TnbLegMesh_EXPORT Standard_Boolean 
				IsNewSegment
				(
					const std::shared_ptr<Aft3d_Node>& theNode0,
					const std::shared_ptr<Aft3d_Node>& theNode1
				);

			static Standard_Boolean CheckAngle(const Aft3d_Facet& theFront, const Aft3d_Node& theNode, const Standard_Real theAngle);
		};

	}
}

#include <Aft3d_VolumeI.hxx>

#endif // !_Aft3d_Volume_Header
