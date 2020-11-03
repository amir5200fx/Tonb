#pragma once
#ifndef _Marine_Section_Header
#define _Marine_Section_Header

#include <Marine_Module.hxx>
#include <Marine_CoordinatedEntity.hxx>
#include <Marine_SectionType.hxx>
#include <Global_Serialization.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

class gp_Trsf2d;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	class Marine_Section
		: public Marine_CoordinatedEntity
	{

		/*Private Data*/

		std::shared_ptr<Pln_Wire> theWire_;


		/*private functions and operators*/

		Marine_Section()
		{}

		auto& ChangeWire()
		{
			return theWire_;
		}

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);
		

		static void CheckWire(const Pln_Wire& theWire, const char* theName);

	protected:

		Marine_Section
		(
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_Section
		(
			std::shared_ptr<Pln_Wire>&& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Pln_Wire>&& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Pln_Wire>&& theWire
		);

	public:

		Entity2d_Box BoundingBox() const;

		const auto& Wire() const
		{
			return theWire_;
		}

		void Transform(const gp_Trsf2d& t);

		void ExportToPlt(OFstream& File) const;

		virtual Standard_Boolean IsWaterSection() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}

		virtual std::shared_ptr<Marine_Section> Copy() const = 0;

		virtual Marine_SectionType Type() const = 0;

		//- static functions

		static Standard_Real 
			GetXcoord
			(
				const std::shared_ptr<Marine_Section>& theSection
			);


	};
}

#endif // !_Marine_Section_Header
