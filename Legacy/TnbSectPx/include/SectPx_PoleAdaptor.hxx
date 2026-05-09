#pragma once
#ifndef _SectPx_PoleAdaptor_Header
#define _SectPx_PoleAdaptor_Header

#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;

	class SectPx_PoleAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_TopoProfile> theProfile_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_PoleAdaptor()
		{}

	public:

		const auto& TopoProfile() const
		{
			return theProfile_;
		}

		void SetTopoProfile(const std::shared_ptr<SectPx_TopoProfile>& theProfile)
		{
			theProfile_ = theProfile;
		}
	};
}

#endif // !_SectPx_PoleAdaptor_Header
