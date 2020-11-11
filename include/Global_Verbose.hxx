#pragma once
#ifndef _Global_Verbose_Header
#define _Global_Verbose_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Global_Verbose
	{

		/*Private Data*/

		Standard_Integer theVerbose_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theVerbose_;
		}

	protected:

		Global_Verbose()
			: theVerbose_(0)
		{}

	public:

		Standard_Integer Verbose() const
		{
			return theVerbose_;
		}

		Standard_Integer& Verbose()
		{
			return theVerbose_;
		}

		void SetVerbisity(const Standard_Integer theVerbose)
		{
			theVerbose_ = theVerbose;
		}
	};
}

#endif // !_Global_Verbose_Header
