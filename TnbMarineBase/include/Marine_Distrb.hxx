#pragma once
#ifndef _Marine_Distrb_Header
#define _Marine_Distrb_Header

#include <Standard_TypeDef.hxx>
#include <Global_Done.hxx>
#include <Marine_Entity.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class Marine_Distrb
		: public Global_Done
		, public Marine_Entity
	{

		/*Private Data*/

		std::shared_ptr<Geo_xDistb> theX_;


	protected:

		Marine_Distrb()
		{}

		auto& ChangeX()
		{
			return theX_;
		}

	public:

		const auto& X() const
		{
			return theX_;
		}


	};
}

#endif // !_Marine_Distrb_Header
