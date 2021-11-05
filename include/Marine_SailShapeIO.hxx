#pragma once
#ifndef _Marine_SailShapeIO_Header
#define _Marine_SailShapeIO_Header

#include <Marine_ShapeIO.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		namespace io
		{

			class SailShape
				: public Shape
			{

				/*Private Data*/


				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive& ar, const unsigned int /*file_version*/)
				{
					ar & boost::serialization::base_object<Shape>(*this);
				}

			public:

				//- default constructor

				SailShape()
				{}

				//- public functions and operators

			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::io::SailShape);

#endif // !_Marine_SailShapeIO_Header
