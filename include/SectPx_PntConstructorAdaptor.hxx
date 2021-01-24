#pragma once
#ifndef _SectPx_PntConstructorAdaptor_Header
#define _SectPx_PntConstructorAdaptor_Header

#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Node;

	class SectPx_PntConstructorAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Node> theNode_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_PntConstructorAdaptor()
		{}

	public:

		const auto& Node() const
		{
			return theNode_;
		}

		void SetNode(const std::shared_ptr<SectPx_Node>& theNode)
		{
			theNode_ = theNode;
		}
	};
}

#endif // !_SectPx_PntConstructorAdaptor_Header
