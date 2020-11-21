#pragma once
#ifndef _Marine_Criterion_Standard_Header
#define _Marine_Criterion_Standard_Header

#include <Standard_TypeDef.hxx>
#include <Marine_Module.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Criterion_Standard
		{

			/*Private Data*/

			Standard_Real theValue_;

		public:

			TnbMarine_EXPORT Criterion_Standard();

			Criterion_Standard(const Standard_Real theValue)
				: theValue_(theValue)
			{}

			auto& Value()
			{
				return theValue_;
			}

			auto Value() const
			{
				return theValue_;
			}

			const Standard_Real& operator()() const
			{
				return Value();
			}

			Standard_Real& operator()()
			{
				return Value();
			}
		};
	}
}

#endif // !_Marine_Criterion_Standard_Header
