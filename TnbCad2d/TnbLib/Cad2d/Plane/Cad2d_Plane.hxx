#pragma once
#ifndef _Cad2d_Plane_Header
#define _Cad2d_Plane_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Pln_Entity.hxx>
#include <Cad2d_Plane_Manager.hxx>
#include <Cad2d_Plane_Auxillary.hxx>
#include <Cad2d_Module.hxx>
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

		TNB_SERIALIZATION(TnbCad2d_EXPORT);


		auto& OuterWireRef()
		{
			return theOuter_;
		}

		auto& InnerWiresRef()
		{
			return theInner_;
		}

		TnbCad2d_EXPORT void SetOuter(const outer&& theOuter);

		TnbCad2d_EXPORT void SetInner(const inner&& theInner);

		std::shared_ptr<Entity2d_Box>
			CalcBoundingBox
			(
				const Standard_Real theTol
			) const;

		TnbCad2d_EXPORT void Make
		(
			const outer& theOuter,
			const inner& theInners
		);

		TnbCad2d_EXPORT void Make
		(
			const outer&& theOuter,
			const inner&& theInners
		);

		static TnbCad2d_EXPORT void CheckOuter(const outer& theOuter, const char* theName);

		static TnbCad2d_EXPORT void CheckInner(const std::shared_ptr<Pln_Wire>& theInner, const char* theName);

		static TnbCad2d_EXPORT void CheckInners(const inner& theInner, const char* theName);

	public:

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const gp_Ax2& theSystem = gp::XOY()
		);

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const gp_Ax2&& theSystem
		);

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const gp_Ax2& theSystem = gp::XOY()
		);

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const gp_Ax2&& theSystem
		);

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const gp_Ax2& theSystem = gp::XOY()
		);

		TnbCad2d_EXPORT Cad2d_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const gp_Ax2&& theSystem
		);

	public:

		TnbCad2d_EXPORT Standard_Integer NbWires() const;

		TnbCad2d_EXPORT Standard_Integer NbFreeCorners() const;

		TnbCad2d_EXPORT Standard_Integer NbHoles() const;

		TnbCad2d_EXPORT Standard_Integer NbEntities(const Pln_EntityType t) const override;

		TnbCad2d_EXPORT Standard_Boolean HasFreeCorner() const;

		TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT std::tuple<Standard_Real, Standard_Real>
			BoundTolerance() const;

		TnbCad2d_EXPORT std::shared_ptr<Entity2d_Chain>
			Polygon() const;

		TnbCad2d_EXPORT std::shared_ptr<Entity2d_Chain>
			MergedPolygon() const;

		TnbCad2d_EXPORT Entity2d_Box BoundingBox
		(
			const Standard_Real Tol
		) const override;

		TnbCad2d_EXPORT const outer& OuterWire() const;

		TnbCad2d_EXPORT const inner& InnerWires() const;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;

		TnbCad2d_EXPORT Pln_EntityType Type() const override;

		TnbCad2d_EXPORT void Approx
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		TnbCad2d_EXPORT void Transform
		(
			const gp_Trsf2d& t
		) override;

		TnbCad2d_EXPORT void RetrieveWiresTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theWires
		) const;

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities, 
			const Pln_EntityType t
		) const override;

		TnbCad2d_EXPORT void ExportToPlt
		(
			OFstream& File
		) const;

		//- Static functions

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT void
			SplitByWires
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

		static TnbCad2d_EXPORT const std::shared_ptr<Pln_Wire>&
			RetrieveOuterWire
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbCad2d_EXPORT void
			CheckOuterWire
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbCad2d_EXPORT void
			CheckWires
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeBox
			(
				const Pnt2d& theCorner, 
				const Standard_Real theDx, 
				const Standard_Real theDy,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeBox
			(
				const Pnt2d& theP0, 
				const Pnt2d& theP1,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane> 
			MakeBox
			(
				const gp_Ax2d& theAx,
				const Standard_Real theDx, 
				const Standard_Real theDy, 
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeCircle
			(
				const gp_Circ2d& C,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeCircle
			(
				const gp_Circ2d& C,
				const Pnt2d& theP,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeCircle
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeCircle
			(
				const Pnt2d& theC,
				const Standard_Real theRadius,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeCircle
			(
				const Pnt2d& theC,
				const Pnt2d& theP,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeEllipse
			(
				const gp_Elips2d& E,
				const gp_Ax2& theSystem = gp::XOY()
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakeEllipse
			(
				const Pnt2d& theS0,
				const Pnt2d& theS1,
				const Pnt2d& theCenter,
				const gp_Ax2& theSystem = gp::XOY()
			);

	};
}

#endif // !_Cad2d_Plane_Header
