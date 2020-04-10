#pragma once
#ifndef _Marine_Discrtize_Header
#define _Marine_Discrtize_Header

#include <Global_Done.hxx>
#include <Global_AccessMethod.hxx>

class gp_Ax2;

#include <memory>
#include <vector>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_SectionDistribution;

	class Marine_Discrtize
		: public Global_Done
	{

		/*Private Data*/

		Standard_Real theMinTolerance_;
		Standard_Real theMaxTolerance_;

		std::vector<std::shared_ptr<Marine_CmpSection>> theSections_;

		const gp_Ax2& theSystem_;

		TopoDS_Shape theShape_;

		std::shared_ptr<Marine_SectionDistribution> theDistributor_;

		auto& ChangeSections()
		{
			return theSections_;
		}

	public:

		Marine_Discrtize(const gp_Ax2& theSystem);

		const auto& Sections() const
		{
			return theSections_;
		}

		const auto& System() const
		{
			return theSystem_;
		}

		const auto& Shape() const
		{
			return theShape_;
		}

		const auto& Distributor() const
		{
			return theDistributor_;
		}

		void Perform();

		void LoadShape
		(
			const TopoDS_Shape& theShape
		)
		{
			theShape_ = theShape;
		}

		void LoadDistributor
		(
			const std::shared_ptr<Marine_SectionDistribution>& theDistributor
		)
		{
			theDistributor_ = theDistributor;
		}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MinTolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MaxTolerance)
	};
}

#endif // !_Marine_Discrtize_Header
