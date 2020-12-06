#pragma once
#ifndef _LegModel_NozzelType1_Parameters_Header
#define _LegModel_NozzelType1_Parameters_Header

#include <Global_AccessMethod.hxx>
#include <LegModel_Parameter.hxx>
#include <CadModel_Module.hxx>

namespace tnbLib
{

	namespace nozzle
	{

		class NozzleType1_Dimensions
		{

			typedef LegModel_Parameter parameter;
			typedef std::shared_ptr<parameter> param_t;

			/*Private Data*/

			param_t theOverallLength_;
			param_t theThroat_;

			param_t theRadiusAtInlet_;
			param_t theRadiusAtOutlet_;
			param_t theRadiusAtThroat_;

		protected:

			TnbCadModel_EXPORT NozzleType1_Dimensions();

		public:

			//- Macros
			GLOBAL_ACCESS_SINGLE(param_t, OverallLength)
				GLOBAL_ACCESS_SINGLE(param_t, Throat)
				GLOBAL_ACCESS_SINGLE(param_t, RadiusAtInlet)
				GLOBAL_ACCESS_SINGLE(param_t, RadiusAtOutlet)
				GLOBAL_ACCESS_SINGLE(param_t, RadiusAtThroat)
				
		};

		class NozzleType1_ProfileParamsBase
		{

			typedef LegModel_Parameter parameter;
			typedef std::shared_ptr<parameter> param_t;

			/*Private Data*/

			param_t theInflection_;
			param_t theRadiusAtInflection_;
			param_t theOffsetAtThroat_;

			param_t theRounding1_;
			param_t theRounding2_;

			param_t theRoundingWeight1_;
			param_t theRoundingWeight2_;

		protected:

			NozzleType1_ProfileParamsBase()
			{}

		public:

			//- Macros
			GLOBAL_ACCESS_SINGLE(param_t, Inflection)
				GLOBAL_ACCESS_SINGLE(param_t, RadiusAtInflection)
				GLOBAL_ACCESS_SINGLE(param_t, OffsetAtThroat)
				GLOBAL_ACCESS_SINGLE(param_t, Rounding1)
				GLOBAL_ACCESS_SINGLE(param_t, Rounding2)
				GLOBAL_ACCESS_SINGLE(param_t, RoundingWeight1)
				GLOBAL_ACCESS_SINGLE(param_t, RoundingWeight2)

		};

		class NozzleType1_InletProfileParams
			: public NozzleType1_ProfileParamsBase
		{

			typedef LegModel_Parameter parameter;
			typedef std::shared_ptr<parameter> param_t;

			/*Private Data*/

			param_t theOffsetAtInlet_;

		protected:

			

		public:

			TnbCadModel_EXPORT NozzleType1_InletProfileParams();

			GLOBAL_ACCESS_SINGLE(param_t, OffsetAtInlet)
		};

		class NozzleType1_OutletProfileParams
			: public NozzleType1_ProfileParamsBase
		{

			typedef LegModel_Parameter parameter;
			typedef std::shared_ptr<parameter> param_t;

			/*Private Data*/

			param_t theTangentAtOutlet_;
			param_t theOffsetAtOutlet_;

		protected:

			

		public:

			TnbCadModel_EXPORT NozzleType1_OutletProfileParams();

			GLOBAL_ACCESS_SINGLE(param_t, TangentAtOutlet)
				GLOBAL_ACCESS_SINGLE(param_t, OffsetAtOutlet)
		};

		class NozzleType1_Params
			: public NozzleType1_Dimensions
		{

			/*Private Data*/

			std::shared_ptr<NozzleType1_InletProfileParams> theInlet_;
			std::shared_ptr<NozzleType1_OutletProfileParams> theOutlet_;

		public:

			TnbCadModel_EXPORT NozzleType1_Params();

			const auto& InletProfile() const
			{
				return theInlet_;
			}

			const auto& OutletProfile() const
			{
				return theOutlet_;
			}
		};
	}
}

#endif // !_LegModel_NozzelType1_Parameters_Header
