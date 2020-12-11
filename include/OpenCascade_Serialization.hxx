#pragma once
#ifndef _OpenCascade_Serialization_Header
#define _OpenCascade_Serialization_Header

#include <Standard_Handle.hxx>
#include <Global_Serialization.hxx>

// Forward Declarations
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void save(Archive & /*ar*/, const Handle(Geom2d_Curve)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Handle(Geom2d_Curve)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGlobal_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Handle(Geom2d_Curve)& c,
				const unsigned int version
				);

		template<>
		TnbGlobal_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				Handle(Geom2d_Curve)& c, 
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const Handle(Geom_Curve)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Handle(Geom_Curve)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGlobal_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Handle(Geom_Curve)& c, 
				const unsigned int version
				);

		template<>
		TnbGlobal_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar, 
				Handle(Geom_Curve)& c, 
				const unsigned int version
				);

		template<class Archive>
		void save(Archive & /*ar*/, const Handle(Geom_Surface)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & /*ar*/, Handle(Geom_Surface)&, const unsigned int /*version*/)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGlobal_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const Handle(Geom_Surface)& s,
				const unsigned int version
				);

		template<>
		TnbGlobal_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar, 
				Handle(Geom_Surface)& s, 
				const unsigned int version
				);
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(Handle(Geom2d_Curve))
BOOST_SERIALIZATION_SPLIT_FREE(Handle(Geom_Curve))
BOOST_SERIALIZATION_SPLIT_FREE(Handle(Geom_Surface))

#endif // !_OpenCascade_Serialization_Header
