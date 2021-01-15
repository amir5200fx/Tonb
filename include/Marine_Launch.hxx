#pragma once
#ifndef _Marine_Launch_Header
#define _Marine_Launch_Header

#include <Global_Done.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	// FOrward Declarations
	class Marine_Wave;

	class Marine_Launch
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_Wave> theWater_;

	protected:

		TnbMarine_EXPORT Marine_Launch();


		TnbMarine_EXPORT void CreateWater(const Standard_Real z);

	public:

		const auto& Water() const
		{
			return theWater_;
		}
	};
}

#endif // !_Marine_Launch_Header
