#pragma once
#ifndef _ShapePx_TopoSectPole_Bnd_Header
#define _ShapePx_TopoSectPole_Bnd_Header

#include <ShapePx_TopoSectPole.hxx>
#include <ShapePx_TopoSectPole_BndAdaptor.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class TopoSectPole_Bnd
			: public ShapePx_TopoSectPole
			, public TopoSectPole_BndAdaptor
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<ShapePx_TopoSectPole>(*this);
				ar & boost::serialization::base_object<TopoSectPole_BndAdaptor>(*this);
			}

		public:

			//- default constructor

			TopoSectPole_Bnd()
			{}


			//- constructors

			TopoSectPole_Bnd(const Standard_Integer theIndex, const word& theName)
				: ShapePx_TopoSectPole(theIndex, theName)
			{}


			TopoSectPole_Bnd
			(
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theCoord, theWeight)
			{}

			TopoSectPole_Bnd
			(
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(std::move(theCoord), theWeight)
			{}

			TopoSectPole_Bnd
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Pnt2d& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theIndex, theName, theCoord, theWeight)
			{}

			TopoSectPole_Bnd
			(
				const Standard_Integer theIndex,
				const word& theName,
				Pnt2d&& theCoord,
				const Standard_Real theWeight
			)
				: ShapePx_TopoSectPole(theIndex, theName, std::move(theCoord), theWeight)
			{}


			//- public functions and operators

			Standard_Boolean IsBoundary() const override
			{
				return Standard_True;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::shapePxLib::TopoSectPole_Bnd);

#endif // !_ShapePx_TopoSectPole_Bnd_Header
