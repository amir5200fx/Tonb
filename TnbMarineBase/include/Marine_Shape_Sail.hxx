#pragma once
#ifndef _Marine_Model_Sail_Header
#define _Marine_Model_Sail_Header

#include <Marine_Shape.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Shape_Sail
			: public Marine_Shape
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_Shape>(*this);
			}

		public:

			template<class... _Types>
			Shape_Sail(_Types&&... _Args)
				: Marine_Shape(_Args...)
			{}

			Marine_ShapeType Type() const override
			{
				return Marine_ShapeType::sail;
			}

			Standard_Boolean IsSail() const override
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Model_Sail_Header
