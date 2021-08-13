#pragma once
#ifndef _Geo_UniDistb_Header
#define _Geo_UniDistb_Header

#include <Geo_xDistb.hxx>
#include <Geo_Module.hxx>

namespace tnbLib
{

	class Geo_UniDistb
		: public Geo_xDistb
	{

		/*Private Data*/

		Standard_Integer theSize_;


		//- Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo_xDistb>(*this);
			ar & theSize_;
		}


	protected:

		//- default constructor

		Geo_UniDistb()
		{}

	public:

		Geo_UniDistb(const Standard_Integer theSize)
			: theSize_(theSize)
		{}

		TnbGeo_EXPORT void Perform();


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_UniDistb);

#endif // !_Geo_UniDistb_Header
