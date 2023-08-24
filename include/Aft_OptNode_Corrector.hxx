#pragma once
#ifndef _Aft_OptNode_Corrector_Header
#define _Aft_OptNode_Corrector_Header

#include <Global_Done.hxx>
#include <Geo_SizeFunctionTraits.hxx>
#include <Aft_OptNode_CorrectorType.hxx>
#include <Mesh_Module.hxx>

#ifdef TnbMesh_EXPORT_DEFINE
#define TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT __declspec(dllexport)
#else
#ifdef TnbMesh_AFTOPTNODECORR_VERBOSE_DEFINE
#define TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT __declspec(dllexport)
#else
#define TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{

	// Forward Declarations
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	template
		<
		Aft_OptNode_CorrectorType Type, 
		class FrontType, 
		class InfoType, 
		class SizeFun, 
		class OptNodeCalculator = void,
		class MetricFun = void
		>
	class Aft_OptNode_Corrector
		: public Global_Done
	{

	public:

		typedef typename point_type_from_sizeMap<SizeFun>::ptType Point;
		typedef Aft_MetricPrcsr<FrontType, SizeFun, MetricFun> metricMap;

	private:

		/*Private Data*/

		Standard_Real theSize_;

		const std::shared_ptr<OptNodeCalculator>& theCalculator_;

		const std::shared_ptr<metricMap>& theMap_;
		const std::shared_ptr<FrontType>& theFront_;
		const Point& theP0_;

		Point theCoord_;

		Standard_Boolean IsConverged_;

	protected:


		auto& CoordRef()
		{
			return theCoord_;
		}

		auto& IsConvergedRef()
		{
			return IsConverged_;
		}

	public:

		static TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT unsigned short verbose;

		// default constructor [3/1/2022 Amir]


		// constructors [3/1/2022 Amir]

		Aft_OptNode_Corrector
		(
			const std::shared_ptr<OptNodeCalculator>& theNodeCalculator,
			const std::shared_ptr<metricMap>& theMap,
			const std::shared_ptr<FrontType>& theFront,
			const Point& theP0,
			const Standard_Real theSize
		)
			: theCalculator_(theNodeCalculator)
			, theMap_(theMap)
			, theFront_(theFront)
			, theP0_(theP0)
			, theSize_(theSize)
			, IsConverged_(Standard_False)
		{}


		// public functions and operators [3/1/2022 Amir]

		const auto& NodeCalculator() const
		{
			return theCalculator_;
		}

		auto Size() const
		{
			return theSize_;
		}

		const auto& MetricMap() const
		{
			return theMap_;
		}

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		void Perform(const InfoType& theInfo);
	};


	template
		<
		Aft_OptNode_CorrectorType Type,
		class FrontType,
		class InfoType,
		class SizeFun,
		class MetricFun
		>
		class Aft_OptNode_Corrector<Type, FrontType, InfoType, SizeFun, void, MetricFun>
		: public Global_Done
	{
	public:

		typedef typename point_type_from_sizeMap<SizeFun>::ptType Point;
		typedef Aft_MetricPrcsr<FrontType, SizeFun, MetricFun> metricMap;

	private:

		/*Private Data*/

		Standard_Real theSize_;

		const std::shared_ptr<metricMap>& theMap_;
		const std::shared_ptr<FrontType>& theFront_;
		const Point& theP0_;

		Point theCoord_;

		Standard_Boolean IsConverged_;

	protected:

		auto& CoordRef()
		{
			return theCoord_;
		}

		auto& IsConvergedRef()
		{
			return IsConverged_;
		}

	public:

		static TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT unsigned short verbose;

		// default constructor [3/7/2022 Amir]


		// constructors [3/7/2022 Amir]

		Aft_OptNode_Corrector
		(
			const std::shared_ptr<metricMap>& theMap,
			const std::shared_ptr<FrontType>& theFront,
			const Point& theP0,
			const Standard_Real theSize
		)
			: theMap_(theMap)
			, theFront_(theFront)
			, theP0_(theP0)
			, theSize_(theSize)
			, IsConverged_(Standard_False)
		{}


		// public functions and operators [3/7/2022 Amir]

		auto Size() const
		{
			return theSize_;
		}

		const auto& MetricMap() const
		{
			return theMap_;
		}

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		void Perform(const InfoType& theInfo);

	};


	template
		<
		Aft_OptNode_CorrectorType Type,
		class FrontType,
		class InfoType,
		class SizeFun
		>
		class Aft_OptNode_Corrector<Type, FrontType, InfoType, SizeFun, void, void>
		: public Global_Done
	{

	public:

		typedef typename point_type_from_sizeMap<SizeFun>::ptType Point;
		typedef Aft_MetricPrcsr<FrontType, SizeFun, void> metricMap;

	private:

		/*Private Data*/

		Standard_Real theSize_;

		const std::shared_ptr<metricMap>& theMap_;
		const std::shared_ptr<FrontType>& theFront_;
		const Point& theP0_;

		Point theCoord_;

		Standard_Boolean IsConverged_;

	protected:


		auto& CoordRef()
		{
			return theCoord_;
		}

		auto& IsConvergedRef()
		{
			return IsConverged_;
		}

	public:

		static TnbMesh_AFTOPTNODECORR_VERBOSE_EXPORT unsigned short verbose;

		// default constructor [3/1/2022 Amir]


		// constructors [3/1/2022 Amir]

		Aft_OptNode_Corrector
		(
			const std::shared_ptr<metricMap>& theMap,
			const std::shared_ptr<FrontType>& theFront,
			const Point& theP0,
			const Standard_Real theSize
		)
			: theMap_(theMap)
			, theFront_(theFront)
			, theP0_(theP0)
			, theSize_(theSize)
			, IsConverged_(Standard_False)
		{}


		// public functions and operators [3/1/2022 Amir]

		auto Size() const
		{
			return theSize_;
		}

		const auto& MetricMap() const
		{
			return theMap_;
		}

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		const auto& P0() const
		{
			return theP0_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		void Perform(const InfoType& theInfo);
	};
}

#endif // !_Aft_OptNode_Corrector_Header
