#pragma once
#ifndef _HsModel_SectionArea_Header
#define _HsModel_SectionArea_Header

#include <HydroStatic_PhysicsModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;
	class Marine_Graph;

	class HsModel_SectionArea
		: public HydroStatic_PhysicsModel
	{

		/*private Data*/

		std::shared_ptr<Marine_Body> theBody_;

		std::shared_ptr<Marine_Graph> theGraph_;


		auto& ChangeGraph()
		{
			return theGraph_;
		}

	public:

		HsModel_SectionArea();

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		void Perform();

		void LoadBody
		(
			const std::shared_ptr<Marine_Body>& theBody
		)
		{
			theBody_ = theBody;
		}

	};
}

#endif // !_HsModel_SectionArea_Header
