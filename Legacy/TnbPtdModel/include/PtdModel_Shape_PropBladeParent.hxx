#pragma once
#ifndef _PtdModel_Shape_PropBladeParent_Header
#define _PtdModel_Shape_PropBladeParent_Header

#include <PtdModel_Shape_PropBlade.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class Shape_PropBladeParent
			: public Shape_PropBlade
		{

			/*Private Data*/

			std::shared_ptr<PtdModel_BladeGlobalPars> theInfo_;

			std::vector<std::shared_ptr<PtdModel_Face>> theFaces_;

			gp_Ax2 theAx_;

			//- private functions and operators

			TNB_SERIALIZATION(TnbPtdModel_EXPORT);

		public:

			//- default constructor

			Shape_PropBladeParent()
			{}


			//- constructors

			TnbPtdModel_EXPORT Shape_PropBladeParent
			(
				const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo,
				const std::shared_ptr<Cad_Shape>&,
				const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces
			);

			TnbPtdModel_EXPORT Shape_PropBladeParent
			(
				std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo,
				std::shared_ptr<Cad_Shape>&&,
				std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces
			);

			TnbPtdModel_EXPORT Shape_PropBladeParent
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo,
				const std::shared_ptr<Cad_Shape>&,
				const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces
			);

			TnbPtdModel_EXPORT Shape_PropBladeParent
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo,
				std::shared_ptr<Cad_Shape>&&,
				std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces
			);


			//- public functions and operators

			const auto& Axis() const
			{
				return theAx_;
			}

			const auto& BladeInfo() const
			{
				return theInfo_;
			}

			const auto& Faces() const
			{
				return theFaces_;
			}

			TnbPtdModel_EXPORT void SetInfo(const std::shared_ptr<PtdModel_BladeGlobalPars>& theInfo);
			TnbPtdModel_EXPORT void SetInfo(std::shared_ptr<PtdModel_BladeGlobalPars>&& theInfo);

			TnbPtdModel_EXPORT void SetFaces(const std::vector<std::shared_ptr<PtdModel_Face>>& theFaces);
			TnbPtdModel_EXPORT void SetFaces(std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces);

			void SetAxis(const gp_Ax2&);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ptdModel::Shape_PropBladeParent);

#endif // !_PtdModel_Shape_PropBladeParent_Header
