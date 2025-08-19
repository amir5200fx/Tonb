#pragma once
#ifndef _Model_Parameter_Header
#define _Model_Parameter_Header

#include <Model_Entity.hxx>
#include <Model_Module.hxx>

namespace tnbLib
{

	class Model_Parameter
		: public Model_Entity
	{

		/*Private Data*/

		Standard_Real theValue_;

	protected:

		// default constructor [12/20/2022 Payvand]

		Model_Parameter()
			: Model_Entity(0, "Parameter")
			, theValue_(0)
		{}


		// constructors [12/20/2022 Payvand]

		Model_Parameter
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue = 0
		)
			: Model_Entity(theIndex, theName)
			, theValue_(theValue)
		{}

	public:

		// Public functions and operators [12/20/2022 Payvand]

		virtual ~Model_Parameter()
		{}


		virtual Standard_Real Lower() const = 0;
		virtual Standard_Real Upper() const = 0;

		virtual Standard_Boolean IsBounded() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsUnbounded() const
		{
			return Standard_False;
		}

		auto Value() const
		{
			return theValue_;
		}

		auto& ValueRef()
		{
			return theValue_;
		}

		auto operator()() const
		{
			return Value();
		}

		auto& operator()()
		{
			return ValueRef();
		}

		void SetValue(const Standard_Real x);

	};
}

#endif // !_Model_Parameter_Header
