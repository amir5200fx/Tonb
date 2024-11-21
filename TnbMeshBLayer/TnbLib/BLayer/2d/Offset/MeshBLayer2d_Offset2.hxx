#pragma once
#ifndef _MeshBLayer2d_Offset2_Header
#define _MeshBLayer2d_Offset2_Header

#include <MeshBLayer_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include <opencascade/Extrema_POnCurv.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Entity2d_CmpMesh;

	class MeshBLayer2d_Offset2
		: public Global_Done
	{

	public:

		class Node
		{
			
		public:

			Pnt2d coord;
			std::weak_ptr<Node> paired;
			
			Node() = default;
			Node(const Pnt2d& theCoord) : coord(theCoord) {}

			virtual Standard_Boolean IsLeft() const { return Standard_False; }
			virtual Standard_Boolean IsRight() const { return Standard_False; }
			virtual Standard_Boolean IsCentre() const { return Standard_False; }
		};

		class LeftNode
			: public Node
		{
		public:

			LeftNode() = default;
			LeftNode(const Pnt2d& theCoord) : Node(theCoord) {}

			Standard_Boolean IsLeft() const override { return Standard_True; }
		};

		class RightNode
			: public Node
		{
		public:

			RightNode() = default;
			RightNode(const Pnt2d& theCoord) : Node(theCoord) {}

			Standard_Boolean IsRight() const override { return Standard_True; }
		};

		class CentreNode
			: public Node
		{
		public:

			std::vector<std::shared_ptr<Node>> lefts;
			std::vector<std::shared_ptr<Node>> rights;

			CentreNode() = default;
			CentreNode(const Pnt2d& theCoord) : Node(theCoord) {}

			Standard_Boolean IsCentre() const override { return Standard_True; }
		};

		struct Offsets
		{
			std::vector<Pnt2d> pnts;
		};

	private:
		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolygon_;
		std::shared_ptr<Entity2d_Polygon> theGeoOffset_;

		Standard_Integer theClusterSize_ = 5;
		Standard_Real theRate_ = 1.003;
		Standard_Real theChevronAngle_ = PI / 6.0;
		Standard_Real theTolerance_ = 1.0e-8;
		Standard_Real theFirstLayer_ = 0;

		// results
		std::shared_ptr<Entity2d_CmpMesh> theMesh_;
		std::vector<std::shared_ptr<Node>> theOffset_;
		
		std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<CentreNode>>>
			theStrip_;
		// Private functions and operators

		std::vector<std::pair<Pnt2d, Pnt2d>> RetrievePairs() const;

		TnbMeshBLayer_EXPORT void CalculateStrip();
		TnbMeshBLayer_EXPORT void RetrieveTopoOffset();
		TnbMeshBLayer_EXPORT void CreateMesh();
		static TnbMeshBLayer_EXPORT Dir2d CalcNormal(const Pnt2d&, const Pnt2d&);
		static TnbMeshBLayer_EXPORT Standard_Real CalcAngle(const Dir2d&, const Dir2d&);
		static TnbMeshBLayer_EXPORT std::vector<Standard_Real>
			UniformDistb(const Standard_Integer n);
		static TnbMeshBLayer_EXPORT std::vector<Pnt2d>
			DiscreteSegment
			(
				const std::pair<Pnt2d, Pnt2d>&,
				const std::vector<Standard_Real>&,
				const Standard_Real theBeta
			);
		static TnbMeshBLayer_EXPORT std::vector<Pnt2d>
			Reverse(const std::vector<std::vector<Pnt2d>>&);

	public:

		// Default Constructor

		MeshBLayer2d_Offset2() = default;

		// constructors


		// Public functions and operators

		const auto& Polygon() const { return thePolygon_; }
		const auto& Offset() const { return theOffset_; }
		const auto& Strip() const { return theStrip_; }
		const auto& Mesh() const { return theMesh_; }

		auto ClusterSize() const { return theClusterSize_; }
		auto Rate() const { return theRate_; }
		auto ChevronAngle() const { return theChevronAngle_; }
		auto Tolerance() const { return theTolerance_; }
		auto FirstLayer() const { return theFirstLayer_; }

		TnbMeshBLayer_EXPORT void Perform();

		TnbMeshBLayer_EXPORT std::shared_ptr<Entity2d_Polygon> RetrieveOffset() const;

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePolygon) { thePolygon_ = thePolygon; }
		void SetGeoOffset(const std::shared_ptr<Entity2d_Polygon>& thePolygon) { theGeoOffset_ = thePolygon; }
		void SetClusterSize(const Standard_Integer n) { theClusterSize_ = n; }
		void SetRate(const Standard_Real theRate) { theRate_ = theRate; }
		void SetChevronAngle(const Standard_Real theAngle) { theChevronAngle_ = theAngle; }
		void SetTolerance(const Standard_Real theTol) { theTolerance_ = theTol; }
		void SetFirtLayer(const Standard_Real theValue) { theFirstLayer_ = theValue; }
		
		// Refer to the computational fluid dynamics by hoffmann vol.1 (p. 378, Eq. 9-57) [9/9/2023 Payvand]
		static TnbMeshBLayer_EXPORT Standard_Real
			CalcRate(const Standard_Real theBeta, const Standard_Real theEta);
	};
}

#endif
