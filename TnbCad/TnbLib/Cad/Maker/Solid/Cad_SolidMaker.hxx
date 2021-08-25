#pragma once
#ifndef _Cad_SolidMaker_Header
#define _Cad_SolidMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>
#include <Cad_TModelManagersFwd.hxx>

#include <memory>
#include <vector>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Surface;
	class Cad_TModel;
	class TModel_Vertex;

	class Cad_SolidMaker
		: public Global_Done
	{

		/*Private Data*/

		const TopoDS_Shape& theShape_;

		Standard_Real theRadius_;
		Standard_Real theTol_;

		std::shared_ptr<Cad_TModel> theSolid_;


		//- private functions and operators

		static TnbCad_EXPORT void SetCornerManager(std::shared_ptr<TModel_CornerManager>&&, const std::shared_ptr<Cad_TModel>&);
		static TnbCad_EXPORT void SetSegmentManager(std::shared_ptr<TModel_SegmentManager>&&, const std::shared_ptr<Cad_TModel>&);
		static TnbCad_EXPORT void SetFaceManager(std::shared_ptr<TModel_FaceManager>&&, const std::shared_ptr<Cad_TModel>&);

	public:

		//- default constructor


		//- constructors

		Cad_SolidMaker
		(
			const TopoDS_Shape& theShape,
			const Standard_Real theMinTol,
			const Standard_Real theMaxTol
		)
			: theShape_(theShape)
			, theTol_(theMinTol)
			, theRadius_(theMaxTol)
		{}


		//- public functions and operators

		const auto& Shape() const
		{
			return theShape_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		const auto& Solid() const
		{
			return theSolid_;
		}

		TnbCad_EXPORT void Perform();
	};
}

#endif // !_Cad_SolidMaker_Header
