#pragma once
#ifndef _Marine_Body_Header
#define _Marine_Body_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_BaseLine.hxx>
#include <Marine_BodyType.hxx>
#include <Marine_SectionType.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_DisctLib;
	class Marine_BodyTools;

	class Marine_Body
		: public Marine_CoordinatedEntity
	{

		friend class Marine_DisctLib;
		friend class Marine_BodyTools;

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_CmpSection>> 
			theSections_;

		Marine_BaseLine theBase_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbMarine_EXPORT);


		void CheckSections();

	protected:
	
		/*template<class... _Types>
		Marine_Body(_Types&&... _Args)
			: Marine_CoordinatedEntity(_Args...)
		{}*/


		//- default constructor

		Marine_Body()
		{}


		//- constructors

		TnbMarine_EXPORT Marine_Body
		(
			const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
		);

		TnbMarine_EXPORT Marine_Body
		(
			std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
		);

		TnbMarine_EXPORT Marine_Body
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
		);

		TnbMarine_EXPORT Marine_Body
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
		);

		auto& ChangeSections()
		{
			return theSections_;
		}

		auto & ChangeBaseLine()
		{
			return theBase_;
		}

	public:

		TnbMarine_EXPORT Standard_Integer NbSections() const;

		const auto& Sections() const
		{
			return theSections_;
		}

		const auto& BaseLine() const
		{
			return theBase_;
		}

		void SetBaseLine(const gp_Ax1& theAx)
		{
			theBase_.BaseLine() = theAx;
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

		virtual Marine_BodyType Type() const = 0;

		virtual std::shared_ptr<Marine_Body>
			Copy() const = 0;

		static TnbMarine_EXPORT void Save(TNB_oARCH_TYPE& ar, const std::shared_ptr<Marine_Body>& theBody);
		static TnbMarine_EXPORT void Load(TNB_iARCH_TYPE& ar, std::shared_ptr<Marine_Body>& theBody);

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_Body);

#endif // !_Marine_Body_Header
