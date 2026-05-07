#pragma once
#ifndef _Mesh_MultiSizeMap_Header
#define _Mesh_MultiSizeMap_Header

#include <Mesh_MultiSizeMapTraits.hxx>
#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class BackMeshData>
	class Mesh_MultiSizeMap
		: public BackMeshData
	{

		/*Private Data*/

		std::vector<std::shared_ptr<BackMeshData>> theMaps_;


		// Private functions and operators [12/8/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<BackMeshData>(*this);
			ar& theMaps_;
		}

	public:

		typedef typename multi_sizeMap_dimension<BackMeshData>::coord Point;


		// default constructor [12/7/2022 Payvand]

		Mesh_MultiSizeMap()
		{}

		// constructors [12/7/2022 Payvand]

		Mesh_MultiSizeMap(const std::vector<std::shared_ptr<BackMeshData>>& theMaps)
			: theMaps_(theMaps)
		{}

		Mesh_MultiSizeMap(std::vector<std::shared_ptr<BackMeshData>>&& theMaps)
			: theMaps_(std::move(theMaps))
		{}


		// Public functions and operators [12/7/2022 Payvand]

		const auto& SizeMaps() const
		{
			return theMaps_;
		}

		auto& SizeMapsRef()
		{
			return theMaps_;
		}

		Standard_Real InterpolateAt(const Point&) const override;
		Standard_Real InterpolateAt(const Point&, Standard_Boolean& theSense) const override;

		void ConnectTopology() override;
		void ExportToPlt(OFstream& File) const override;
		void ExportToVtk(OFstream& File) const override;
		void ExportToVtk(std::ostream&) const override;

		void SetSizeMaps(const std::vector<std::shared_ptr<BackMeshData>>& theMaps)
		{
			theMaps_ = theMaps;
		}

		void SetSizeMaps(std::vector<std::shared_ptr<BackMeshData>>&& theMaps)
		{
			theMaps_ = std::move(theMaps);
		}
	};
}

#endif // !_Mesh_MultiSizeMap_Header
