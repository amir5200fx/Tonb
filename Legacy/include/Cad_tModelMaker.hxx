#pragma once
#ifndef _Cad_tModelMaker_Header
#define _Cad_tModelMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>
#include <Cad_TModelManagersFwd.hxx>

#include <opencascade/TopoDS_Shape.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/6/2022 Amir]
	class Cad_TModel;
	class Cad_tModelMakerInfo;
	class Cad_tEdgeMakerInfo;
	class Cad_tSurfaceMakerInfo;
	class Cad_tModelMaker_PairCrvCriterion;

	class Cad_tModelMaker
		: public Global_Done
	{

	public:

		struct MakerInfo
		{
			std::shared_ptr<Cad_tModelMakerInfo> modelInfo;
			std::shared_ptr<Cad_tEdgeMakerInfo> edgeInfo;
			std::shared_ptr<Cad_tSurfaceMakerInfo> surfInfo;

			MakerInfo() {}

			TnbCad_EXPORT MakerInfo
			(
				const std::shared_ptr<Cad_tModelMakerInfo>& theModelInfo,
				const std::shared_ptr<Cad_tEdgeMakerInfo>& theEdgeInfo,
				const std::shared_ptr<Cad_tSurfaceMakerInfo>& theSurfaceInfo
			);

			TnbCad_EXPORT void Check() const;
		};

	private:

		/*Private Data*/

		TopoDS_Shape theShape_;

		std::shared_ptr<MakerInfo> theInfo_;
		std::shared_ptr<Cad_tModelMaker_PairCrvCriterion> theCriterion_;

		// results [1/6/2022 Amir]

		std::shared_ptr<Cad_TModel> theModel_;


		// private functions and operators [1/9/2022 Amir]

		static TnbCad_EXPORT void SetCornerManager(std::shared_ptr<TModel_CornerManager>&&, const std::shared_ptr<Cad_TModel>&);
		static TnbCad_EXPORT void SetSegmentManager(std::shared_ptr<TModel_SegmentManager>&&, const std::shared_ptr<Cad_TModel>&);
		static TnbCad_EXPORT void SetFaceManager(std::shared_ptr<TModel_FaceManager>&&, const std::shared_ptr<Cad_TModel>&);

	public:

		static TnbCad_EXPORT unsigned short verbose;

		static TnbCad_EXPORT const std::shared_ptr<MakerInfo> DEFAULT_INFO;
		static TnbCad_EXPORT const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion> DEFAULT_CRITERION;

		// default constructor [1/6/2022 Amir]

		Cad_tModelMaker()
			: theInfo_(DEFAULT_INFO)
			, theCriterion_(DEFAULT_CRITERION)
		{}

		// constructors [1/6/2022 Amir]

		Cad_tModelMaker
		(
			const TopoDS_Shape& theShape,
			const std::shared_ptr<MakerInfo>& theInfo,
			const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>& theCriterion
		)
			: theShape_(theShape)
			, theInfo_(theInfo)
			, theCriterion_(theCriterion)
		{}


		// public functions and operators [1/6/2022 Amir]

		const auto& Shape() const
		{
			return theShape_;
		}

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& GetInfo() const
		{
			return theInfo_;
		}

		const auto& PairCriterion() const
		{
			return theCriterion_;
		}

		TnbCad_EXPORT void Perform();
		TnbCad_EXPORT void MakeSolid();

	};
}

#endif // !_Cad_tModelMaker_Header
