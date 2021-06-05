#pragma once
#ifndef _Mesh_Domain_Header
#define _Mesh_Domain_Header

#include <Standard_TypeDef.hxx>

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	//- Forward Declarations
	template<class ElementType>
	class Mesh_GlobalData;

	template<class GeomType, class ElementType>
	class Mesh_Domain
	{

	public:

		typedef Mesh_GlobalData<ElementType> meshData;

	private:


		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<GeomType>> theGeometries_;
		std::map<Standard_Integer, std::shared_ptr<meshData>> theMeshes_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "it's not suppoed to be called!" << endl
				<< abort(FatalError);
		}

	public:

		//- default constructor

		Mesh_Domain()
		{}

		//- constructors


		//- public functions and operators

		const auto& Geometries() const
		{
			return theGeometries_;
		}

		const auto& Meshes() const
		{
			return theMeshes_;
		}

		void Import(const Standard_Integer theIndex, const std::shared_ptr<GeomType>& theGeometry);
		void Import(const Standard_Integer theIndex, const std::shared_ptr<meshData>& theMesh);
	};
}

#endif // !_Mesh_Domain_Header
