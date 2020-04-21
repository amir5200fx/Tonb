#pragma once
#ifndef _Marine_WireFrameModel_Header
#define _Marine_WireFrameModel_Header

#include <Marine_Entity.hxx>

#include <TopoDS_Shape.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Body;
	class Marine_DisctLib;

	class Marine_WireFrameModel
		: public Marine_Entity
	{

		friend class Marine_DisctLib;

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;


		TopoDS_Shape theShape_;


		auto& ChangeBody()
		{
			return theBody_;
		}

		auto& ChangeShape()
		{
			return theShape_;
		}

	public:

		Marine_WireFrameModel();

		Marine_WireFrameModel
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		const auto& Body() const
		{
			return theBody_;
		}

		const auto& Shape() const
		{
			return theShape_;
		}

	};
}

#endif // !_Marine_WireFrameModel_Header
