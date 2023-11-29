#pragma once
#ifndef _Mesh2d_VolumeSizeMapTool_Info_Header
#define _Mesh2d_VolumeSizeMapTool_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Mesh2d_VolumeSizeMapTool_Info
	{

		/*Private Data*/

		Standard_Integer theUnBalancing_;
		Standard_Integer theBucketSize_;

		Standard_Integer theNbSamples_;

		Standard_Boolean PostBalance_;

		Standard_Integer theMaxNbCorrIters_;


		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theUnBalancing_;
			ar& theBucketSize_;
			ar& theNbSamples_;
			ar& PostBalance_;
			ar& theMaxNbCorrIters_;
		}

	public:

		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_MAX_NB_CORR_ITERS;

		static TnbMesh_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructor [7/13/2023 Payvand]

		Mesh2d_VolumeSizeMapTool_Info()
			: theUnBalancing_(DEFAULT_UNBALANCING)
			, theBucketSize_(DEFAULT_BUCKET_SIZE)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, PostBalance_(POST_BALANCE)
			, theMaxNbCorrIters_(DEFAULT_MAX_NB_CORR_ITERS)
		{}

		// constructors [7/13/2023 Payvand]


		// Public functions and operators [7/13/2023 Payvand]

		auto Unbalancing() const { return theUnBalancing_; }
		auto BucketSize() const { return theBucketSize_; }
		auto NbSamples() const { return theNbSamples_; }
		auto MaxNbCorrIters() const { return theMaxNbCorrIters_; }
		auto PostBalance() const { return PostBalance_; }

		void SetUnbalancing(const Standard_Integer n) { theUnBalancing_ = n; }
		void SetBucketSize(const Standard_Integer n) { theBucketSize_ = n; }
		void SetNbSamples(const Standard_Integer n) { theNbSamples_ = n; }
		void SetMaxNbCorrIters(const Standard_Integer n) { theMaxNbCorrIters_ = n; }
		void SetPostBalance(const Standard_Boolean apply) { PostBalance_ = apply; }

	};
}

#endif // !_Mesh2d_VolumeSizeMapTool_Info_Header
