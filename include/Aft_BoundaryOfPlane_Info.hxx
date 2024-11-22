#pragma once
#ifndef _Aft_BoundaryOfPlane_Info_Header
#define _Aft_BoundaryOfPlane_Info_Header

#include <Mesh_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Mesh_Curve_Info;

	struct Aft_BoundaryOfPlane_Info_Base
	{

		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;


	private:

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			//- empty body
		}

	protected:

		//- default constructor

		Aft_BoundaryOfPlane_Info_Base()
		{}

		//- constructors

	};

	template<class MetricPrcsrInfo>
	class Aft_BoundaryOfPlane_Info
		: public Aft_BoundaryOfPlane_Info_Base
	{

		/*Private Data*/

		Standard_Real theMergeTolerance_;

		std::shared_ptr<Mesh_Curve_Info> theGlobalCurve_;
		std::shared_ptr<MetricPrcsrInfo> theGlobalMetricPrcsr_;

		std::map
			<
			Standard_Integer,
			std::shared_ptr<Mesh_Curve_Info>
			> theCurve_;

		Standard_Boolean OverrideInfo_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This functions is not supposed to be called!" << endl;
			NotImplemented;
		}


		//- default constructor


	public:

		static TnbMesh_EXPORT const std::string extension;


		//- constructors

		Aft_BoundaryOfPlane_Info()
			: OverrideInfo_(Standard_False)
			, theMergeTolerance_(DEFAULT_TOLERANCE)
		{}


		//- public functions and operators

		auto OverrideInfo() const
		{
			return OverrideInfo_;
		}

		const auto& GlobalCurve() const
		{
			return theGlobalCurve_;
		}

		const auto& GlobalMetricPrcsr() const
		{
			return theGlobalMetricPrcsr_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		auto& Curve()
		{
			return theCurve_;
		}

		void OverrideGlobalCurve(const std::shared_ptr<Mesh_Curve_Info>& theInfo)
		{
			theGlobalCurve_ = theInfo;
		}

		void OverrideGlobalMetricPrcsr(const std::shared_ptr<MetricPrcsrInfo>& theInfo)
		{
			theGlobalMetricPrcsr_ = theInfo;
		}

		void SetOverrideInfo(const Standard_Boolean cond)
		{
			OverrideInfo_ = cond;
		}


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MergeTolerance)
	};
}

#endif // !_Aft_BoundaryOfPlane_Info_Header
