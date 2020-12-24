#pragma once
#ifndef _Marine_CmpSection_Header
#define _Marine_CmpSection_Header

#include <Entity2d_BoxFwd.hxx>
#include <Marine_CoordinatedEntity.hxx>
#include <Marine_SectionType.hxx>
#include <Marine_Module.hxx>
#include <OFstream.hxx>

#include <vector>
#include <list>

#include <Standard_Handle.hxx>

class TopoDS_Edge;
class TopoDS_Shape;
class Geom2d_Curve;
class gp_Trsf2d;

namespace tnbLib
{

	// Forward Declarations
	class MarineBase_Tools;
	class Marine_Section;
	class Marine_SectTools;
	class Pln_Curve;
	class Pln_Wire;

	class Marine_CmpSection
		: public Marine_CoordinatedEntity
	{

		friend class MarineBase_Tools;
		friend class Marine_SectTools;

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_Section>> theSections_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	protected:	

		TnbMarine_EXPORT void Insert
		(
			const std::shared_ptr<Marine_Section>& theSection
		);

	protected:

		TnbMarine_EXPORT Marine_CmpSection();

		TnbMarine_EXPORT Marine_CmpSection
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_CmpSection
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		TnbMarine_EXPORT Marine_CmpSection
		(
			const std::shared_ptr<Marine_Section>& theSection
		);

		TnbMarine_EXPORT Marine_CmpSection
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Marine_Section>& theSection
		);

		TnbMarine_EXPORT Marine_CmpSection
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<Marine_Section>& theSection
		);

		static TnbMarine_EXPORT Standard_Boolean
			LessDiameterSize
			(
				const std::shared_ptr<Pln_Wire>& theW0, 
				const std::shared_ptr<Pln_Wire>& theW1
			);

		static TnbMarine_EXPORT void
			SortWires
			(
				std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbMarine_EXPORT void
			RetrieveInnerOuterWires
			(
				std::list<std::shared_ptr<Pln_Wire>>& theWires,
				std::shared_ptr<Pln_Wire>& theOuter, 
				std::vector<std::shared_ptr<Pln_Wire>>& theInners
			);

	public:

		static TnbMarine_EXPORT const std::shared_ptr<Marine_CmpSection> null;

		TnbMarine_EXPORT Entity2d_Box BoundingBox() const;

		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		auto& ChangeSections()
		{
			return theSections_;
		}

		TnbMarine_EXPORT Marine_SectionType Type() const;

		virtual Standard_Boolean IsXsection() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsZsection() const
		{
			return Standard_False;
		}

		virtual Standard_Real X() const = 0; 

		virtual std::shared_ptr<Marine_CmpSection> Copy() const = 0;

		TnbMarine_EXPORT void Transform(const gp_Trsf2d& t);

		TnbMarine_EXPORT void ExportToPlt(OFstream& File) const;

		static TnbMarine_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveParaCurves
			(
				const std::vector<TopoDS_Edge>& theEdges,
				const gp_Ax2& theSystem
			);

		static TnbMarine_EXPORT std::vector<TopoDS_Edge>
			RetrieveEdges
			(
				const TopoDS_Shape& theEdges
			);

		//- saving and loading the composite sections outside of the project!
		static void Save(TNB_oARCH_TYPE& ar, const std::shared_ptr<Marine_CmpSection>&);
		static void Load(TNB_oARCH_TYPE& ar, std::shared_ptr<Marine_CmpSection>&);

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_CmpSection);

#endif // !_Marine_CmpSection_Header
