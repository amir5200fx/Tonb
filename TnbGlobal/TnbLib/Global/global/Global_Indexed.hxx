#pragma once
#ifndef _Global_Indexed_Header
#define _Global_Indexed_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Global_Indexed
	{

		/*Private Data*/

		Standard_Integer theIndex_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & theIndex_;
		}

	protected:

		Global_Indexed()
			: theIndex_(0)
		{}

		Global_Indexed
		(
			const Standard_Integer theIndex
		)
			: theIndex_(theIndex)
		{}

	public:

		Standard_Integer Index() const
		{
			return theIndex_;
		}

		Standard_Integer& Index()
		{
			return theIndex_;
		}

		void SetIndex(const Standard_Integer theIndex)
		{
			theIndex_ = theIndex;
		}
	};
}

#endif // !_Global_Indexed_Header
