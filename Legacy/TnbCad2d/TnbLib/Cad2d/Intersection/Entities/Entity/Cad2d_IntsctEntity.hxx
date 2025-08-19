#pragma once
#ifndef _Cad2d_IntsctEntity_Header
#define _Cad2d_IntsctEntity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad2d_IntsctEntity_Adaptor.hxx>
#include <Cad2d_Module.hxx>

#include <memory>

namespace tnbLib
{

	class Cad2d_IntsctEntity
		: public Global_Indexed
		, public Global_Named
		, public Cad2d_IntsctEntity_Adaptor
		, public std::enable_shared_from_this<Cad2d_IntsctEntity>
	{

		/*Private Data*/


		// private functions and operators [3/22/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
			ar& boost::serialization::base_object<Global_Named>(*this);
			ar& boost::serialization::base_object<Cad2d_IntsctEntity_Adaptor>(*this);
		}

	protected:


		//- default constructor

		Cad2d_IntsctEntity()
		{}


		//- constructors

		Cad2d_IntsctEntity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		Cad2d_IntsctEntity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:


		//- public functions and operators

		virtual ~Cad2d_IntsctEntity()
		{}

		virtual Standard_Boolean IsPoint() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSegment() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cad2d_IntsctEntity);

#endif // !_Cad2d_IntsctEntity_Header
