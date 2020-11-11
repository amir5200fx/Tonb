#pragma once
#ifndef _Global_Named_Header
#define _Global_Named_Header

#include <Global_Serialization.hxx>
#include <word.hxx>

namespace tnbLib
{

	class Global_Named
	{

		/*Private Data*/

		word theName_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theName_;
		}

	protected:

		Global_Named()
		{}

		Global_Named
		(
			const word& theName
		)
			: theName_(theName)
		{}

	public:

		const word& Name() const
		{
			return theName_;
		}

		word& Name()
		{
			return theName_;
		}

		void SetName(const word& theName)
		{
			theName_ = theName;
		}
	};
}

#endif // !_Global_Named_Header
