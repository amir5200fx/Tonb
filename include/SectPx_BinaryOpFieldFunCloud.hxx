#pragma once
#ifndef _SectPx_BinaryOpFieldFunCloud_Header
#define _SectPx_BinaryOpFieldFunCloud_Header

#include <SectPx_nonParFieldFunCloud.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFunCloud;

	class SectPx_BinaryOpFieldFunCloud
		: public SectPx_nonParFieldFunCloud
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFunCloud(_Types&&... _Args)
			: SectPx_nonParFieldFunCloud(_Args...)
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


	template<class T1, class T2>
	class SectPx_BinaryOpFieldFunCloud_Memory
	{};

	template<>
	class SectPx_BinaryOpFieldFunCloud_Memory
		<
		std::shared_ptr<SectPx_FieldFunCloud>,
		std::shared_ptr<SectPx_FieldFunCloud>
		>
		: public SectPx_BinaryOpFieldFunCloud
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFunCloud> theLeft_;
		std::shared_ptr<SectPx_FieldFunCloud> theRight_;

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFunCloud(_Args...)
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
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetLeft
		(
			std::shared_ptr<SectPx_FieldFunCloud>&& theField
		)
		{
			theLeft_ = std::move(theField);
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theRight_ = theField;
		}

		void SetRight
		(
			std::shared_ptr<SectPx_FieldFunCloud>&& theField
		)
		{
			theRight_ = std::move(theField);
		}

	};

	template<>
	class SectPx_BinaryOpFieldFunCloud_Memory
		<
		std::weak_ptr<SectPx_FieldFunCloud>,
		std::shared_ptr<SectPx_FieldFunCloud>
		>
		: public SectPx_BinaryOpFieldFunCloud
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFunCloud> theLeft_;
		std::shared_ptr<SectPx_FieldFunCloud> theRight_;

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFunCloud(_Args...)
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
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theRight_ = theField;
		}

		void SetRight
		(
			std::shared_ptr<SectPx_FieldFunCloud>&& theField
		)
		{
			theRight_ = std::move(theField);
		}

	};

	template<>
	class SectPx_BinaryOpFieldFunCloud_Memory
		<
		std::shared_ptr<SectPx_FieldFunCloud>,
		std::weak_ptr<SectPx_FieldFunCloud>
		>
		: public SectPx_BinaryOpFieldFunCloud
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFunCloud> theLeft_;
		std::weak_ptr<SectPx_FieldFunCloud> theRight_;

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFunCloud(_Args...)
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
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetLeft
		(
			std::shared_ptr<SectPx_FieldFunCloud>&& theField
		)
		{
			theLeft_ = std::move(theField);
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theRight_ = theField;
		}

	};

	template<>
	class SectPx_BinaryOpFieldFunCloud_Memory
		<
		std::weak_ptr<SectPx_FieldFunCloud>,
		std::weak_ptr<SectPx_FieldFunCloud>
		>
		: public SectPx_BinaryOpFieldFunCloud
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFunCloud> theLeft_;
		std::weak_ptr<SectPx_FieldFunCloud> theRight_;

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_BinaryOpFieldFunCloud(_Args...)
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
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theRight_ = theField;
		}

	};
}

#endif // !_SectPx_BinaryOpFieldFunCloud_Header
