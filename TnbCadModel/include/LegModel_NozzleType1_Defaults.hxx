#pragma once
#ifndef _LegModel_NozzleType1_Defaults_Header
#define _LegModel_NozzleType1_Defaults_Header

#include <LegModel_ConstParameter.hxx>

namespace tnbLib
{

	class LegModel_NozzleType1_Defaults
	{

		typedef LegModel_ConstParameter param;

		/*Private Data*/

	public:

		static const param OVERALL_LENGTH;
		static const param THROAT_LOCATION;
		static const param RADIUS_AT_INLET;
		static const param RADIUS_AT_OUTLET;
		static const param RADIUS_AT_THROAT;


		static const param INLET_INFLECTION;
		static const param INLET_RADIUS_AT_INFLECTION;
		static const param INLET_OFFSET_AT_THROAT;
		static const param INLET_OFFSET_AT_INLET;
		static const param INLET_ROUNDING_1;
		static const param INLET_ROUNDING_2;
		static const param INLET_ROUNDING_WEIGHT1;
		static const param INLET_ROUNDING_WEIGHT2;

		static const param OUTLET_INFLECTION;
		static const param OUTLET_RADIUS_AT_INFLECTION;
		static const param OUTLET_OFFSET_AT_THROAT;
		static const param OUTLET_OFFSET_AT_OUTLET;
		static const param OUTLET_ROUNDING_1;
		static const param OUTLET_ROUNDING_2;
		static const param OUTLET_ROUNDING_WEIGHT1;
		static const param OUTLET_ROUNDING_WEIGHT2;
		static const param OUTLET_TANGENT_AT_OUTLET;


	};
}

#endif // !_LegModel_NozzleType1_Defaults_Header
