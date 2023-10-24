#pragma once
#ifndef _VoyageMesh_CorrectSizeMap_Header
#define _VoyageMesh_CorrectSizeMap_Header

#include <Voyage_PathDir.hxx>
#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_RayFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Indexed.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/19/2023 aamir]
	class Voyage_MetricInfo;
	class VoyageGeo_Path2;

	class VoyageMesh_CorrectSizeMap
		: public Global_Done
	{

	public:

		// Forward Declarations [8/19/2023 aamir]
		class Edge;

		class Chain
		{

			/*Private Data*/

			std::vector<std::shared_ptr<Edge>> theEdges_;

		public:

			// default constructor [8/21/2023 aamir]

			Chain()
			{}

			// constructors [8/21/2023 aamir]

			Chain(const std::vector<std::shared_ptr<Edge>>& theEdges)
				: theEdges_(theEdges)
			{}

			Chain(std::vector<std::shared_ptr<Edge>>&& theEdges)
				: theEdges_(std::move(theEdges))
			{}


			// Public functions and operators [8/21/2023 aamir]

			const auto& Edges() const { return theEdges_; }

			void SetEdges(const std::vector<std::shared_ptr<Edge>>& theEdges) { theEdges_ = theEdges; }
			void SetEdges(std::vector<std::shared_ptr<Edge>>&& theEdges) { theEdges_ = std::move(theEdges); }

		};

		class AngleBisect
		{

			/*Private Data*/

			std::shared_ptr<Entity2d_Ray> theRay_;
			std::shared_ptr<Chain> theRightSide_;
			std::shared_ptr<Chain> theLeftSide_;

			Standard_Real theAngle_;

		public:

			// default constructor [8/19/2023 aamir]

			AngleBisect()
				: theAngle_(0)
			{}

			// constructors [8/19/2023 aamir]

			AngleBisect
			(
				const std::shared_ptr<Entity2d_Ray>& theRay,
				const std::shared_ptr<Chain>& theRight,
				const std::shared_ptr<Chain>& theLeft
			)
				: theRay_(theRay)
				, theRightSide_(theRight)
				, theLeftSide_(theLeft)
				, theAngle_(0)
			{}

			// Public functions and operators [8/19/2023 aamir]

			const auto& Ray() const { return theRay_; }
			const auto& RightSide() const { return theRightSide_; }
			const auto& LeftSide() const { return theLeftSide_; }

			auto Angle() const { return theAngle_; }

			void SetRay(const std::shared_ptr<Entity2d_Ray>& theRay) { theRay_ = theRay; }
			void SetLeftSide(const std::shared_ptr<Chain>& thePoly) { theLeftSide_ = thePoly; }
			void SetRightSide(const std::shared_ptr<Chain>& thePoly) { theRightSide_ = thePoly; }
			
			void SetAngle(const Standard_Real theAngle) { theAngle_ = theAngle; }

		};

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

		public:

			// default constructor [8/19/2023 aamir]

			Node()
			{}

			// Constructors [8/19/2023 aamir]

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

			// Public functions and operators [8/19/2023 aamir]

			const auto& Coord() const { return theCoord_; }

			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }
		};

		class Edge
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			// default constructor [8/19/2023 aamir]

			Edge()
			{}

			// constructors [8/19/2023 aamir]

			Edge
			(
				const std::shared_ptr<Node>& theNode0,
				const std::shared_ptr<Node>& theNode1
			)
				: theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			// Public functions and operators [8/19/2023 aamir]

			const auto& Node0() const { return theNode0_; }
			const auto& Node1() const { return theNode1_; }

			TnbVoyage_EXPORT Pnt2d CalcCentre() const;
			TnbVoyage_EXPORT Dir2d CalcNormal() const;

			void SetNode0(const std::shared_ptr<Node>& theNode) { theNode0_ = theNode; }
			void SetNode1(const std::shared_ptr<Node>& theNode) { theNode1_ = theNode; }
		};

	private:

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path2> thePath_;
		std::shared_ptr<Geo2d_SizeFunction> theSizeFunction_;
		std::shared_ptr<Voyage_MetricInfo> theInfo_;
		voyageLib::PathDirect theDirection_;

		Standard_Integer theMaxNbCorrs_;
		Standard_Real theSmoothingFactor_;

		Standard_Real theBaseSize_;

		// Results [8/19/2023 aamir]

		std::shared_ptr<GeoMesh2d_Background> theBackMesh_;


		// Private functions and operators [8/19/2023 aamir]

		TnbVoyage_EXPORT std::vector<std::shared_ptr<Entity2d_Polygon>> RetrievePolygons() const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<AngleBisect>> CalcBisectAngles() const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<Chain>> CalcEdges() const;
		
		static TnbVoyage_EXPORT std::shared_ptr<Edge> LastEdge(const Chain&);
		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Ray> 
			CalcBisectRay
			(
				const Pnt2d& theP0, 
				const Pnt2d& theP1, 
				const Pnt2d& theP2,
				Standard_Real& theAngle
			);

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Ray>
			CalcBisectRay
			(
				const Edge& theEdge0, 
				const Edge& theEdge1,
				Standard_Real& theAngle
			);

		static TnbVoyage_EXPORT std::shared_ptr<AngleBisect>
			CalcAngle
			(
				const std::shared_ptr<Chain>&,
				const std::shared_ptr<Chain>&
			);
		static TnbVoyage_EXPORT std::shared_ptr<Chain>
			CalcChain(const Entity2d_Polygon&);
		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Node>>
			RetrieveNodes(const std::vector<std::shared_ptr<Edge>>&);
		static TnbVoyage_EXPORT std::tuple<Standard_Real, Pnt2d, Standard_Boolean>
			CalcDistance
			(
				const Edge& theEdge,
				const Entity2d_Ray& theRay, 
				const Geo2d_MetricPrcsrAnIso&, 
				const Standard_Boolean reverse_normal = Standard_False
			);

		static TnbVoyage_EXPORT std::vector<Pnt2d>
			RetrieveCoords(const std::vector<std::shared_ptr<Entity2d_Polygon>>&);

	public:

		static TnbVoyage_EXPORT unsigned short verbose;

		static TnbVoyage_EXPORT Standard_Real DEFAULT_BASE_SIZE;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_SMOOTHING_FACTOR;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_MAX_NB_CORRS;

		// default constructor [8/19/2023 aamir]

		VoyageMesh_CorrectSizeMap()
			: theBaseSize_(DEFAULT_BASE_SIZE)
			, theMaxNbCorrs_(DEFAULT_MAX_NB_CORRS)
			, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
		{}

		// constructors [8/19/2023 aamir]

		VoyageMesh_CorrectSizeMap
		(
			const std::shared_ptr<VoyageGeo_Path2>& thePath, 
			const std::shared_ptr<Geo2d_SizeFunction>& theFunction,
			const std::shared_ptr<Voyage_MetricInfo>& theInfo
		)
			: thePath_(thePath)
			, theSizeFunction_(theFunction)
			, theBaseSize_(DEFAULT_BASE_SIZE)
			, theMaxNbCorrs_(DEFAULT_MAX_NB_CORRS)
			, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
			, theInfo_(theInfo)
		{}


		// Public functions and operators [8/19/2023 aamir]

		const auto& Path() const { return thePath_; }
		const auto& SizeFun() const { return theSizeFunction_; }
		const auto& GetInfo() const { return theInfo_; }

		const auto& BackMesh() const { return theBackMesh_; }
		auto Direction() const { return theDirection_; }

		auto MaxNbCorrs() const { return theMaxNbCorrs_; }
		auto SmoothingFactor() const { return theSmoothingFactor_; }

		auto BaseSize() const { return theBaseSize_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theFunc) { theSizeFunction_ = theFunc; }
		void SetDirection(const voyageLib::PathDirect theDir) { theDirection_ = theDir; }
		void SetBaseSize(const Standard_Real theSize) { theBaseSize_ = theSize; }
		void SetInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }
	};
}

#endif // !_VoyageMesh_CorrectSizeMap_Header
