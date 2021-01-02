#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Header
#define _SectPx_BinaryOpFieldFun_Header

#include <SectPx_nonParFieldFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	class SectPx_BinaryOpFieldFun
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
		SectPx_BinaryOpFieldFun(_Types&&... _Args)
			: SectPx_nonParFieldFun(_Args...)
		{}

	public:

		virtual Standard_Boolean HandleLeftMemory() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean HandleRightMemory() const
		{
			return Standard_False;
		}

	};

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(SectPx_BinaryOpFieldFun);


	template<class T1, class T2>
	class SectPx_BinaryOpFieldFun_Memory
	{};

	template<>
	class SectPx_BinaryOpFieldFun_Memory
		<
		std::shared_ptr<SectPx_FieldFun>, 
		std::shared_ptr<SectPx_FieldFun>
		>
		: public SectPx_BinaryOpFieldFun
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theLeft_;
		std::shared_ptr<SectPx_FieldFun> theRight_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_BinaryOpFieldFun>(*this);
			ar & theLeft_;
			ar & theRight_;
		}

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFun(_Args...)
		{}

	public:

		Standard_Boolean HandleLeftMemory() const override
		{
			return Standard_True;
		}

		Standard_Boolean HandleRightMemory() const override
		{
			return Standard_True;
		}

		const auto& Left() const
		{
			return theLeft_;
		}

		const auto& Right() const
		{
			return theRight_;
		}

		void SetLeft
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetLeft
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theLeft_ = std::move(theField);
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theRight_ = theField;
		}

		void SetRight
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theRight_ = std::move(theField);
		}

	};

	typedef SectPx_BinaryOpFieldFun_Memory
		<
		std::shared_ptr<SectPx_FieldFun>,
		std::shared_ptr<SectPx_FieldFun>
		> binOpFieldFun_Memory_SF_SF;

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(binOpFieldFun_Memory_SF_SF);

	template<>
	class SectPx_BinaryOpFieldFun_Memory
		<
		std::weak_ptr<SectPx_FieldFun>,
		std::shared_ptr<SectPx_FieldFun>
		>
		: public SectPx_BinaryOpFieldFun
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFun> theLeft_;
		std::shared_ptr<SectPx_FieldFun> theRight_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_BinaryOpFieldFun>(*this);
			ar & theLeft_;
			ar & theRight_;
		}

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFun(_Args...)
		{}

	public:

		Standard_Boolean HandleRightMemory() const override
		{
			return Standard_True;
		}

		const auto& Left() const
		{
			return theLeft_;
		}

		const auto& Right() const
		{
			return theRight_;
		}

		void SetLeft
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theRight_ = theField;
		}

		void SetRight
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theRight_ = std::move(theField);
		}

	};

	typedef SectPx_BinaryOpFieldFun_Memory
		<
		std::weak_ptr<SectPx_FieldFun>,
		std::shared_ptr<SectPx_FieldFun>
		> binOpFieldFun_Memory_WF_SF;

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(binOpFieldFun_Memory_WF_SF);

	template<>
	class SectPx_BinaryOpFieldFun_Memory
		<
		std::shared_ptr<SectPx_FieldFun>, 
		std::weak_ptr<SectPx_FieldFun>
		>
		: public SectPx_BinaryOpFieldFun
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theLeft_;
		std::weak_ptr<SectPx_FieldFun> theRight_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_BinaryOpFieldFun>(*this);
			ar & theLeft_;
			ar & theRight_;
		}

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFun(_Args...)
		{}

	public:

		Standard_Boolean HandleLeftMemory() const override
		{
			return Standard_True;
		}

		const auto& Left() const
		{
			return theLeft_;
		}

		const auto& Right() const
		{
			return theRight_;
		}

		void SetLeft
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetLeft
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theLeft_ = std::move(theField);
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theRight_ = theField;
		}

	};

	typedef SectPx_BinaryOpFieldFun_Memory
		<
		std::shared_ptr<SectPx_FieldFun>,
		std::weak_ptr<SectPx_FieldFun>
		> binOpFieldFun_Memory_SF_WF;

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(binOpFieldFun_Memory_SF_WF);

	template<>
	class SectPx_BinaryOpFieldFun_Memory
		<
		std::weak_ptr<SectPx_FieldFun>, 
		std::weak_ptr<SectPx_FieldFun>
		>
		: public SectPx_BinaryOpFieldFun
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFun> theLeft_;
		std::weak_ptr<SectPx_FieldFun> theRight_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_BinaryOpFieldFun>(*this);
			ar & theLeft_;
			ar & theRight_;
		}

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFun_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFun(_Args...)
		{}

	public:

		const auto& Left() const
		{
			return theLeft_;
		}

		const auto& Right() const
		{
			return theRight_;
		}

		void SetLeft
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theRight_ = theField;
		}

	};

	typedef SectPx_BinaryOpFieldFun_Memory
		<
		std::weak_ptr<SectPx_FieldFun>,
		std::weak_ptr<SectPx_FieldFun>
		> binOpFieldFun_Memory_WF_WF;

	BOOST_SERIALIZATION_ASSUME_ABSTRACT(binOpFieldFun_Memory_WF_WF);
}

#endif // !_SectPx_BinaryOpFieldFun_Header
