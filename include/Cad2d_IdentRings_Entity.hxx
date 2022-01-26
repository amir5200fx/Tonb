#pragma once
#ifndef _Cad2d_IdentRings_Entity_Header
#define _Cad2d_IdentRings_Entity_Header

#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	namespace cad2dLib
	{

		class IdentRings_Entity
			: public Global_Indexed
			, public std::enable_shared_from_this<IdentRings_Entity>
		{

			/*Private Data*/

		protected:

			// default constructor [1/25/2022 Amir]

			IdentRings_Entity()
			{}

			// constructors [1/26/2022 Amir]

			explicit IdentRings_Entity(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

		public:

			virtual ~IdentRings_Entity()
			{}

			// public functions and operators [1/26/2022 Amir]

			auto This() const
			{
				return std::const_pointer_cast<IdentRings_Entity>(this->weak_from_this().lock());
			}
		};
	}
}

#endif // !_Cad2d_IdentRings_Entity_Header
