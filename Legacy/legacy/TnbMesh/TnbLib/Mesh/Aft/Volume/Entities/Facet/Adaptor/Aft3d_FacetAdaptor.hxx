#pragma once
#ifndef _Aft3d_FacetAdaptor_Header
#define _Aft3d_FacetAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/24/2023 Payvand]
		class Aft3d_Element;

		class Aft3d_FacetAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Aft3d_Element> theUpper_;
			std::weak_ptr<Aft3d_Element> theLower_;


			// Private functions and operators [2/24/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/24/2023 Payvand]

			Aft3d_FacetAdaptor()
			{}


			// constructors [2/24/2023 Payvand]

		public:

			// Public functions and operators [2/24/2023 Payvand]

			const auto& UpperElement() const { return theUpper_; }
			const auto& LowerElement() const { return theLower_; }

			void SetUpperElement(const std::shared_ptr<Aft3d_Element>& theElement) { theUpper_ = theElement; }
			void SetLowerElement(const std::shared_ptr<Aft3d_Element>& theElement) { theLower_ = theElement; }

		};
	}
}

#endif // !_Aft3d_FacetAdaptor_Header
