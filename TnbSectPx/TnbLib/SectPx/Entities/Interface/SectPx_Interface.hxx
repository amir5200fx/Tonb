#pragma once
#ifndef _SectPx_Interface_Header
#define _SectPx_Interface_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_InterfaceType.hxx>
#include <SectPx_InterfacesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Node;
	class SectPx_Tools;

	class SectPx_Interface
		: public SectPx_RegObj
	{

		friend class SectPx_Tools;

		/*Private Data*/

		std::shared_ptr<SectPx_Node> theNode_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_Interface()
		{}

		TnbSectPx_EXPORT SectPx_Interface
		(
			const std::shared_ptr<SectPx_Node>& theNode
		);

		TnbSectPx_EXPORT SectPx_Interface
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode
		);

		TnbSectPx_EXPORT SectPx_Interface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode
		);

		void SetNode(const std::shared_ptr<SectPx_Node>& node)
		{
			theNode_ = node;
		}

		virtual void disJoint() = 0;

		virtual Standard_Boolean IsRemovable() const = 0;

	public:

		const auto& Node() const
		{
			return theNode_;
		}

		virtual sectPxLib::interfaceType InterfaceType() const = 0;

		TnbSectPx_EXPORT virtual Standard_Boolean IsEmpty() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsPaired() const;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsInterface() const override;

		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Interface);

#endif // !_SectPx_Interface_Header
