#pragma once
#ifndef _HydStatic_Shape_Header
#define _HydStatic_Shape_Header

#include <HydStatic_Entity.hxx>
#include <Marine_ModelsFwd.hxx>

namespace tnbLib
{

	class HydStatic_Shape
		: public HydStatic_Entity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
		}


	protected:

		template<class... Types>
		HydStatic_Shape(Types&&... _Args)
			: HydStatic_Entity(_Args...)
		{}

	public:

		//- public functions and operators
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::HydStatic_Shape);

#endif // !_HydStatic_Shape_Header
