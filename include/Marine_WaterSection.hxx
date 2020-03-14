#pragma once
#ifndef _Marine_WaterSection_Header
#define _Marine_WaterSection_Header

#include <Marine_Entity.hxx>
#include <Global_Done.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Wave;

	class Marine_WaterSection
		: public Marine_Entity
		, public Global_Done
	{

		/*private Data*/

		std::shared_ptr<Marine_Wave> theWave_;

		TopoDS_Shape theVessel_;

		TopoDS_Shape theSection_;

	public:

		Marine_WaterSection();

		Marine_WaterSection(const Standard_Integer theIndex);

		Marine_WaterSection(const Standard_Integer theIndex, const word& theName);

		const auto& Vessel() const
		{
			return theVessel_;
		}

		const auto& Wave() const
		{
			return theWave_;
		}

		void Perform();

		void LoadWave(const std::shared_ptr<Marine_Wave>& theWave)
		{
			theWave_ = theWave;
		}

		void LoadVessel(const TopoDS_Shape& theShape)
		{
			theVessel_ = theShape;
		}

		
	};
}

#endif // !_Marine_WaterSection_Header
