#pragma once
#ifndef _Marine_WaterDomains_Header
#define _Marine_WaterDomains_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WaterDomain;

	class Marine_WaterDomains
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_WaterDomain>> theDomains_;

	public:

		Marine_WaterDomains();

		Marine_WaterDomains
		(
			const Standard_Integer theIndex
		);

		Marine_WaterDomains
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		const auto& Domains() const
		{
			return theDomains_;
		}

		auto& ChangeDomains()
		{
			return theDomains_;
		}

	};
}

#endif // !_Marine_WaterDomains_Header
