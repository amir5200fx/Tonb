#pragma once
#ifndef _PtdModel_SolidMaker_PropBlade_Header
#define _PtdModel_SolidMaker_PropBlade_Header

#include <Standard_Handle.hxx>
#include <Global_Done.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

// Forward Declarations
class Geom_Surface;
class Geom_BSplineCurve;
class TopoDS_Shape;

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropBlade;
	class PtdModel_Face;
	class Cad_Shape;

	namespace ptdModel
	{

		// Forward Declarations
		class Shape_PropBladeParent;

		class SolidMaker_PropBlade
			: public Global_Done
		{

		public:

			//struct Faces
			//{

			//	/*Private Data*/

			//	std::shared_ptr<PtdModel_Face> Tip;
			//	std::shared_ptr<PtdModel_Face> Root;

			//	std::shared_ptr<PtdModel_Face> Leading;
			//	std::shared_ptr<PtdModel_Face> Trailing;

			//	TNB_SERIALIZATION(TnbPtdModel_EXPORT);
			//};

		private:

			/*Private Data*/

			std::shared_ptr<PtdModel_PropBlade> theBlade_;

			//std::shared_ptr<Faces> theFaces_;

			Standard_Real theTolerance_;

			Standard_Boolean hasLeadingPatch_;
			Standard_Boolean hasTrailingPatch_;


			std::shared_ptr<Shape_PropBladeParent> theShape_;

			//- private functions and operators


			TNB_SERIALIZATION(TnbPtdModel_EXPORT);


			static TnbPtdModel_EXPORT std::pair<Handle(Geom_Surface), Handle(Geom_Surface)>
				RetrievePatches(const std::shared_ptr<PtdModel_PropBlade>&);

			static TnbPtdModel_EXPORT std::vector<Handle(Geom_BSplineCurve)>
				RetrieveCurves(const TopoDS_Shape&);

		public:


			static TnbPtdModel_EXPORT const Standard_Real DEFAULT_TOLERANCE;

			//- default constructor

			SolidMaker_PropBlade()
				: theTolerance_(DEFAULT_TOLERANCE)
				, hasLeadingPatch_(Standard_True)
				, hasTrailingPatch_(Standard_True)
			{}


			//- constructors

			SolidMaker_PropBlade(const std::shared_ptr<PtdModel_PropBlade>& theBlade)
				: theBlade_(theBlade)
				, theTolerance_(DEFAULT_TOLERANCE)
				, hasLeadingPatch_(Standard_True)
				, hasTrailingPatch_(Standard_True)
			{}

			SolidMaker_PropBlade(std::shared_ptr<PtdModel_PropBlade>&& theBlade)
				: theBlade_(std::move(theBlade))
				, theTolerance_(DEFAULT_TOLERANCE)
				, hasLeadingPatch_(Standard_True)
				, hasTrailingPatch_(Standard_True)
			{}


			//- public functions and operators

			const auto& Blade() const
			{
				return theBlade_;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			auto Tolerance() const
			{
				return theTolerance_;
			}

			auto HasTrailingPatch() const
			{
				return hasTrailingPatch_;
			}

			auto HasLeadingPatch() const
			{
				return hasLeadingPatch_;
			}

			TnbPtdModel_EXPORT void Perform();

			inline void LoadBlade(const std::shared_ptr<PtdModel_PropBlade>&);
			inline void LoadBlade(std::shared_ptr<PtdModel_PropBlade>&&);
			inline void SetTolerance(const Standard_Real);
			inline void SetToCreateLeadingPatch(const Standard_Boolean);
			inline void SetToCreateTrailingPatch(const Standard_Boolean);
		};
	}
}

#include <PtdModel_SolidMaker_PropBladeI.hxx>

#endif // !_PtdModel_SolidMaker_PropBlade_Header
