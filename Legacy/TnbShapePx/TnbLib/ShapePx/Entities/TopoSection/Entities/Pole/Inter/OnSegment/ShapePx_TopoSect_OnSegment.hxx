#pragma once
#ifndef _ShapePx_TopoSect_OnSegment_Header
#define _ShapePx_TopoSect_OnSegment_Header

#include <ShapePx_TopoSectPole_Inter.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class TopoSect_OnSegment
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

			TopoSect_OnSegment()
			{}


			//- constructors

			TopoSect_OnSegment(const Standard_Integer theIndex, const word& theName)
				: TopoSectPole_Inter(theIndex, theName)
			{}


			TopoSect_OnSegment
			(
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(theCoord, theWeight)
			{}

			TopoSect_OnSegment
			(
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(std::move(theCoord), theWeight)
			{}

			TopoSect_OnSegment
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: TopoSectPole_Inter(theIndex, theName, theCoord, theWeight)
			{}

			TopoSect_OnSegment
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

BOOST_CLASS_EXPORT_KEY(tnbLib::shapePxLib::TopoSect_OnSegment);

#endif // !_ShapePx_TopoSect_OnSegment_Header
