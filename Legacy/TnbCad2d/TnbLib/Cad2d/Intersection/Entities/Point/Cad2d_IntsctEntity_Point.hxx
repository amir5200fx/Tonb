#pragma once
#ifndef _Cad2d_IntsctEntity_Point_Header
#define _Cad2d_IntsctEntity_Point_Header

#include <Cad2d_IntsctEntity.hxx>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;

	class Cad2d_IntsctEntity_Point
		: public Cad2d_IntsctEntity
	{

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVertex_;


		// private functions and operators [3/22/2022 Amir]

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:

		//- default constructor

		Cad2d_IntsctEntity_Point()
		{}


		// constructors [1/27/2022 Amir]

		explicit Cad2d_IntsctEntity_Point
		(
			const Standard_Integer theIndex
		)
			: Cad2d_IntsctEntity(theIndex)
		{}

		Cad2d_IntsctEntity_Point
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theVtx
		)
			: Cad2d_IntsctEntity(theIndex)
			, theVertex_(theVtx)
		{}

		Cad2d_IntsctEntity_Point
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Pln_Vertex>&& theVtx
		)
			: Cad2d_IntsctEntity(theIndex)
			, theVertex_(std::move(theVtx))
		{}

		Cad2d_IntsctEntity_Point
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Cad2d_IntsctEntity(theIndex, theName)
		{}

		//- public functions and operators

		const auto& ParentVertex() const
		{
			return theVertex_;
		}

		Standard_Boolean IsPoint() const override
		{
			return Standard_True;
		}

		void SetParentVertex(const std::shared_ptr<Pln_Vertex>& theVtx)
		{
			theVertex_ = theVtx;
		}

		void SetParentVertex(std::shared_ptr<Pln_Vertex>&& theVtx)
		{
			theVertex_ = std::move(theVtx);
		}

		//- Macros
		//GLOBAL_ACCESS_ONLY_SINGLE(std::shared_ptr<Pln_Vertex>, Vertex)

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad2d_IntsctEntity_Point);

#endif // !_Cad2d_IntsctEntity_Point_Header
