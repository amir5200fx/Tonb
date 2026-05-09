#pragma once
#ifndef _Ship_Profile_Header
#define _Ship_Profile_Header

#include <Ship_Entity.hxx>

class Geom2d_Curve;

#include <Standard_Handle.hxx>

namespace tnbLib
{

	class Ship_Profile
		: public Ship_Entity
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theGeometry_;

	public:

		// default constructor [10/31/2022 Amir]


		// constructors [10/31/2022 Amir]

		Ship_Profile(const Handle(Geom2d_Curve)& theGeometry)
			: theGeometry_(theGeometry)
		{}

		Ship_Profile
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theGeometry
		)
			: Ship_Entity(theIndex, theName)
			, theGeometry_(theGeometry)
		{}


		// public functions and operators [10/31/2022 Amir]

		Standard_Real CalcValue(const Standard_Real x) const;

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		void SetGeometry(const Handle(Geom2d_Curve)& theGeometry)
		{
			theGeometry_ = theGeometry;
		}
	};
}

#endif // !_Ship_Profile_Header
