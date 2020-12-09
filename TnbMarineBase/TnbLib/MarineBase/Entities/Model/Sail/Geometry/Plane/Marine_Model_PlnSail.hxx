#pragma once
#ifndef _Marine_Model_PlnSail_Header
#define _Marine_Model_PlnSail_Header

#include <Marine_Model_GeoSail.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_PlnSail
			: public Model_GeoSail
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<Model_GeoSail>(*this);
			}

		protected:

			template<class... _Types>
			Model_PlnSail(_Types&&... _Args)
				: Model_GeoSail(_Args...)
			{}

		public:

			Standard_Boolean IsPlanar() const override
			{
				return Standard_True;
			}

			virtual Standard_Boolean IsTwoDimApprox() const
			{
				return Standard_False;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Model_PlnSail);

#endif // !_Marine_Model_PlnSail_Header
