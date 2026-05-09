#pragma once
#ifndef _Cad_MergeParaCurves_NodeAdaptor_Header
#define _Cad_MergeParaCurves_NodeAdaptor_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/3/2022 Amir]
			class Link;

			class NodeAdaptor
			{

				/*Private Data*/

				std::map<Standard_Integer, std::shared_ptr<Link>> theLinks_;

			protected:

				// default constructor [6/3/2022 Amir]

				NodeAdaptor()
				{}

				// constructors [6/3/2022 Amir]


			public:

				const auto& Links() const
				{
					return theLinks_;
				}

				void Insert(const Standard_Integer theIndex, const std::shared_ptr<Link>&);
				void Remove(const Standard_Integer theIndex);
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_NodeAdaptor_Header
