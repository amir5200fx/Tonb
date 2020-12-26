#pragma once
#ifndef _Marine_MidSection_Header
#define _Marine_MidSection_Header

#include <Global_Done.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Wave;

	class Marine_MidSection
	{

		/*Private Data*/

		const std::shared_ptr<marineLib::Body_Displacer>& theDisplacer_;
		const std::shared_ptr<marineLib::Body_Wetted>& theBody_;
		const std::shared_ptr<Marine_Wave>& theWave_;

		Standard_Real theMinTol_;
		Standard_Real theMaxTol_;

	public:

		TnbMarine_EXPORT Marine_MidSection
		(
			const std::shared_ptr<marineLib::Body_Displacer>& theDisplacer,
			const std::shared_ptr<marineLib::Body_Wetted>& theBody,
			const std::shared_ptr<Marine_Wave>& theWave
		);

		const auto& Displacer() const
		{
			return theDisplacer_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Wave() const
		{
			return theWave_;
		}

		auto MaxTol() const
		{
			return theMaxTol_;
		}

		auto MinTol() const
		{
			return theMinTol_;
		}

		TnbMarine_EXPORT Standard_Boolean HasShape() const;

		TnbMarine_EXPORT void ApplyAt(const Standard_Real x);

		std::shared_ptr<Marine_CmpSection> ApplyAt(const std::shared_ptr<Marine_CmpSection>& theSect);

		void SetMinTol(const Standard_Real tol)
		{
			theMinTol_ = tol;
		}

		void SetMaxTol(const Standard_Real tol)
		{
			theMaxTol_ = tol;
		}
		
	};
}

#endif // !_Marine_MidSection_Header
