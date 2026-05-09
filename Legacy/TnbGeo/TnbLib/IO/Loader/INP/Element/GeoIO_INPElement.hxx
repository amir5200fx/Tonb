#pragma once
#ifndef _GeoIO_INPElement_Header
#define _GeoIO_INPElement_Header

#include <Geo_Module.hxx>
#include <Global_Indexed.hxx>
#include <Global_TypeDef.hxx>
#include <Istream.hxx>
#include <word.hxx>

#include <vector>

namespace tnbLib
{

	class GeoIO_INPElement
		: public Global_Indexed
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
		}

	protected:

		// default constructor [9/5/2023 aamir]

		GeoIO_INPElement()
		{}

		// constructors [9/5/2023 aamir]

		GeoIO_INPElement(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

	public:

		virtual word ElementType() const = 0;

		virtual Standard_Integer NbPoints() const = 0;
		virtual std::vector<Standard_Integer> RetrieveIndices() const = 0;

	};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoIO_INPElement);

#endif // !_GeoIO_INPElement_Header
