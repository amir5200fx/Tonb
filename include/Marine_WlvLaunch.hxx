#pragma once
#ifndef _Marine_WlvLaunch_Header
#define _Marine_WlvLaunch_Header

#include <Marine_Launch.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WLVolume;

	class Marine_WlvLaunch
		: public Marine_Launch
	{

		/*Private Data*/

		std::shared_ptr<Marine_WLVolume> theGraph_;

	public:

		Marine_WlvLaunch();

		Marine_WlvLaunch(const std::shared_ptr<Marine_WLVolume>& theGraph);

		const auto& Graph() const
		{
			return theGraph_;
		}

		void Perform();

		void LoadGraph
		(
			const std::shared_ptr<Marine_WLVolume>& theGraph
		)
		{
			theGraph_ = theGraph;
		}
	};
}

#endif // !_Marine_WlvLaunch_Header
