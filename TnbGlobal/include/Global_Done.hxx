#pragma once
#ifndef _Global_Done_Header
#define _Global_Done_Header

#include <Global_CascadeTypes.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Global_Done
	{

		/*Private Data*/

		Standard_Boolean IsDone_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & IsDone_;
		}

	protected:

		Global_Done()
			: IsDone_(Standard_False)
		{}

		Standard_Boolean& Change_IsDone()
		{
			return IsDone_;
		}

	public:

		Standard_Boolean IsDone() const
		{
			return IsDone_;
		}
	};
}

#endif // !_Global_Done_Header
