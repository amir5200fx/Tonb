#include <LegModel_NozzleType1_Parameters.hxx>

#include <LegModel_NozzleType1_Defaults.hxx>
#include <LegModel_ConstParameter.hxx>
#include <LegModel_BoundedParameter.hxx>

typedef tnbLib::LegModel_NozzleType1_Defaults DP;

#define Const_Param_Subt(x) x.Index(), x.Name(), x.Value()
#define Bounded_Param_Subt(x) x.Index(), x.Name(), x.Value(), 0, 1

#define new_Const_Param(x) std::make_shared<LegModel_ConstParameter>(Const_Param_Subt(x))
#define new_Bounded_Param(x) std::make_shared<LegModel_BoundedParameter>(Bounded_Param_Subt(x))

tnbLib::nozzle::NozzleType1_Dimensions::NozzleType1_Dimensions()
{
	theOverallLength_ = new_Const_Param(DP::OVERALL_LENGTH);
	theThroat_ = new_Bounded_Param(DP::THROAT_LOCATION);

	theRadiusAtInlet_ = new_Const_Param(DP::RADIUS_AT_INLET);
	theRadiusAtOutlet_ = new_Const_Param(DP::RADIUS_AT_OUTLET);
	theRadiusAtThroat_ = new_Bounded_Param(DP::RADIUS_AT_THROAT);
}

tnbLib::nozzle::NozzleType1_InletProfileParams::NozzleType1_InletProfileParams()
{
	Inflection() = new_Bounded_Param(DP::INLET_INFLECTION);
	RadiusAtInflection() = new_Bounded_Param(DP::INLET_RADIUS_AT_INFLECTION);
	OffsetAtThroat() = new_Bounded_Param(DP::INLET_OFFSET_AT_THROAT);
	Rounding1() = new_Bounded_Param(DP::INLET_ROUNDING_1);
	Rounding2() = new_Bounded_Param(DP::INLET_ROUNDING_2);
	RoundingWeight1() = new_Bounded_Param(DP::INLET_ROUNDING_WEIGHT1);
	RoundingWeight2() = new_Bounded_Param(DP::INLET_ROUNDING_WEIGHT2);

	theOffsetAtInlet_ = new_Bounded_Param(DP::INLET_OFFSET_AT_INLET);
}

tnbLib::nozzle::NozzleType1_OutletProfileParams::NozzleType1_OutletProfileParams()
{
	Inflection() = new_Bounded_Param(DP::OUTLET_INFLECTION);
	RadiusAtInflection() = new_Bounded_Param(DP::OUTLET_RADIUS_AT_INFLECTION);
	OffsetAtThroat() = new_Bounded_Param(DP::OUTLET_OFFSET_AT_THROAT);
	Rounding1() = new_Bounded_Param(DP::OUTLET_ROUNDING_1);
	Rounding2() = new_Bounded_Param(DP::OUTLET_ROUNDING_2);
	RoundingWeight1() = new_Bounded_Param(DP::OUTLET_ROUNDING_WEIGHT1);
	RoundingWeight2() = new_Bounded_Param(DP::OUTLET_ROUNDING_WEIGHT2);

	theTangentAtOutlet_ = new_Bounded_Param(DP::OUTLET_TANGENT_AT_OUTLET);
	theOffsetAtOutlet_ = new_Bounded_Param(DP::OUTLET_OFFSET_AT_OUTLET);
}

tnbLib::nozzle::NozzleType1_Params::NozzleType1_Params()
{
	theInlet_ = std::make_shared<NozzleType1_InletProfileParams>();
	theOutlet_ = std::make_shared<NozzleType1_OutletProfileParams>();
}