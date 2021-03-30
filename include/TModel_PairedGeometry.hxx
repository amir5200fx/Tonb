#pragma once
#ifndef _TModel_PairedGeometry_Header
#define _TModel_PairedGeometry_Header

#include <Standard_TypeDef.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>
#include <OFstream.hxx>

#include <memory>

namespace tnbLib
{

	class TModel_PairedGeometry
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Polygon> theMesh_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		TModel_PairedGeometry()
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

#endif // !_TModel_PairedGeometry_Header
