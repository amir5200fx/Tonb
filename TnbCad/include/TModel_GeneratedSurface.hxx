#pragma once
#ifndef _TModel_GeneratedSurface_Header
#define _TModel_GeneratedSurface_Header

#include <TModel_Surface.hxx>
#include <GModel_SurfaceGeometry.hxx>
#include <TModel_FaceOrientation.hxx>

namespace tnbLib
{

	class TModel_GeneratedSurface
		: public TModel_Surface
		, public GModel_SurfaceGeometry
	{

		typedef std::shared_ptr<TModel_Wire> outer;
		typedef std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> inners;

		/*Private Data*/

		outer theOuter_;
		inners theInners_;

		Entity2d_Box theParaBoundingBox_;

		TModel_FaceOrientation theOrientation_;

		//- Private functions and operators

		TnbCad_EXPORT void CalcParametricBoundingBox();

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [3/8/2023 Payvand]

		TModel_GeneratedSurface()
		{}

	public:

		// constructors [3/8/2023 Payvand]

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inners& theInner = nullptr
		);

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			std::shared_ptr<Cad_GeomSurface>&& theGeometry,
			outer&& theOuter,
			inners&& theInner
		);

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inners& theInner = nullptr
		);

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Cad_GeomSurface>&& theGeometry,
			outer&& theOuter,
			inners&& theInners
		);

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inners& theInners = nullptr
		);

		TnbCad_EXPORT TModel_GeneratedSurface
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Cad_GeomSurface>&& theGeometry,
			outer&& theOuter,
			inners&& theInners
		);

		// Public functions and operators [3/8/2023 Payvand]

		TnbCad_EXPORT Standard_Boolean HasHole() const;
		TnbCad_EXPORT Standard_Integer NbHoles() const;

		const auto& Outer() const { return theOuter_; }
		const auto& Inners() const { return theInners_; }

		const auto& ParaBoundingBox() const { return theParaBoundingBox_; }

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Edge>>
			RetrieveEdges() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_GeneratedSurface);

#endif // !_TModel_GeneratedSurface_Header
