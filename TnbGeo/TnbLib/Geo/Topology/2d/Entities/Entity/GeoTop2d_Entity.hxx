#pragma once
#ifndef _GeoTop2d_Entity_Header
#define _GeoTop2d_Entity_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	class GeoTop2d_Entity
		: public Global_Indexed
		, public std::enable_shared_from_this<GeoTop2d_Entity>
	{

		/*Private Data*/

		// Private functions and operators [2/17/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_versrion)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
		}

	protected:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Entity()
		{}

		// constructors [2/17/2023 Payvand]

		explicit GeoTop2d_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		virtual ~GeoTop2d_Entity()
		{}

		// Public functions and operators [2/17/2023 Payvand]

		auto This() const
		{
			return std::const_pointer_cast<GeoTop2d_Entity>(this->weak_from_this().lock());
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoTop2d_Entity);

#endif // !_GeoTop2d_Entity_Header
