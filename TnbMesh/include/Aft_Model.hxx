#pragma once
#ifndef _Aft_Model_Base_Header
#define _Aft_Model_Base_Header

#include <Entity_Box.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity_StaticData.hxx>
#include <Aft_MetricPrcsr.hxx>
#include <Aft_Core.hxx>
#include <Aft_Model_Traits.hxx>
#include <Aft_Model_Cache.hxx>
#include <Aft_Model_Constants.hxx>
#include <Traits.hxx>

namespace tnbLib
{

	template<class ModelType, class SizeFun, class MetricFun = void>
	class Aft_Model
		: public Aft_Core
		<
		typename aft_model_traits<ModelType, SizeFun, MetricFun>::nodeCalculator,
		SizeFun,
		typename aft_model_traits<ModelType, SizeFun, MetricFun>::frontInfo,
		typename aft_model_traits<ModelType, SizeFun, MetricFun>::globalData,
		MetricFun
		>
		, public aft_model_traits<ModelType, SizeFun, MetricFun>::cacheType
		, public Aft_Model_Constants
	{

	public:

		typedef Aft_Core
			<
			typename aft_model_traits<ModelType, SizeFun, MetricFun>::nodeCalculator,
			SizeFun,
			typename aft_model_traits<ModelType, SizeFun, MetricFun>::frontInfo,
			typename aft_model_traits<ModelType, SizeFun, MetricFun>::globalData,
			MetricFun
			> base;

		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::frontType frontType;
		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::elementType elementType;
		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::nodeCalculator nodeCalculator;
		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::frontInfo frontInfo;
		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::globalData frontData;
		typedef typename aft_model_traits<ModelType, SizeFun, MetricFun>::cacheType cache;

		//typedef typename frontInfo::frontType frontType;
		typedef typename frontInfo::nodeType nodeType;
		typedef typename nodeType::ptType Point;

		static constexpr bool isTwoDimension = is_two_dimension<(int)Point::dim>::value;

		typedef Entity_StaticData<Point, typename elementType::connectType>
			staticMesh;

		typedef Aft_MetricPrcsr<frontType, SizeFun, MetricFun> metricPrcsr;

	private:

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		//- Boundary size map which may be different with the domain's size map
		std::shared_ptr<metricPrcsr> theBoundaryMap_;

		std::vector<std::shared_ptr<frontType>> theBoundaryEntity_;


		std::shared_ptr<staticMesh> theTriangulation_;


		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << " This function is not supposed to be called!" << endl;
			NotImplemented;
		}

		void Import
		(
			const std::vector<std::shared_ptr<frontType>>& theBoundary,
			const std::shared_ptr<metricPrcsr>& theBoundaryMap
		);

		//- static functions and operators

		static Entity_Box<Point>
			RetrieveBoundingBox
			(
				const std::vector<std::shared_ptr<nodeType>>& theNodes
			);

		static void CheckBoundary
		(
			const std::vector<std::shared_ptr<frontType>>& theFronts
		);

	protected:

		auto& ChangeBoundary()
		{
			return theBoundaryEntity_;
		}

		Standard_Integer Meshing();

		void MeshingOneLevel();

		void FindValidNode
		(
			const std::vector<std::shared_ptr<nodeType>>& theCandidates,
			const std::vector<std::shared_ptr<frontType>>& theEffectives
		);

		void Update();

		void InsertNewFrontsToLevels();

	public:

		//- default constructor

		Aft_Model()
		{}

		//- constructors


		//- public functions and operators

		Standard_Boolean IsBoundaryLoaded() const;
		Standard_Boolean IsBoundaryMapLoaded() const;
		Standard_Boolean IsLoaded() const;

		const std::vector<std::shared_ptr<frontType>>& GetBoundaryEntities() const;
		const std::shared_ptr<staticMesh>& GetTriangulation() const;
		const std::shared_ptr<metricPrcsr>& GetBoundaryMap() const;


		void Perform();

		void CreateStaticMesh();

		void CompactNumbering(const std::vector<std::shared_ptr<elementType>>& theElements) const;

		void LoadBoundaryEdges
		(
			const std::vector<std::shared_ptr<frontType>>& theBoundaryEdges
		)
		{
			theBoundaryEntity_ = theBoundaryEdges;
		}

		void LoadBoundaryMetricMap
		(
			const std::shared_ptr<metricPrcsr>& theSizeMap
		)
		{
			theBoundaryMap_ = theSizeMap;
		}

		//- static functions and operators

		static void ActiveFront
		(
			const std::vector<std::shared_ptr<frontType>>& theEdges
		);

		static std::vector<std::shared_ptr<nodeType>>
			RetrieveNodesFrom
			(
				const std::vector<std::shared_ptr<frontType>>& theFronts
			);

		static std::vector<std::shared_ptr<nodeType>>
			RetrieveNodesFrom
			(
				const std::vector<std::shared_ptr<elementType>>& theElements
			);

		static std::vector<std::shared_ptr<frontType>>
			RetrieveEdgesFrom
			(
				const std::vector<std::shared_ptr<elementType>>& theElements
			);

		static std::vector<Point>
			RetrieveGeometryFrom
			(
				const std::vector<std::shared_ptr<nodeType>>& theNodes
			);

		static std::vector<typename elementType::connectType>
			RetrieveGeometryFrom
			(
				const std::vector<std::shared_ptr<elementType>>& theElements,
				std::map<unsigned, unsigned>& theNodesIndices
			);
	};
}

#include <Aft_ModelI.hxx>

#endif // !_Aft_Model_Base_Header
