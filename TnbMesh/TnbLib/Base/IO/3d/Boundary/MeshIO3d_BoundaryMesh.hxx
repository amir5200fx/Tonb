#ifndef _MeshIO3d_BoundaryMesh_Header
#define _MeshIO3d_BoundaryMesh_Header

#include <Mesh_Module.hxx>
#include <Entity3d_SurfTriangulationFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations [6/13/2023 Payvand]

	class Cad_TModel;

	class MeshIO3d_BoundaryMesh
	{

		/*Private Data*/

		std::shared_ptr<Cad_TModel> theModel_;

		std::map<Standard_Integer, std::shared_ptr<Entity3d_SurfTriangulation>>
			theMeshes_;


		// Private functions and operators [6/13/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [6/13/2023 Payvand]

		MeshIO3d_BoundaryMesh()
		{}

		// constructors [6/13/2023 Payvand]


		// Public functions and operators [6/13/2023 Payvand]

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& Meshes() const
		{
			return theMeshes_;
		}

		void SetModel(const std::shared_ptr<Cad_TModel>& theModel)
		{
			theModel_ = theModel;
		}

		void SetMeshes(const std::map<Standard_Integer, std::shared_ptr<Entity3d_SurfTriangulation>>& theMeshes)
		{
			theMeshes_ = theMeshes;
		}

		void SetMeshes(std::map<Standard_Integer, std::shared_ptr<Entity3d_SurfTriangulation>>&& theMeshes)
		{
			theMeshes_ = std::move(theMeshes);
		}

	};
}

#endif // !_MeshIO3d_BoundaryMesh_Header
