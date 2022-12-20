#pragma once
#ifndef _Mesh_SizeMapToolBase_Header
#define _Mesh_SizeMapToolBase_Header

#include <Mesh_SizeMapTool_Traits.hxx>
#include <Mesh_Conditions.hxx>
#include <Mesh_Values.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class Box>
	class Mesh_ReferenceValues;

	class Mesh_SizeMapToolBaseNonTemplate
	{

		/*Private Data*/

	protected:

		// default constructor [7/20/2022 Amir]

		Mesh_SizeMapToolBaseNonTemplate()
		{}


		// constructors [7/20/2022 Amir]

	public:

		static TnbMesh_EXPORT unsigned short verbose;

		// public functions and operators [7/20/2022 Amir]

	};

	template<class BackGroundMesh>
	class Mesh_SizeMapToolBase
		: public Mesh_SizeMapToolBaseNonTemplate
	{

	public:

		typedef typename mesh_sizeMapTool_traits<BackGroundMesh>::boxType boxType;
		typedef Mesh_ReferenceValues<boxType> meshRefValuesType;

	private:

		/*Private Data*/

		std::shared_ptr<Mesh_Conditions> theConditions_;
		std::shared_ptr<Mesh_Values> theValues_;

		std::shared_ptr<boxType> theDomain_;
		std::shared_ptr<meshRefValuesType> theReference_;
		std::shared_ptr<BackGroundMesh> theBackMesh_;

		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// it's not supposed to be called! [5/30/2021 Amir]
			NotImplemented;
		}

		void AllocateMemory();

	protected:


		//- default constructor

		Mesh_SizeMapToolBase()
		{
			AllocateMemory();
		}


		//- constructor

		Mesh_SizeMapToolBase
		(
			const std::shared_ptr<meshRefValuesType>& theRef,
			const std::shared_ptr<boxType>& theDomain
		)
			: theReference_(theRef)
			, theDomain_(theDomain)
		{
			AllocateMemory();
		}

		auto& ChangeBackMesh()
		{
			return theBackMesh_;
		}


	public:


		virtual ~Mesh_SizeMapToolBase()
		{}

		//- public functions and operators

		const auto& MeshConditions() const
		{
			return theConditions_;
		}

		const auto& MeshValues() const
		{
			return theValues_;
		}

		const auto& ReferenceValues() const
		{
			return theReference_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& BackgroundMesh() const
		{
			return theBackMesh_;
		}

		Standard_Real RetrieveTargetSize() const;
		Standard_Real GetBaseSize() const;
		Standard_Real GetTargetSurfaceSize() const;
		Standard_Real GetBoundaryGrowthRate() const;

		void RetrieveValues
		(
			Standard_Real& theElementSize,
			Standard_Real& theMinSize,
			Standard_Real& theSpanAngle
		) const;

		void ClearBackMesh()
		{
			theBackMesh_.reset();
		}
	};
}

#include <Mesh_SizeMapToolBaseI.hxx>

#endif // !_Mesh_SizeMapToolBase_Header
