#pragma once
#ifndef _SectPx_Node_Header
#define _SectPx_Node_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_NodeAdaptor.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class SectPx_Tools;

	class SectPx_Node
		: public SectPx_RegObj
		, public SectPx_NodeAdaptor
	{

		friend class SectPx_Tools;

		/*Private Data*/

		std::shared_ptr<SectPx_Pnt> thePnt_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		void SetPnt
		(
			const std::shared_ptr<SectPx_Pnt>& thePnt
		)
		{
			thePnt_ = thePnt;
		}

	protected:

		SectPx_Node()
		{}

	public:

		static const char* typeName_;

		SectPx_Node
		(
			const std::shared_ptr<SectPx_Pnt>& thePnt
		);

		SectPx_Node
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Pnt>& thePnt
		);

		SectPx_Node
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_Pnt>& thePnt
		);

		const auto& Pnt() const
		{
			return thePnt_;
		}

		word RegObjTypeName() const override;

		Standard_Boolean IsNode() const override;

		sectPxLib::regObjType RegObjType() const override;
	};
}

#endif // !_SectPx_Node_Header
