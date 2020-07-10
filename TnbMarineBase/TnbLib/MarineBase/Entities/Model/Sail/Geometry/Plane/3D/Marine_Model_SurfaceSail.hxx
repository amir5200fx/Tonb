#pragma once
#ifndef _Marine_Model_SurfaceSail_Header
#define _Marine_Model_SurfaceSail_Header

#include <Marine_PlnSailModel.hxx>
#include <TopoDS_Face.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_SurfaceSail
			: public Marine_PlnSailModel
		{

			/*Private Data*/

			TopoDS_Face theFace_;

		public:

			Model_SurfaceSail
			(
				const TopoDS_Face& theFace
			);

			Model_SurfaceSail
			(
				TopoDS_Face&& theFace
			);

			Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const TopoDS_Face& theFace
			);

			Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				TopoDS_Face&& theFace
			);

			Model_SurfaceSail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const TopoDS_Face& theFace
			);

			Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const word& theName, 
				TopoDS_Face&& theFace
			);


			const auto& Face() const
			{
				return theFace_;
			}
		};
	}
}

#endif // !_Marine_Model_SurfaceSail_Header
