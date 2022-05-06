#pragma once
#ifndef _SectPx_Coord_Header
#define _SectPx_Coord_Header

#include <Pnt2d.hxx>
#include <SectPx_CoordAdaptor.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_Coord
		: public SectPx_CoordAdaptor
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			boost::serialization::base_object<SectPx_CoordAdaptor>(*this);
		}

	protected:

		// default constructor [4/27/2022 Amir]

		SectPx_Coord()
		{}


		// constructors [4/27/2022 Amir]

	public:


		// public functions and operators [4/27/2022 Amir]

		virtual Standard_Real xCoord() const = 0;

		virtual Standard_Real yCoord() const = 0;

		virtual Pnt2d Coord() const = 0;

		virtual Standard_Boolean IsComplete() const = 0;

		TnbSectPx_EXPORT virtual Standard_Boolean IsDatum() const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Coord);

#endif // !_SectPx_Coord_Header
