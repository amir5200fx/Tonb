#pragma once
#ifndef _Mesh_SizeMapControl_Info_Header
#define _Mesh_SizeMapControl_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [7/18/2022 Amir]
	class GeoMesh_Background_SmoothingHvCorrection_Info;

	class Mesh_SizeMapControl_Info
	{

		/*Private Data*/

		Standard_Integer theMaxUnbalancing_;
		Standard_Real theTol_;

		std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info> theHvCorrInfo_;


		// private functions and operators [7/18/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_UNBALANCING;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		static TnbMesh_EXPORT const std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info> DEFAULT_HV_CORR_INFO;

		// default constructor [7/18/2022 Amir]

		Mesh_SizeMapControl_Info()
			: theMaxUnbalancing_(DEFAULT_MAX_UNBALANCING)
			, theTol_(DEFAULT_TOLERANCE)
			, theHvCorrInfo_(DEFAULT_HV_CORR_INFO)
		{}

		// constructors [7/18/2022 Amir]


		// public functions and operators [7/18/2022 Amir]

		auto MaxUnbalancing() const
		{
			return theMaxUnbalancing_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		const auto& HvCorrInfo() const
		{
			return theHvCorrInfo_;
		}

		void SetMaxUnbalancing(const Standard_Integer theMaxUnbalancing)
		{
			theMaxUnbalancing_ = theMaxUnbalancing;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}

		void SetHvCorrInfo(const std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info>& theInfo)
		{
			theHvCorrInfo_ = theInfo;
		}

		void SetHvCorrInfo(std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info>&& theInfo)
		{
			theHvCorrInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Mesh_SizeMapControl_Info_Header
