#pragma once
#ifndef _Voyage_OffsetProfile_Segment_Header
#define _Voyage_OffsetProfile_Segment_Header

#include <Voyage_OffsetProfile.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class Voyage_OffsetProfile_Segment
		: public Voyage_OffsetProfile
	{

		/*Private Data*/

	public:

		//- Default constructor

		Voyage_OffsetProfile_Segment()
		{}

		//- Constructors


		//- Public functions and operators

		TnbVoyage_EXPORT std::shared_ptr<Pln_Curve> Geometry(const Pnt2d& theP0, const Pnt2d& theP1) const override;

	};
}

#endif // !_Voyage_OffsetProfile_Segment_Header
