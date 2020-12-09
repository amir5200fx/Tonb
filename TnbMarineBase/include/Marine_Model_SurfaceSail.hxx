#pragma once
#ifndef _Marine_Model_SurfaceSail_Header
#define _Marine_Model_SurfaceSail_Header

#include <Marine_Model_PlnSail.hxx>
#include <TopoDS_Face.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Model_SurfaceSail
			: public Model_PlnSail
		{

			/*Private Data*/

			TopoDS_Face theFace_;


			TNB_SERIALIZATION(TnbMarine_EXPORT);

		protected:

			Model_SurfaceSail()
			{}

		public:

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const TopoDS_Face& theFace
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				TopoDS_Face&& theFace
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const TopoDS_Face& theFace
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				TopoDS_Face&& theFace
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const TopoDS_Face& theFace
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const word& theName, 
				TopoDS_Face&& theFace
			);

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::surface;
			}

			const auto& Face() const
			{
				return theFace_;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_SurfaceSail);

#endif // !_Marine_Model_SurfaceSail_Header
