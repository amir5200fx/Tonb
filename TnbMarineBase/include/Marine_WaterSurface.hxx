#pragma once
#ifndef _Marine_WaterSurface_Header
#define _Marine_WaterSurface_Header

#include <Marine_Entity.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Wave;
	class Marine_Model;

	class Marine_WaterSurface
		: public Marine_Entity
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_Model> theModel_;
		std::shared_ptr<Marine_Wave> theWave_;


	};
}

#endif // !_Marine_WaterSurface_Header
