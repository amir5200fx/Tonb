#pragma once
#ifndef _Ship_xParams_Header
#define _Ship_xParams_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [10/31/2022 Amir]

	class Ship_SectionCtrlPts;

	class Ship_xParams
	{

		/*Private Data*/

		std::vector<Standard_Real> xXcoords_;
		std::vector<Standard_Real> xYcoords_;
		std::vector<Standard_Real> xZcoords_;

		std::vector<Standard_Real> xDepth_;
		std::vector<Standard_Real> xSheer_;

		std::vector<Standard_Real> xTightness_;
		std::vector<Standard_Real> xFlare_;
		std::vector<Standard_Real> xDeadRise_;
		std::vector<Standard_Real> xSideSlope_;
		std::vector<Standard_Real> xSideSlopeAngle_;

		std::vector<Standard_Real> xRake_;

		std::vector<std::shared_ptr<Ship_SectionCtrlPts>> xSections_;

	public:

		// default constructor [10/31/2022 Amir]

		Ship_xParams()
		{}


		// constructors [10/31/2022 Amir]


		// public functions and operators [10/31/2022 Amir]

		const auto& xXcoords() const
		{
			return xXcoords_;
		}

		auto& xXcoordsRef()
		{
			return xXcoords_;
		}

		const auto& xYcoords() const
		{
			return xYcoords_;
		}

		auto& xYcoordsRef()
		{
			return xYcoords_;
		}

		const auto& xZcoords() const
		{
			return xZcoords_;
		}

		auto& xZcoordsRef()
		{
			return xZcoords_;
		}

		const auto& xDepth() const
		{
			return xDepth_;
		}

		auto& xDepthRef()
		{
			return xDepth_;
		}

		const auto& xSheer() const
		{
			return xSheer_;
		}

		auto& xSheerRef()
		{
			return xSheer_;
		}

		const auto& xTightness() const
		{
			return xTightness_;
		}

		auto& xTightnessRef()
		{
			return xTightness_;
		}

		const auto& xFlare() const
		{
			return xFlare_;
		}

		auto& xFlareRef()
		{
			return xFlare_;
		}

		const auto& xDeadRise() const
		{
			return xDeadRise_;
		}

		auto& xDeadRiseRef()
		{
			return xDeadRise_;
		}

		const auto& xSideSlope() const
		{
			return xSideSlope_;
		}

		auto& xSideSlopeRef()
		{
			return xSideSlope_;
		}

		const auto& xSideSlopeAngle() const
		{
			return xSideSlopeAngle_;
		}

		auto& xSideSlopeAngleRef()
		{
			return xSideSlopeAngle_;
		}

		const auto& xRake() const
		{
			return xRake_;
		}

		auto& xRakeRef()
		{
			return xRake_;
		}

		const auto& xSections() const
		{
			return xSections_;
		}

		auto& xSectionsRef()
		{
			return xSections_;
		}
	};
}

#endif // !_Ship_xParams_Header
