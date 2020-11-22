#pragma once
#ifndef _SectPx_NodeAdaptor_Header
#define _SectPx_NodeAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;
	class SectPx_Interface;

	namespace maker { class Interface; }

	class SectPx_NodeAdaptor
	{

		friend class SectPx_TopoProfile;
		friend class maker::Interface;

		/*Private Data*/

		std::weak_ptr<SectPx_TopoProfile> theProfile_;
		std::weak_ptr<SectPx_Interface> theInterface_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		SectPx_NodeAdaptor()
		{}

		void SetProfile(const std::weak_ptr<SectPx_TopoProfile>& theProfile)
		{
			theProfile_ = theProfile;
		}

		void SetInterface(const std::weak_ptr<SectPx_Interface>& theInterface)
		{
			theInterface_ = theInterface;
		}

	public:

		const auto& Profile() const
		{
			return theProfile_;
		}

		const auto& Interface() const
		{
			return theInterface_;
		}
	
	};
}

#endif // !_SectPx_NodeAdaptor_Header
