#pragma once
#ifndef _Ship_Dimens_Header
#define _Ship_Dimens_Header

#include <Ship_Parameter.hxx>

namespace tnbLib
{

	class Ship_Dimens
	{

		/*Private Data*/

		Ship_Parameter theDraft_;
		Ship_Parameter theTransomHeight_;

		Ship_Parameter theDepthAtBow_;
		Ship_Parameter theDepthAtTransom_;

		Ship_Parameter theBeamOnDeck_;
		Ship_Parameter theLengthOnDeck_;

		Standard_Integer theNbNetRows_;
		Standard_Integer theNbNetColumns_;

	public:

		// default constructor [11/1/2022 Amir]

		Ship_Dimens()
		{}

		// constructors [11/1/2022 Amir]

		const auto& Draft() const
		{
			return theDraft_;
		}

		auto& DraftRef()
		{
			return theDraft_;
		}

		const auto& TransomHeight() const
		{
			return theTransomHeight_;
		}

		auto& TransomHeightRef()
		{
			return theTransomHeight_;
		}

		const auto& DepthAtBow() const
		{
			return theDepthAtBow_;
		}

		auto& DepthAtBowRef()
		{
			return theDepthAtBow_;
		}

		const auto& DepthAtTransom() const
		{
			return theDepthAtTransom_;
		}

		auto& DepthAtTransomRef()
		{
			return theDepthAtTransom_;
		}

		const auto& BeamOnDeck() const
		{
			return theBeamOnDeck_;
		}

		auto& BeamOnDeckRef()
		{
			return theBeamOnDeck_;
		}

		const auto& LengthOnDeck() const
		{
			return theLengthOnDeck_;
		}

		auto& LengthOnDeckRef()
		{
			return theLengthOnDeck_;
		}

		auto NbNetRows() const
		{
			return theNbNetRows_;
		}

		auto NbNetColumns() const
		{
			return theNbNetColumns_;
		}

		void SetNbNetRows(const Standard_Integer n)
		{
			theNbNetRows_ = n;
		}

		void SetNbNetColumns(const Standard_Integer n)
		{
			theNbNetColumns_ = n;
		}
	};
}

#endif // !_Ship_Dimens_Header

