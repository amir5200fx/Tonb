#pragma once
#ifndef _Cad2d_Modeler_Corner_Header
#define _Cad2d_Modeler_Corner_Header

#include <Pnt2d.hxx>
#include <Cad2d_Modeler_Entity.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;

	namespace cad2dLib
	{

		class Modeler_Corner
			: public Modeler_Entity
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
				theVertices_;

			Standard_Real theRadius_;
			Standard_Real theTol_;

			Pnt2d theCoord_;

		public:

			static const Standard_Real DEFAULT_RADIUS;

			typedef Pnt2d ptType;

			Modeler_Corner();

			Modeler_Corner
			(
				const Standard_Integer theIndex
			);

			Modeler_Corner
			(
				const Standard_Integer theIndex,
				const word& theName
			);


			auto NbVertices() const
			{
				return (Standard_Integer)theVertices_.size();
			}

			auto Radius() const
			{
				return theRadius_;
			}

			auto Tolerance() const
			{
				return theTol_;
			}

			const auto& Coord() const
			{
				return theCoord_;
			}

			const auto& Vertices() const
			{
				return theVertices_;
			}

			void SetRadius(const Standard_Real theR)
			{
				theRadius_ = theR;
			}

			void InsertToCorners
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			std::shared_ptr<Pln_Vertex> Remove(const Standard_Integer theIndex);

			std::shared_ptr<Pln_Entity> Copy() const override;
		};
	}


}

#endif // !_Cad2d_Modeler_Corner_Header
