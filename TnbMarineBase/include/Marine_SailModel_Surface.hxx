#pragma once
#ifndef _Marine_SailModel_Surface_Header
#define _Marine_SailModel_Surface_Header

#include <Marine_PlnSailModel.hxx>
#include <TopoDS_Face.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class SailModel_Surface
			: public Marine_PlnSailModel
		{

			/*Private Data*/

			TopoDS_Face theFace_;

		public:

			SailModel_Surface(const TopoDS_Face& theFace);

			SailModel_Surface(TopoDS_Face&& theFace);

			SailModel_Surface(const Standard_Integer theIndex, const TopoDS_Face& theFace);

			SailModel_Surface(const Standard_Integer theIndex, TopoDS_Face&& theFace);

			SailModel_Surface(const Standard_Integer theIndex, const word& theName, const TopoDS_Face& theFace);

			SailModel_Surface(const Standard_Integer theIndex, const word& theName, TopoDS_Face&& theFace);


			const auto& Face() const
			{
				return theFace_;
			}
		};
	}
}

#endif // !_Marine_SailModel_Surface_Header
