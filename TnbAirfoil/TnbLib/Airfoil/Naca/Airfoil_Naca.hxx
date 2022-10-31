#pragma once
#ifndef _Airfoil_Naca_Header
#define _Airfoil_Naca_Header

#include <Airfoil_Entity.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [10/30/2022 Amir]
	class Airfoil_NacaThickness;
	class Airfoil_NacaMidline;
	class Geo_xDistb;

	class Airfoil_Naca
		: public Global_Done
	{

		/*Private Data*/

		Standard_Real theChord_;

		std::shared_ptr<Airfoil_NacaMidline> theMidLine_;
		std::shared_ptr<Airfoil_NacaThickness> theThickness_;

		std::shared_ptr<Geo_xDistb> theXc_;


		// results [10/30/2022 Amir]

		std::vector<Pnt2d> theUpper_;
		std::vector<Pnt2d> theLower_;

		// Private functions and operators [10/30/2022 Amir]

		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcCamber(const std::vector<Standard_Real>& theXc) const;
		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcThickness(const std::vector<Standard_Real>& theXc) const;
		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcTangents(const std::vector<Standard_Real>& theXc, const std::vector<Standard_Real>& theYc) const;


		auto& UpperRef()
		{
			return theUpper_;
		}

		auto& LowerRef()
		{
			return theLower_;
		}

	public:

		// default constructor [10/30/2022 Amir]

		Airfoil_Naca()
			: theChord_(0)
		{}


		// constructors [10/30/2022 Amir]


		// public functions and operators [10/30/2022 Amir]

		auto Chord() const
		{
			return theChord_;
		}

		const auto& MidLine() const
		{
			return theMidLine_;
		}

		const auto& Thickness() const
		{
			return theThickness_;
		}

		const auto& Xc() const
		{
			return theXc_;
		}

		const auto& Lower() const
		{
			return theLower_;
		}

		const auto& Upper() const
		{
			return theUpper_;
		}

		TnbAirfoil_EXPORT void Perform();

		void SetChord(const Standard_Real theChord)
		{
			theChord_ = theChord;
		}

		void SetMidLine(const std::shared_ptr<Airfoil_NacaMidline>& theLine)
		{
			theMidLine_ = theLine;
		}

		void SetThickness(const std::shared_ptr<Airfoil_NacaThickness>& theProfile)
		{
			theThickness_ = theProfile;
		}

		void SetXc(const std::shared_ptr<Geo_xDistb>& theXc)
		{
			theXc_ = theXc;
		}
	};
}

#endif // !_Airfoil_Naca_Header
