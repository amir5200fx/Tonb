#pragma once
#ifndef _Aft3d_SizeFun_Header
#define _Aft3d_SizeFun_Header
#include <Mesh_Module.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Global_Serialization.hxx>
#include <memory>

#include <Standard_TypeDef.hxx>
namespace tnbLib
{
	namespace legLib
	{
		class Aft3d_SizeFun
		{
		public:
			typedef Entity3d_Box Domain;
		private:
			/*Private Data*/
			std::shared_ptr<Domain> theDomain_;
			// Private functions and operators
			TNB_SERIALIZATION(TnbLegMesh_EXPORT);
		protected:
			// default constructor
			Aft3d_SizeFun() = default;
			// constructors
			Aft3d_SizeFun(std::shared_ptr<Domain> theDomain);
		public:
			//.
			// Public functions and operators
			const auto& GetDomain() const { return theDomain_; }
			//.
			// Virtual functions
			virtual Standard_Real Value(const Pnt3d&) const = 0;
		};
	}
}
BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_SizeFun);
#endif