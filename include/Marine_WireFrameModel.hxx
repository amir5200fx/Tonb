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

	class Marine_WireFrameModel
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_CmpSection>> theSections_;


		TopoDS_Shape theShape_;

	public:

		Marine_WireFrameModel
		(
			const TopoDS_Shape& theShape
		);

		Marine_WireFrameModel
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const TopoDS_Shape& theShape
		);


		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		auto& ChangeSections()
		{
			return theSections_;
		}

		const auto& Shape() const
		{
			return theShape_;
		}

	};
}

#endif // !_Marine_WireFrameModel_Header
