#pragma once
#ifndef _MeshBLayer2d_AdvLayer_Header
#define _MeshBLayer2d_AdvLayer_Header

#include <MeshBLayer2d_AdvLayer_EdgeSet.hxx>
#include <MeshBLayer2d_AdvLayer_NodeList.hxx>
#include <MeshBLayer2d_AdvLayer_NodeCondition.hxx>
#include <MeshBLayer2d_Node.hxx>
#include <Geo2d_SizeFunFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo_AdTree.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class MeshBLayer2d_AdvLayer
		: public Global_Done
	{

		/*Private Data*/

		meshBLayerLib::AdvLayer_NodeCondition theCondition_;

		std::shared_ptr<Geo2d_SizeFun> theSizeFun_;
		std::shared_ptr<Geo2d_MetricFunction> theMetricFun_;

		meshBLayerLib::AdvLayer_NodeList theFronts_;
		meshBLayerLib::AdvLayer_EdgeSet theEdges_;

		Geo_AdTree<std::shared_ptr<MeshBLayer2d_Node>> theEngine_;

		// Private functions and operators [1/31/2023 Payvand]

		const auto& Condition() const
		{
			return theCondition_;
		}

		auto& ConditionRef()
		{
			return theCondition_;
		}

		const auto& Fronts() const
		{
			return theFronts_;
		}

		auto& FrontsRef()
		{
			return theFronts_;
		}

		auto& EngineRef()
		{
			return theEngine_;
		}

		std::pair<Pnt2d, meshBLayerLib::AdvLayer_NodeCondition> IsMovable(const std::shared_ptr<MeshBLayer2d_Node>&) const;

		void ExecuteOneLevel();

	public:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_AdvLayer()
		{}


		// Constructors [1/31/2023 Payvand]


		// Public functions and operators [1/31/2023 Payvand]

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& SizeFun() const
		{
			return theSizeFun_;
		}

		const auto& MetricFun() const
		{
			return theMetricFun_;
		}

		void Perform();

		void SetSizeFun(const std::shared_ptr<Geo2d_SizeFun>&);
		

	};
}

#endif // !_MeshBLayer2d_AdvLayer_Header
