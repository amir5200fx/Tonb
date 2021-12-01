#pragma once
#ifndef _Aft_Core_Header
#define _Aft_Core_Header

#include <Aft_Core_Base.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template
		<
		class OptNodeAlg, class SizeFun,
		class FrontInfo, class FrontData,
		class MetricFun = void
		>
		class Aft_Core
		: public Aft_Core_Base
		<
		OptNodeAlg, FrontInfo,
		FrontData, SizeFun,
		MetricFun
		>
	{

	public:

		typedef Aft_Core_Base
			<
			OptNodeAlg, FrontInfo,
			FrontData, SizeFun,
			MetricFun
			>
			base;

		typedef typename base::nodeType nodeType;
		typedef typename base::frontType frontType;
		typedef typename base::elementType elementType;

		typedef typename nodeType::ptType Point;

		typedef Mesh_GlobalData<typename FrontInfo::elementType>
			globalData;
		typedef FrontInfo frontInfo;
		typedef FrontData frontData;

		typedef Aft_MetricPrcsr<frontType, SizeFun, MetricFun>
			metricMap;

		/*Private Data*/


		// Private functions and operators [11/24/2021 Amir]


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	protected:


		// Protected functions and operators [11/24/2021 Amir]

		void RetrieveLocalFrontNodes
		(
			std::vector<std::shared_ptr<nodeType>>& theLocals,
			std::vector<std::shared_ptr<nodeType>>& theSearching
		) const;

		void ModifyLocalFront
		(
			const Standard_Real theFactor
		);

		void UpdateFront();

	public:

		//- default constructor

		Aft_Core()
		{}


		//- constructors

		Aft_Core
		(
			const std::shared_ptr<metricMap>& theSizeMap,
			const std::shared_ptr<OptNodeAlg>& theCoordCalculator
		)
			: base(theSizeMap, theCoordCalculator)
		{}
		
	};

	template
		<
		class OptNodeAlg, class SizeFun,
		class FrontInfo, class FrontData
		>
		class Aft_Core
		<
		OptNodeAlg, SizeFun,
		FrontInfo, FrontData,
		void
		>
		: public Aft_Core_Base
		<
		OptNodeAlg, FrontInfo,
		FrontData, SizeFun,
		void
		>
	{

	public:

		typedef Aft_Core_Base
			<
			OptNodeAlg, FrontInfo,
			FrontData, SizeFun,
			void
			>
			base;

		typedef typename base::nodeType nodeType;
		typedef typename base::frontType frontType;
		typedef typename base::elementType elementType;

		typedef typename nodeType::ptType Point;

		typedef Mesh_GlobalData<typename FrontInfo::elementType>
			globalData;
		typedef FrontInfo frontInfo;
		typedef FrontData frontData;

		typedef Aft_MetricPrcsr<frontType, SizeFun, void>
			metricMap;

		/*Private Data*/


		// Private functions and operators [11/24/2021 Amir]


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	protected:


		// Protected functions and operators [11/24/2021 Amir]

		void RetrieveLocalFrontNodes
		(
			std::vector<std::shared_ptr<nodeType>>& theLocals,
			std::vector<std::shared_ptr<nodeType>>& theSearching
		) const;

		void ModifyLocalFront
		(
			const Standard_Real theFactor
		);

		void UpdateFront();


	public:


		// default constructor [11/24/2021 Amir]

		Aft_Core()
		{}


		// constructors [11/24/2021 Amir]

		Aft_Core
		(
			const std::shared_ptr<metricMap>& theSizeMap,
			const std::shared_ptr<OptNodeAlg>& theCoordCalculator
		)
			: base(theSizeMap, theCoordCalculator)
		{}


		// Public functions and operators [11/24/2021 Amir]

	};

}

#include <Aft_CoreI.hxx>

#endif // !_Aft_Core_Header