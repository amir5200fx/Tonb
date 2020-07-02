#pragma once
#ifndef _Marine_WireFrameShape_Header
#define _Marine_WireFrameShape_Header

#include <Marine_Entity.hxx>
#include <Marine_BodyType.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Body;
	class Marine_DisctLib;

	class Marine_WireFrameShape
		: public Marine_Entity
	{

		friend class Marine_DisctLib;

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;

		auto& ChangeBody()
		{
			return theBody_;
		}

	protected:

		template<class... _Types>
		Marine_WireFrameShape(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

	public:

		const auto& Body() const
		{
			return theBody_;
		}

		virtual Standard_Boolean HasShape() const
		{
			return Standard_False;
		}

		Marine_BodyType Type() const;
	};
}

#endif // !_Marine_WireFrameShape_Header
