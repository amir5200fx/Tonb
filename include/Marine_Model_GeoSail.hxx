#pragma once
#ifndef _Marine_Model_GeoSail_Header
#define _Marine_Model_GeoSail_Header

#include <Marine_Model_Sail.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_GeoSail
			: public Model_Sail
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<Model_Sail>(*this);
			}

		protected:

			template<class... _Types>
			Model_GeoSail(_Types&&... _Args)
				: Model_Sail(_Args...)
			{}

		public:

			Standard_Boolean HasGeometry() const override
			{
				return Standard_True;
			}

			virtual Standard_Boolean IsPlanar() const
			{
				return Standard_False;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Model_GeoSail);

#endif // !_Marine_Model_GeoSail_Header
