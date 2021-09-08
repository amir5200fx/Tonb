#pragma once
#ifndef _ShapePx_TopoSectPole_Inter_Header
#define _ShapePx_TopoSectPole_Inter_Header

#include <ShapePx_TopoSectPole.hxx>
#include <ShapePx_TopoSectPole_InterAdaptor.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class TopoSectPole_Inter
			: public ShapePx_TopoSectPole
			, public TopoSectPole_InterAdaptor
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<ShapePx_TopoSectPole>(*this);
				ar & boost::serialization::base_object<TopoSectPole_InterAdaptor>(*this);
			}

		protected:

			//- default constructor

			TopoSectPole_Inter()
			{}


			//- constructors

			TopoSectPole_Inter(const Standard_Integer theIndex, const word& theName)
				: ShapePx_TopoSectPole(theIndex, theName)
			{}


			TopoSectPole_Inter
			(
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theCoord, theWeight)
			{}

			TopoSectPole_Inter
			(
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(std::move(theCoord), theWeight)
			{}

			TopoSectPole_Inter
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theIndex, theName, theCoord, theWeight)
			{}

			TopoSectPole_Inter
			(
				const Standard_Integer theIndex,
				const word& theName,
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theIndex, theName, std::move(theCoord), theWeight)
			{}

		public:

			//- public functions and operators

			Standard_Boolean IsInterior() const override
			{
				return Standard_True;
			}
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::shapePxLib::TopoSectPole_Inter);

#endif // !_ShapePx_TopoSectPole_Inter_Header
