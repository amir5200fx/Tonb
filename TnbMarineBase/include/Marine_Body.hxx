#pragma once
#ifndef _Marine_Body_Header
#define _Marine_Body_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_BaseLine.hxx>
#include <Marine_BodyType.hxx>
#include <Marine_Module.hxx>

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

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

	protected:
	
		template<class... _Types>
		Marine_Body(_Types&&... _Args)
			: Marine_CoordinatedEntity(_Args...)
		{}

		auto& ChangeSections()
		{
			return theSections_;
		}

		auto & ChangeBaseLine()
		{
			return theBase_;
		}

	public:

		Standard_Integer NbSections() const;

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
	};
}

#endif // !_Marine_Body_Header
