#pragma once
#ifndef _Cad2d_Modeler_Corner_Header
#define _Cad2d_Modeler_Corner_Header

#include <Pnt2d.hxx>
#include <Cad2d_Modeler_Entity.hxx>
#include <Cad2d_Modeler_CornerAdaptor.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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
			, public Modeler_CornerAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
				theVertices_;

			Standard_Real theRadius_;
			Standard_Real theTol_;

			Pnt2d theCoord_;


			/*private functions and operators*/
			TNB_SERIALIZATION(TnbCad2d_EXPORT);

			auto& ChangeVertices()
			{
				return theVertices_;
			}

			auto& ChangeRadius()
			{
				return theRadius_;
			}

			auto& ChangeTolerance()
			{
				return theTol_;
			}

			auto& ChangeCoord()
			{
				return theCoord_;
			}

		public:

			using Modeler_CornerAdaptor::IsContains;

			static TnbCad2d_EXPORT const Standard_Real DEFAULT_RADIUS;

			typedef Pnt2d ptType;

			TnbCad2d_EXPORT Modeler_Corner();

			TnbCad2d_EXPORT Modeler_Corner
			(
				const Standard_Integer theIndex
			);

			TnbCad2d_EXPORT Modeler_Corner
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			~Modeler_Corner()
			{
				theVertices_.clear();
			}

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

			TnbCad2d_EXPORT Standard_Boolean
				IsContains
				(
					const std::shared_ptr<Pln_Vertex>& theVtx
				) const;

			Pnt2d CalcMeanCoord() const;

			void SetRadius(const Standard_Real theR)
			{
				theRadius_ = theR;
			}

			void SetTolerance(const Standard_Real theTol)
			{
				theTol_ = theTol;
			}

			TnbCad2d_EXPORT void InsertToCorners
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> Remove(const Standard_Integer theIndex);

			TnbCad2d_EXPORT std::shared_ptr<Modeler_Entity> Copy() const;


			static const Pnt2d& GetCoord
			(
				const std::shared_ptr<Modeler_Corner>& theEnt
			)
			{
				Debug_Null_Pointer(theEnt);
				return theEnt->Coord();
			}

			static Standard_Boolean 
				IsLess
				(
					const std::shared_ptr<Modeler_Corner>& theC0, 
					const std::shared_ptr<Modeler_Corner>& theC1
				)
			{
				Debug_Null_Pointer(theC0);
				Debug_Null_Pointer(theC1);
				return theC0->Index() < theC1->Index();
			}
		};
	}


}

#endif // !_Cad2d_Modeler_Corner_Header
