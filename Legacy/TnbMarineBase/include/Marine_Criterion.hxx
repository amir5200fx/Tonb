#pragma once
#ifndef _Marine_Criterion_Header
#define _Marine_Criterion_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Marine_Criterion_Epln.hxx>
#include <Marine_Criterion_Standard.hxx>
#include <Marine_Criterion_Status.hxx>
#include <Marine_Criterion_Value.hxx>
#include <Marine_Module.hxx>

namespace tnbLib
{

	class Marine_Criterion
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		marineLib::Criterion_Value theValue_;
		marineLib::Criterion_Standard theStandard_;
		marineLib::Criterion_Epln theExpln_;

		marineLib::Criterion_Status theStatus_;

	public:

		TnbMarine_EXPORT Marine_Criterion();

		TnbMarine_EXPORT Marine_Criterion(const Standard_Integer theIndex, const word& theName);

		const auto& Value() const
		{
			return theValue_;
		}

		const auto& Standard() const
		{
			return theStandard_;
		}

		const auto& Expln() const
		{
			return theExpln_;
		}

		auto Status() const
		{
			return theStatus_;
		}

		void SetValue(const marineLib::Criterion_Value& theValue)
		{
			theValue_ = theValue;
		}

		void SetValue(const marineLib::Criterion_Value&& theValue)
		{
			theValue_ = std::move(theValue);
		}

		void SetStandard(const marineLib::Criterion_Standard& theValue)
		{
			theStandard_ = theValue;
		}

		void SetStandard(const marineLib::Criterion_Standard&& theValue)
		{
			theStandard_ = std::move(theValue);
		}

		void SetExpln(const marineLib::Criterion_Epln& theExpl)
		{
			theExpln_ = theExpl;
		}

		void SetExpln(const marineLib::Criterion_Epln&& theExpl)
		{
			theExpln_ = std::move(theExpl);
		}

		void SetStatus(const marineLib::Criterion_Status st)
		{
			theStatus_ = st;
		}
	};
}

#endif // !_Marine_Criterion_Header
