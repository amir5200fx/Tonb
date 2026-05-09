#include <UnitSystem.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#define UNIT_EXPONENTS_Imp(Unit, Exp0, Exp1, Exp2, Exp3, Exp4, Exp5, Exp6)		\
//constexpr int Unit##UnitExps::MASS = Exp0;											\
//constexpr int Unit##UnitExps::LENGTH = Exp1;										\
//constexpr int Unit##UnitExps::TIME = Exp2;											\
//constexpr int Unit##UnitExps::TEMPERATURE = Exp3;									\
//constexpr int Unit##UnitExps::MOLES = Exp4;											\
//constexpr int Unit##UnitExps::CURRENT = Exp5;										\
//constexpr int Unit##UnitExps::LUMINOUS_INTENSITY = Exp6; 

namespace tnbLib
{

	string toString(const UnitSystem_Length unit)
	{
		switch (unit)
		{
		case UnitSystem_Length_cm: return "cm";
		case UnitSystem_Length_ft: return "ft";
		case UnitSystem_Length_in: return "in";
		case UnitSystem_Length_km: return "km";
		case UnitSystem_Length_m: return "m";
		case UnitSystem_Length_mi: return "mi";
		case UnitSystem_Length_mm: return "mm";
		case UnitSystem_Length_um: return "um";
		case UnitSystem_Length_yd: return "yd";
		}

		FatalErrorIn("string toString(const UnitSystem_Length unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Mass unit)
	{
		switch (unit)
		{
		case UnitSystem_Mass_g: return "g";
		case UnitSystem_Mass_ImperialTonne: return "LT";
		case UnitSystem_Mass_kg: return "kg";
		case UnitSystem_Mass_lb: return "lb";
		case UnitSystem_Mass_mg: return "mg";
		case UnitSystem_Mass_oz: return "oz";
		case UnitSystem_Mass_tonne: return "t";
		case UnitSystem_Mass_usTonne: return "ST";
		}

		FatalErrorIn("string toString(const UnitSystem_Mass unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Pressure unit)
	{
		switch (unit)
		{
		case UnitSystem_Pressure_atm: return "atm";
		case UnitSystem_Pressure_bar: return "bar";
		case UnitSystem_Pressure_GPa: return "GPa";
		case UnitSystem_Pressure_MPa: return "MPa";
		case UnitSystem_Pressure_Pa: return "Pa";
		case UnitSystem_Pressure_psi: return "psi";
		}

		FatalErrorIn("string toString(const UnitSystem_Pressure unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Velocity unit)
	{
		switch (unit)
		{
		case UnitSystem_Velocity_ftPerSec: return "ft/s";
		case UnitSystem_Velocity_kmPerHour: return "km/h";
		case UnitSystem_Velocity_kn: return "kn";
		case UnitSystem_Velocity_kt: return "kt";
		case UnitSystem_Velocity_mPerSec: return "m/s";
		case UnitSystem_Velocity_mph: return "mph";
		}

		FatalErrorIn("string toString(const UnitSystem_Velocity unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Acceleration unit)
	{
		switch (unit)
		{
		case UnitSystem_Acceleration_ftPerSecPerSec: return "ft/sec";
		case UnitSystem_Acceleration_mPerSecPerSec: return "m/sec";
		}

		FatalErrorIn("string toString(const UnitSystem_Acceleration unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Density unit)
	{
		switch (unit)
		{
		case UnitSystem_Density_kgPerMeterQubic: return "kg/m^3";
		case UnitSystem_Density_lbPerFtQubic: return "lb/ft^3";
		case UnitSystem_Density_lbPerInchQubic: return "lb/in^3";
		case UnitSystem_Density_SlugPerFtQubic: return "slug/ft^3";
		}

		FatalErrorIn("string toString(const UnitSystem_Density unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Power unit)
	{
		switch (unit)
		{
		case UnitSystem_Power_ftlbPerMin: return "ft*lb/min";
		case UnitSystem_Power_ftlbPerSec: return "ft*lb/sec";
		case UnitSystem_Power_hp: return "hp";
		case UnitSystem_Power_kW: return "kW";
		case UnitSystem_Power_MW: return "MW";
		case UnitSystem_Power_W: return "W";
		}

		FatalErrorIn("string toString(const UnitSystem_Power unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Temperature unit)
	{
		switch (unit)
		{
		case UnitSystem_Temperature_C: return "C";
		case UnitSystem_Temperature_F: return "F";
		case UnitSystem_Temperature_K: return "K";
		case UnitSystem_Temperature_R: return "R";
		}

		FatalErrorIn("string toString(const UnitSystem_Temperature unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Force unit)
	{
		switch (unit)
		{
		case UnitSystem_Force_dyn: return "dyn";
		case UnitSystem_Force_gf: return "gf";
		case UnitSystem_Force_kgf: return "kgf";
		case UnitSystem_Force_kN: return "kN";
		case UnitSystem_Force_lbf: return "lbf";
		case UnitSystem_Force_lbftPerSecPerSec: return "lb*ft/sec^2";
		case UnitSystem_Force_N: return "N";
		case UnitSystem_Force_tf: return "tf";
		}

		FatalErrorIn("string toString(const UnitSystem_Force unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_Angle unit)
	{
		switch (unit)
		{
		case UnitSystem_Angle_deg: return "deg";
		case UnitSystem_Angle_grad: return "grad";
		case UnitSystem_Angle_rad: return "rad";
		}

		FatalErrorIn("string toString(const UnitSystem_Angle unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_DynViscosity unit)
	{
		switch (unit)
		{
		case UnitSystem_DynViscosity_gPerCmPerSec: return "g/(cm*sec)";
		case UnitSystem_DynViscosity_lbPerFtPerSec: return "lb/(ft*sec)";
		case UnitSystem_DynViscosity_NSecPerSquareMeter: return "N*sec/m^2";
		case UnitSystem_DynViscosity_PaSec: return "Pa*sec";
		case UnitSystem_DynViscosity_slugPerFtPerSec: return "slup/(ft*sec)";
		}

		FatalErrorIn("string toString(const UnitSystem_DynViscosity unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}

	string toString(const UnitSystem_KinViscosity unit)
	{
		switch (unit)
		{
		case UnitSystem_KinViscosity_squareFtPerSec: return "ft^2/sec";
		case UnitSystem_KinViscosity_squareMeterPerSec: return "m^2/sec";
		}

		FatalErrorIn("string toString(const UnitSystem_KinViscosity unit)")
			<< " Invalid unit type"
			<< abort(FatalError);
		return "";
	}
}

namespace tnbLib
{
	namespace Convertor
	{

		const scalar Length<0, 0>::value = (scalar)1.0;
		const scalar Length<0, 1>::value = (scalar)100.0;
		const scalar Length<0, 2>::value = (scalar)3.28084;
		const scalar Length<0, 3>::value = (scalar)39.3701;
		const scalar Length<0, 4>::value = (scalar)0.001;
		const scalar Length<0, 5>::value = (scalar)0.000621371;
		const scalar Length<0, 6>::value = (scalar)1000.0;
		const scalar Length<0, 7>::value = (scalar)1000000.0;
		const scalar Length<0, 8>::value = (scalar)1.09361;

		const scalar Length<1, 0>::value = (scalar)0.01;
		const scalar Length<1, 1>::value = (scalar)1.0;
		const scalar Length<1, 2>::value = (scalar)0.0328084;
		const scalar Length<1, 3>::value = (scalar)0.393701;
		const scalar Length<1, 4>::value = (scalar)0.00001;
		const scalar Length<1, 5>::value = (scalar)0.00000621371;
		const scalar Length<1, 6>::value = (scalar)10.0;
		const scalar Length<1, 7>::value = (scalar)10000.0;
		const scalar Length<1, 8>::value = (scalar)0.0109361;

		const scalar Length<2, 0>::value = (scalar)0.3048;
		const scalar Length<2, 1>::value = (scalar)30.48;
		const scalar Length<2, 2>::value = (scalar)1.0;
		const scalar Length<2, 3>::value = (scalar)12.0;
		const scalar Length<2, 4>::value = (scalar)0.0003048;
		const scalar Length<2, 5>::value = (scalar)0.000189394;
		const scalar Length<2, 6>::value = (scalar)304.8;
		const scalar Length<2, 7>::value = (scalar)304800;
		const scalar Length<2, 8>::value = (scalar)0.333333;

		const scalar Length<3, 0>::value = (scalar)0.0254;
		const scalar Length<3, 1>::value = (scalar)2.54;
		const scalar Length<3, 2>::value = (scalar)0.0833333;
		const scalar Length<3, 3>::value = (scalar)1.0;
		const scalar Length<3, 4>::value = (scalar)2.54e-5;
		const scalar Length<3, 5>::value = (scalar)1.5783e-5;
		const scalar Length<3, 6>::value = (scalar)25.4;
		const scalar Length<3, 7>::value = (scalar)25400;
		const scalar Length<3, 8>::value = (scalar)0.0277778;

		const scalar Length<4, 0>::value = (scalar)1000.0;
		const scalar Length<4, 1>::value = (scalar)100000.0;
		const scalar Length<4, 2>::value = (scalar)3280.84;
		const scalar Length<4, 3>::value = (scalar)39370.1;
		const scalar Length<4, 4>::value = (scalar)1.0;
		const scalar Length<4, 5>::value = (scalar)0.621371;
		const scalar Length<4, 6>::value = (scalar)1e+6;
		const scalar Length<4, 7>::value = (scalar)1e+9;
		const scalar Length<4, 8>::value = (scalar)1093.61;

		const scalar Length<5, 0>::value = (scalar)1609.34;
		const scalar Length<5, 1>::value = (scalar)160934.0;
		const scalar Length<5, 2>::value = (scalar)5280.0;
		const scalar Length<5, 3>::value = (scalar)63360.0;
		const scalar Length<5, 4>::value = (scalar)1.60934;
		const scalar Length<5, 5>::value = (scalar)1.0;
		const scalar Length<5, 6>::value = (scalar)1.609e+6;
		const scalar Length<5, 7>::value = (scalar)1.609e+9;
		const scalar Length<5, 8>::value = (scalar)1760.0;

		const scalar Length<6, 0>::value = (scalar)0.001;
		const scalar Length<6, 1>::value = (scalar)0.1;
		const scalar Length<6, 2>::value = (scalar)0.00328084;
		const scalar Length<6, 3>::value = (scalar)0.0393701;
		const scalar Length<6, 4>::value = (scalar)1e-6;
		const scalar Length<6, 5>::value = (scalar)6.2137e-7;
		const scalar Length<6, 6>::value = (scalar)1.0;
		const scalar Length<6, 7>::value = (scalar)1000.0;
		const scalar Length<6, 8>::value = (scalar)0.00109361;

		const scalar Length<7, 0>::value = (scalar)1e-6;
		const scalar Length<7, 1>::value = (scalar)1e-4;
		const scalar Length<7, 2>::value = (scalar)3.2808e-6;
		const scalar Length<7, 3>::value = (scalar)3.937e-5;
		const scalar Length<7, 4>::value = (scalar)1e-9;
		const scalar Length<7, 5>::value = (scalar)6.2137e-10;
		const scalar Length<7, 6>::value = (scalar)0.001;
		const scalar Length<7, 7>::value = (scalar)1.0;
		const scalar Length<7, 8>::value = (scalar)1.0936e-6;

		const scalar Length<8, 0>::value = (scalar)0.9144;
		const scalar Length<8, 1>::value = (scalar)91.44;
		const scalar Length<8, 2>::value = (scalar)3.0;
		const scalar Length<8, 3>::value = (scalar)36.0;
		const scalar Length<8, 4>::value = (scalar)0.0009144;
		const scalar Length<8, 5>::value = (scalar)0.000568182;
		const scalar Length<8, 6>::value = (scalar)914.4;
		const scalar Length<8, 7>::value = (scalar)9.144e+8;
		const scalar Length<8, 8>::value = (scalar)1.0;


		const scalar Mass<0, 0>::value = (scalar)1.0;
		const scalar Mass<0, 1>::value = (scalar)0.001;
		const scalar Mass<0, 2>::value = (scalar)1000.0;
		const scalar Mass<0, 3>::value = (scalar)1e+6;
		const scalar Mass<0, 4>::value = (scalar)0.00110231;
		const scalar Mass<0, 5>::value = (scalar)0.000984207;
		const scalar Mass<0, 6>::value = (scalar)2.20462;
		const scalar Mass<0, 7>::value = (scalar)35.274;

		const scalar Mass<1, 0>::value = (scalar)1000.0;
		const scalar Mass<1, 1>::value = (scalar)1.0;
		const scalar Mass<1, 2>::value = (scalar)1e+6;
		const scalar Mass<1, 3>::value = (scalar)1e+9;
		const scalar Mass<1, 4>::value = (scalar)1.10231;
		const scalar Mass<1, 5>::value = (scalar)0.984207;
		const scalar Mass<1, 6>::value = (scalar)2204.62;
		const scalar Mass<1, 7>::value = (scalar)35274.0;

		const scalar Mass<2, 0>::value = (scalar)0.001;
		const scalar Mass<2, 1>::value = (scalar)1e-6;
		const scalar Mass<2, 2>::value = (scalar)1.0;
		const scalar Mass<2, 3>::value = (scalar)1000.0;
		const scalar Mass<2, 4>::value = (scalar)1.1023e-6;
		const scalar Mass<2, 5>::value = (scalar)9.8421e-7;
		const scalar Mass<2, 6>::value = (scalar)0.00220462;
		const scalar Mass<2, 7>::value = (scalar)0.035274;

		const scalar Mass<3, 0>::value = (scalar)1e-6;
		const scalar Mass<3, 1>::value = (scalar)1e-9;
		const scalar Mass<3, 2>::value = (scalar)0.001;
		const scalar Mass<3, 3>::value = (scalar)1.0;
		const scalar Mass<3, 4>::value = (scalar)1.1023e-9;
		const scalar Mass<3, 5>::value = (scalar)9.8421e-10;
		const scalar Mass<3, 6>::value = (scalar)2.2046e-6;
		const scalar Mass<3, 7>::value = (scalar)3.5274e-5;

		const scalar Mass<4, 0>::value = (scalar)907.185;
		const scalar Mass<4, 1>::value = (scalar)0.907185;
		const scalar Mass<4, 2>::value = (scalar)907185.0;
		const scalar Mass<4, 3>::value = (scalar)9.072e+8;
		const scalar Mass<4, 4>::value = (scalar)1.0;
		const scalar Mass<4, 5>::value = (scalar)0.892857;
		const scalar Mass<4, 6>::value = (scalar)2000.0;
		const scalar Mass<4, 7>::value = (scalar)32000.0;

		const scalar Mass<5, 0>::value = (scalar)1016.05;
		const scalar Mass<5, 1>::value = (scalar)1.01605;
		const scalar Mass<5, 2>::value = (scalar)1.016e+6;
		const scalar Mass<5, 3>::value = (scalar)1.016e+9;
		const scalar Mass<5, 4>::value = (scalar)1.12;
		const scalar Mass<5, 5>::value = (scalar)1.0;
		const scalar Mass<5, 6>::value = (scalar)2240.0;
		const scalar Mass<5, 7>::value = (scalar)35840.0;

		const scalar Mass<6, 0>::value = (scalar)0.453592;
		const scalar Mass<6, 1>::value = (scalar)0.000453592;
		const scalar Mass<6, 2>::value = (scalar)453.592;
		const scalar Mass<6, 3>::value = (scalar)453592.0;
		const scalar Mass<6, 4>::value = (scalar)0.0005;
		const scalar Mass<6, 5>::value = (scalar)0.000446429;
		const scalar Mass<6, 6>::value = (scalar)1.0;
		const scalar Mass<6, 7>::value = (scalar)16.0;

		const scalar Mass<7, 0>::value = (scalar)0.0283495;
		const scalar Mass<7, 1>::value = (scalar)2.835e-5;
		const scalar Mass<7, 2>::value = (scalar)28.3495;
		const scalar Mass<7, 3>::value = (scalar)28349.5;
		const scalar Mass<7, 4>::value = (scalar)3.125e-5;
		const scalar Mass<7, 5>::value = (scalar)2.7902e-5;
		const scalar Mass<7, 6>::value = (scalar)0.0625;
		const scalar Mass<7, 7>::value = (scalar)1.0;


		const scalar Pressure<0, 0>::value = (scalar)1.0;
		const scalar Pressure<0, 1>::value = (scalar)1.01325;
		const scalar Pressure<0, 2>::value = (scalar)101325.0;
		const scalar Pressure<0, 3>::value = (scalar)0.101325;
		const scalar Pressure<0, 4>::value = (scalar)0.000101325;
		const scalar Pressure<0, 5>::value = (scalar)14.69594880285;

		const scalar Pressure<1, 0>::value = (scalar)0.98692326671601;
		const scalar Pressure<1, 1>::value = (scalar)1.0;
		const scalar Pressure<1, 2>::value = (scalar)100000.0;
		const scalar Pressure<1, 3>::value = (scalar)0.1;
		const scalar Pressure<1, 4>::value = (scalar)0.0001;
		const scalar Pressure<1, 5>::value = (scalar)14.5037738;

		const scalar Pressure<2, 0>::value = (scalar)0.0000098692326671601;
		const scalar Pressure<2, 1>::value = (scalar)0.000010;
		const scalar Pressure<2, 2>::value = (scalar)1.0;
		const scalar Pressure<2, 3>::value = (scalar)0.0000010;
		const scalar Pressure<2, 4>::value = (scalar)0.0000000010;
		const scalar Pressure<2, 5>::value = (scalar)0.000145037738;

		const scalar Pressure<3, 0>::value = (scalar)9.8692326671601;
		const scalar Pressure<3, 1>::value = (scalar)10.0;
		const scalar Pressure<3, 2>::value = (scalar)1000000.0;
		const scalar Pressure<3, 3>::value = (scalar)1.0;
		const scalar Pressure<3, 4>::value = (scalar)0.001;
		const scalar Pressure<3, 5>::value = (scalar)145.037738;

		const scalar Pressure<4, 0>::value = (scalar)9869.2326671601;
		const scalar Pressure<4, 1>::value = (scalar)10000.0;
		const scalar Pressure<4, 2>::value = (scalar)1000000000.0;
		const scalar Pressure<4, 3>::value = (scalar)1000000.0;
		const scalar Pressure<4, 4>::value = (scalar)1.0;
		const scalar Pressure<4, 5>::value = (scalar)145.037738;

		const scalar Pressure<5, 0>::value = (scalar)0.068045963783303;
		const scalar Pressure<5, 1>::value = (scalar)0.068947572803431;
		const scalar Pressure<5, 2>::value = (scalar)6894.7572803431;
		const scalar Pressure<5, 3>::value = (scalar)0.0068947572803431;
		const scalar Pressure<5, 4>::value = (scalar)0.0000068947572803431;
		const scalar Pressure<5, 5>::value = (scalar)1.0;


		const scalar Velocity<0, 0>::value = (scalar)1.0;
		const scalar Velocity<0, 1>::value = (scalar)3.6;
		const scalar Velocity<0, 2>::value = (scalar)3.2808398950131;
		const scalar Velocity<0, 3>::value = (scalar)2.2369362920544;
		const scalar Velocity<0, 4>::value = (scalar)1.9426025694156;
		const scalar Velocity<0, 5>::value = (scalar)1.9438444924406;

		const scalar Velocity<1, 0>::value = (scalar)0.27777777777778;
		const scalar Velocity<1, 1>::value = (scalar)1.0;
		const scalar Velocity<1, 2>::value = (scalar)0.91134441528142;
		const scalar Velocity<1, 3>::value = (scalar)0.62137119223733;
		const scalar Velocity<1, 4>::value = (scalar)0.53961182483767;
		const scalar Velocity<1, 5>::value = (scalar)0.53995680345572;

		const scalar Velocity<2, 0>::value = (scalar)0.3048;
		const scalar Velocity<2, 1>::value = (scalar)1.09728;
		const scalar Velocity<2, 2>::value = (scalar)1.0;
		const scalar Velocity<2, 3>::value = (scalar)0.68181818181818;
		const scalar Velocity<2, 4>::value = (scalar)0.59210526315787;
		const scalar Velocity<2, 5>::value = (scalar)0.5924838012959;

		const scalar Velocity<3, 0>::value = (scalar)0.44704;
		const scalar Velocity<3, 1>::value = (scalar)1.609344;
		const scalar Velocity<3, 2>::value = (scalar)1.4666666666667;
		const scalar Velocity<3, 3>::value = (scalar)1.0;
		const scalar Velocity<3, 4>::value = (scalar)0.86842105263155;
		const scalar Velocity<3, 5>::value = (scalar)0.86897624190065;

		const scalar Velocity<4, 0>::value = (scalar)0.51477333333335;
		const scalar Velocity<4, 1>::value = (scalar)1.8531840000001;
		const scalar Velocity<4, 2>::value = (scalar)1.6888888888889;
		const scalar Velocity<4, 3>::value = (scalar)1.1515151515152;
		const scalar Velocity<4, 4>::value = (scalar)1.0;
		const scalar Velocity<4, 5>::value = (scalar)1.0006393088553;

		const scalar Velocity<5, 0>::value = (scalar)0.51444444444444;
		const scalar Velocity<5, 1>::value = (scalar)1.852;
		const scalar Velocity<5, 2>::value = (scalar)1.6878098571012;
		const scalar Velocity<5, 3>::value = (scalar)1.1507794480235;
		const scalar Velocity<5, 4>::value = (scalar)0.99936109959936;
		const scalar Velocity<5, 5>::value = (scalar)1.0;


		const scalar Acceleration<0, 0>::value = (scalar)1.0;
		const scalar Acceleration<0, 1>::value = (scalar)3.2808398950131;

		const scalar Acceleration<1, 0>::value = (scalar)0.3048;
		const scalar Acceleration<1, 1>::value = (scalar)1.0;


		const scalar Density<0, 0>::value = (scalar)1.0;
		const scalar Density<0, 1>::value = (scalar)0.062427961;
		const scalar Density<0, 2>::value = (scalar)0.000036127;
		const scalar Density<0, 3>::value = (scalar)0.00194032;

		const scalar Density<1, 0>::value = (scalar)16.018463374;
		const scalar Density<1, 1>::value = (scalar)1.0;
		const scalar Density<1, 2>::value = (scalar)0.000578704;
		const scalar Density<1, 3>::value = (scalar)0.03108095;

		const scalar Density<2, 0>::value = (scalar)27679.904710191;
		const scalar Density<2, 1>::value = (scalar)1728.0;
		const scalar Density<2, 2>::value = (scalar)1.0;
		const scalar Density<2, 3>::value = (scalar)53.707881896;

		const scalar Density<3, 0>::value = (scalar)515.378818393;
		const scalar Density<3, 1>::value = (scalar)32.174048556;
		const scalar Density<3, 2>::value = (scalar)0.018619241;
		const scalar Density<3, 3>::value = (scalar)1.0;


		const scalar Power<0, 0>::value = (scalar)1.0;
		const scalar Power<0, 1>::value = (scalar)0.001;
		const scalar Power<0, 2>::value = (scalar)0.0000010;
		const scalar Power<0, 3>::value = (scalar)0.73756214927727;
		const scalar Power<0, 4>::value = (scalar)44.253728956636;
		const scalar Power<0, 5>::value = (scalar)0.001341022089595;

		const scalar Power<1, 0>::value = (scalar)1000.0;
		const scalar Power<1, 1>::value = (scalar)1.0;
		const scalar Power<1, 2>::value = (scalar)0.001;
		const scalar Power<1, 3>::value = (scalar)737.56214927727;
		const scalar Power<1, 4>::value = (scalar)44253.728956636;
		const scalar Power<1, 5>::value = (scalar)1.341022089595;

		const scalar Power<2, 0>::value = (scalar)1000000.0;
		const scalar Power<2, 1>::value = (scalar)1000.0;
		const scalar Power<2, 2>::value = (scalar)1.0;
		const scalar Power<2, 3>::value = (scalar)737562.14927726;
		const scalar Power<2, 4>::value = (scalar)44253728.956636;
		const scalar Power<2, 5>::value = (scalar)1341.022089595;

		const scalar Power<3, 0>::value = (scalar)1.3558179483314;
		const scalar Power<3, 1>::value = (scalar)0.0013558179483314;
		const scalar Power<3, 2>::value = (scalar)0.0000013558179483314;
		const scalar Power<3, 3>::value = (scalar)1.0;
		const scalar Power<3, 4>::value = (scalar)60.0;
		const scalar Power<3, 5>::value = (scalar)0.0018181818181818;

		const scalar Power<4, 0>::value = (scalar)0.022596965805523;
		const scalar Power<4, 1>::value = (scalar)0.000022596965805523;
		const scalar Power<4, 2>::value = (scalar)0.000000022596965805523;
		const scalar Power<4, 3>::value = (scalar)0.016666666666667;
		const scalar Power<4, 4>::value = (scalar)1.0;
		const scalar Power<4, 5>::value = (scalar)0.00003030303030303;

		const scalar Power<5, 0>::value = (scalar)745.69987158227;
		const scalar Power<5, 1>::value = (scalar)0.74569987158227;
		const scalar Power<5, 2>::value = (scalar)0.00074569987158227;
		const scalar Power<5, 3>::value = (scalar)550.0;
		const scalar Power<5, 4>::value = (scalar)33000.0;
		const scalar Power<5, 5>::value = (scalar)1.0;


		const scalar Force<0, 0>::value = (scalar)1.0;
		const scalar Force<0, 1>::value = (scalar)0.001;
		const scalar Force<0, 2>::value = (scalar)100000.0;
		const scalar Force<0, 3>::value = (scalar)101.971621298;
		const scalar Force<0, 4>::value = (scalar)0.101971621;
		const scalar Force<0, 5>::value = (scalar)0.000101972;
		const scalar Force<0, 6>::value = (scalar)0.224808943;
		const scalar Force<0, 7>::value = (scalar)7.233013851;

		const scalar Force<1, 0>::value = (scalar)1000.0;
		const scalar Force<1, 1>::value = (scalar)1.0;
		const scalar Force<1, 2>::value = (scalar)100000000.0;
		const scalar Force<1, 3>::value = (scalar)101971.62129779;
		const scalar Force<1, 4>::value = (scalar)101.971621298;
		const scalar Force<1, 5>::value = (scalar)0.101971621;
		const scalar Force<1, 6>::value = (scalar)224.8089431;
		const scalar Force<1, 7>::value = (scalar)7233.01385121;

		const scalar Force<2, 0>::value = (scalar)0.00001;
		const scalar Force<2, 1>::value = (scalar)0.00000001;
		const scalar Force<2, 2>::value = (scalar)1.0;
		const scalar Force<2, 3>::value = (scalar)0.001019716;
		const scalar Force<2, 4>::value = (scalar)0.00000102;
		const scalar Force<2, 5>::value = (scalar)0.000000001;
		const scalar Force<2, 6>::value = (scalar)0.000002248;
		const scalar Force<2, 7>::value = (scalar)0.00007233;

		const scalar Force<3, 0>::value = (scalar)0.00980665;
		const scalar Force<3, 1>::value = (scalar)0.000009807;
		const scalar Force<3, 2>::value = (scalar)980.665;
		const scalar Force<3, 3>::value = (scalar)1.0;
		const scalar Force<3, 4>::value = (scalar)0.001;
		const scalar Force<3, 5>::value = (scalar)0.000001;
		const scalar Force<3, 6>::value = (scalar)0.002204623;
		const scalar Force<3, 7>::value = (scalar)0.070931635;

		const scalar Force<4, 0>::value = (scalar)9.80665;
		const scalar Force<4, 1>::value = (scalar)0.00980665;
		const scalar Force<4, 2>::value = (scalar)980665.0;
		const scalar Force<4, 3>::value = (scalar)1000.0;
		const scalar Force<4, 4>::value = (scalar)1.0;
		const scalar Force<4, 5>::value = (scalar)0.001;
		const scalar Force<4, 6>::value = (scalar)2.204622622;
		const scalar Force<4, 7>::value = (scalar)70.931635284;

		const scalar Force<5, 0>::value = (scalar)9806.65;
		const scalar Force<5, 1>::value = (scalar)9.80665;
		const scalar Force<5, 2>::value = (scalar)980665000.0;
		const scalar Force<5, 3>::value = (scalar)1000000.0;
		const scalar Force<5, 4>::value = (scalar)1000.0;
		const scalar Force<5, 5>::value = (scalar)1.0;
		const scalar Force<5, 6>::value = (scalar)2204.622621852;
		const scalar Force<5, 7>::value = (scalar)70931.635283967;

		const scalar Force<6, 0>::value = (scalar)4.448221615;
		const scalar Force<6, 1>::value = (scalar)0.004448222;
		const scalar Force<6, 2>::value = (scalar)444822.16152548;
		const scalar Force<6, 3>::value = (scalar)453.592369999;
		const scalar Force<6, 4>::value = (scalar)0.45359237;
		const scalar Force<6, 5>::value = (scalar)0.000453592;
		const scalar Force<6, 6>::value = (scalar)1.0;
		const scalar Force<6, 7>::value = (scalar)32.174048556;

		const scalar Force<7, 0>::value = (scalar)0.138254954;
		const scalar Force<7, 1>::value = (scalar)0.000138255;
		const scalar Force<7, 2>::value = (scalar)13825.4954376;
		const scalar Force<7, 3>::value = (scalar)14.09808185;
		const scalar Force<7, 4>::value = (scalar)0.014098082;
		const scalar Force<7, 5>::value = (scalar)0.000014098;
		const scalar Force<7, 6>::value = (scalar)0.03108095;
		const scalar Force<7, 7>::value = (scalar)1.0;


		const scalar Angle<0, 0>::value = (scalar)1.0;
		const scalar Angle<0, 1>::value = (scalar)0.017453293;
		const scalar Angle<0, 2>::value = (scalar)1.111111111;

		const scalar Angle<1, 0>::value = (scalar)57.295779513;
		const scalar Angle<1, 1>::value = (scalar)1.0;
		const scalar Angle<1, 2>::value = (scalar)63.661977237;

		const scalar Angle<2, 0>::value = (scalar)0.9;
		const scalar Angle<2, 1>::value = (scalar)0.015707963;
		const scalar Angle<2, 2>::value = (scalar)1.0;


		const scalar DynViscosity<0, 0>::value = (scalar)1.0;
		const scalar DynViscosity<0, 1>::value = (scalar)1.0;
		const scalar DynViscosity<0, 2>::value = (scalar)10.0;
		const scalar DynViscosity<0, 3>::value = (scalar)0.020885434;
		const scalar DynViscosity<0, 4>::value = (scalar)0.671968975;

		const scalar DynViscosity<1, 0>::value = (scalar)1.0;
		const scalar DynViscosity<1, 1>::value = (scalar)1.0;
		const scalar DynViscosity<1, 2>::value = (scalar)10.0;
		const scalar DynViscosity<1, 3>::value = (scalar)0.020885434;
		const scalar DynViscosity<1, 4>::value = (scalar)0.671968975;

		const scalar DynViscosity<2, 0>::value = (scalar)0.1;
		const scalar DynViscosity<2, 1>::value = (scalar)0.1;
		const scalar DynViscosity<2, 2>::value = (scalar)1.0;
		const scalar DynViscosity<2, 3>::value = (scalar)0.002088543;
		const scalar DynViscosity<2, 4>::value = (scalar)0.067196898;

		const scalar DynViscosity<3, 0>::value = (scalar)47.88025898;
		const scalar DynViscosity<3, 1>::value = (scalar)47.88025898;
		const scalar DynViscosity<3, 2>::value = (scalar)478.802589802;
		const scalar DynViscosity<3, 3>::value = (scalar)1.0;
		const scalar DynViscosity<3, 4>::value = (scalar)32.174048556;

		const scalar DynViscosity<4, 0>::value = (scalar)1.488163944;
		const scalar DynViscosity<4, 1>::value = (scalar)1.488163944;
		const scalar DynViscosity<4, 2>::value = (scalar)14.881639436;
		const scalar DynViscosity<4, 3>::value = (scalar)0.03108095;
		const scalar DynViscosity<4, 4>::value = (scalar)1.0;



		const scalar KinViscosity<0, 0>::value = (scalar)1.0;
		const scalar KinViscosity<0, 1>::value = (scalar)10.763910417;

		const scalar KinViscosity<1, 0>::value = (scalar)0.09290304;
		const scalar KinViscosity<1, 1>::value = (scalar)1.0;
	}


	const scalar ConvertorTables::Length[9][9] =
	{
		{Convertor::Length<0,0>::value, Convertor::Length<0,1>::value, Convertor::Length<0,2>::value,Convertor::Length<0,3>::value, Convertor::Length<0,4>::value, Convertor::Length<0,5>::value, Convertor::Length<0,6>::value, Convertor::Length<0,7>::value, Convertor::Length<0,8>::value},
		{Convertor::Length<1,0>::value, Convertor::Length<1,1>::value, Convertor::Length<1,2>::value,Convertor::Length<1,3>::value, Convertor::Length<1,4>::value, Convertor::Length<1,5>::value, Convertor::Length<1,6>::value, Convertor::Length<1,7>::value, Convertor::Length<1,8>::value},
		{Convertor::Length<2,0>::value, Convertor::Length<2,1>::value, Convertor::Length<2,2>::value,Convertor::Length<2,3>::value, Convertor::Length<2,4>::value, Convertor::Length<2,5>::value, Convertor::Length<2,6>::value, Convertor::Length<2,7>::value, Convertor::Length<2,8>::value},
		{Convertor::Length<3,0>::value, Convertor::Length<3,1>::value, Convertor::Length<3,2>::value,Convertor::Length<3,3>::value, Convertor::Length<3,4>::value, Convertor::Length<3,5>::value, Convertor::Length<3,6>::value, Convertor::Length<3,7>::value, Convertor::Length<3,8>::value},
		{Convertor::Length<4,0>::value, Convertor::Length<4,1>::value, Convertor::Length<4,2>::value,Convertor::Length<4,3>::value, Convertor::Length<4,4>::value, Convertor::Length<4,5>::value, Convertor::Length<4,6>::value, Convertor::Length<4,7>::value, Convertor::Length<4,8>::value},
		{Convertor::Length<5,0>::value, Convertor::Length<5,1>::value, Convertor::Length<5,2>::value,Convertor::Length<5,3>::value, Convertor::Length<5,4>::value, Convertor::Length<5,5>::value, Convertor::Length<5,6>::value, Convertor::Length<5,7>::value, Convertor::Length<5,8>::value},
		{Convertor::Length<6,0>::value, Convertor::Length<6,1>::value, Convertor::Length<6,2>::value,Convertor::Length<6,3>::value, Convertor::Length<6,4>::value, Convertor::Length<6,5>::value, Convertor::Length<6,6>::value, Convertor::Length<6,7>::value, Convertor::Length<6,8>::value},
		{Convertor::Length<7,0>::value, Convertor::Length<7,1>::value, Convertor::Length<7,2>::value,Convertor::Length<7,3>::value, Convertor::Length<7,4>::value, Convertor::Length<7,5>::value, Convertor::Length<7,6>::value, Convertor::Length<7,7>::value, Convertor::Length<7,8>::value},
		{Convertor::Length<8,0>::value, Convertor::Length<8,1>::value, Convertor::Length<8,2>::value,Convertor::Length<8,3>::value, Convertor::Length<8,4>::value, Convertor::Length<8,5>::value, Convertor::Length<8,6>::value, Convertor::Length<8,7>::value, Convertor::Length<8,8>::value}
	};

	const scalar ConvertorTables::Mass[8][8] =
	{
		{Convertor::Mass<0,0>::value, Convertor::Mass<0,1>::value, Convertor::Mass<0,2>::value, Convertor::Mass<0,3>::value, Convertor::Mass<0,4>::value, Convertor::Mass<0,5>::value, Convertor::Mass<0,6>::value, Convertor::Mass<0,7>::value},
		{Convertor::Mass<1,0>::value, Convertor::Mass<1,1>::value, Convertor::Mass<1,2>::value, Convertor::Mass<1,3>::value, Convertor::Mass<1,4>::value, Convertor::Mass<1,5>::value, Convertor::Mass<1,6>::value, Convertor::Mass<1,7>::value},
		{Convertor::Mass<2,0>::value, Convertor::Mass<2,1>::value, Convertor::Mass<2,2>::value, Convertor::Mass<2,3>::value, Convertor::Mass<2,4>::value, Convertor::Mass<2,5>::value, Convertor::Mass<2,6>::value, Convertor::Mass<2,7>::value},
		{Convertor::Mass<3,0>::value, Convertor::Mass<3,1>::value, Convertor::Mass<3,2>::value, Convertor::Mass<3,3>::value, Convertor::Mass<3,4>::value, Convertor::Mass<3,5>::value, Convertor::Mass<3,6>::value, Convertor::Mass<3,7>::value},
		{Convertor::Mass<4,0>::value, Convertor::Mass<4,1>::value, Convertor::Mass<4,2>::value, Convertor::Mass<4,3>::value, Convertor::Mass<4,4>::value, Convertor::Mass<4,5>::value, Convertor::Mass<4,6>::value, Convertor::Mass<4,7>::value},
		{Convertor::Mass<5,0>::value, Convertor::Mass<5,1>::value, Convertor::Mass<5,2>::value, Convertor::Mass<5,3>::value, Convertor::Mass<5,4>::value, Convertor::Mass<5,5>::value, Convertor::Mass<5,6>::value, Convertor::Mass<5,7>::value},
		{Convertor::Mass<6,0>::value, Convertor::Mass<6,1>::value, Convertor::Mass<6,2>::value, Convertor::Mass<6,3>::value, Convertor::Mass<6,4>::value, Convertor::Mass<6,5>::value, Convertor::Mass<6,6>::value, Convertor::Mass<6,7>::value},
		{Convertor::Mass<7,0>::value, Convertor::Mass<7,1>::value, Convertor::Mass<7,2>::value, Convertor::Mass<7,3>::value, Convertor::Mass<7,4>::value, Convertor::Mass<7,5>::value, Convertor::Mass<7,6>::value, Convertor::Mass<7,7>::value}
	};

	const scalar ConvertorTables::Pressure[6][6] =
	{
		{Convertor::Pressure<0,0>::value, Convertor::Pressure<0,1>::value, Convertor::Pressure<0,2>::value, Convertor::Pressure<0,3>::value, Convertor::Pressure<0,4>::value, Convertor::Pressure<0,5>::value},
		{Convertor::Pressure<1,0>::value, Convertor::Pressure<1,1>::value, Convertor::Pressure<1,2>::value, Convertor::Pressure<1,3>::value, Convertor::Pressure<1,4>::value, Convertor::Pressure<1,5>::value},
		{Convertor::Pressure<2,0>::value, Convertor::Pressure<2,1>::value, Convertor::Pressure<2,2>::value, Convertor::Pressure<2,3>::value, Convertor::Pressure<2,4>::value, Convertor::Pressure<2,5>::value},
		{Convertor::Pressure<3,0>::value, Convertor::Pressure<3,1>::value, Convertor::Pressure<3,2>::value, Convertor::Pressure<3,3>::value, Convertor::Pressure<3,4>::value, Convertor::Pressure<3,5>::value},
		{Convertor::Pressure<4,0>::value, Convertor::Pressure<4,1>::value, Convertor::Pressure<4,2>::value, Convertor::Pressure<4,3>::value, Convertor::Pressure<4,4>::value, Convertor::Pressure<4,5>::value},
		{Convertor::Pressure<5,0>::value, Convertor::Pressure<5,1>::value, Convertor::Pressure<5,2>::value, Convertor::Pressure<5,3>::value, Convertor::Pressure<5,4>::value, Convertor::Pressure<5,5>::value}
	};

	const scalar ConvertorTables::Velocity[6][6] =
	{
		{Convertor::Velocity<0,0>::value, Convertor::Velocity<0,1>::value, Convertor::Velocity<0,2>::value, Convertor::Velocity<0,3>::value, Convertor::Velocity<0,4>::value, Convertor::Velocity<0,5>::value},
		{Convertor::Velocity<1,0>::value, Convertor::Velocity<1,1>::value, Convertor::Velocity<1,2>::value, Convertor::Velocity<1,3>::value, Convertor::Velocity<1,4>::value, Convertor::Velocity<1,5>::value},
		{Convertor::Velocity<2,0>::value, Convertor::Velocity<2,1>::value, Convertor::Velocity<2,2>::value, Convertor::Velocity<2,3>::value, Convertor::Velocity<2,4>::value, Convertor::Velocity<2,5>::value},
		{Convertor::Velocity<3,0>::value, Convertor::Velocity<3,1>::value, Convertor::Velocity<3,2>::value, Convertor::Velocity<3,3>::value, Convertor::Velocity<3,4>::value, Convertor::Velocity<3,5>::value},
		{Convertor::Velocity<4,0>::value, Convertor::Velocity<4,1>::value, Convertor::Velocity<4,2>::value, Convertor::Velocity<4,3>::value, Convertor::Velocity<4,4>::value, Convertor::Velocity<4,5>::value},
		{Convertor::Velocity<5,0>::value, Convertor::Velocity<5,1>::value, Convertor::Velocity<5,2>::value, Convertor::Velocity<5,3>::value, Convertor::Velocity<5,4>::value, Convertor::Velocity<5,5>::value}
	};

	const scalar ConvertorTables::Acceleration[2][2] =
	{
		{Convertor::Acceleration<0,0>::value, Convertor::Acceleration<0,1>::value},
		{Convertor::Acceleration<1,0>::value, Convertor::Acceleration<1,1>::value}
	};

	const scalar ConvertorTables::Density[4][4] =
	{
		{Convertor::Density<0,0>::value, Convertor::Density<0,1>::value, Convertor::Density<0,2>::value, Convertor::Density<0,3>::value},
		{Convertor::Density<1,0>::value, Convertor::Density<1,1>::value, Convertor::Density<1,2>::value, Convertor::Density<1,3>::value},
		{Convertor::Density<2,0>::value, Convertor::Density<2,1>::value, Convertor::Density<2,2>::value, Convertor::Density<2,3>::value},
		{Convertor::Density<3,0>::value, Convertor::Density<3,1>::value, Convertor::Density<3,2>::value, Convertor::Density<3,3>::value}
	};

	const scalar ConvertorTables::Power[5][5] =
	{
		{Convertor::Power<0,1>::value, Convertor::Power<0,2>::value, Convertor::Power<0,3>::value, Convertor::Power<0,4>::value, Convertor::Power<0,5>::value},
		{Convertor::Power<1,1>::value, Convertor::Power<1,2>::value, Convertor::Power<1,3>::value, Convertor::Power<1,4>::value, Convertor::Power<1,5>::value},
		{Convertor::Power<2,1>::value, Convertor::Power<2,2>::value, Convertor::Power<2,3>::value, Convertor::Power<2,4>::value, Convertor::Power<2,5>::value},
		{Convertor::Power<3,1>::value, Convertor::Power<3,2>::value, Convertor::Power<3,3>::value, Convertor::Power<3,4>::value, Convertor::Power<3,5>::value},
		{Convertor::Power<4,1>::value, Convertor::Power<4,2>::value, Convertor::Power<4,3>::value, Convertor::Power<4,4>::value, Convertor::Power<4,5>::value}
	};

	const scalar ConvertorTables::Force[8][8] =
	{
		{Convertor::Force<0,0>::value, Convertor::Force<0,1>::value, Convertor::Force<0,2>::value, Convertor::Force<0,3>::value, Convertor::Force<0,4>::value, Convertor::Force<0,5>::value, Convertor::Force<0,6>::value, Convertor::Force<0,7>::value},
		{Convertor::Force<1,0>::value, Convertor::Force<1,1>::value, Convertor::Force<1,2>::value, Convertor::Force<1,3>::value, Convertor::Force<1,4>::value, Convertor::Force<1,5>::value, Convertor::Force<1,6>::value, Convertor::Force<1,7>::value},
		{Convertor::Force<2,0>::value, Convertor::Force<2,1>::value, Convertor::Force<2,2>::value, Convertor::Force<2,3>::value, Convertor::Force<2,4>::value, Convertor::Force<2,5>::value, Convertor::Force<2,6>::value, Convertor::Force<2,7>::value},
		{Convertor::Force<3,0>::value, Convertor::Force<3,1>::value, Convertor::Force<3,2>::value, Convertor::Force<3,3>::value, Convertor::Force<3,4>::value, Convertor::Force<3,5>::value, Convertor::Force<3,6>::value, Convertor::Force<3,7>::value},
		{Convertor::Force<4,0>::value, Convertor::Force<4,1>::value, Convertor::Force<4,2>::value, Convertor::Force<4,3>::value, Convertor::Force<4,4>::value, Convertor::Force<4,5>::value, Convertor::Force<4,6>::value, Convertor::Force<4,7>::value},
		{Convertor::Force<5,0>::value, Convertor::Force<5,1>::value, Convertor::Force<5,2>::value, Convertor::Force<5,3>::value, Convertor::Force<5,4>::value, Convertor::Force<5,5>::value, Convertor::Force<5,6>::value, Convertor::Force<5,7>::value},
		{Convertor::Force<6,0>::value, Convertor::Force<6,1>::value, Convertor::Force<6,2>::value, Convertor::Force<6,3>::value, Convertor::Force<6,4>::value, Convertor::Force<6,5>::value, Convertor::Force<6,6>::value, Convertor::Force<6,7>::value},
		{Convertor::Force<7,0>::value, Convertor::Force<7,1>::value, Convertor::Force<7,2>::value, Convertor::Force<7,3>::value, Convertor::Force<7,4>::value, Convertor::Force<7,5>::value, Convertor::Force<7,6>::value, Convertor::Force<7,7>::value}
	};

	const scalar ConvertorTables::Angle[3][3] =
	{
		{Convertor::Angle<0,0>::value, Convertor::Angle<0,1>::value, Convertor::Angle<0,2>::value},
		{Convertor::Angle<1,0>::value, Convertor::Angle<1,1>::value, Convertor::Angle<1,2>::value},
		{Convertor::Angle<2,0>::value, Convertor::Angle<2,1>::value, Convertor::Angle<2,2>::value}
	};

	const scalar ConvertorTables::DynViscosity[5][5] =
	{
		{Convertor::DynViscosity<0,0>::value, Convertor::DynViscosity<0,1>::value, Convertor::DynViscosity<0,2>::value, Convertor::DynViscosity<0,3>::value, Convertor::DynViscosity<0,4>::value},
		{Convertor::DynViscosity<1,0>::value, Convertor::DynViscosity<1,1>::value, Convertor::DynViscosity<1,2>::value, Convertor::DynViscosity<1,3>::value, Convertor::DynViscosity<1,4>::value},
		{Convertor::DynViscosity<2,0>::value, Convertor::DynViscosity<2,1>::value, Convertor::DynViscosity<2,2>::value, Convertor::DynViscosity<2,3>::value, Convertor::DynViscosity<2,4>::value},
		{Convertor::DynViscosity<3,0>::value, Convertor::DynViscosity<3,1>::value, Convertor::DynViscosity<3,2>::value, Convertor::DynViscosity<3,3>::value, Convertor::DynViscosity<3,4>::value}
	};

	const scalar ConvertorTables::KinViscosity[2][2] =
	{
		{Convertor::KinViscosity<0,0>::value, Convertor::KinViscosity<0,1>::value},
		{Convertor::KinViscosity<1,0>::value, Convertor::KinViscosity<1,1>::value}
	};

}