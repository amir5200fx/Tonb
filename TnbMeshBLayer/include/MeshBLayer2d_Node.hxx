#pragma once
#ifndef _MeshBLayer2d_Node_Header
#define _MeshBLayer2d_Node_Header

#include <MeshBLayer2d_NodeAdaptor.hxx>
#include <MeshBLayer2d_Entity.hxx>
#include <Pnt2d.hxx>
#include <Vec2d.hxx>

namespace tnbLib
{

	class MeshBLayer2d_Node
		: public MeshBLayer2d_Entity
		, public MeshBLayer2d_NodeAdaptor
	{

		/*Private Data*/

		Standard_Integer theWireId_;

		Pnt2d theCoord_;
		Vec2d theNormal_;

	public:

		typedef Pnt2d ptType;

		// default constructor [1/30/2023 Payvand]

		MeshBLayer2d_Node()
			: theWireId_(0)
		{}


		// constructors [1/30/2023 Payvand]

		MeshBLayer2d_Node
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: MeshBLayer2d_Entity(theIndex)
			, theCoord_(theCoord)
			, theWireId_(0)
		{}

		MeshBLayer2d_Node
		(
			const Standard_Integer theIndex,
			Pnt2d&& theCoord
		)
			: MeshBLayer2d_Entity(theIndex)
			, theCoord_(std::move(theCoord))
			, theWireId_(0)
		{}


		// Public functions and operators [1/30/2023 Payvand]

		virtual Standard_Boolean IsBoundary() const;
		virtual Standard_Boolean IsInner() const;

		auto WireId() const
		{
			return theWireId_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

		const auto& Normal() const
		{
			return theNormal_;
		}

		auto& NormalRef()
		{
			return theNormal_;
		}

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Pnt2d&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		void SetNormal(const Vec2d& theNormal)
		{
			theNormal_ = theNormal;
		}

		void SetNormal(Vec2d&& theNormal)
		{
			theNormal_ = std::move(theNormal);
		}

		void SetWireId(const Standard_Integer theId)
		{
			theWireId_ = theId;
		}
	};
}

#endif // !_MeshBLayer2d_Node_Header
