#pragma once
#ifndef _Cad_tSurfaceMaker_Header
#define _Cad_tSurfaceMaker_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <TopoDS_Face.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/6/2022 Amir]
	class TModel_Surface;
	class Cad_tEdgeMakerInfo;
	class Cad_tSurfaceMakerInfo;

	class Cad_tSurfaceMaker
		: public Global_Done
	{

	public:

		struct MakerInfo
		{
			std::shared_ptr<Cad_tEdgeMakerInfo> Edge;
			std::shared_ptr<Cad_tSurfaceMakerInfo> Surface;
		};

	private:

		/*Private Data*/


		// inputs [1/6/2022 Amir]
		TopoDS_Face theFace_;

		std::shared_ptr<MakerInfo> theInfo_;

		// outputs [1/6/2022 Amir]

		std::shared_ptr<TModel_Surface> theSurface_;

	public:

		static TnbCad_EXPORT const std::shared_ptr<MakerInfo> DEFAULT_INFO;

		// default constructor [1/7/2022 Amir]

		Cad_tSurfaceMaker()
			: theInfo_(DEFAULT_INFO)
		{}

		// constructors [1/7/2022 Amir]

		Cad_tSurfaceMaker
		(
			const TopoDS_Face& theFace,
			const std::shared_ptr<MakerInfo>& theInfo
		)
			: theFace_(theFace)
			, theInfo_(theInfo)
		{}


		// public functions and operators [1/7/2022 Amir]

		const auto& Face() const
		{
			return theFace_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		TnbCad_EXPORT void Perform();

		void SetFace(const TopoDS_Face& theFace)
		{
			theFace_ = theFace;
		}

		void SetInfo(const std::shared_ptr<MakerInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}
	}; 
}

#endif // !_Cad_tSurfaceMaker_Header
