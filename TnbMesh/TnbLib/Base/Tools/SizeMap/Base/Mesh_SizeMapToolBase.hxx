#pragma once
#ifndef _Mesh_SizeMapToolBase_Header
#define _Mesh_SizeMapToolBase_Header

#include <Mesh_Conditions.hxx>
#include <Mesh_Values.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Mesh_ReferenceValues;

	template<class BackGroundMesh>
	class Mesh_SizeMapToolBase
	{

		/*Private Data*/

		Mesh_Conditions theConditions_;

		Mesh_Values theValues_;

		std::shared_ptr<Mesh_ReferenceValues> theReference_;
		std::shared_ptr<BackGroundMesh> theBackMesh_;

		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< " this function is not supposed to be called!" << endl
				<< abort(FatalError);
		}

	protected:


		//- default constructor

		Mesh_SizeMapToolBase()
		{}


		//- constructor

		Mesh_SizeMapToolBase
		(
			const std::shared_ptr<Mesh_ReferenceValues>& theRef
		)
			: theReference_(theRef)
		{}


		auto& ChangeBackMesh()
		{
			return theBackMesh_;
		}

		void RetrieveValues
		(
			Standard_Real& theElementSize,
			Standard_Real& theMinSize,
			Standard_Real& theSpanAngle
		) const;

	public:


		//- public functions and operators

		const auto& MeshConditions() const
		{
			return theConditions_;
		}

		auto& MeshConditionsRef()
		{
			return theConditions_;
		}

		const auto& MeshValues() const
		{
			return theValues_;
		}

		auto& MeshValuesRef()
		{
			return theValues_;
		}

		const auto& ReferenceValues() const
		{
			return theReference_;
		}

		const auto& BackgroundMesh() const
		{
			return theBackMesh_;
		}

		Standard_Real RetrieveTargetSize() const;
		Standard_Real GetBaseSize() const;
		Standard_Real GetTargetSurfaceSize() const;
		Standard_Real GetBoundaryGrowthRate() const;



	};
}

#include <Mesh_SizeMapToolBaseI.hxx>

#endif // !_Mesh_SizeMapToolBase_Header
