#pragma once
#ifndef _Marine_MultLevWaterDomain_Header
#define _Marine_MultLevWaterDomain_Header

#include <Marine_Entity.hxx>
#include <Marine_Module.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WaterDomain;
	class Marine_WaterLib;

	class Marine_MultLevWaterDomain
		: public Marine_Entity
	{

		friend class Marine_WaterLib;

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_WaterDomain>> theDomains_;


		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

		auto& ChangeDomains()
		{
			return theDomains_;
		}

		void SetDomains
		(
			const std::vector<std::shared_ptr<Marine_WaterDomain>>&& theDomains
		)
		{
			theDomains_ = std::move(theDomains);
		}

		void SetDomains
		(
			const std::vector<std::shared_ptr<Marine_WaterDomain>>& theDomains
		)
		{
			theDomains_ = theDomains;
		}

	public:

		template<class... _Types>
		Marine_MultLevWaterDomain(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

		const auto& Domains() const
		{
			return theDomains_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_MultLevWaterDomain);

#endif // !_Marine_MultLevWaterDomain_Header
