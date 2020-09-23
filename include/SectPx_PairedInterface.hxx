#pragma once
#ifndef _SectPx_PairedInterface_Header
#define _SectPx_PairedInterface_Header

#include <SectPx_Interface.hxx>
#include <SectPx_PairedInterfaceAdaptor.hxx>

namespace tnbLib
{

	class SectPx_PairedInterface
		: public SectPx_Interface
		, public SectPx_PairedInterfaceAdaptor
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_PairedInterface(_Types&&... _Args)
			: SectPx_Interface(_Args...)
		{}

		void disJoint() override;

	public:

		static const std::shared_ptr<SectPx_PairedInterface> null;

		Standard_Boolean IsPaired() const override;
		
	};
}

#endif // !_SectPx_PairedInterface_Header
