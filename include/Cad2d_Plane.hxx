#pragma once
#ifndef _Cad2d_Plane_Header
#define _Cad2d_Plane_Header

#include <Global_AccessMethod.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Pln_Entity.hxx>
#include <Cad2d_Plane_Manager.hxx>
#include <Cad2d_Plane_Auxillary.hxx>
#include <OFstream.hxx>

#include <vector>

class gp_Ax22d;
class gp_Ax2d;
class gp_Trsf2d;

#include <gp.hxx>
#include <gp_Ax2.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;
	class Pln_Edge;
	class Pln_Curve;
	class Pln_Vertex;

	class Geo_ApprxCurve_Info;

	class Cad2d_Plane
		: public Pln_Entity
		, public cad2dLib::Plane_Auxillary
		, public cad2dLib::Plane_Manager
	{

		typedef std::vector<std::shared_ptr<Pln_Wire>> wireList;
		typedef std::shared_ptr<Pln_Wire> outer;
		typedef std::shared_ptr<wireList> inner;

		using cad2dLib::Plane_Auxillary::BoundingBox;

		/*Private Data*/	

		outer theOuter_;
		inner theInner_;


		//- private functions and operators

		void SetOuter(const outer&& theOuter);

		void SetInner(const inner&& theInner);

		std::shared_ptr<Entity2d_Box>
			CalcBoundingBox
			(
				const Standard_Real theTol
			) const;

		void Make
		(
			const outer& theOuter,
			const inner& theInners
		);

		void Make
		(
			const outer&& theOuter,
			const inner&& theInners
		);

		static void CheckOuter(const outer& theOuter, const char* theName);

		static void CheckInner(const std::shared_ptr<Pln_Wire>& theInner, const char* theName);

		static void CheckInners(const inner& theInner, const char* theName);

	public:

		Cad2d_Plane
		(
			const gp_Ax2& theSystem = gp::XOY()
		);

		Cad2d_Plane
		(
			const gp_Ax2&& theSystem
		);

		Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const gp_Ax2& theSystem = gp::XOY()
		);

		Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const gp_Ax2&& theSystem
		);

		Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const gp_Ax2& theSystem = gp::XOY()
		);

		Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const gp_Ax2&& theSystem
		);

	public:

		Standard_Integer NbWires() const;

		Standard_Integer NbFreeCorners() const;

		Standard_Integer NbHoles() const;

		Standard_Integer NbEntities(const Pln_EntityType t) const override;

		Standard_Boolean HasFreeCorner() const;

		Standard_Boolean IsOrphan() const override;

		std::tuple<Standard_Real, Standard_Real> 
			BoundTolerance() const;

		std::shared_ptr<Entity2d_Chain>
			Polygon() const;

		std::shared_ptr<Entity2d_Chain>
			MergedPolygon() const;

		Entity2d_Box BoundingBox
		(
			const Standard_Real Tol
		) const override;

		const outer& OuterWire() const;

		const inner& InnerWires() const;

		std::shared_ptr<Pln_Entity>
			Copy() const override;

		Pln_EntityType Type() const override;

		void Approx
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		void Transform
		(
			const gp_Trsf2d& t
		) override;

		void RetrieveWiresTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theWires
		) const;

		void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities, 
			const Pln_EntityType t
		) const override;

		void ExportToPlt
		(
			OFstream& File
		) const;

		//- Static functions

		static std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static void
			SplitByWires
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

		static const std::shared_ptr<Pln_Wire>& 
			RetrieveOuterWire
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static void
			CheckOuterWire
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static void
			CheckWires
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static std::shared_ptr<Cad2d_Plane> 
			MakeBox
			(
				const Pnt2d& theCorner, 
				const Standard_Real theDx, 
				const Standard_Real theDy,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static std::shared_ptr<Cad2d_Plane> 
			MakeBox
			(
				const Pnt2d& theP0, 
				const Pnt2d& theP1,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static std::shared_ptr<Cad2d_Plane> 
			MakeCircle
			(
				const gp_Ax22d& A, 
				const Standard_Real Radius
			);

		static std::shared_ptr<Cad2d_Plane> 
			MakeCircle
			(
				const gp_Ax2d& A,
				const Standard_Real Radius, 
				const Standard_Boolean Sense = Standard_True
			);

	};
}

#endif // !_Cad2d_Plane_Header
