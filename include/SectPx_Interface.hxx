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

	class SectPx_Interface
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Node> theNode_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		SectPx_Interface()
		{}

		SectPx_Interface
		(
			const std::shared_ptr<SectPx_Node>& theNode
		);

		SectPx_Interface
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode
		);

		SectPx_Interface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode
		);


		virtual void disJoint() = 0;

	public:

		virtual sectPxLib::interfaceType InterfaceType() const = 0;

		virtual Standard_Boolean IsEmpty() const;

		virtual Standard_Boolean IsPaired() const;

		sectPxLib::regObjType RegObjType() const override;

		Standard_Boolean IsInterface() const override;

		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Interface);

#endif // !_SectPx_Interface_Header
