#pragma once
#ifndef _Aft3d_SizeFun_Uniform_Header
#define _Aft3d_SizeFun_Uniform_Header
#include <Aft3d_SizeFun.hxx>

namespace tnbLib
{
	namespace legLib
	{
		class Aft3d_SizeFun_Uniform
			: public Aft3d_SizeFun
		{
			/*Private Data*/
			Standard_Real theValue_;
			//.
			// Private functions and operators
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_SizeFun>(*this);
				ar& theValue_;
			}
		protected:
			// default constructor
			Aft3d_SizeFun_Uniform() = default;
		public:
			//.
			// constructors
			Aft3d_SizeFun_Uniform(std::shared_ptr<Domain> theDomain, Standard_Real theValue);
			//
			// Public functions and operators
			Standard_Real Value(const Pnt3d&) const override;
		};
	}
}
BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_SizeFun_Uniform);
#endif