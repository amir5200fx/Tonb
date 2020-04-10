#pragma once
#ifndef _Marine_WaterPlane_Header
#define _Marine_WaterPlane_Header

#include <Marine_Entity.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_FlatWave;
	class Pln_Wire;

	class Marine_WaterPlane
		: public Marine_Entity
		, public Global_Done
	{

		typedef std::vector<std::shared_ptr<Pln_Wire>> wireList;

		/*Private Data*/

		TopoDS_Shape theHull_;

		std::shared_ptr<Marine_FlatWave> theWater_;

		wireList thePlane_;

	public:

		Marine_WaterPlane();

		Marine_WaterPlane(const Standard_Integer theIndex);

		Marine_WaterPlane(const Standard_Integer theIndex, const word& theName);


		const auto& Plane() const
		{
			return thePlane_;
		}

		void Perform();

		void LoadHull(const TopoDS_Shape& theHull)
		{
			theHull_ = theHull;
		}

		void LoadWater(const std::shared_ptr<Marine_FlatWave>& theWater)
		{
			theWater_ = theWater;
		}
	};
}

#endif // !_Marine_WaterPlane_Header
