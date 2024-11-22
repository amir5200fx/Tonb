#pragma once
#ifndef _Voyage_Profile_Header
#define _Voyage_Profile_Header

#include <Voyage_Module.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Geo_InterplFunction;

	class Voyage_Profile
	{

		/*Private Data*/

		std::shared_ptr<Geo_InterplFunction> theFunc_;

		Standard_Real theX0_;
		Standard_Real theX1_;

	public:

		// default constructor [7/11/2023 Payvand]
		

		// constructors [7/11/2023 Payvand]

		TnbVoyage_EXPORT Voyage_Profile(const std::shared_ptr<Geo_InterplFunction>& theFun);
		TnbVoyage_EXPORT Voyage_Profile(std::shared_ptr<Geo_InterplFunction>&& theFun);

		// Public functions and operators [7/11/2023 Payvand]

		const auto& GeoFun() const { return theFunc_; }

		TnbVoyage_EXPORT Standard_Real X0() const;
		TnbVoyage_EXPORT Standard_Real X1() const;

		inline Standard_Real Value0() const;
		inline Standard_Real Value1() const;

		TnbVoyage_EXPORT Standard_Real Value(const Standard_Real x) const;

	};
}

#include <Voyage_ProfileI.hxx>

#endif // !_Voyage_Profile_Header
