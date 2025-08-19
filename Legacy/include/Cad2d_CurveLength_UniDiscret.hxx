#pragma once
#ifndef _Cad2d_CurveLength_UniDiscret_Header
#define _Cad2d_CurveLength_UniDiscret_Header

#include <Cad2d_CurveLength.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class CurveLength_UniDiscret
			: public Cad2d_CurveLength
		{

			/*Private Data*/

			Standard_Integer theNbSegments_;

		public:

			static TnbCad2d_EXPORT const Standard_Integer DEFAULT_NB_SEGMENTS;

			// default constructor [2/6/2022 Amir]

			CurveLength_UniDiscret()
				: theNbSegments_(DEFAULT_NB_SEGMENTS)
			{}

			// constructors [2/6/2022 Amir]

			explicit CurveLength_UniDiscret(const Standard_Integer theNbSegments)
				: theNbSegments_(theNbSegments)
			{}


			// override functions and operators [2/6/2022 Amir]

			TnbCad2d_EXPORT Standard_Real 
				CalcLength
				(
					const std::shared_ptr<Pln_Curve>&
				) const override;

			TnbCad2d_EXPORT Standard_Real 
				CalcLength
				(
					const std::shared_ptr<Pln_Curve>&, 
					const Standard_Real theLower,
					const Standard_Real theUpper
				) const override;

			// public functions and operators [2/6/2022 Amir]

			auto NbSegments() const
			{
				return theNbSegments_;
			}

			void SetNbSegments(const Standard_Integer theNbSegments)
			{
				theNbSegments_ = theNbSegments;
			}
			
		};
	}
}

#endif // !_Cad2d_CurveLength_UniDiscret_Header
