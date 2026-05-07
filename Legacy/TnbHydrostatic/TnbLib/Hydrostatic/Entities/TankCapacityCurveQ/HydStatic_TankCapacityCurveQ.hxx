#pragma once
#ifndef _HydStatic_TankCapacityCurveQ_Header
#define _HydStatic_TankCapacityCurveQ_Header

#include <HydStatic_HydOffsetCurve.hxx>

namespace tnbLib
{

	class HydStatic_TankCapacityCurveQ
		: public HydStatic_HydOffsetCurve
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydOffsetCurve>(*this);
		}


		void Check();

	public:

		//- default constructor

		HydStatic_TankCapacityCurveQ()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_TankCapacityCurveQ
		(
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		);

		TnbHydStatic_EXPORT HydStatic_TankCapacityCurveQ
		(
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		);

		TnbHydStatic_EXPORT HydStatic_TankCapacityCurveQ
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		);

		TnbHydStatic_EXPORT HydStatic_TankCapacityCurveQ
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs
		);


		//- public functions and operators

		TnbHydStatic_EXPORT Standard_Real FirstVolume() const;
		TnbHydStatic_EXPORT Standard_Real LastVolume() const;
		TnbHydStatic_EXPORT Standard_Real MaxVolume() const;

		TnbHydStatic_EXPORT Standard_Real LowerZ() const;
		TnbHydStatic_EXPORT Standard_Real UpperZ() const;

		TnbHydStatic_EXPORT Standard_Real Volume(const Standard_Real theZ) const;

		TnbHydStatic_EXPORT void SetQs(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs) override;
		TnbHydStatic_EXPORT void SetQs(std::vector<std::pair<Standard_Real, Standard_Real>>&&) override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_TankCapacityCurveQ);


#endif // !_HydStatic_TankCapacityCurveQ_Header
