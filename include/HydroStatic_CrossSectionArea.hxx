#pragma once
#ifndef _HydroStatic_CrossSectionArea_Header
#define _HydroStatic_CrossSectionArea_Header

#include <HydroStatic_PhysicsModel.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Graph;
	class Marine_Body;

	class HydroStatic_CrossSectionArea
		: public HydroStatic_PhysicsModel
	{

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;

		std::shared_ptr<Marine_Graph> theArea_;


		auto& ChangeArea()
		{
			return theArea_;
		}

	public:

		HydroStatic_CrossSectionArea();

		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Area() const
		{
			return theArea_;
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

#endif // !_HydroStatic_CrossSectionArea_Header
