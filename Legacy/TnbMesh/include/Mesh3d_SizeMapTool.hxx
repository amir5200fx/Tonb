#pragma once
#ifndef _Mesh3d_SizeMapTool_Header
#define _Mesh3d_SizeMapTool_Header

#include <Global_Done.hxx>
#include <Mesh_SizeMapToolBase.hxx>
#include <GeoMesh3d_BackgroundFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [6/22/2022 Amir]
	class Cad_TModel;

	class Mesh3d_SizeMapTool
		: public Mesh_SizeMapToolBase<GeoMesh3d_Background>
		, public Global_Done
	{

	public:

		using Mesh_SizeMapToolBase<GeoMesh3d_Background>::boxType;

	private:

		/*Private Data*/

		std::shared_ptr<Cad_TModel> theModel_;


		// private functions and operators [6/22/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [6/22/2022 Amir]

		Mesh3d_SizeMapTool()
		{}

		// constructors [6/22/2022 Amir]

		Mesh3d_SizeMapTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<boxType>& theDomain,
			const std::shared_ptr<Cad_TModel>& theModel
		)
			: Mesh_SizeMapToolBase<GeoMesh3d_Background>(theRef, theDomain)
			, theModel_(theModel)
		{}

	public:

		// public functions and operators [6/23/2022 Amir]

		const auto& Model() const
		{
			return theModel_;
		}

		virtual void Perform() = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh3d_SizeMapTool);

#endif // !_Mesh3d_SizeMapTool_Header
