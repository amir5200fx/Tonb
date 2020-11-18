#pragma once
#ifndef _Marine_WireFrameShape_Header
#define _Marine_WireFrameShape_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_BodyType.hxx>
#include <Marine_Module.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Body;
	class Marine_DisctLib;

	class Marine_WireFrameShape
		: public Marine_CoordinatedEntity
	{

		friend class Marine_DisctLib;

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;


		/*private functions and operators*/

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

		auto& ChangeBody()
		{
			return theBody_;
		}

	protected:

		template<class... _Types>
		Marine_WireFrameShape(_Types&&... _Args)
			: Marine_CoordinatedEntity(_Args...)
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

		TnbMarine_EXPORT Marine_BodyType Type() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_WireFrameShape);

#endif // !_Marine_WireFrameShape_Header
