#pragma once
#ifndef _HydStatic_SailShape_Header
#define _HydStatic_SailShape_Header

#include <HydStatic_Shape.hxx>

namespace tnbLib
{

	class HydStatic_SailShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Model_Sail> theSail_;


		Standard_Real theArea_;
		Standard_Real theZ_;

		
		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);

	public:

		//- default constructor

		HydStatic_SailShape()
		{}

		//- constructors

		explicit HydStatic_SailShape
		(
			const std::shared_ptr<marineLib::Model_Sail>& theModel
		)
			: theSail_(theModel)
		{}


		//- public functions and operators

		const auto& Sail() const
		{
			return theSail_;
		}

		auto LateralArea() const
		{
			return theArea_;
		}

		auto Z() const
		{
			return theZ_;
		}

		void SetLateralArea(const Standard_Real theArea)
		{
			theArea_ = theArea;
		}

		void SetZ(const Standard_Real theZ)
		{
			theZ_ = theZ;
		}

		void SetSail
		(
			const std::shared_ptr<marineLib::Model_Sail>& theModel
		)
		{
			theSail_ = theModel;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_SailShape);

#endif // !_HydStatic_SailShape_Header
