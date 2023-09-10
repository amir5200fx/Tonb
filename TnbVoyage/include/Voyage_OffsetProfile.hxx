#pragma once
#ifndef _Voyage_OffsetProfile_Header
#define _Voyage_OffsetProfile_Header

#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class Pln_Curve;

	class Voyage_OffsetProfile
	{

		/*Private Data*/

	protected:

		//- default constructor

		Voyage_OffsetProfile()
		{}

		//- constructors

	public:

		//- Public functions and operators

		virtual std::shared_ptr<Pln_Curve> Geometry(const Pnt2d&, const Pnt2d&) const = 0;

	};

}

#endif // !_Voyage_OffsetProfile_Header
