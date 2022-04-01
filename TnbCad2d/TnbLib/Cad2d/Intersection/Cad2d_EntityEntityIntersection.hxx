#pragma once
#ifndef _Cad2d_EntityEntityIntersection_Header
#define _Cad2d_EntityEntityIntersection_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>
#include <Global_AccessMethod.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_IntsctEntity;
	class Cad2d_IntsctEntity_Pair;

	class Cad2d_EntityEntityIntersection
		: public Global_Indexed
		, public Global_Named
		/*, public Global_Done*/
		, public std::enable_shared_from_this<Cad2d_EntityEntityIntersection>
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Cad2d_IntsctEntity_Pair>>
			theEntities_;

		Standard_Real theTolerance_;


		// private functions and operators [3/22/2022 Amir]

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:

		//- default constructor

		Cad2d_EntityEntityIntersection()
		{}

		//- constructors

		Cad2d_EntityEntityIntersection(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		Cad2d_EntityEntityIntersection(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbCad2d_EXPORT const std::string extension;

		//- public functions and operators


		auto NbEntities() const
		{
			return (Standard_Integer)theEntities_.size();
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Entities() const
		{
			return theEntities_;
		}

		auto& EntitiesRef()
		{
			return theEntities_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetEntities(const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Pair>>& theEntities)
		{
			theEntities_ = theEntities;
		}

		void SetEntities(std::vector<std::shared_ptr<Cad2d_IntsctEntity_Pair>>&& theEntities)
		{
			theEntities_ = std::move(theEntities);
		}

		// virtual functions and operators [2/4/2022 Amir]

		virtual Standard_Boolean IsEdgeEdge() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsVertexEdge() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsVertexVertex() const
		{
			return Standard_False;
		}



		//- Macros
		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad2d_EntityEntityIntersection);

#endif // !_Cad2d_EntityEntityIntersection_Header
