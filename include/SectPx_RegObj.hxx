#pragma once
#ifndef _SectPx_RegObj_Header
#define _SectPx_RegObj_Header

#include <SectPx_Entity.hxx>
#include <SectPx_RegObjType.hxx>

namespace tnbLib
{

	class SectPx_RegObj
		: public SectPx_Entity
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_RegObj(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{}

	public:

		virtual word RegObjTypeName() const = 0;

		virtual sectPxLib::regObjType RegObjType() const = 0;

		virtual Standard_Boolean IsParent() const;

		virtual Standard_Boolean IsChild() const;

		virtual Standard_Boolean IsEdge() const;

		virtual Standard_Boolean IsSegment() const;

		virtual Standard_Boolean IsPole() const;

		virtual Standard_Boolean IsInterface() const;

		virtual Standard_Boolean IsNode() const;

		virtual Standard_Boolean IsProfile() const;

		virtual Standard_Boolean IsCmptProfile() const;

		virtual Standard_Boolean IsFrame() const;

		virtual Standard_Boolean IsOverrider() const;
	};
}

#endif // !_SectPx_RegObj_Header
