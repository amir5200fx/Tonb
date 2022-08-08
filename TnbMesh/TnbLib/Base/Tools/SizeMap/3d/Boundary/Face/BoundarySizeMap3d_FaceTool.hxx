#pragma once
#ifndef _BoundarySizeMap3d_FaceTool_Header
#define _BoundarySizeMap3d_FaceTool_Header

#include <Mesh3d_BoundarySizeMapTool.hxx>
#include <Mesh_SizeMapTool_Info.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/10/2022 Amir]

	class BoundarySizeMap3d_FaceTool
		: public Mesh3d_BoundarySizeMapTool
	{


		Standard_Integer theMaxNbCorrIters_;


		// private functions and operators [7/20/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapTool>(*this);
			ar & theMaxNbCorrIters_;
		}

	protected:

		// default constructor [7/9/2022 Amir]

		BoundarySizeMap3d_FaceTool()
		{}

		// constructors [7/9/2022 Amir]

		BoundarySizeMap3d_FaceTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Cad_TModel>& theModel
		)
			: Mesh3d_BoundarySizeMapTool(theModel, theDomain, theRef)
			, theMaxNbCorrIters_(DEFAULT_MAX_NB_CORR_ITERS)
		{}

	public:

		
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_NB_CORR_ITERS;


		// public functions and operators [7/9/2022 Amir]

		auto MaxNbCorrIters() const
		{
			return theMaxNbCorrIters_;
		}

		void SetMaxNbCorrIters(const Standard_Integer theIters)
		{
			theMaxNbCorrIters_ = theIters;
		}


		TnbMesh_EXPORT std::vector<std::shared_ptr<TModel_Surface>> RetrieveFaces() const;

		TnbMesh_EXPORT void RetrieveFacesTo(std::vector<std::shared_ptr<TModel_Surface>>&) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::BoundarySizeMap3d_FaceTool);

#endif // !_BoundarySizeMap3d_FaceTool_Header
