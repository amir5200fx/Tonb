#pragma once
#ifndef _Geo_CosineDistb_Header
#define _Geo_CosineDistb_Header

#include <Geo_xDistb.hxx>
#include <Geo_Module.hxx>

namespace tnbLib
{

	class Geo_CosineDistb
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

		Geo_CosineDistb()
		{}

	public:

		Geo_CosineDistb(const Standard_Integer theSize)
			: theSize_(theSize)
		{}

		TnbGeo_EXPORT void Perform();
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_CosineDistb);

#endif // !_Geo_CosineDistb_Header
