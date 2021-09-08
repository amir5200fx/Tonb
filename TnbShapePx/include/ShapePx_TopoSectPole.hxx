#pragma once
#ifndef _ShapePx_TopoSectPole_Header
#define _ShapePx_TopoSectPole_Header

#include <ShapePx_TopoSectEntity.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class ShapePx_TopoSectPole
		: public ShapePx_TopoSectEntity
	{

		/*Private Data*/

		Pnt2d theCoord_;

		Standard_Real theWeight_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<ShapePx_TopoSectEntity>(*this);

			ar & theCoord_;
			ar & theWeight_;
		}

	protected:


		//- default constructor

		ShapePx_TopoSectPole()
		{}


		//- constructors

		ShapePx_TopoSectPole(const Standard_Integer theIndex, const word& theName)
			: ShapePx_TopoSectEntity(theIndex, theName)
		{}


		ShapePx_TopoSectPole(const Pnt2d& theCoord, const Standard_Real theWeight)
			: theCoord_(theCoord)
			, theWeight_(theWeight)
		{}

		ShapePx_TopoSectPole(Pnt2d&& theCoord, const Standard_Real theWeight)
			: theCoord_(std::move(theCoord))
			, theWeight_(theWeight)
		{}

		ShapePx_TopoSectPole
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt2d& theCoord, 
			const Standard_Real theWeight
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theCoord_(theCoord)
			, theWeight_(theWeight)
		{}

		ShapePx_TopoSectPole
		(
			const Standard_Integer theIndex, 
			const word& theName,
			Pnt2d&& theCoord,
			const Standard_Real theWeight
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theCoord_(std::move(theCoord))
			, theWeight_(theWeight)
		{}

	public:

		//- public functions and operators

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto Weight() const
		{
			return theWeight_;
		}

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Pnt2d&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		void SetWeight(const Standard_Real theWeight)
		{
			theWeight_ = theWeight;
		}

		virtual Standard_Boolean IsInterior() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsBoundary() const
		{
			return Standard_False;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ShapePx_TopoSectPole);

#endif // !_ShapePx_TopoSectPole_Header
