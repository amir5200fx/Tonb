#pragma once
#ifndef _HydStatic_FloatBody_Header
#define _HydStatic_FloatBody_Header

#include <HydStatic_Entity.hxx>
#include <Marine_BodiesFwd.hxx>

namespace tnbLib
{


	class HydStatic_FloatBody
		: public HydStatic_Entity
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Body_Dry> theDry_;
		std::shared_ptr<marineLib::Body_Wetted> theWetted_;

	public:

		//- default constructor

		HydStatic_FloatBody()
		{}


		//- constructors

		HydStatic_FloatBody
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		HydStatic_FloatBody
		(
			const std::shared_ptr<marineLib::Body_Dry>& theDry,
			const std::shared_ptr<marineLib::Body_Wetted>& theWetted
		);

		HydStatic_FloatBody
		(
			std::shared_ptr<marineLib::Body_Dry>&& theDry,
			std::shared_ptr<marineLib::Body_Wetted>&& theWetted
		);

		HydStatic_FloatBody
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<marineLib::Body_Dry>& theDry, 
			const std::shared_ptr<marineLib::Body_Wetted>& theWetted
		);

		HydStatic_FloatBody
		(
			const Standard_Integer theIndex, 
			const word& theName,
			std::shared_ptr<marineLib::Body_Dry>&& theDry, 
			std::shared_ptr<marineLib::Body_Wetted>&& theWetted
		);


		//- public functions and operators

		const auto& Dry()const
		{
			return theDry_;
		}

		const auto& Wetted() const
		{
			return theWetted_;
		}

		void SetDry
		(
			const std::shared_ptr<marineLib::Body_Dry>& theBody
		)
		{
			theDry_ = theBody;
		}

		void SetWetted
		(
			const std::shared_ptr<marineLib::Body_Wetted>& theBody
		)
		{
			theWetted_ = theBody;
		}

		void SetDry
		(
			std::shared_ptr<marineLib::Body_Dry>&& theBody
		)
		{
			theDry_ = std::move(theBody);
		}

		void SetWetted
		(
			std::shared_ptr<marineLib::Body_Wetted>&& theBody
		)
		{
			theWetted_ = std::move(theBody);
		}
	};
}

#endif // !_HydStatic_FloatBody_Header
