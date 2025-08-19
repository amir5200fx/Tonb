#pragma once
#ifndef _Marine_Criterion_Epln_Header
#define _Marine_Criterion_Epln_Header

#include <word.hxx>
#include <Marine_Module.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Criterion_Epln
		{

			/*Private Data*/

			word theValue_;

		public:

			TnbMarine_EXPORT Criterion_Epln();

			Criterion_Epln(const word& theValue)
				: theValue_(theValue)
			{}

			auto& Value()
			{
				return theValue_;
			}

			const auto& Value() const
			{
				return theValue_;
			}

			const word& operator()() const
			{
				return Value();
			}

			word& operator()()
			{
				return Value();
			}
		};
	}
}

#endif // !_Marine_Criterion_Epln_Header
