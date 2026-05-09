#pragma once
#ifndef _Pln_EdgeAdaptor_Header
#define _Pln_EdgeAdaptor_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	class Pln_EdgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<Pln_Wire> theWire_;


		/*private functions and operators*/

		auto& ChangeWire()
		{
			return theWire_;
		}

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:

		Pln_EdgeAdaptor()
		{}

	public:

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::weak_ptr<Pln_Wire>, Wire)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_EdgeAdaptor);

#endif // !_Pln_EdgeAdaptor_Header
