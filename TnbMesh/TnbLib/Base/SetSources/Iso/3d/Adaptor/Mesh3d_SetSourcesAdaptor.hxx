#pragma once
#ifndef _Mesh3d_SetSourcesAdaptor_Header
#define _Mesh3d_SetSourcesAdaptor_Header

#include <Mesh3d_ElementFwd.hxx>
#include <Mesh_Module.hxx>
#include <Geo3d_AttrbBalPrTreeLeaf_Adaptor.hxx>
#include <Global_TypeDef.hxx>

#include <map>
#include <memory>
#include <vector>

namespace tnbLib
{

	template<>
	class Geo3d_AttrbBalPrTreeLeaf_Adaptor<Mesh3d_Element>
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Mesh3d_Element>> theTets_;

	protected:

		// default constructor [8/10/2022 Amir]

		Geo3d_AttrbBalPrTreeLeaf_Adaptor()
		{}


		// constructors [8/10/2022 Amir]


	public:

		// public functions and operators [8/10/2022 Amir]

		Standard_Integer NbTets() const;

		const auto& Tets() const
		{
			return theTets_;
		}

		TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh3d_Element>> RetrieveTets() const;

		TnbMesh_EXPORT void InsertToTets(const std::shared_ptr<Mesh3d_Element>& theElement);
		TnbMesh_EXPORT void InsertToTets(std::shared_ptr<Mesh3d_Element>&&);
		TnbMesh_EXPORT void InsertToTets(const Standard_Integer theIndex, const std::shared_ptr<Mesh3d_Element>& theElement);
		TnbMesh_EXPORT void InsertToTets(const Standard_Integer theIndex, std::shared_ptr<Mesh3d_Element>&& theElement);

		TnbMesh_EXPORT void RemoveFromTets(const std::shared_ptr<Mesh3d_Element>&);
		TnbMesh_EXPORT void RemoveFromTets(const Standard_Integer theIndex);

		TnbMesh_EXPORT void RetrieveTetsTo(std::vector<std::shared_ptr<Mesh3d_Element>>&) const;
	};
}

#endif // !_Mesh3d_SetSourcesAdaptor_Header
