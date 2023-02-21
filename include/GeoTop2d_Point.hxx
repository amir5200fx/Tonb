#pragma once
#ifndef _GeoTop2d_Point_Header
#define _GeoTop2d_Point_header

#include <Global_Serialization.hxx>
#include <Geo_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class GeoTop2d_Point
	{

		/*Private Data*/

		// Private functions and operators [2/17/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{}

	protected:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Point()
		{}

		// constructors [2/17/2023 Payvand]


	public:

		// Public functions and operators [2/17/2023 Payvand]

		virtual Standard_Boolean Is2d() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean Is3d() const
		{
			return Standard_False;
		}

		virtual std::shared_ptr<GeoTop2d_Point> Copy() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoTop2d_Point);

#endif // !_GeoTop2d_Point_Header
