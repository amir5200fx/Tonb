#pragma once
#ifndef _VoyageField_Earth_Header
#define _VoyageField_Earth_Header

#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/22/2023 Payvand]
	class VoyageField_Current;

	class VoyageField_Earth
	{

		/*Private Data*/

		std::shared_ptr<VoyageField_Current> theCurrentField_;

	public:

		// default constructor [7/20/2023 Payvand]

		VoyageField_Earth()
		{}

		// constructors [7/20/2023 Payvand]


		// Public functions and operators [7/20/2023 Payvand]

		const auto& CurrentField() const { return theCurrentField_; }

		Standard_Boolean IsLand(const Pnt2d&) const { return Standard_True; }
		Standard_Boolean IsWater(const Pnt2d&) const { return Standard_True; }

		void SetCurrentField(const std::shared_ptr<VoyageField_Current>& theField) { theCurrentField_ = theField; }
		void SetCurrentField(std::shared_ptr<VoyageField_Current>&& theField) { theCurrentField_ = std::move(theField); }

	};
}

#endif // !_VoyageField_Earth_Header
