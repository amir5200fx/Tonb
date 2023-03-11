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

				inline Standard_Boolean IsOnCurrentLevel(const std::shared_ptr<Aft3d_Facet>&) const;
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

				Pnt3d theCoord_;

				std::shared_ptr<Entity3d_Box> theRegion_;

				std::shared_ptr<Aft3d_Node> theTemp_;
				std::shared_ptr<Aft3d_Node> theValid_;

				std::shared_ptr<Aft3d_Facet> theCurrent_;

				std::shared_ptr<Aft3d_Element> theElement_;

				Standard_Boolean appendedNode_;

				Standard_Integer theCandidateSize_ = 0;

				Standard_Integer theNodeCounter_ = 0;

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

				auto NodeCounter() const { return theNodeCounter_; }

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

				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet0() const;
				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet1() const;
				inline const std::shared_ptr<Aft3d_Facet>& PairedFacet2() const;

				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge3() const;
				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge4() const;
				inline const std::shared_ptr<Aft3d_Edge>& PairedEdge5() const;

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
				void SetSearchRadius(const Standard_Real);
				void SetElementSize(const Standard_Real);
				void SetNodeCounter(const Standard_Integer);

				inline void SetCycleMode(const cycleMode);
				inline void SetNodeMode(const nodeMode);

				inline void Reset();

			};

			class cavityFronts
			{

				/*Private Data*/

				std::set<std::shared_ptr<Aft3d_Facet>> theUncertainty_;
				std::set<std::shared_ptr<Aft3d_Facet>> theCertainty_;

			public:

				// default constructor [2/26/2023 Payvand]

				cavityFronts()
				{}

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

				Standard_Boolean Insert(const std::shared_ptr<Aft3d_Element>&);
				Standard_Boolean Insert(std::shared_ptr<Aft3d_Element>&&);

				Standard_Boolean Remove(const std::shared_ptr<Aft3d_Element>&);

				inline void SetNbNodes(const Standard_Integer);
				inline void Clear();

			};

		protected:

			/*Private Data*/

			std::shared_ptr<Aft3d_GeoPrcsr> theMetricMap_;
			std::shared_ptr<Geo_SearchTree<std::shared_ptr<Aft3d_Node>>> theEngine_;

			Standard_Integer theALLOWED_MAX_LEVEL_;

			Standard_Real theMinDistanceFactor_ = 0;
			Standard_Real theMinEdgeDistanceFactor_ = 0;

			

			// Memories [2/26/2023 Payvand]
			frontHandler FrontHandler;
			cycleSpecs CycleInfo;
			cavityFronts Cavities;


			// Results [2/26/2023 Payvand]

			meshData Mesh;

			static const Standard_Real SIZE_TO_HIGHT_ELEMENT_COEFF;


			// Private functions and operators [2/26/2023 Payvand]

			void CheckBoundaries();

			inline Standard_Boolean IsNewNode() const;
			Standard_Boolean GetCurrent();
			Standard_Boolean IsBelongToFront() const;
			Standard_Boolean IsNewNodeValid(const std::vector<std::shared_ptr<Aft3d_Facet>>&) const;
			Standard_Boolean IsNewEdgeValid
			(
				const Pnt3d&, const Pnt3d&,
				const std::vector<std::shared_ptr<Aft3d_Edge>>&
			) const;
			Standard_Boolean IsSameLevelSupplied();
			Standard_Boolean IsNextLevelSupplied();
			Standard_Boolean IsCavityRemoverSupplied();

			Entity3d_Box CalcSearchingRegion() const;

			auto CycleMode() const { return CycleInfo.CycleMode(); }

			const auto& Current() const { return CycleInfo.Current(); }
			const auto& ValidNode() const { return CycleInfo.ValidNode(); }

			void RetrieveEarlyNodes(std::vector<std::shared_ptr<Aft3d_Node>>&) const;
			void RetrieveLocalFrontNodes
			(
				std::vector<std::shared_ptr<Aft3d_Node>>& theLocals,
				std::vector<std::shared_ptr<Aft3d_Node>>& theSearching
			);
			void RetrieveLocalFrontEntities(std::vector<std::shared_ptr<Aft3d_Node>>&, std::vector<std::shared_ptr<Aft3d_Facet>>&) const;
			void RetrieveEffectiveFronts(const std::vector<std::shared_ptr<Aft3d_Facet>>&, std::vector<std::shared_ptr<Aft3d_Facet>>&) const;

			void SortNodes(std::vector<std::shared_ptr<Aft3d_Node>>&) const;

			void AddOptimumNodeTo(std::vector<std::shared_ptr<Aft3d_Node>>&);

			void SetCurrent(const std::shared_ptr<Aft3d_Facet>&);
			void CalcLocalFrontRadius();
			void ModifyLocalFront(const Standard_Real theFactor);

			void RemoveCurrentFromFront();
			void CalcElementSize();
			void CalcOptimumCoord();
			void SetDepthSearching();

			static std::vector<std::shared_ptr<Aft3d_Node>> 
				NodesInRadius
				(
					const Standard_Real theRadius,
					const Pnt3d& theCoord, 
					const Aft3d_GeoPrcsr& theMetricMap,
					const std::vector<std::shared_ptr<Aft3d_Node>>&
				);
			static void Update_Pmin_Pmax(const Pnt3d&, Pnt3d& theP0, Pnt3d& theP1);
			static Standard_Boolean IsIntersect(const Aft3d_Facet& theFacet, const Pnt3d& theP0, const Pnt3d& theP1);

			// default constructor [2/26/2023 Payvand]

			Aft3d_VolumeCore()
			{}

			// constructors [2/26/2023 Payvand]


		public:

			static unsigned short verbose;

			

			// Public functions and operators [2/26/2023 Payvand]

			auto MinDistFactor() const { return theMinDistanceFactor_; }
			auto MinDistEdgeFactor() const { return theMinEdgeDistanceFactor_; }

			const auto& MetricMap() const { return theMetricMap_; }
			const auto& Engine() const { return theEngine_; }
			
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

			Standard_Integer Meshing();

			void MeshOneLevel();
			void FindValidNode(const std::vector<std::shared_ptr<Aft3d_Node>>&, const std::vector<std::shared_ptr<Aft3d_Facet>>&);
			void Update();
			void InsertNewFrontsToLevels();

		public:

			// default constructor [3/1/2023 Payvand]

			Aft3d_Volume()
			{}


			// constructors [3/1/2023 Payvand]


			// Public functions and operators [3/1/2023 Payvand]

			void Perform();

		};

	}
}

#include <Aft3d_VolumeI.hxx>

#endif // !_Aft3d_Volume_Header
