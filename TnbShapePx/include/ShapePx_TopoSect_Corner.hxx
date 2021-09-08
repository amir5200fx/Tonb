#pragma once
#ifndef _ShapePx_TopoSect_Corner_Header
#define _ShapePx_TopoSect_Corner_Header

#include <ShapePx_TopoSectPole_Inter.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class TopoSect_Corner
			: public TopoSectPole_Inter
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<TopoSectPole_Inter>(*this);
			}

		public:

			//- default constructor

			TopoSect_Corner()
			{}


			//- constructors

			TopoSect_Corner(const Standard_Integer theIndex, const word& theName)
				: TopoSectPole_Inter(theIndex, theName)
			{}


			TopoSect_Corner
			(
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(theCoord, theWeight)
			{}

			TopoSect_Corner
			(
				Pnt2d&& theCoord, 
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(std::move(theCoord), theWeight)
			{}

			TopoSect_Corner
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(theIndex, theName, theCoord, theWeight)
			{}

			TopoSect_Corner
			(
				const Standard_Integer theIndex,
				const word& theName,
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(theIndex, theName, std::move(theCoord), theWeight)
			{}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::shapePxLib::TopoSect_Corner);

#endif // !_ShapePx_TopoSect_Corner_Header
