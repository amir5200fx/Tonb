#pragma once
#ifndef _NModel_SegmentGeometry_Header
#define _NModel_SegmentGeometry_Header

#include <Entity3d_PolygonFwd.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>
#include <OFstream.hxx>

#include <memory>

namespace tnbLib
{

	class NModel_SegmentGeometry
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Polygon> theMesh_;

	protected:

		NModel_SegmentGeometry()
		{}

	public:

		auto HasMesh() const
		{
			return (Standard_Boolean)theMesh_;
		}

		//- Io functions and operators

		void ExportToPlt(OFstream& File) const;

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Entity3d_Polygon>, Mesh)
	};
}

#endif // !_NModel_SegmentGeometry_Header
