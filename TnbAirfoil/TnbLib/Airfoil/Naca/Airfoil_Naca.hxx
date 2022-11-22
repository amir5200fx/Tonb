#pragma once
#ifndef _Airfoil_Naca_Header
#define _Airfoil_Naca_Header

#include <Airfoil_Entity.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <vector>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

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

		Standard_Real theTrim_;

		Standard_Real theChord_;
		Standard_Real theMaxThick_;

		std::shared_ptr<Airfoil_NacaMidline> theMidLine_;
		std::shared_ptr<Airfoil_NacaThickness> theThickness_;

		std::shared_ptr<Geo_xDistb> theXc_;

		Standard_Boolean ApplyTrim_;

		// results [10/30/2022 Amir]

		std::vector<Pnt2d> theUpper_;
		std::vector<Pnt2d> theLower_;

		// Private functions and operators [10/30/2022 Amir]

		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcCamber(const std::vector<Standard_Real>& theXc) const;
		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcThickness(const std::vector<Standard_Real>& theXc) const;
		TnbAirfoil_EXPORT std::pair<std::vector<Standard_Real>, Handle(Geom2d_Curve)> CalcTangents(const std::vector<Standard_Real>& theXc, const std::vector<Standard_Real>& theYc) const;

		static std::pair<Standard_Real, Standard_Real> CalcTangent(const Standard_Real x, const Handle(Geom2d_Curve)& theCurve);

		auto& UpperRef()
		{
			return theUpper_;
		}

		auto& LowerRef()
		{
			return theLower_;
		}

		TnbAirfoil_EXPORT std::vector<Pnt2d> 
			CalcThicknessOffsets
			(
				const std::vector<Standard_Real>& theXc,
				const std::vector<Standard_Real>& theYt
			) const;

		// the first parameter is the trimmed location on the curve, the second is 
		// the location of the centre of the circle and the third is the radius [11/19/2022 Amir]
		TnbAirfoil_EXPORT std::tuple<Pnt2d, Standard_Real, Standard_Real> 
			CalcRadius
			(
				const std::vector<Pnt2d>& theThickness
			) const;

		TnbAirfoil_EXPORT std::vector<Standard_Real> CalcXs() const;

		void TrimThickness();

	public:

		struct ioData
		{
			std::vector<Pnt2d> upper;
			std::vector<Pnt2d> lower;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar & upper;
				ar & lower;
			}

			static TnbAirfoil_EXPORT const word extension;
		};

		// default constructor [10/30/2022 Amir]

		Airfoil_Naca()
			: theChord_(0)
			, theMaxThick_(0)
			, theTrim_(0)
			, ApplyTrim_(Standard_False)
		{}


		// constructors [10/30/2022 Amir]


		// public functions and operators [10/30/2022 Amir]

		auto Chord() const
		{
			return theChord_;
		}

		auto Trim() const
		{
			return theTrim_;
		}

		auto ApplyTrim() const
		{
			return ApplyTrim_;
		}

		auto MaxThickness() const
		{
			return theMaxThick_;
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

		void SetMaxThickness(const Standard_Real theThick)
		{
			theMaxThick_ = theThick;
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

		void SetTrim(const Standard_Real theTrim)
		{
			theTrim_ = theTrim;
		}

		void SetApplyTrim(const Standard_Boolean theApply)
		{
			ApplyTrim_ = theApply;
		}
	};
}

#endif // !_Airfoil_Naca_Header
