#pragma once
#ifndef _Marine_Model_AreaSail_Header
#define _Marine_Model_AreaSail_Header

#include <Pnt2d.hxx>
#include <Marine_Model_Sail.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_AreaSail
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
			Model_AreaSail(_Types&&... _Args)
				: Model_Sail(_Args...)
			{}

		public:


		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Model_AreaSail);

#endif // !_Marine_Model_AreaSail_Header
