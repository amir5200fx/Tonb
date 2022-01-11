#pragma once
#ifndef _Cad_tEdgeMaker_Header
#define _Cad_tEdgeMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <memory>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>

namespace tnbLib
{

	// Forward Declarations [1/6/2022 Amir]
	class TModel_Edge;
	class Cad_tEdgeMakerInfo;

	class Cad_tEdgeMaker
		: public Global_Done
	{

		/*Private Data*/


		// inputs [1/6/2022 Amir]

		TopoDS_Edge theShape_;
		TopoDS_Face theFace_;

		std::shared_ptr<Cad_tEdgeMakerInfo> theInfo_;

		// outputs [1/6/2022 Amir]

		std::shared_ptr<TModel_Edge> theEdge_;

	public:

		static TnbCad_EXPORT const std::shared_ptr<Cad_tEdgeMakerInfo> DEFAULT_INFO;

		// default constructor [1/6/2022 Amir]

		Cad_tEdgeMaker()
			: theInfo_(DEFAULT_INFO)
		{}

		// constructors [1/6/2022 Amir]

		Cad_tEdgeMaker
		(
			const TopoDS_Edge& theShape,
			const TopoDS_Face& theFace,
			const std::shared_ptr<Cad_tEdgeMakerInfo>& theInfo
		)
			: theShape_(theShape)
			, theFace_(theFace)
			, theInfo_(theInfo)
		{}

		// public functions and operators [1/6/2022 Amir]

		const auto& Shape() const
		{
			return theShape_;
		}

		const auto& Face() const
		{
			return theFace_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		const auto& Edge() const
		{
			return theEdge_;
		}
		
		TnbCad_EXPORT void Perform();
		
		void SetShape(const TopoDS_Edge& theEdge)
		{
			theShape_ = theEdge;
		}

		void SetFace(const TopoDS_Face& theFace)
		{
			theFace_ = theFace;
		}
	};
}

#endif // !_Cad_tEdgeMaker_Header
