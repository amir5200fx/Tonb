#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Header
#define _SectPx_UnaryOpFieldFun_Header

#include <SectPx_nonParFieldFun.hxx>

namespace tnbLib
{

	class SectPx_UnaryOpFieldFun
		: public SectPx_nonParFieldFun
	{

		/*Private Data*/


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_nonParFieldFun>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFun(_Types&&... _Args)
			: SectPx_nonParFieldFun(_Args...)
		{}

	public:

		virtual Standard_Boolean HandleMemory() const = 0;
	};


	template<class T>
	class SectPx_UnaryOpFieldFun_Memory
	{};
	
	template<>
	class SectPx_UnaryOpFieldFun_Memory<std::shared_ptr<SectPx_FieldFun>>
		: public SectPx_UnaryOpFieldFun
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theField_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_UnaryOpFieldFun>(*this);
			ar & theField_;
		}

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_UnaryOpFieldFun(_Args...)
		{}

	public:

		Standard_Boolean HandleMemory() const override
		{
			return Standard_True;
		}

		const auto& FieldFun() const
		{
			return theField_;
		}

		void SetField
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theField_ = theField;
		}

		void SetField
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theField_ = std::move(theField);
		}
	};


	template<>
	class SectPx_UnaryOpFieldFun_Memory<std::weak_ptr<SectPx_FieldFun>>
		: public SectPx_UnaryOpFieldFun
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFun> theField_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_UnaryOpFieldFun>(*this);
			ar & theField_;
		}

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_UnaryOpFieldFun(_Args...)
		{}

	public:

		Standard_Boolean HandleMemory() const override
		{
			return Standard_False;
		}

		const auto& FieldFun() const
		{
			return theField_;
		}

		void SetField
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theField_ = theField;
		}
	};
}

#endif // !_SectPx_UnaryOpFieldFun_Header
