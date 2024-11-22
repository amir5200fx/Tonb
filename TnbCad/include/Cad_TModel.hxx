#pragma once
#ifndef _Cad_TModel_Header
#define _Cad_TModel_Header

#include <TModel_Entity.hxx>
#include <Cad_TModelManager.hxx>
#include <Entity3d_Box.hxx>
#include <OFstream.hxx>

#include <opencascade/TopoDS_Shape.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Shell;
	class Cad_Tools;
	class Cad_SolidMaker;
	class Cad_tModelMaker;

	class Cad_TModel
		: public TModel_Entity
		, public Cad_TModelManager
	{

		typedef std::vector<std::shared_ptr<TModel_Shell>> shellList;

		typedef std::shared_ptr<TModel_Shell> outer;
		typedef std::shared_ptr<shellList> inner;

		friend class Cad_Tools;
		friend class Cad_SolidMaker;
		friend class Cad_tModelMaker;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		TopoDS_Shape theShape_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:

		void SetShape
		(
			const TopoDS_Shape& theShape
		)
		{
			theShape_ = theShape;
		}

	public:

		static TnbCad_EXPORT const std::string extension;

		// default constructor [1/16/2022 Amir]

		Cad_TModel()
		{}

		explicit Cad_TModel
		(
			const Standard_Integer theIndex
		)
			: TModel_Entity(theIndex, "tmodel")
		{}

		Cad_TModel
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: TModel_Entity(theIndex, theName)
		{}


		// public functions and operators [1/16/2022 Amir]

		const auto& Shape() const
		{
			return theShape_;
		}

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Holes() const
		{
			return theInner_;
		}

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		auto HasHole() const
		{
			return (Standard_Boolean)NbHoles();
		}

		//- IO functions and operators

		TnbCad_EXPORT void ExportCornersToPlt(OFstream& File) const;

		TnbCad_EXPORT void ExportSegmentsToPlt(OFstream& File) const;

		TnbCad_EXPORT void ExportFacesToPlt(OFstream& File) const;

		TnbCad_EXPORT void ExportFreeSegmentsToPlt(OFstream& File) const;


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad_TModel);

#endif // !_Cad_TModel_Header]
