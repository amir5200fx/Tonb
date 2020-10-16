#pragma once
#ifndef _Geo_Naca4Digit_Header
#define _Geo_Naca4Digit_Header

#include <Global_Done.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_Naca4Digit
		: public Global_Done
	{

	public:

		struct Parameter
		{
			Standard_Integer nbSections;

			Standard_Real maxCamberLoc;
			Standard_Real maxCamber;
			Standard_Real maxThick;
			Standard_Real chord;
		};


	private:

		/*Private Data*/

		std::vector<Pnt2d> theUpper_;
		std::vector<Pnt2d> theLower_;

		Parameter theParameters_;	

		Standard_Boolean CloseTail = Standard_False;

		void SetDefaults();

		auto& UpperRef()
		{
			return theUpper_;
		}

		auto& LowerRef()
		{
			return theLower_;
		}

		static std::vector<Standard_Real> 
			CosDistb
			(
				const Standard_Integer n
			);

		static std::vector<Standard_Real>
			CalcCamberOffsets
			(
				const std::vector<Standard_Real>& x, 
				const Parameter& pars
			);

		static std::vector<Standard_Real> 
			CalcThicknessDistb
			(
				const std::vector<Standard_Real>& x, 
				const Parameter& pars
			);

		static std::vector<Standard_Real> 
			CalcCamberTangentDistb
			(
				const std::vector<Standard_Real>& x,
				const Parameter& pars
			);

	public:

		Geo_Naca4Digit()
		{
			SetDefaults();
		}

		Geo_Naca4Digit(Parameter&& theParameters)
			: theParameters_(std::move(theParameters))
		{}

		Geo_Naca4Digit(const Parameter& theParameters)
			: theParameters_(theParameters)
		{}

		const auto& Upper() const
		{
			return theUpper_;
		}

		const auto& Lower() const
		{
			return theLower_;
		}

		const auto& Parameters() const
		{
			return theParameters_;
		}

		auto& ParametersRef()
		{
			return theParameters_;
		}

		void Perform();

		void SetCloseTail(const Standard_Boolean close)
		{
			CloseTail = close;
		}
	};
}

#endif // !_Geo_Naca4Digit_Header
