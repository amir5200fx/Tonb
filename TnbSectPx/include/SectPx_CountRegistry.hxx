#pragma once
#ifndef _SectPx_CountRegistry_Header
#define _SectPx_CountRegistry_Header

#include <Geo_ItemCounter.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{

	class SectPx_CountRegistry
	{

		/*Private Data*/

		mutable Geo_ItemCounter theCounter_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theCounter_;
		}

	public:

		SectPx_CountRegistry()
		{}

		auto& Counter() const
		{
			return theCounter_;
		}
	};
}

#endif // !_SectPx_CountRegistry_Header
